#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QStyleFactory>
#include <QLineEdit>
#include <QProcess>
#include <QClipboard>
#include <QDateTime>
#include <QDate>
#include <QPushButton>
#include <QComboBox>

#include "MemoryStream.h"
#include "debug.h"

#include "workerdialog.h"

#define PROGRAM_NAME    "qrdbtool"
#define PROGRAM_VERSION 2.9f
#define PROGRAM_STATUS  " "
//#define PROGRAM_STATUS  " "

#define PREVIEW_TEXTURE_SIZE    350

enum
{
    COLUMN_NAME,
    COLUMN_HASH,
    COLUMN_SIZE,
    COLUMN_TYPE,
    COLUMN_VERSION
};

class MyTreeWidgetItem : public QTreeWidgetItem
{
public:
   MyTreeWidgetItem(QTreeWidget* parent=nullptr):QTreeWidgetItem(parent) { }

private:

    bool operator<(const QTreeWidgetItem &other) const
    {
        int column = treeWidget()->sortColumn();

        if (column == COLUMN_SIZE)
        {
            const QString str1 = text(column);
            const QString str2 = other.text(column);

            return (str1.left(str1.indexOf(' ')).toLongLong() <  str2.left(str2.indexOf(' ')).toLongLong());
        }
        else if (column == COLUMN_VERSION)
        {
            const QString str1 = text(column);
            const QString str2 = other.text(column);
            bool external1 = false, external2 = false;

            if (str1.startsWith("External ("))
                external1 = true;

            if (str2.startsWith("External ("))
                external2 = true;

            if (external1 && !external2)
                return false;
            else if (!external1 && external2)
                return true;
            else if (external1 && external2)
            {
                QString dt1_str = str1.mid(10);
                QString dt2_str = str2.mid(10);

                dt1_str.chop(1);
                dt2_str.chop(1);

                if (dt1_str == "NE")
                    return true;
                else if (dt2_str == "NE")
                    return false;

                QDate dt1 = QDate::fromString(dt1_str, "yyyy/MMM/dd");
                QDate dt2 = QDate::fromString(dt2_str, "yyyy/MMM/dd");

                return (dt1 < dt2);
            }
            else
            {
                int pos1 = str1.indexOf(" / ");
                int pos2 = str2.indexOf(" / ");

                if (pos1 >= 0 && pos2 >= 0)
                {
                    return (str1.mid(pos1) < str2.mid(pos2));
                }
            }
        }

        return QTreeWidgetItem::operator<(other);
    }
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetDarkTheme()
{
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(53,53,53));
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::Base, QColor(15,15,15));
    palette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    palette.setColor(QPalette::ToolTipBase, Qt::white);
    palette.setColor(QPalette::ToolTipText, Qt::white);
    palette.setColor(QPalette::Text, Qt::white);
    palette.setColor(QPalette::Button, QColor(53,53,53));
    palette.setColor(QPalette::ButtonText, Qt::white);
    palette.setColor(QPalette::BrightText, Qt::red);

    //palette.setColor(QPalette::Highlight, QColor(142,45,197).lighter());
    palette.setColor(QPalette::HighlightedText, Qt::black);
    palette.setColor(QPalette::Disabled, QPalette::Text, Qt::darkGray);
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, Qt::darkGray);
    qApp->setPalette(palette);
}

