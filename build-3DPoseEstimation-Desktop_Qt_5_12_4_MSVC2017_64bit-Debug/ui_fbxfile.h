/********************************************************************************
** Form generated from reading UI file 'fbxfile.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FBXFILE_H
#define UI_FBXFILE_H

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

class Ui_fbxFile
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

    void setupUi(QDialog *fbxFile)
    {
        if (fbxFile->objectName().isEmpty())
            fbxFile->setObjectName(QString::fromUtf8("fbxFile"));
        fbxFile->resize(693, 499);
        pushButton_del = new QPushButton(fbxFile);
        pushButton_del->setObjectName(QString::fromUtf8("pushButton_del"));
        pushButton_del->setGeometry(QRect(10, 60, 75, 23));
        pushButton_openfile = new QPushButton(fbxFile);
        pushButton_openfile->setObjectName(QString::fromUtf8("pushButton_openfile"));
        pushButton_openfile->setGeometry(QRect(490, 80, 75, 23));
        label = new QLabel(fbxFile);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 450, 54, 12));
        pushButton_conf = new QPushButton(fbxFile);
        pushButton_conf->setObjectName(QString::fromUtf8("pushButton_conf"));
        pushButton_conf->setGeometry(QRect(490, 50, 75, 23));
        pushButton_delAll = new QPushButton(fbxFile);
        pushButton_delAll->setObjectName(QString::fromUtf8("pushButton_delAll"));
        pushButton_delAll->setGeometry(QRect(120, 60, 75, 23));
        tableView = new QTableView(fbxFile);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(150, 140, 431, 251));
        lineEdit = new QLineEdit(fbxFile);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(130, 450, 113, 20));
        pushButton_change = new QPushButton(fbxFile);
        pushButton_change->setObjectName(QString::fromUtf8("pushButton_change"));
        pushButton_change->setGeometry(QRect(280, 450, 75, 23));
        pushButton_close = new QPushButton(fbxFile);
        pushButton_close->setObjectName(QString::fromUtf8("pushButton_close"));
        pushButton_close->setGeometry(QRect(620, 20, 61, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix2/Buttons/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_close->setIcon(icon);

        retranslateUi(fbxFile);

        QMetaObject::connectSlotsByName(fbxFile);
    } // setupUi

    void retranslateUi(QDialog *fbxFile)
    {
        fbxFile->setWindowTitle(QApplication::translate("fbxFile", "Dialog", nullptr));
        pushButton_del->setText(QApplication::translate("fbxFile", "\345\210\240\351\231\244", nullptr));
        pushButton_openfile->setText(QApplication::translate("fbxFile", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        label->setText(QApplication::translate("fbxFile", "\350\276\223\345\207\272\350\267\257\345\276\204", nullptr));
        pushButton_conf->setText(QApplication::translate("fbxFile", "\347\241\256\345\256\232", nullptr));
        pushButton_delAll->setText(QApplication::translate("fbxFile", "\346\270\205\347\251\272\345\210\227\350\241\250", nullptr));
        pushButton_change->setText(QApplication::translate("fbxFile", "\346\233\264\346\224\271", nullptr));
        pushButton_close->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class fbxFile: public Ui_fbxFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FBXFILE_H