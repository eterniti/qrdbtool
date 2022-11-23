/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionAbout;
    QAction *actionExtract_selection;
    QAction *actionExtract_all;
    QAction *actionFind_dead_files_1_01;
    QAction *actionFind_dead_files_1_02;
    QAction *actionFind_dead_files_1_03;
    QAction *actionFind_dead_files_1_03b;
    QAction *actionFind_dead_files_1_04;
    QAction *actionFind_dead_files_1_04a;
    QAction *actionFind_dead_files_1_05;
    QAction *actionFind_dead_files_1_06;
    QAction *actionFind_dead_files_1_08;
    QAction *actionFind_dead_files_1_09;
    QAction *actionFind_dead_files_1_10;
    QAction *actionFind_dead_files_1_11;
    QAction *actionFind_dead_files_1_12;
    QAction *actionFind_dead_files_1_13;
    QAction *actionFind_dead_files_1_14;
    QAction *actionFind_dead_files_1_15;
    QAction *actionFind_dead_files_1_16;
    QAction *actionCopy_name_to_clipboard;
    QAction *actionCopy_hash_to_clipboard;
    QAction *actionFind_dead_files_1_17;
    QAction *actionFind_dead_files_1_18;
    QAction *actionFind_dead_files_1_19;
    QAction *actionFind_dead_files_1_20;
    QAction *actionFind_dead_files_1_21;
    QAction *actionFind_dead_files_1_22;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QTreeWidget *filesList;
    QFrame *previewFrame;
    QComboBox *previewComboBox;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuAbout;
    QMenu *menuTools;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1030, 560);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionExtract_selection = new QAction(MainWindow);
        actionExtract_selection->setObjectName(QString::fromUtf8("actionExtract_selection"));
        actionExtract_all = new QAction(MainWindow);
        actionExtract_all->setObjectName(QString::fromUtf8("actionExtract_all"));
        actionFind_dead_files_1_01 = new QAction(MainWindow);
        actionFind_dead_files_1_01->setObjectName(QString::fromUtf8("actionFind_dead_files_1_01"));
        actionFind_dead_files_1_02 = new QAction(MainWindow);
        actionFind_dead_files_1_02->setObjectName(QString::fromUtf8("actionFind_dead_files_1_02"));
        actionFind_dead_files_1_03 = new QAction(MainWindow);
        actionFind_dead_files_1_03->setObjectName(QString::fromUtf8("actionFind_dead_files_1_03"));
        actionFind_dead_files_1_03b = new QAction(MainWindow);
        actionFind_dead_files_1_03b->setObjectName(QString::fromUtf8("actionFind_dead_files_1_03b"));
        actionFind_dead_files_1_04 = new QAction(MainWindow);
        actionFind_dead_files_1_04->setObjectName(QString::fromUtf8("actionFind_dead_files_1_04"));
        actionFind_dead_files_1_04a = new QAction(MainWindow);
        actionFind_dead_files_1_04a->setObjectName(QString::fromUtf8("actionFind_dead_files_1_04a"));
        actionFind_dead_files_1_05 = new QAction(MainWindow);
        actionFind_dead_files_1_05->setObjectName(QString::fromUtf8("actionFind_dead_files_1_05"));
        actionFind_dead_files_1_06 = new QAction(MainWindow);
        actionFind_dead_files_1_06->setObjectName(QString::fromUtf8("actionFind_dead_files_1_06"));
        actionFind_dead_files_1_08 = new QAction(MainWindow);
        actionFind_dead_files_1_08->setObjectName(QString::fromUtf8("actionFind_dead_files_1_08"));
        actionFind_dead_files_1_09 = new QAction(MainWindow);
        actionFind_dead_files_1_09->setObjectName(QString::fromUtf8("actionFind_dead_files_1_09"));
        actionFind_dead_files_1_10 = new QAction(MainWindow);
        actionFind_dead_files_1_10->setObjectName(QString::fromUtf8("actionFind_dead_files_1_10"));
        actionFind_dead_files_1_11 = new QAction(MainWindow);
        actionFind_dead_files_1_11->setObjectName(QString::fromUtf8("actionFind_dead_files_1_11"));
        actionFind_dead_files_1_12 = new QAction(MainWindow);
        actionFind_dead_files_1_12->setObjectName(QString::fromUtf8("actionFind_dead_files_1_12"));
        actionFind_dead_files_1_13 = new QAction(MainWindow);
        actionFind_dead_files_1_13->setObjectName(QString::fromUtf8("actionFind_dead_files_1_13"));
        actionFind_dead_files_1_14 = new QAction(MainWindow);
        actionFind_dead_files_1_14->setObjectName(QString::fromUtf8("actionFind_dead_files_1_14"));
        actionFind_dead_files_1_15 = new QAction(MainWindow);
        actionFind_dead_files_1_15->setObjectName(QString::fromUtf8("actionFind_dead_files_1_15"));
        actionFind_dead_files_1_16 = new QAction(MainWindow);
        actionFind_dead_files_1_16->setObjectName(QString::fromUtf8("actionFind_dead_files_1_16"));
        actionCopy_name_to_clipboard = new QAction(MainWindow);
        actionCopy_name_to_clipboard->setObjectName(QString::fromUtf8("actionCopy_name_to_clipboard"));
        actionCopy_hash_to_clipboard = new QAction(MainWindow);
        actionCopy_hash_to_clipboard->setObjectName(QString::fromUtf8("actionCopy_hash_to_clipboard"));
        actionFind_dead_files_1_17 = new QAction(MainWindow);
        actionFind_dead_files_1_17->setObjectName(QString::fromUtf8("actionFind_dead_files_1_17"));
        actionFind_dead_files_1_18 = new QAction(MainWindow);
        actionFind_dead_files_1_18->setObjectName(QString::fromUtf8("actionFind_dead_files_1_18"));
        actionFind_dead_files_1_19 = new QAction(MainWindow);
        actionFind_dead_files_1_19->setObjectName(QString::fromUtf8("actionFind_dead_files_1_19"));
        actionFind_dead_files_1_20 = new QAction(MainWindow);
        actionFind_dead_files_1_20->setObjectName(QString::fromUtf8("actionFind_dead_files_1_20"));
        actionFind_dead_files_1_21 = new QAction(MainWindow);
        actionFind_dead_files_1_21->setObjectName(QString::fromUtf8("actionFind_dead_files_1_21"));
        actionFind_dead_files_1_22 = new QAction(MainWindow);
        actionFind_dead_files_1_22->setObjectName(QString::fromUtf8("actionFind_dead_files_1_22"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(3, 0, 3, 0);
        filesList = new QTreeWidget(centralWidget);
        filesList->setObjectName(QString::fromUtf8("filesList"));
        filesList->setContextMenuPolicy(Qt::ActionsContextMenu);
        filesList->setRootIsDecorated(false);

        horizontalLayout_2->addWidget(filesList);

        previewFrame = new QFrame(centralWidget);
        previewFrame->setObjectName(QString::fromUtf8("previewFrame"));
        previewFrame->setAutoFillBackground(true);
        previewFrame->setFrameShape(QFrame::StyledPanel);
        previewFrame->setFrameShadow(QFrame::Raised);

        horizontalLayout_2->addWidget(previewFrame);

        previewComboBox = new QComboBox(centralWidget);
        previewComboBox->setObjectName(QString::fromUtf8("previewComboBox"));

        horizontalLayout_2->addWidget(previewComboBox);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1030, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionExtract_selection);
        menuFile->addAction(actionExtract_all);
        menuFile->addAction(actionExit);
        menuAbout->addAction(actionAbout);
        menuTools->addAction(actionFind_dead_files_1_01);
        menuTools->addAction(actionFind_dead_files_1_02);
        menuTools->addAction(actionFind_dead_files_1_03);
        menuTools->addAction(actionFind_dead_files_1_03b);
        menuTools->addAction(actionFind_dead_files_1_04);
        menuTools->addAction(actionFind_dead_files_1_04a);
        menuTools->addAction(actionFind_dead_files_1_05);
        menuTools->addAction(actionFind_dead_files_1_06);
        menuTools->addAction(actionFind_dead_files_1_08);
        menuTools->addAction(actionFind_dead_files_1_09);
        menuTools->addAction(actionFind_dead_files_1_10);
        menuTools->addAction(actionFind_dead_files_1_11);
        menuTools->addAction(actionFind_dead_files_1_12);
        menuTools->addAction(actionFind_dead_files_1_13);
        menuTools->addAction(actionFind_dead_files_1_14);
        menuTools->addAction(actionFind_dead_files_1_15);
        menuTools->addAction(actionFind_dead_files_1_16);
        menuTools->addAction(actionFind_dead_files_1_17);
        menuTools->addAction(actionFind_dead_files_1_18);
        menuTools->addAction(actionFind_dead_files_1_19);
        menuTools->addAction(actionFind_dead_files_1_20);
        menuTools->addAction(actionFind_dead_files_1_21);
        menuTools->addAction(actionFind_dead_files_1_22);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionExtract_selection);
        mainToolBar->addAction(actionExtract_all);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "qrdbtool", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionExtract_selection->setText(QCoreApplication::translate("MainWindow", "Extract selection", nullptr));
        actionExtract_all->setText(QCoreApplication::translate("MainWindow", "Extract all", nullptr));
        actionFind_dead_files_1_01->setText(QCoreApplication::translate("MainWindow", "Find dead files (1.01)", nullptr));
        actionFind_dead_files_1_02->setText(QCoreApplication::translate("MainWindow", "Find dead files (1.02)", nullptr));
        actionFind_dead_files_1_03->setText(QCoreApplication::translate("MainWindow", "Find dead files (1.03)", nullptr));
        actionFind_dead_files_1_03b->setText(QCoreApplication::translate("MainWindow", "Find dead files (1.03b)", nullptr));
        actionFind_dead_files_1_04->setText(QCoreApplication::translate("MainWindow", "Find dead files (1.04)", nullptr));
        actionFind_dead_files_1_04a->setText(QCoreApplication::translate("MainWindow", "Find dead files (1.04a)", nullptr));
        actionFind_dead_files_1_05->setText(QCoreApplication::translate("MainWindow", "Find dead files (1.05)", nullptr));
        actionFind_dead_files_1_06->setText(QCoreApplication::translate("MainWindow", "Find dead files (1.06)", nullptr));
        actionFind_dead_files_1_08->setText(QCoreApplication::translate("MainWindow", "Find dead files (1.08)", nullptr));
        actionFind_dead_files_1_09->setText(QCoreApplication::translate("MainWindow", "Find dead files (1.09)", nullptr));
        actionFind_dead_files_1_10->setText(QCoreApplication::translate("MainWindow", "Find dead files (1.10)", nullptr));
        actionFind_dead_files_1_11->setText(QCoreApplication::translate("MainWindow", "Find dead files (1.11)", nullptr));
        actionFind_dead_files_1_12->setText(QCoreApplication::translate("MainWindow", "Find dead files (1.12)", nullptr));
        actionFind_dead_files_1_13->setText(QCoreApplication::translate("MainWindow", "Find dead files (1.13)", nullptr));
        actionFind_dead_files_1_14->setText(QCoreApplication::translate("MainWindow", "Find dead files (1.14)", nullptr));
        actionFind_dead_files_1_15->setText(QCoreApplication::translate("MainWindow", "Find dead files (1.15)", nullptr));
        actionFind_dead_files_1_16->setText(QCoreApplication::translate("MainWindow", "Find dead files (1.16)", nullptr));
        actionCopy_name_to_clipboard->setText(QCoreApplication::translate("MainWindow", "Copy name to clipboard", nullptr));
        actionCopy_hash_to_clipboard->setText(QCoreApplication::translate("MainWindow", "Copy hash to clipboard", nullptr));
        actionFind_dead_files_1_17->setText(QCoreApplication::translate("MainWindow", "Find dead files (1.17)", nullptr));
        actionFind_dead_files_1_18->setText(QCoreApplication::translate("MainWindow", "Find dead files (1.18)", nullptr));
        actionFind_dead_files_1_19->setText(QCoreApplication::translate("MainWindow", "Find dead files (1.19)", nullptr));
        actionFind_dead_files_1_20->setText(QCoreApplication::translate("MainWindow", "Find dead files (1.20)", nullptr));
        actionFind_dead_files_1_21->setText(QCoreApplication::translate("MainWindow", "Find dead files (1.21)", nullptr));
        actionFind_dead_files_1_22->setText(QCoreApplication::translate("MainWindow", "Find dead files (1.22)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = filesList->headerItem();
        ___qtreewidgetitem->setText(4, QCoreApplication::translate("MainWindow", "Container / Version", nullptr));
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("MainWindow", "Type", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("MainWindow", "Size", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("MainWindow", "Hash", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "Name", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
        menuTools->setTitle(QCoreApplication::translate("MainWindow", "Tools", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