bool MainWindow::Initialize()
{
    /*qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(53,53,53));
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::Base, QColor(15,15,15));
    palette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    palette.setColor(QPalette::ToolTipBase, Qt::white);
    palette.setColor(QPalette::ToolTipText, Qt::white);
    palette.setColor(QPalette::Text, Qt::white);
    palette.setColor(QPalette::Button, QColor(53,53,53));
    palette.setColor(QPalette::ButtonText, Qt::white);
    palette.setColor(QPalette::BrightText, Qt::red);

    //palette.setColor(QPalette::Highlight, QColor(142,45,197).lighter());
    palette.setColor(QPalette::HighlightedText, Qt::black);
    palette.setColor(QPalette::Disabled, QPalette::Text, Qt::darkGray);
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, Qt::darkGray);
    qApp->setPalette(palette);*/

    ui->previewFrame->setVisible(false);
    ui->previewComboBox->setVisible(false);
    ui->previewComboBox->setFixedWidth(70);

    searchTimer.setSingleShot(true);
    connect(&searchTimer, SIGNAL(timeout()), this, SLOT(doSearch()));

    ui->mainToolBar->addSeparator();
    QLabel *searchLabel = new QLabel();
    searchLabel->setFixedWidth(60);
    searchLabel->setText("          Find:  ");
    ui->mainToolBar->addWidget(searchLabel);

    searchEdit = new QLineEdit();
    searchEdit->setFixedWidth(330);
    ui->mainToolBar->addWidget(searchEdit);

    connect(searchEdit, SIGNAL(textEdited(QString)), this, SLOT(onSearch()));

    rdb = nullptr;
    last_preview_width = 0;

    statusLabel = new QLabel(this);
    ui->statusBar->addPermanentWidget(statusLabel);

    QLabel *tipLabel = new QLabel(this);
    ui->statusBar->addPermanentWidget(tipLabel);

    tipLabel->setText("Tip: use Ctrl for multi-select, and shift to select a range.");

    ui->filesList->sortByColumn(COLUMN_NAME, Qt::AscendingOrder);
    ui->filesList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->filesList->setSortingEnabled(true);
    ui->filesList->setCurrentItem(nullptr);
    ui->filesList->header()->resizeSection(COLUMN_NAME, 560);
    //ui->filesList->header()->resizeSection(COLUMN_VERSION, 150);

    ui->filesList->addAction(ui->actionExtract_selection);
    ui->filesList->addAction(ui->actionExtract_all);
    ui->filesList->addAction(ui->actionCopy_name_to_clipboard);
    ui->filesList->addAction(ui->actionCopy_hash_to_clipboard);

    ui->actionExtract_selection->setDisabled(true);
    ui->actionExtract_all->setDisabled(true);
    ui->actionCopy_name_to_clipboard->setDisabled(true);
    ui->actionCopy_hash_to_clipboard->setDisabled(true);

    ui->actionFind_dead_files_1_01->setDisabled(true);
    ui->actionFind_dead_files_1_02->setDisabled(true);
    ui->actionFind_dead_files_1_03->setDisabled(true);
    ui->actionFind_dead_files_1_03b->setDisabled(true);
    ui->actionFind_dead_files_1_04->setDisabled(true);
    ui->actionFind_dead_files_1_04a->setDisabled(true);
    ui->actionFind_dead_files_1_05->setDisabled(true);
    ui->actionFind_dead_files_1_06->setDisabled(true);
    ui->actionFind_dead_files_1_08->setDisabled(true);
    ui->actionFind_dead_files_1_09->setDisabled(true);
    ui->actionFind_dead_files_1_10->setDisabled(true);
    ui->actionFind_dead_files_1_11->setDisabled(true);
    ui->actionFind_dead_files_1_12->setDisabled(true);
    ui->actionFind_dead_files_1_13->setDisabled(true);
    ui->actionFind_dead_files_1_14->setDisabled(true);
    ui->actionFind_dead_files_1_15->setDisabled(true);
    ui->actionFind_dead_files_1_16->setDisabled(true);
    ui->actionFind_dead_files_1_17->setDisabled(true);
    ui->actionFind_dead_files_1_18->setDisabled(true);
    ui->actionFind_dead_files_1_19->setDisabled(true);
    ui->actionFind_dead_files_1_20->setDisabled(true);
    ui->actionFind_dead_files_1_21->setDisabled(true);
    ui->actionFind_dead_files_1_22->setDisabled(true);

    ui->actionOpen->setIcon(this->style()->standardIcon(QStyle::SP_DirIcon));
    ui->actionExtract_selection->setIcon(this->style()->standardIcon(QStyle::SP_ArrowDown));
    ui->actionExtract_all->setIcon(this->style()->standardIcon(QStyle::SP_ArrowDown));

    ui->previewFrame->setAutoFillBackground(true);

    set_debug_level(2);
    QDir::setCurrent(qApp->applicationDirPath());
    LoadConfig();

    this->setWindowTitle(QString("%1 %2 %3").arg(PROGRAM_NAME).arg(PROGRAM_VERSION, 2).arg(PROGRAM_STATUS));

    if (qApp->arguments().size() >= 2)
    {
        QString file = qApp->arguments()[1];
        QString version;

        if (qApp->arguments().size() >= 3)
        {
            version = qApp->arguments()[2];
            SetDarkTheme();
        }

        LoadRdb(file, version);
    }

    return true;
}

