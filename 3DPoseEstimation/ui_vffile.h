/********************************************************************************
** Form generated from reading UI file 'vffile.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VFFILE_H
#define UI_VFFILE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_vfFile
{
public:
    QPushButton *pushButton_del;
    QPushButton *pushButton_openfile;
    QLabel *label;
    QPushButton *pushButton_conf;
    QPushButton *pushButton_delAll;
    QTableView *tableView;
    QLineEdit *lineEdit;
    QPushButton *pushButton_change;
    QPushButton *pushButton_close;

    void setupUi(QDialog *vfFile)
    {
        if (vfFile->objectName().isEmpty())
            vfFile->setObjectName(QString::fromUtf8("vfFile"));
        vfFile->resize(705, 517);
        pushButton_del = new QPushButton(vfFile);
        pushButton_del->setObjectName(QString::fromUtf8("pushButton_del"));
        pushButton_del->setGeometry(QRect(20, 60, 75, 23));
        pushButton_openfile = new QPushButton(vfFile);
        pushButton_openfile->setObjectName(QString::fromUtf8("pushButton_openfile"));
        pushButton_openfile->setGeometry(QRect(500, 80, 75, 23));
        label = new QLabel(vfFile);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 450, 54, 12));
        pushButton_conf = new QPushButton(vfFile);
        pushButton_conf->setObjectName(QString::fromUtf8("pushButton_conf"));
        pushButton_conf->setGeometry(QRect(500, 50, 75, 23));
        pushButton_delAll = new QPushButton(vfFile);
        pushButton_delAll->setObjectName(QString::fromUtf8("pushButton_delAll"));
        pushButton_delAll->setGeometry(QRect(130, 60, 75, 23));
        tableView = new QTableView(vfFile);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(160, 140, 431, 251));
        lineEdit = new QLineEdit(vfFile);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(140, 450, 113, 20));
        pushButton_change = new QPushButton(vfFile);
        pushButton_change->setObjectName(QString::fromUtf8("pushButton_change"));
        pushButton_change->setGeometry(QRect(290, 450, 75, 23));
        pushButton_close = new QPushButton(vfFile);
        pushButton_close->setObjectName(QString::fromUtf8("pushButton_close"));
        pushButton_close->setGeometry(QRect(630, 20, 61, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix2/Buttons/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_close->setIcon(icon);

        retranslateUi(vfFile);

        QMetaObject::connectSlotsByName(vfFile);
    } // setupUi

    void retranslateUi(QDialog *vfFile)
    {
        vfFile->setWindowTitle(QCoreApplication::translate("vfFile", "Dialog", nullptr));
        pushButton_del->setText(QCoreApplication::translate("vfFile", "\345\210\240\351\231\244", nullptr));
        pushButton_openfile->setText(QCoreApplication::translate("vfFile", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        label->setText(QCoreApplication::translate("vfFile", "\350\276\223\345\207\272\350\267\257\345\276\204", nullptr));
        pushButton_conf->setText(QCoreApplication::translate("vfFile", "\347\241\256\345\256\232", nullptr));
        pushButton_delAll->setText(QCoreApplication::translate("vfFile", "\346\270\205\347\251\272\345\210\227\350\241\250", nullptr));
        pushButton_change->setText(QCoreApplication::translate("vfFile", "\346\233\264\346\224\271", nullptr));
        pushButton_close->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class vfFile: public Ui_vfFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VFFILE_H
