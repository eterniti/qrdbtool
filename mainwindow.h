#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTreeWidget>
#include <QLineEdit>
#include <QTimer>

#include "DOA6/RdbFile.h"
#include "DOA6/G1tFile.h"
#include "IniFile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool Initialize();

    RdbFile *rdb;

public slots:

    void onSearch();
    void doSearch();

private slots:
    void on_actionOpen_triggered();

    void on_actionAbout_triggered();

    void on_actionExtract_selection_triggered();

    void on_actionExtract_all_triggered();

    void on_actionExit_triggered();

    void deadFilesTrigger(const QString &version);

    void on_actionFind_dead_files_1_01_triggered();

    void on_actionFind_dead_files_1_02_triggered();

    void on_actionFind_dead_files_1_03_triggered();

    void on_actionFind_dead_files_1_03b_triggered();

    void on_actionFind_dead_files_1_04_triggered();

    void on_actionFind_dead_files_1_04a_triggered();

    void on_actionFind_dead_files_1_05_triggered();

    void on_actionFind_dead_files_1_06_triggered();

    void on_actionFind_dead_files_1_08_triggered();

    void on_actionFind_dead_files_1_09_triggered();

    void on_actionFind_dead_files_1_10_triggered();

    void on_actionFind_dead_files_1_11_triggered();

    void on_actionFind_dead_files_1_12_triggered();

    void on_actionFind_dead_files_1_13_triggered();

    void on_actionFind_dead_files_1_14_triggered();

    void on_actionFind_dead_files_1_15_triggered();

    void on_actionFind_dead_files_1_16_triggered();

    void on_actionCopy_name_to_clipboard_triggered();

    void on_actionCopy_hash_to_clipboard_triggered();

    void on_actionFind_dead_files_1_17_triggered();

    void on_actionFind_dead_files_1_18_triggered();

    void on_actionFind_dead_files_1_19_triggered();

    void on_actionFind_dead_files_1_20_triggered();

    void on_actionFind_dead_files_1_21_triggered();

    void on_actionFind_dead_files_1_22_triggered();

    void on_filesList_itemSelectionChanged();

    void on_previewComboBox_currentIndexChanged(int index);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

    QLineEdit *searchEdit;
    QLabel *statusLabel;
    std::string rdb_name;
    IniFile config;

    std::string last_rdb;
    std::string last_dir;

    G1tFile preview_g1t;
    std::vector<uint8_t *> preview_array; // Only for g1t that have array
    uint32_t last_preview_width;

    QTimer searchTimer;

    bool PreviewG1T(size_t g1t_idx, bool first);
    void PreviewFirstG1T(size_t rdb_idx);

    void LoadConfig();
    void SaveConfig();

    void RdbEntryToGui(size_t idx, QTreeWidgetItem *item);
    bool LoadRdb(const QString &file, const QString &version="");

    size_t GetSelectedHashes(std::vector<uint32_t> &hashes);
    void ExtractMultiple(const std::vector<uint32_t> *hashes);

    void SetDarkTheme();

    static bool SetImage(QImage &image, const uint32_t *raw, uint32_t width, uint32_t height, bool alpha);


};

#endif // MAINWINDOW_H