void MainWindow::RdbEntryToGui(size_t idx, QTreeWidgetItem *item)
{
    static const std::unordered_map<std::string, QString> pkg_to_version =
    {
        { "bin", "1.01" },
        { "bin_0", "1.01" },
        { "bin2", "1.02" },
        { "bin2_0", "1.02" },
        { "bin3", "1.03" },
        { "bin3_0", "1.03" },
        { "bin4", "1.03b" },
        { "bin4_0", "1.03b" },
        { "bin6", "1.04" },
        { "bin6_0", "1.04" },
        { "bin7", "1.04a" },
        { "bin7_0", "1.04a" },
        { "bin8", "1.05" },
        { "bin8_0", "1.05" },
        { "bin9", "1.06" },
        { "bin9_0", "1.06" },
        { "bin11", "1.08" },
        { "bin11_0", "1.08" },
        { "bin12", "1.09" },
        { "bin12_0", "1.09" },
        { "bin13", "1.10" },
        { "bin13_0", "1.10" },
        { "bin14", "1.11" },
        { "bin14_0", "1.11" },
        { "bin15", "1.12" },
        { "bin15_0", "1.12" },
        { "bin16", "1.13" },
        { "bin16_0", "1.13" },
        { "bin17", "1.14" },
        { "bin17_0", "1.14" },
        { "bin18", "1.15" },
        { "bin18_0", "1.15" },
        { "bin19", "1.15" },
        { "bin19_0", "1.15" },
        { "bin20", "1.16" },
        { "bin20_0", "1.16" },
        { "bin21", "1.17" },
        { "bin21_0", "1.17" },
        { "bin22", "1.18" },
        { "bin22_0", "1.18" },
        { "bin23", "1.19" },
        { "bin23_0", "1.19" },
        { "bin24", "1.20" },
        { "bin24_0", "1.20" },
        { "bin25", "1.21 "},
        { "bin25_0", "1.21 "},
        { "bin27", "1.22 "},
        { "bin27_0", "1.22 "},
    };

    std::string name;
    char hash[16];
    const RdbEntry &entry = rdb->GetEntry(idx);
    rdb->GetFileName(idx, name);

    snprintf(hash, sizeof(hash), "0x%08x", entry.file_id);

    QString version = Utils::StdStringToQString(entry.bin_file).mid(1);
    auto it = pkg_to_version.find(Utils::QStringToStdString(version));
    if (it != pkg_to_version.end())
    {
        version += " / " + it->second;
    }

    if (version == "")
    {
        bool exists = false;

        version = "External";

        std::string ext_path = rdb->GetExternalPath(idx);

        if (ext_path.length() > 0)
        {
            QFileInfo info(Utils::StdStringToQString(ext_path));

            if (info.exists())
            {
                exists = true;

                QDate date = info.lastModified().date();
                version += " (";
                version += date.toString("yyyy/MMM/dd");
                version += ")";
            }
        }

        if (!exists)
            version += " (NE)";
    }

    item->setText(COLUMN_NAME, Utils::StdStringToQString(name, false));
    item->setText(COLUMN_HASH, QString(hash));
    item->setText(COLUMN_SIZE, QString("%1 bytes").arg(entry.file_size));
    item->setText(COLUMN_TYPE, Utils::StdStringToQString(name.substr(name.rfind('.')+1), false).toUpper());
    item->setText(COLUMN_VERSION, version);
}

