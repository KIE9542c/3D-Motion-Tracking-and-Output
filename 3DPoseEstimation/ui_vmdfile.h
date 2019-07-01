/********************************************************************************
** Form generated from reading UI file 'vmdfile.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VMDFILE_H
#define UI_VMDFILE_H

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

class Ui_vmdfile
{
public:
    QPushButton *pushButton_del;
    QPushButton *pushButton_delAll;
    QPushButton *pushButton_close;
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *pushButton_openfile;
    QPushButton *pushButton_change;
    QPushButton *pushButton_conf;
    QTableView *tableView;

    void setupUi(QDialog *vmdfile)
    {
        if (vmdfile->objectName().isEmpty())
            vmdfile->setObjectName(QString::fromUtf8("vmdfile"));
        vmdfile->resize(753, 507);
        pushButton_del = new QPushButton(vmdfile);
        pushButton_del->setObjectName(QString::fromUtf8("pushButton_del"));
        pushButton_del->setGeometry(QRect(30, 60, 75, 23));
        pushButton_delAll = new QPushButton(vmdfile);
        pushButton_delAll->setObjectName(QString::fromUtf8("pushButton_delAll"));
        pushButton_delAll->setGeometry(QRect(140, 60, 75, 23));
        pushButton_close = new QPushButton(vmdfile);
        pushButton_close->setObjectName(QString::fromUtf8("pushButton_close"));
        pushButton_close->setGeometry(QRect(640, 20, 61, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix2/Buttons/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_close->setIcon(icon);
        lineEdit = new QLineEdit(vmdfile);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(130, 450, 141, 20));
        label = new QLabel(vmdfile);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 450, 54, 12));
        pushButton_openfile = new QPushButton(vmdfile);
        pushButton_openfile->setObjectName(QString::fromUtf8("pushButton_openfile"));
        pushButton_openfile->setGeometry(QRect(510, 80, 75, 23));
        pushButton_change = new QPushButton(vmdfile);
        pushButton_change->setObjectName(QString::fromUtf8("pushButton_change"));
        pushButton_change->setGeometry(QRect(300, 450, 75, 23));
        pushButton_conf = new QPushButton(vmdfile);
        pushButton_conf->setObjectName(QString::fromUtf8("pushButton_conf"));
        pushButton_conf->setGeometry(QRect(510, 50, 75, 23));
        tableView = new QTableView(vmdfile);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(170, 140, 431, 251));

        retranslateUi(vmdfile);

        QMetaObject::connectSlotsByName(vmdfile);
    } // setupUi

    void retranslateUi(QDialog *vmdfile)
    {
        vmdfile->setWindowTitle(QCoreApplication::translate("vmdfile", "Dialog", nullptr));
        pushButton_del->setText(QCoreApplication::translate("vmdfile", "\345\210\240\351\231\244", nullptr));
        pushButton_delAll->setText(QCoreApplication::translate("vmdfile", "\346\270\205\347\251\272\345\210\227\350\241\250", nullptr));
        pushButton_close->setText(QString());
        lineEdit->setText(QCoreApplication::translate("vmdfile", "\346\234\252\351\200\211\346\213\251\350\276\223\345\207\272\350\267\257\345\276\204", nullptr));
        label->setText(QCoreApplication::translate("vmdfile", "\350\276\223\345\207\272\350\267\257\345\276\204", nullptr));
        pushButton_openfile->setText(QCoreApplication::translate("vmdfile", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        pushButton_change->setText(QCoreApplication::translate("vmdfile", "\346\233\264\346\224\271", nullptr));
        pushButton_conf->setText(QCoreApplication::translate("vmdfile", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class vmdfile: public Ui_vmdfile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VMDFILE_H
