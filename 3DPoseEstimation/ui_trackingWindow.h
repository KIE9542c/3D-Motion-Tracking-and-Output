/********************************************************************************
** Form generated from reading UI file 'trackingWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACKINGWINDOW_H
#define UI_TRACKINGWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TrackingWindow
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_VMD;
    QPushButton *pushButton_FBX;
    QPushButton *pushButton_VF;
    QTableView *tableView;
    QPushButton *pushButton_path;
    QPushButton *pushButton_del;
    QPushButton *pushButton_2;
    QPushButton *pushButton_start;
    QPushButton *pushButton_delAll;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *comboBox;
    QCheckBox *checkBox;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *pushButton_help;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TrackingWindow)
    {
        if (TrackingWindow->objectName().isEmpty())
            TrackingWindow->setObjectName(QString::fromUtf8("TrackingWindow"));
        TrackingWindow->setEnabled(true);
        TrackingWindow->resize(1101, 731);
        TrackingWindow->setMinimumSize(QSize(1101, 731));
        TrackingWindow->setMaximumSize(QSize(1101, 731));
        TrackingWindow->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(TrackingWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 1081, 681));
        frame->setStyleSheet(QString::fromUtf8("#frame{background-color: rgb(255, 255, 255);}\n"
"\n"
"\n"
""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButton_6 = new QPushButton(frame);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(960, 0, 61, 41));
        pushButton_6->setStyleSheet(QString::fromUtf8("#pushButton_6{background-color: transparent;\n"
"border-color: transparent;}\n"
"#pushButton_6:hover\n"
"{\n"
"    	border-image: url(:/new/prefix2/red.png);\n"
"\n"
"}\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix2/Buttons/min.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_6->setIcon(icon);
        pushButton_6->setIconSize(QSize(30, 30));
        pushButton_7 = new QPushButton(frame);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(1020, 0, 61, 41));
        pushButton_7->setStyleSheet(QString::fromUtf8("#pushButton_7{background-color: transparent;\n"
"border-color: transparent;}\n"
"#pushButton_7:hover\n"
"{\n"
"    	border-image: url(:/new/prefix2/red.png);\n"
"\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix2/Buttons/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_7->setIcon(icon1);
        pushButton_7->setIconSize(QSize(30, 30));
        pushButton_VMD = new QPushButton(frame);
        pushButton_VMD->setObjectName(QString::fromUtf8("pushButton_VMD"));
        pushButton_VMD->setGeometry(QRect(30, 230, 103, 121));
        pushButton_VMD->setStyleSheet(QString::fromUtf8("#pushButton_VMD:hover\n"
"{\n"
"	border-image: url(:/new/prefix2/VMD_hover.png);\n"
"\n"
"}\n"
"#pushButton_VMD{border-image: url(:/new/prefix2/VMD.png);\n"
"}\n"
""));
        pushButton_VMD->setIconSize(QSize(103, 121));
        pushButton_FBX = new QPushButton(frame);
        pushButton_FBX->setObjectName(QString::fromUtf8("pushButton_FBX"));
        pushButton_FBX->setGeometry(QRect(30, 380, 103, 121));
        pushButton_FBX->setStyleSheet(QString::fromUtf8("#pushButton_FBX{border-image: url(:/new/prefix2/FBX.png);}\n"
"#pushButton_FBX:hover{border-image: url(:/new/prefix2/FBX_hover.png);}"));
        pushButton_FBX->setIconSize(QSize(103, 121));
        pushButton_VF = new QPushButton(frame);
        pushButton_VF->setObjectName(QString::fromUtf8("pushButton_VF"));
        pushButton_VF->setGeometry(QRect(30, 530, 103, 121));
        pushButton_VF->setStyleSheet(QString::fromUtf8("#pushButton_VF:hover\n"
"{\n"
"border-image: url(:/new/prefix2/vmdfbx_hover.png);\n"
"}\n"
"#pushButton_VF\n"
"{\n"
"border-image: url(:/new/prefix2/vmdfbx.png);\n"
"}"));
        pushButton_VF->setIconSize(QSize(103, 121));
        tableView = new QTableView(frame);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(170, 110, 881, 541));
        tableView->setStyleSheet(QString::fromUtf8("QHeaderView::section {background-color:white; border:1px solid gray;}"));
        tableView->verticalHeader()->setCascadingSectionResizes(false);
        pushButton_path = new QPushButton(frame);
        pushButton_path->setObjectName(QString::fromUtf8("pushButton_path"));
        pushButton_path->setGeometry(QRect(30, 60, 111, 41));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_path->sizePolicy().hasHeightForWidth());
        pushButton_path->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font.setBold(false);
        font.setWeight(50);
        pushButton_path->setFont(font);
        pushButton_path->setStyleSheet(QString::fromUtf8("#pushButton_path{background-color:transparent;}\n"
"#pushButton_path:hover{border-image: url(:/new/prefix2/grey.png);}\n"
""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix2/openfile.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_path->setIcon(icon2);
        pushButton_path->setIconSize(QSize(30, 30));
        pushButton_del = new QPushButton(frame);
        pushButton_del->setObjectName(QString::fromUtf8("pushButton_del"));
        pushButton_del->setGeometry(QRect(190, 60, 71, 41));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_del->sizePolicy().hasHeightForWidth());
        pushButton_del->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        pushButton_del->setFont(font1);
        pushButton_del->setStyleSheet(QString::fromUtf8("#pushButton_del{background-color:transparent;}\n"
"#pushButton_del:hover{border-image:url(:/new/prefix2/grey.png);}\n"
""));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/prefix2/del.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_del->setIcon(icon3);
        pushButton_del->setIconSize(QSize(30, 30));
        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(780, 60, 101, 41));
        pushButton_2->setFont(font1);
        pushButton_2->setStyleSheet(QString::fromUtf8("#pushButton_2{background-color: transparent;}\n"
"#pushButton_2:hover{border-image: url(:/new/prefix2/grey.png);}\n"
""));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/new/prefix2/return.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon4);
        pushButton_2->setIconSize(QSize(30, 30));
        pushButton_start = new QPushButton(frame);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));
        pushButton_start->setGeometry(QRect(410, 60, 101, 41));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font2.setPointSize(9);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setUnderline(false);
        font2.setWeight(50);
        font2.setStrikeOut(false);
        pushButton_start->setFont(font2);
        pushButton_start->setStyleSheet(QString::fromUtf8("#pushButton_start{background-color:transparent;\n"
"}\n"
"\n"
"\n"
"#pushButton_start:hover{border-image: url(:/new/prefix2/grey.png);}\n"
""));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/new/prefix2/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_start->setIcon(icon5);
        pushButton_start->setIconSize(QSize(30, 30));
        pushButton_delAll = new QPushButton(frame);
        pushButton_delAll->setObjectName(QString::fromUtf8("pushButton_delAll"));
        pushButton_delAll->setGeometry(QRect(270, 60, 101, 41));
        pushButton_delAll->setFont(font1);
        pushButton_delAll->setStyleSheet(QString::fromUtf8("#pushButton_delAll{background-color:transparent;}\n"
"#pushButton_delAll:hover{\n"
"border-image: url(:/new/prefix2/grey.png)}"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/new/prefix2/delAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_delAll->setIcon(icon6);
        pushButton_delAll->setIconSize(QSize(30, 30));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 190, 121, 16));
        label->setFont(font1);
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(380, 50, 16, 51));
        label_2->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix2/vertical.png);"));
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(530, 50, 16, 51));
        label_3->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix2/vertical.png);"));
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(162, 50, 16, 51));
        label_4->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix2/vertical.png);"));
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(940, 60, 141, 41));
        label_5->setStyleSheet(QString::fromUtf8(""));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix2/logo3.png")));
        label_5->setScaledContents(true);
        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(0, 0, 1081, 41));
        label_6->setToolTipDuration(-5);
        label_6->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix2/frame.jpg);"));
        comboBox = new QComboBox(frame);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(30, 150, 111, 22));
        comboBox->setFont(font1);
        comboBox->setStyleSheet(QString::fromUtf8("#comboBox{\n"
"    border: 1px solid gray;\n"
"    border-radius: 3px;\n"
"    padding: 1px 2px 1px 2px; \n"
"    min-width: 6em;   \n"
"}\n"
"#comboBox:drop-down {\n"
"   \n"
"    width: 20px;\n"
" \n"
"    border-left-width: 1px;\n"
"    border-left-color: darkgray;\n"
"    border-left-style: solid; /* just a single line */\n"
"    border-top-right-radius: 3px; /* same radius as the QComboBox */\n"
"    border-bottom-right-radius: 3px;\n"
"}\n"
" \n"
"#comboBox:down-arrow {\n"
"	border-image: url(:/new/prefix2/downArrow.png);\n"
"}"));
        checkBox = new QCheckBox(frame);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(560, 65, 171, 31));
        checkBox->setFont(font1);
        checkBox->setStyleSheet(QString::fromUtf8("QCheckBox::indicator { \n"
"    width: 26px;\n"
"    height: 50px;\n"
"}\n"
"/*\346\234\252\351\200\211\344\270\255*/\n"
"QCheckBox::indicator::unchecked {   \n"
"    \n"
"	image: url(:/new/prefix2/unchecked.png);\n"
"}\n"
"/*\351\200\211\344\270\255*/\n"
"QCheckBox::indicator::checked { \n"
"    \n"
"	image: url(:/new/prefix2/check.png);\n"
"}"));
        label_7 = new QLabel(frame);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(750, 50, 16, 51));
        label_7->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix2/vertical.png);"));
        label_8 = new QLabel(frame);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 120, 121, 16));
        label_8->setFont(font1);
        pushButton_help = new QPushButton(frame);
        pushButton_help->setObjectName(QString::fromUtf8("pushButton_help"));
        pushButton_help->setGeometry(QRect(900, 0, 61, 41));
        pushButton_help->setStyleSheet(QString::fromUtf8("#pushButton_help{background-color: transparent;\n"
"border-color: transparent;}\n"
"#pushButton_help:hover\n"
"{\n"
"    	border-image: url(:/new/prefix2/red.png);\n"
"\n"
"}\n"
""));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/new/prefix2/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_help->setIcon(icon7);
        pushButton_help->setIconSize(QSize(20, 20));
        label_6->raise();
        pushButton_6->raise();
        pushButton_7->raise();
        pushButton_VMD->raise();
        pushButton_FBX->raise();
        pushButton_VF->raise();
        tableView->raise();
        pushButton_path->raise();
        pushButton_del->raise();
        pushButton_2->raise();
        pushButton_start->raise();
        pushButton_delAll->raise();
        label->raise();
        label_2->raise();
        label_3->raise();
        label_4->raise();
        label_5->raise();
        comboBox->raise();
        checkBox->raise();
        label_7->raise();
        label_8->raise();
        pushButton_help->raise();
        TrackingWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TrackingWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setSizeGripEnabled(false);
        TrackingWindow->setStatusBar(statusBar);

        retranslateUi(TrackingWindow);

        QMetaObject::connectSlotsByName(TrackingWindow);
    } // setupUi

    void retranslateUi(QMainWindow *TrackingWindow)
    {
        TrackingWindow->setWindowTitle(QCoreApplication::translate("TrackingWindow", "MainWindow", nullptr));
        pushButton_6->setText(QString());
        pushButton_7->setText(QString());
        pushButton_VMD->setText(QString());
        pushButton_FBX->setText(QString());
        pushButton_VF->setText(QString());
        pushButton_path->setText(QCoreApplication::translate("TrackingWindow", "\346\211\223\345\274\200\346\226\207\344\273\266\345\244\271", nullptr));
        pushButton_del->setText(QCoreApplication::translate("TrackingWindow", "\347\247\273\351\231\244", nullptr));
        pushButton_2->setText(QCoreApplication::translate("TrackingWindow", "\350\277\224\345\233\236\350\217\234\345\215\225", nullptr));
        pushButton_start->setText(QCoreApplication::translate("TrackingWindow", "\345\274\200\345\247\213\345\244\204\347\220\206", nullptr));
        pushButton_delAll->setText(QCoreApplication::translate("TrackingWindow", "\346\270\205\347\251\272\345\210\227\350\241\250", nullptr));
        label->setText(QCoreApplication::translate("TrackingWindow", "\345\257\274\345\207\272\345\212\250\344\275\234\346\226\207\344\273\266\346\240\274\345\274\217", nullptr));
        label_2->setText(QString());
        label_3->setText(QString());
        label_4->setText(QString());
        label_5->setText(QString());
        label_6->setText(QString());
        comboBox->setItemText(0, QCoreApplication::translate("TrackingWindow", "OpenMMD", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("TrackingWindow", "VNect", nullptr));

        checkBox->setText(QCoreApplication::translate("TrackingWindow", "\345\244\204\347\220\206\345\220\216\346\230\257\345\220\246\346\230\276\347\244\272\345\212\250\347\224\273", nullptr));
        label_7->setText(QString());
        label_8->setText(QCoreApplication::translate("TrackingWindow", "\351\200\211\346\213\251\344\270\211\347\273\264\351\207\215\345\273\272\347\256\227\346\263\225", nullptr));
        pushButton_help->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TrackingWindow: public Ui_TrackingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACKINGWINDOW_H