bool MainWindow::LoadRdb(const QString &file, const QString &version)
{
    if (rdb)
        delete rdb;

    std::string std_file = Utils::QStringToStdString(file);
    rdb = new RdbFile(std_file);

    if (!rdb->LoadFromFile(std_file))
        return false;

    if (version == "1.01")
    {
        rdb->ReloadAsDeadFiles(".bin", ".bin_0");
    }
    else if (version == "1.02")
    {
        rdb->ReloadAsDeadFiles(".bin2", ".bin2_0");
    }
    else if (version == "1.03")
    {
        rdb->ReloadAsDeadFiles(".bin3", ".bin3_0");
    }
    else if (version == "1.03b")
    {
        rdb->ReloadAsDeadFiles(".bin4", ".bin4_0");
    }
    else if (version == "1.04")
    {
        rdb->ReloadAsDeadFiles(".bin6", ".bin6_0");
    }
    else if (version == "1.04a")
    {
        rdb->ReloadAsDeadFiles(".bin7", ".bin7_0");
    }
    else if (version == "1.05")
    {
        rdb->ReloadAsDeadFiles(".bin8", ".bin8_0");
    }
    else if (version == "1.06")
    {
        rdb->ReloadAsDeadFiles(".bin9", ".bin9_0");
    }
    else if (version == "1.08")
    {
        rdb->ReloadAsDeadFiles(".bin11", ".bin11_0");
    }
    else if (version == "1.09")
    {
        rdb->ReloadAsDeadFiles(".bin12", ".bin12_0");
    }
    else if (version == "1.10")
    {
        rdb->ReloadAsDeadFiles(".bin13", ".bin13_0");
    }
    else if (version == "1.11")
    {
        rdb->ReloadAsDeadFiles(".bin14", ".bin14_0");
    }
    else if (version == "1.12")
    {
        rdb->ReloadAsDeadFiles(".bin15", ".bin15_0");
    }
    else if (version == "1.13")
    {
        rdb->ReloadAsDeadFiles(".bin16", ".bin16_0");
    }
    else if (version == "1.14")
    {
        rdb->ReloadAsDeadFiles(".bin17", ".bin17_0");
    }
    else if (version == "1.15")
    {
        rdb->ReloadAsDeadFiles(".bin18", ".bin18_0", ".bin19", ".bin19_0");
    }
    else if (version == "1.16")
    {
        rdb->ReloadAsDeadFiles(".bin20", ".bin20_0");
    }
    else if (version == "1.17")
    {
        rdb->ReloadAsDeadFiles(".bin21", ".bin21_0");
    }
    else if (version == "1.18")
    {
        rdb->ReloadAsDeadFiles(".bin22", ".bin22_0");
    }
    else if (version == "1.19")
    {
        rdb->ReloadAsDeadFiles(".bin23", ".bin23_0");
    }
    else if (version == "1.20")
    {
        rdb->ReloadAsDeadFiles(".bin24", ".bin24_0");
    }
    else if (version == "1.21")
    {
        rdb->ReloadAsDeadFiles(".bin25", ".bin25_0");
    }
    else if (version == "1.22")
    {
        rdb->ReloadAsDeadFiles(".bin27", ".bin27_0");
    }

    if (version != "" && rdb->GetNumFiles() == 0)
    {
        DPRINTF("No dead files found for that version.\n");
        exit(-1);
    }

    last_rdb = std_file;

    rdb_name = Utils::GetFileNameString(std_file);
    size_t last_dot = rdb_name.rfind('.');
    if (last_dot != std::string::npos)
        rdb_name = rdb_name.substr(0, last_dot);

    ui->filesList->clear();

    for (size_t i = 0; i < rdb->GetNumFiles(); i++)
    {
        //QTreeWidgetItem *item = new QTreeWidgetItem();
        QTreeWidgetItem *item = new MyTreeWidgetItem();
        item->setData(0, Qt::UserRole, QVariant(i));

        RdbEntryToGui(i, item);
        ui->filesList->addTopLevelItem(item);
    }

    ui->actionExtract_selection->setEnabled(true);
    ui->actionExtract_all->setEnabled(true);
    ui->actionCopy_name_to_clipboard->setEnabled(true);
    ui->actionCopy_hash_to_clipboard->setEnabled(true);

    ui->actionFind_dead_files_1_01->setEnabled(true);
    ui->actionFind_dead_files_1_02->setEnabled(true);
    ui->actionFind_dead_files_1_03->setEnabled(true);
    ui->actionFind_dead_files_1_03b->setEnabled(true);
    ui->actionFind_dead_files_1_04->setEnabled(true);
    ui->actionFind_dead_files_1_04a->setEnabled(true);
    ui->actionFind_dead_files_1_05->setEnabled(true);
    ui->actionFind_dead_files_1_06->setEnabled(true);
    ui->actionFind_dead_files_1_08->setEnabled(true);
    ui->actionFind_dead_files_1_09->setEnabled(true);
    ui->actionFind_dead_files_1_10->setEnabled(true);
    ui->actionFind_dead_files_1_11->setEnabled(true);
    ui->actionFind_dead_files_1_12->setEnabled(true);
    ui->actionFind_dead_files_1_13->setEnabled(true);
    ui->actionFind_dead_files_1_14->setEnabled(true);
    ui->actionFind_dead_files_1_15->setEnabled(true);
    ui->actionFind_dead_files_1_16->setEnabled(true);
    ui->actionFind_dead_files_1_17->setEnabled(true);
    ui->actionFind_dead_files_1_18->setEnabled(true);
    ui->actionFind_dead_files_1_19->setEnabled(true);
    ui->actionFind_dead_files_1_20->setEnabled(true);
    ui->actionFind_dead_files_1_21->setEnabled(true);
    ui->actionFind_dead_files_1_22->setEnabled(true);

    if (version == "")
        statusLabel->setText(QString("%1 files").arg(rdb->GetNumFiles()));
    else
    {
        statusLabel->setText(QString("Dead files of version %1. %2 files").arg(version).arg(rdb->GetNumFiles()));
        this->setWindowTitle(QString("%1 %2  - Dead files of version %3").arg(PROGRAM_NAME).arg(PROGRAM_VERSION, 2).arg(version));
    }

    return true;
}

