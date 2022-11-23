#include "workerdialog.h"
#include "ui_workerdialog.h"

#include "debug.h"

WorkerDialog::WorkerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorkerDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    window = dynamic_cast<MainWindow *>(parent);
}

WorkerDialog::~WorkerDialog()
{
    delete ui;
}

int WorkerDialog::exec()
{
    DoExport();
    return QDialog::exec();
}

void WorkerDialog::setExport(RdbFile *rdb, const std::vector<uint32_t> &hashes, const std::string &dir)
{
    this->rdb = rdb;
    this->max_jobs = (int)hashes.size();
    files_idx.clear();
    files_idx.resize(hashes.size());

    for (size_t i = 0; i < hashes.size(); i++)
    {
        files_idx[i] = rdb->FindFileByID(hashes[i]);
    }

    out_dir = dir;

    ui->label->setText("Extracting files...");
    setWindowTitle("Extracting files...");
    ui->progressBar->setMaximum((int)files_idx.size());
}

void WorkerDialog::setExportAll(RdbFile *rdb, const std::string &dir)
{
    this->rdb = rdb;
    this->max_jobs = (int)rdb->GetNumFiles();
    files_idx.clear();
    files_idx.resize(rdb->GetNumFiles());

    for (size_t i = 0; i < files_idx.size(); i++)
        files_idx[i] = i;

    out_dir = dir;

    ui->label->setText("Extracting files...");
    setWindowTitle("Extracting files...");
    ui->progressBar->setMaximum((int)files_idx.size());
}

void WorkerDialog::DoExport()
{
    QThreadPool *pool = QThreadPool::globalInstance();
    QVector<ExportWork *> works;

    works.resize((int)files_idx.size());

    priority = ui->priorityComboBox->currentIndex();

    for (int i = 0; i < (int)files_idx.size(); i++)
    {
        std::string file;

        rdb->GetFileName(files_idx[i], file);
        file = Utils::MakePathString(out_dir, file);

        works[i] = new ExportWork(window, files_idx[i], file, &priority);
        connect(works[i], SIGNAL(workFinished()), this, SLOT(onWorkFinished()));
        connect(this, SIGNAL(cancelSignal()), works[i], SLOT(onCancel()));
        connect(works[i], SIGNAL(errorSignal()), this, SLOT(onError()));
    }

    jobs_finished = 0;

    /*pool->setMaxThreadCount(QThread::idealThreadCount());

    if (pool->maxThreadCount() > 16)
        pool->setMaxThreadCount(16);*/

    pool->setMaxThreadCount(1); // Currently RdbFile::ExtractFile is not multithread safe.

    //pool->setMaxThreadCount(1); // For slower testing

    for (int i = 0; i < works.size(); i++)
    {
        pool->start(works[i]);
    }
}

void WorkerDialog::onWorkFinished()
{
    QMutexLocker locker(&mutex);

    jobs_finished++;
    ui->progressBar->setValue(jobs_finished);

    if (jobs_finished == max_jobs)
    {
        QThreadPool::globalInstance()->waitForDone();
        done(1);
    }
}

void WorkerDialog::reject()
{
    QMutexLocker locker(&mutex);

    if (jobs_finished != max_jobs)
    {
        ui->label->setText("Cancelling...");

        QThreadPool::globalInstance()->clear();
        emit cancelSignal();

        QThreadPool::globalInstance()->waitForDone();
        done(0);
    }
}

void WorkerDialog::onError()
{
    QMutexLocker locker(&mutex);

    ui->label->setText("There was an error. Cancelling all jobs...");

    QThreadPool::globalInstance()->clear();
    emit cancelSignal();

    QThreadPool::globalInstance()->waitForDone();
    done(-1);
}

void WorkerDialog::onSetWorkSize(int size)
{
    max_jobs = size;
    ui->progressBar->setMaximum(size);
}

void WorkerDialog::on_cancelButton_clicked()
{
    reject();
}

void WorkerDialog::on_priorityComboBox_activated(int index)
{
    priority = index;
}

void ExportWork::run()
{
    if (*current_priority == 1)
    {
        SetThreadPriority(GetCurrentThread(), THREAD_MODE_BACKGROUND_BEGIN);
    }
    else
    {
        SetThreadPriority(GetCurrentThread(), THREAD_MODE_BACKGROUND_END);
    }

    if (cancel)
        return;

    bool success = window->rdb->ExtractFile(idx, file, true, true);
    if (!success && !cancel)
    {
        emit errorSignal();
        return;
    }


    if (cancel)
        return;

    emit workFinished();
}

void ExportWork::onCancel()
{
    cancel = true;
}
