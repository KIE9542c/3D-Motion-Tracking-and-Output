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
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_vfFile
{
public:
    QTableView *tableView;
    QFrame *frame;
    QPushButton *pushButton_del;
    QPushButton *pushButton_delAll;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton_change;
    QPushButton *pushButton_conf;
    QPushButton *pushButton_close;
    QPushButton *pushButton_openfile;

    void setupUi(QDialog *vfFile)
    {
        if (vfFile->objectName().isEmpty())
            vfFile->setObjectName(QString::fromUtf8("vfFile"));
        vfFile->resize(752, 507);
        tableView = new QTableView(vfFile);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(25, 110, 700, 321));
        tableView->setStyleSheet(QString::fromUtf8("QHeaderView::section {background-color:white; border:1px solid gray;}"));
        frame = new QFrame(vfFile);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 731, 491));
        frame->setStyleSheet(QString::fromUtf8("#frame{background-color: rgb(255, 255, 255);}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButton_del = new QPushButton(frame);
        pushButton_del->setObjectName(QString::fromUtf8("pushButton_del"));
        pushButton_del->setGeometry(QRect(20, 50, 71, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font.setBold(false);
        font.setWeight(50);
        pushButton_del->setFont(font);
        pushButton_del->setStyleSheet(QString::fromUtf8("#pushButton_del{background-color:transparent;}\n"
"#pushButton_del:hover{border-image:url(:/new/prefix2/grey.png);}\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix2/del.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_del->setIcon(icon);
        pushButton_del->setIconSize(QSize(30, 30));
        pushButton_delAll = new QPushButton(frame);
        pushButton_delAll->setObjectName(QString::fromUtf8("pushButton_delAll"));
        pushButton_delAll->setGeometry(QRect(100, 50, 91, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        pushButton_delAll->setFont(font1);
        pushButton_delAll->setStyleSheet(QString::fromUtf8("#pushButton_delAll{background-color:transparent;}\n"
"#pushButton_delAll:hover{\n"
"border-image: url(:/new/prefix2/grey.png)}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix2/delAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_delAll->setIcon(icon1);
        pushButton_delAll->setIconSize(QSize(30, 30));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 450, 71, 21));
        label->setFont(font1);
        lineEdit = new QLineEdit(frame);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(90, 450, 361, 20));
        lineEdit->setFont(font1);
        pushButton_change = new QPushButton(frame);
        pushButton_change->setObjectName(QString::fromUtf8("pushButton_change"));
        pushButton_change->setGeometry(QRect(460, 445, 71, 30));
        pushButton_change->setFont(font1);
        pushButton_change->setStyleSheet(QString::fromUtf8("#pushButton_change{background-color:transparent;}\n"
"#pushButton_change:hover{\n"
"border-image: url(:/new/prefix2/grey.png)}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix2/openfile.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_change->setIcon(icon2);
        pushButton_change->setIconSize(QSize(20, 20));
        pushButton_conf = new QPushButton(frame);
        pushButton_conf->setObjectName(QString::fromUtf8("pushButton_conf"));
        pushButton_conf->setGeometry(QRect(640, 50, 71, 41));
        pushButton_conf->setFont(font1);
        pushButton_conf->setStyleSheet(QString::fromUtf8("#pushButton_conf{background-color:transparent;}\n"
"#pushButton_conf:hover{\n"
"border-image: url(:/new/prefix2/grey.png)}"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/prefix2/conf.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_conf->setIcon(icon3);
        pushButton_conf->setIconSize(QSize(30, 30));
        pushButton_close = new QPushButton(frame);
        pushButton_close->setObjectName(QString::fromUtf8("pushButton_close"));
        pushButton_close->setGeometry(QRect(680, 0, 51, 31));
        pushButton_close->setStyleSheet(QString::fromUtf8("#pushButton_close{background-color:transparent;}\n"
"#pushButton_close:hover{	border-image: url(:/new/prefix2/red.png);\n"
"}\n"
""));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/new/prefix2/close_win.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_close->setIcon(icon4);
        pushButton_close->setIconSize(QSize(10, 10));
        pushButton_openfile = new QPushButton(frame);
        pushButton_openfile->setObjectName(QString::fromUtf8("pushButton_openfile"));
        pushButton_openfile->setGeometry(QRect(540, 50, 91, 41));
        pushButton_openfile->setFont(font1);
        pushButton_openfile->setStyleSheet(QString::fromUtf8("#pushButton_openfile{background-color:transparent;}\n"
"#pushButton_openfile:hover{\n"
"border-image: url(:/new/prefix2/grey.png)}"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/new/prefix2/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_openfile->setIcon(icon5);
        pushButton_openfile->setIconSize(QSize(30, 30));
        frame->raise();
        tableView->raise();

        retranslateUi(vfFile);

        QMetaObject::connectSlotsByName(vfFile);
    } // setupUi

    void retranslateUi(QDialog *vfFile)
    {
        vfFile->setWindowTitle(QCoreApplication::translate("vfFile", "Dialog", nullptr));
        pushButton_del->setText(QCoreApplication::translate("vfFile", "\347\247\273\351\231\244", nullptr));
        pushButton_delAll->setText(QCoreApplication::translate("vfFile", "\346\270\205\347\251\272\345\210\227\350\241\250", nullptr));
        label->setText(QCoreApplication::translate("vfFile", "\350\276\223\345\207\272\350\267\257\345\276\204", nullptr));
        lineEdit->setText(QCoreApplication::translate("vfFile", "\346\234\252\351\200\211\346\213\251\350\276\223\345\207\272\350\267\257\345\276\204", nullptr));
        pushButton_change->setText(QCoreApplication::translate("vfFile", "\346\233\264\346\224\271", nullptr));
        pushButton_conf->setText(QCoreApplication::translate("vfFile", "\347\241\256\345\256\232", nullptr));
        pushButton_close->setText(QString());
        pushButton_openfile->setText(QCoreApplication::translate("vfFile", "\346\267\273\345\212\240\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class vfFile: public Ui_vfFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VFFILE_H