static bool get_hex_name(const std::string &fn, uint32_t *ret)
{
    if (!Utils::BeginsWith(fn, "0x", false))
        return false;

    if (fn.length() == 2)
        return false;

    for (size_t i = 2; i < fn.length(); i++)
    {
        char ch = (char)tolower(fn[i]);

        if (ch == '.')
            break;

        bool ok = false;

        if (ch >= '0' && ch <= '9')
            ok = true;
        else if (ch >= 'a' && ch <= 'f')
            ok = true;

        if (!ok)
            return false;
    }

    *ret = Utils::GetUnsigned(fn);
    return true;
}

size_t MainWindow::GetSelectedHashes(std::vector<uint32_t> &hashes)
{
    QList<QTreeWidgetItem *> selection = ui->filesList->selectedItems();

    hashes.clear();
    hashes.reserve(selection.size());

    for (QTreeWidgetItem *item : selection)
    {
        uint32_t hash;

        if (!get_hex_name(Utils::QStringToStdString(item->text(COLUMN_HASH)), &hash))
        {
            UPRINTF("Internal error\n");
            return 0;
        }

        hashes.push_back(hash);
    }

    return hashes.size();
}

void MainWindow::ExtractMultiple(const std::vector<uint32_t> *hashes)
{
    QString dir = QFileDialog::getExistingDirectory(this, "Select directory", Utils::StdStringToQString(last_dir));
    if (dir.isEmpty())
        return;

    std::string dir_std = Utils::QStringToStdString(dir);
    last_dir = dir_std;

    std::string dir_name;

    if (dir_std.back() == '/' || dir_std.back() == '\\')
    {
        dir_name = Utils::GetFileNameString(dir_std.substr(0, dir_std.length()-1));
    }
    else
    {
        dir_name = Utils::GetFileNameString(dir_std);
    }

    if (dir_name.length() != rdb_name.length() || !Utils::BeginsWith(dir_name, rdb_name, false))
    {
        QString message = QString("Do you want to store the files in a folder called %1 inside the selected folder?\n"
                                  "If you choose no, the files will be directly extracted in the folder you selected.\n").arg(Utils::StdStringToQString(rdb_name));

        if (QMessageBox::question(this, "Question", message, QMessageBox::StandardButtons(QMessageBox::Yes|QMessageBox::No), QMessageBox::Yes) == QMessageBox::Yes)
        {
            dir_std = Utils::MakePathString(dir_std, rdb_name);
            Utils::CreatePath(dir_std, true);
        }
    }

    WorkerDialog dialog(this);

    if (hashes)
        dialog.setExport(rdb, *hashes, dir_std);
    else
        dialog.setExportAll(rdb, dir_std);

    int ret = dialog.exec();

    if (ret > 0)
    {
        UPRINTF("Files extracted succesfully.\n");
    }
    else if (ret < 0)
    {
        DPRINTF("An error happened while extracting the files.\n");
    }
    else if (ret == 0)
    {
        // UPRINTF("Cancelled by user");
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, "Open RDB", Utils::StdStringToQString(Utils::GetDirNameString(last_rdb)), "RDB Files (*.rdb)");
    if (file.isEmpty())
        return;

    LoadRdb(file);
}

void MainWindow::on_actionAbout_triggered()
{
    UPRINTF("%s %0.1f %sby eternity", PROGRAM_NAME, PROGRAM_VERSION, PROGRAM_STATUS);

    //
    //rdb->ReloadAsDeadFiles(".bin6", ".bin6_0");

    //
    /*QString file = QFileDialog::getSaveFileName(this, "Save names txt", "", "Text Files (*.txt)");
    if (file.isEmpty())
        return;

    if (!rdb->SaveNamesToTxt(Utils::QStringToStdString(file)))
        DPRINTF("Fail!\n");

    UPRINTF("Ok.\n");*/
}

