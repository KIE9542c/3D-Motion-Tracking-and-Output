/********************************************************************************
** Form generated from reading UI file 'trackingWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACKINGWINDOW_H
#define UI_TRACKINGWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
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
    QLabel *label_5;
    QPushButton *pushButton_VMD;
    QPushButton *pushButton_FBX;
    QPushButton *pushButton_VF;
    QTableView *tableView;
    QPushButton *pushButton_path;
    QPushButton *pushButton_add;
    QPushButton *pushButton_del;
    QPushButton *pushButton_2;
    QPushButton *pushButton_start;
    QPushButton *pushButton_stop;
    QPushButton *pushButton_delAll;
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
"    background-color: rgb(255, 0, 0);\n"
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
"    background-color: red;\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix2/Buttons/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_7->setIcon(icon1);
        pushButton_7->setIconSize(QSize(30, 30));
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(0, 0, 1081, 41));
        label_5->setStyleSheet(QString::fromUtf8("\n"
"background-image: url(:/new/prefix2/frame.jpg);"));
        pushButton_VMD = new QPushButton(frame);
        pushButton_VMD->setObjectName(QString::fromUtf8("pushButton_VMD"));
        pushButton_VMD->setGeometry(QRect(20, 130, 93, 28));
        pushButton_FBX = new QPushButton(frame);
        pushButton_FBX->setObjectName(QString::fromUtf8("pushButton_FBX"));
        pushButton_FBX->setGeometry(QRect(20, 250, 93, 28));
        pushButton_VF = new QPushButton(frame);
        pushButton_VF->setObjectName(QString::fromUtf8("pushButton_VF"));
        pushButton_VF->setGeometry(QRect(20, 490, 93, 28));
        tableView = new QTableView(frame);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(355, 131, 701, 541));
        tableView->verticalHeader()->setCascadingSectionResizes(false);
        pushButton_path = new QPushButton(frame);
        pushButton_path->setObjectName(QString::fromUtf8("pushButton_path"));
        pushButton_path->setGeometry(QRect(20, 70, 181, 28));
        pushButton_add = new QPushButton(frame);
        pushButton_add->setObjectName(QString::fromUtf8("pushButton_add"));
        pushButton_add->setGeometry(QRect(180, 590, 93, 28));
        pushButton_del = new QPushButton(frame);
        pushButton_del->setObjectName(QString::fromUtf8("pushButton_del"));
        pushButton_del->setGeometry(QRect(220, 70, 93, 28));
        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(530, 70, 99, 23));
        pushButton_start = new QPushButton(frame);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));
        pushButton_start->setGeometry(QRect(330, 70, 101, 23));
        pushButton_stop = new QPushButton(frame);
        pushButton_stop->setObjectName(QString::fromUtf8("pushButton_stop"));
        pushButton_stop->setGeometry(QRect(440, 70, 75, 23));
        pushButton_delAll = new QPushButton(frame);
        pushButton_delAll->setObjectName(QString::fromUtf8("pushButton_delAll"));
        pushButton_delAll->setGeometry(QRect(220, 110, 75, 23));
        label_5->raise();
        pushButton_6->raise();
        pushButton_7->raise();
        pushButton_VMD->raise();
        pushButton_FBX->raise();
        pushButton_VF->raise();
        tableView->raise();
        pushButton_path->raise();
        pushButton_add->raise();
        pushButton_del->raise();
        pushButton_2->raise();
        pushButton_start->raise();
        pushButton_stop->raise();
        pushButton_delAll->raise();
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
        TrackingWindow->setWindowTitle(QApplication::translate("TrackingWindow", "MainWindow", nullptr));
        pushButton_6->setText(QString());
        pushButton_7->setText(QString());
        label_5->setText(QString());
        pushButton_VMD->setText(QApplication::translate("TrackingWindow", "vmd", nullptr));
        pushButton_FBX->setText(QApplication::translate("TrackingWindow", "fbx", nullptr));
        pushButton_VF->setText(QApplication::translate("TrackingWindow", "vmd\345\222\214fbx", nullptr));
        pushButton_path->setText(QApplication::translate("TrackingWindow", "\351\200\211\346\213\251\350\276\223\345\207\272\346\226\207\344\273\266\345\244\271", nullptr));
        pushButton_add->setText(QApplication::translate("TrackingWindow", "\346\267\273\345\212\240", nullptr));
        pushButton_del->setText(QApplication::translate("TrackingWindow", "\345\210\240\351\231\244", nullptr));
        pushButton_2->setText(QApplication::translate("TrackingWindow", "\350\277\224\345\233\236\350\217\234\345\215\225", nullptr));
        pushButton_start->setText(QApplication::translate("TrackingWindow", "\345\274\200\345\247\213\345\244\204\347\220\206", nullptr));
        pushButton_stop->setText(QApplication::translate("TrackingWindow", "\345\201\234\346\255\242", nullptr));
        pushButton_delAll->setText(QApplication::translate("TrackingWindow", "\346\270\205\347\251\272\345\210\227\350\241\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TrackingWindow: public Ui_TrackingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACKINGWINDOW_H
