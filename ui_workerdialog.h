/********************************************************************************
** Form generated from reading UI file 'workerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORKERDIALOG_H
#define UI_WORKERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_WorkerDialog
{
public:
    QLabel *label;
    QProgressBar *progressBar;
    QPushButton *cancelButton;
    QLabel *label_2;
    QComboBox *priorityComboBox;

    void setupUi(QDialog *WorkerDialog)
    {
        if (WorkerDialog->objectName().isEmpty())
            WorkerDialog->setObjectName(QString::fromUtf8("WorkerDialog"));
        WorkerDialog->resize(474, 172);
        label = new QLabel(WorkerDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(16, 30, 111, 16));
        progressBar = new QProgressBar(WorkerDialog);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(16, 70, 454, 23));
        progressBar->setValue(0);
        cancelButton = new QPushButton(WorkerDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(360, 120, 75, 23));
        label_2 = new QLabel(WorkerDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(250, 30, 71, 16));
        priorityComboBox = new QComboBox(WorkerDialog);
        priorityComboBox->addItem(QString());
        priorityComboBox->addItem(QString());
        priorityComboBox->setObjectName(QString::fromUtf8("priorityComboBox"));
        priorityComboBox->setGeometry(QRect(340, 30, 111, 22));

        retranslateUi(WorkerDialog);

        QMetaObject::connectSlotsByName(WorkerDialog);
    } // setupUi

    void retranslateUi(QDialog *WorkerDialog)
    {
        WorkerDialog->setWindowTitle(QCoreApplication::translate("WorkerDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("WorkerDialog", "Extracting files...", nullptr));
        cancelButton->setText(QCoreApplication::translate("WorkerDialog", "Cancel", nullptr));
        label_2->setText(QCoreApplication::translate("WorkerDialog", "IO Priority:", nullptr));
        priorityComboBox->setItemText(0, QCoreApplication::translate("WorkerDialog", "Normal", nullptr));
        priorityComboBox->setItemText(1, QCoreApplication::translate("WorkerDialog", "Background", nullptr));

    } // retranslateUi

};

namespace Ui {
    class WorkerDialog: public Ui_WorkerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORKERDIALOG_H