void MainWindow::on_actionExtract_selection_triggered()
{
    if (!rdb)
        return;

    std::vector<uint32_t> hashes;

    if (GetSelectedHashes(hashes) == 0)
    {
        UPRINTF("No items are selected!");
        return;
    }

    if (hashes.size() == 1)
    {
        std::string path;
        std::string ext;
        std::string filter;

        size_t idx = rdb->FindFileByID(hashes[0]);
        assert(idx == (size_t)-1);

        rdb->GetFileName(idx, path);
        ext = path.substr(path.rfind('.') + 1);
        filter = Utils::ToUpperCase(ext) + " Files (*." + ext + ")";
        path = Utils::MakePathString(last_dir, path);

        QString file = QFileDialog::getSaveFileName(this, "Save file", Utils::StdStringToQString(path), Utils::StdStringToQString(filter));
        if (file.isNull())
            return;

        last_dir = Utils::QStringToStdString(file);
        last_dir = last_dir.substr(0, last_dir.length()-Utils::GetFileNameString(last_dir).length());

        if (!rdb->ExtractFile(idx, Utils::QStringToStdString(file)))
        {
            DPRINTF("Extraction failed!\n");
            return;
        }
        else
        {
            UPRINTF("File extracted successfully!");
        }
    }
    else
    {
        ExtractMultiple(&hashes);
    }
}

void MainWindow::on_actionExtract_all_triggered()
{
    if (!rdb)
        return;

    ExtractMultiple(nullptr);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    SaveConfig();
    event->accept();
}

bool MainWindow::PreviewG1T(size_t g1t_idx, bool first)
{
    bool alpha;
    uint32_t *dec = nullptr;
    uint32_t w = 0, h = 0;

    if (preview_array.size() > 0)
    {
        if (g1t_idx >= preview_array.size())
            return false;

        w = preview_g1t[0].width;
        h = preview_g1t[0].height;
        dec = preview_g1t.Decode(preview_array[g1t_idx], preview_g1t.CalculateTextureSize(0, true), w, h, preview_g1t[0].format, &alpha, false);
    }
    else
    {
        if (g1t_idx >= preview_g1t.GetNumTextures())
            return false;

       dec = preview_g1t.Decode(g1t_idx, &alpha, false);
       w = preview_g1t[g1t_idx].width;
       h = preview_g1t[g1t_idx].height;
    }

    if (!dec)
        return false;

    ui->previewFrame->setVisible(true);

    QPalette p = QPalette();
    QImage img;    

    SetImage(img, dec, w, h, alpha);
    delete[] dec;

    if (w == h)
    {
        img = img.scaled(PREVIEW_TEXTURE_SIZE, PREVIEW_TEXTURE_SIZE);
    }
    else if (w > h)
    {
        float ratio = (float)h / (float)w;
        img = img.scaled(PREVIEW_TEXTURE_SIZE, (int)(PREVIEW_TEXTURE_SIZE*ratio), Qt::KeepAspectRatio);
    }
    else
    {
        float ratio = (float)w / (float)h;
        img = img.scaled((int)(PREVIEW_TEXTURE_SIZE*ratio), PREVIEW_TEXTURE_SIZE, Qt::KeepAspectRatio);
    }

    ui->previewFrame->setFixedSize(img.width(), img.height());

    if (first)
        last_preview_width = 0;

    if (!this->isMaximized() && first)
    {
        last_preview_width = img.width();
        this->resize(this->width() + img.width(), this->height());
    }

    p.setBrush(QPalette::Background, img);
    ui->previewFrame->setPalette(p);

    return true;
}

void MainWindow::PreviewFirstG1T(size_t rdb_idx)
{
    if (!rdb)
        return;

    MemoryStream out;

    if (!rdb->ExtractFile(rdb_idx, &out, true, false))
        return;

    if (!preview_g1t.Load(out.GetMemory(false), out.GetSize()))
        return;

    if (preview_g1t.GetNumTextures() == 0) // Would be a weird case...
        return;

    preview_array.clear();

    if (preview_g1t.GetNumTextures() == 1 && preview_g1t.IsArrayTexture(0))
    {
        if (!preview_g1t.DecomposeArrayTextureFast(0, preview_array, true))
            preview_array.clear();
    }

    if (PreviewG1T(0, true) && (preview_g1t.GetNumTextures() > 1 || preview_array.size() > 0))
    {
        ui->previewComboBox->clear();

        if (preview_array.size() > 0)
        {
            for (size_t i = 0; i < preview_array.size(); i++)
            {
                ui->previewComboBox->addItem(QString("Arr %1").arg(i));
            }
        }
        else
        {
            for (size_t i = 0; i < preview_g1t.GetNumTextures(); i++)
            {
                ui->previewComboBox->addItem(QString("Tex %1").arg(i));
            }
        }

        ui->previewComboBox->setCurrentIndex(0);
        ui->previewComboBox->setVisible(true);

        if (!this->isMaximized())
        {
            last_preview_width += ui->previewComboBox->width();
            this->resize(this->width() + ui->previewComboBox->width(), this->height());
        }
    }
}

