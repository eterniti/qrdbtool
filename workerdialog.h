#ifndef WORKERDIALOG_H
#define WORKERDIALOG_H

#include <QDialog>
#include <QThreadPool>
#include <QMutexLocker>
#include "mainwindow.h"

namespace Ui {
class WorkerDialog;
}

class ExportWork : public QObject, public QRunnable
{
    Q_OBJECT

public:

    ExportWork(MainWindow *window, size_t idx, const std::string &file, int *priority) : QRunnable(), window(window), idx(idx), file(file), current_priority(priority){ }

    void run();

public slots:

    void onCancel();

signals:

    void workFinished();
    void errorSignal();

private:

    MainWindow *window;
    size_t idx;
    std::string file;

    bool cancel = false;
    int *current_priority;
};

class WorkerDialog : public QDialog
{
    Q_OBJECT

public slots:
    void onWorkFinished();
    void reject() override;
    void onError();
    void onSetWorkSize(int size);

public:
    explicit WorkerDialog(QWidget *parent = nullptr);
    ~WorkerDialog();

    int exec() override;

    void setExport(RdbFile *rdb, const std::vector<uint32_t> &hashes, const std::string &dir);
    void setExportAll(RdbFile *rdb, const std::string &dir);

signals:

    void cancelSignal();

private slots:
    void on_cancelButton_clicked();

    void on_priorityComboBox_activated(int index);

private:
    Ui::WorkerDialog *ui;

    MainWindow *window;
    RdbFile *rdb;
    std::vector<size_t> files_idx;
    std::string out_dir;

    QMutex mutex;
    int jobs_finished = 0;
    int max_jobs;
    int priority=0;

    void DoExport();
};

#endif // WORKERDIALOG_H