void MainWindow::LoadConfig()
{
    if (!config.LoadFromFile("config.ini", false))
    {
        last_rdb.clear();
        last_dir.clear();
    }

    config.GetStringValue("General", "last_rdb", last_rdb);
    config.GetStringValue("General", "last_dir", last_dir);
}

void MainWindow::SaveConfig()
{
    config.SetStringValue("General", "last_rdb", last_rdb);
    config.SetStringValue("General", "last_dir", last_dir);

    config.SaveToFile("config.ini", false);
}

void MainWindow::on_actionExit_triggered()
{
    SaveConfig();
    qApp->exit();
}

static QString WildcardToRegExp(const QString &str)
{
    QString ret = str;

    int fwc = ret.indexOf('*');
    if (fwc != -1 && fwc != 0)
    {
        ret.prepend('*');
    }

    int lwc = ret.lastIndexOf('*');
    if (lwc != -1 && lwc != ret.length()-1)
    {
        ret += '*';
    }

    return ret.replace("*", ".*");
}

void MainWindow::doSearch()
{
    /*if (searchEdit->text().isEmpty())
        return;

    QString re = WildcardToRegExp(searchEdit->text());

    QList<QTreeWidgetItem *> items = ui->filesList->findItems(re, Qt::MatchRegExp, COLUMN_NAME);

    if (items.size() == 0)
        items = ui->filesList->findItems(searchEdit->text(), Qt::MatchContains, COLUMN_NAME);

    if (items.size() == 0)
        items = ui->filesList->findItems(re, Qt::MatchRegExp, COLUMN_HASH);

    if (items.size() == 0)
        items = ui->filesList->findItems(searchEdit->text(), Qt::MatchContains, COLUMN_HASH);

    if (items.size() >= 1)
    {
        ui->filesList->scrollToItem(items[0], QAbstractItemView::PositionAtCenter);
        items[0]->setSelected(true);
    }
    else
    {
        DPRINTF("Not found\n");
    }*/

    QString search = WildcardToRegExp(searchEdit->text()).trimmed();

    if ((search.length() > 0 && search.length() < 3) || !rdb)
        return;

    ui->filesList->clear();

    for (size_t i = 0; i < rdb->GetNumFiles(); i++)
    {
        QString name;
        std::string name_std;
        RdbEntry entry;
        bool found = false;

        if (search.length() == 0)
            found = true;

        QRegularExpression re = QRegularExpression(search, QRegularExpression::CaseInsensitiveOption);

        if (!found)
        {
            rdb->GetFileName(i, name_std);
            entry = rdb->GetEntry(i);

            name = Utils::StdStringToQString(name_std, false);

            if (name.indexOf(re) >= 0)
            {
                found = true;
            }
            else
            {   if (name.indexOf(search, 0, Qt::CaseInsensitive) >= 0)
                {
                    found = true;
                }
            }
        }

        if (!found)
        {
            QString hash = Utils::StdStringToQString(Utils::UnsignedToHexString(entry.file_id, true));

            if (hash.indexOf(re) >= 0)
            {
                found = true;
            }
            else
            {   if (hash.indexOf(search, 0, Qt::CaseInsensitive) >= 0)
                {
                    found = true;
                }
            }
        }

        if (found)
        {
            QTreeWidgetItem *item = new MyTreeWidgetItem();
            item->setData(0, Qt::UserRole, QVariant(i));

            RdbEntryToGui(i, item);
            ui->filesList->addTopLevelItem(item);
        }
    }
}

void MainWindow::onSearch()
{
    searchTimer.start(100);
}

bool MainWindow::SetImage(QImage &image, const uint32_t *raw, uint32_t width, uint32_t height, bool alpha)
{
    if (alpha)
        image = QImage(width, height, QImage::Format_ARGB32);
    else
        image = QImage(width, height, QImage::Format_RGB32);

    image.fill(QColor(255, 0, 255));

    for(uint32_t y = 0; y < height; y++)
    {
        uint8_t *lineOut = image.scanLine(y);
        const uint8_t *lineIn = (const uint8_t *)(raw + (y*width));

        for(uint32_t x = 0; x < width; x++)
        {
            lineOut[0] = lineIn[0];
            lineOut[1] = lineIn[1];
            lineOut[2] = lineIn[2];

            if (alpha)
                lineOut[3] = lineIn[3];
            else
                lineOut[3] = 0xFF;

            lineOut += 4;
            lineIn += 4;
        }
    }

    return true;
}

void MainWindow::deadFilesTrigger(const QString &version)
{
    if (!rdb)
        return;

    QStringList args;
    args.push_back(Utils::StdStringToQString(last_rdb));
    args.push_back(version);

    QProcess::startDetached(qApp->applicationFilePath(), args);
}

void MainWindow::on_actionFind_dead_files_1_01_triggered()
{
    deadFilesTrigger("1.01");
}

void MainWindow::on_actionFind_dead_files_1_02_triggered()
{
    deadFilesTrigger("1.02");
}

void MainWindow::on_actionFind_dead_files_1_03_triggered()
{
    deadFilesTrigger("1.03");
}

void MainWindow::on_actionFind_dead_files_1_03b_triggered()
{
    deadFilesTrigger("1.03b");
}

void MainWindow::on_actionFind_dead_files_1_04_triggered()
{
   deadFilesTrigger("1.04");
}

void MainWindow::on_actionFind_dead_files_1_04a_triggered()
{
    deadFilesTrigger("1.04a");
}

void MainWindow::on_actionFind_dead_files_1_05_triggered()
{
    deadFilesTrigger("1.05");
}

void MainWindow::on_actionFind_dead_files_1_06_triggered()
{
    deadFilesTrigger("1.06");
}

void MainWindow::on_actionFind_dead_files_1_08_triggered()
{
   deadFilesTrigger("1.08");
}

void MainWindow::on_actionFind_dead_files_1_09_triggered()
{
    deadFilesTrigger("1.09");
}

void MainWindow::on_actionFind_dead_files_1_10_triggered()
{
    deadFilesTrigger("1.10");
}

void MainWindow::on_actionFind_dead_files_1_11_triggered()
{
    deadFilesTrigger("1.11");
}

void MainWindow::on_actionFind_dead_files_1_12_triggered()
{
    deadFilesTrigger("1.12");
}

void MainWindow::on_actionFind_dead_files_1_13_triggered()
{
    deadFilesTrigger("1.13");
}

void MainWindow::on_actionFind_dead_files_1_14_triggered()
{
    deadFilesTrigger("1.14");
}

void MainWindow::on_actionFind_dead_files_1_15_triggered()
{
    deadFilesTrigger("1.15");
}

void MainWindow::on_actionFind_dead_files_1_16_triggered()
{
    deadFilesTrigger("1.16");
}

void MainWindow::on_actionCopy_name_to_clipboard_triggered()
{
    QList<QTreeWidgetItem *> selection = ui->filesList->selectedItems();
    QString content;

    for (int i = 0;  i < selection.size(); i++)
    {
        content += selection[i]->text(0);

        if (i != (selection.size()-1))
        {
            content += '\n';
        }
    }

    if (content.length() > 0)
    {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(content);
    }
}

void MainWindow::on_actionCopy_hash_to_clipboard_triggered()
{
    QList<QTreeWidgetItem *> selection = ui->filesList->selectedItems();
    QString content;

    for (int i = 0;  i < selection.size(); i++)
    {
        content += selection[i]->text(1);

        if (i != (selection.size()-1))
        {
            content += '\n';
        }
    }

    if (content.length() > 0)
    {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(content);
    }
}

void MainWindow::on_actionFind_dead_files_1_17_triggered()
{
    deadFilesTrigger("1.17");
}

void MainWindow::on_actionFind_dead_files_1_18_triggered()
{
    deadFilesTrigger("1.18");
}

void MainWindow::on_actionFind_dead_files_1_19_triggered()
{
    deadFilesTrigger("1.19");
}

void MainWindow::on_actionFind_dead_files_1_20_triggered()
{
    deadFilesTrigger("1.20");
}

void MainWindow::on_actionFind_dead_files_1_21_triggered()
{
    deadFilesTrigger("1.21");
}

void MainWindow::on_actionFind_dead_files_1_22_triggered()
{
    deadFilesTrigger("1.22");
}

void MainWindow::on_filesList_itemSelectionChanged()
{
    bool was_visible = ui->previewFrame->isVisible();

    ui->previewFrame->setVisible(false);
    ui->previewComboBox->setVisible(false);

    if (was_visible && !isMaximized() && last_preview_width != 0)
    {
        this->resize(this->width() - last_preview_width, this->height());
    }

    if (!rdb)
        return;

    std::vector<uint32_t> hashes;

    if (GetSelectedHashes(hashes) != 1)
        return;

    size_t idx = rdb->FindFileByID(hashes.front());
    if (idx == (size_t)-1)
        return;

    if (rdb->MatchesType(idx, 0xafbec60c))
    {
        PreviewFirstG1T(idx);
    }
}

void MainWindow::on_previewComboBox_currentIndexChanged(int index)
{
    if (!ui->previewComboBox->isVisible())
        return;

    PreviewG1T(index, false);
}
