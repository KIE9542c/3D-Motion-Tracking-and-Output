/********************************************************************************
** Form generated from reading UI file 'trackingWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
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
        pushButton_VMD->setGeometry(QRect(50, 210, 103, 121));
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
        pushButton_FBX->setGeometry(QRect(50, 350, 103, 121));
        pushButton_FBX->setStyleSheet(QString::fromUtf8("#pushButton_FBX{border-image: url(:/new/prefix2/FBX.png);}\n"
"#pushButton_FBX:hover{border-image: url(:/new/prefix2/FBX_hover.png);}"));
        pushButton_FBX->setIconSize(QSize(103, 121));
        pushButton_VF = new QPushButton(frame);
        pushButton_VF->setObjectName(QString::fromUtf8("pushButton_VF"));
        pushButton_VF->setGeometry(QRect(50, 490, 103, 121));
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
        tableView->setGeometry(QRect(200, 100, 881, 581));
        tableView->verticalHeader()->setCascadingSectionResizes(false);
        pushButton_path = new QPushButton(frame);
        pushButton_path->setObjectName(QString::fromUtf8("pushButton_path"));
        pushButton_path->setGeometry(QRect(10, 50, 131, 41));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_path->sizePolicy().hasHeightForWidth());
        pushButton_path->setSizePolicy(sizePolicy);
        pushButton_path->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix2/output.png);"));
        pushButton_del = new QPushButton(frame);
        pushButton_del->setObjectName(QString::fromUtf8("pushButton_del"));
        pushButton_del->setGeometry(QRect(200, 50, 71, 41));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_del->sizePolicy().hasHeightForWidth());
        pushButton_del->setSizePolicy(sizePolicy1);
        pushButton_del->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix2/delete.png);"));
        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(660, 60, 99, 23));
        pushButton_start = new QPushButton(frame);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));
        pushButton_start->setGeometry(QRect(430, 60, 101, 23));
        pushButton_stop = new QPushButton(frame);
        pushButton_stop->setObjectName(QString::fromUtf8("pushButton_stop"));
        pushButton_stop->setGeometry(QRect(560, 60, 75, 23));
        pushButton_delAll = new QPushButton(frame);
        pushButton_delAll->setObjectName(QString::fromUtf8("pushButton_delAll"));
        pushButton_delAll->setGeometry(QRect(300, 50, 91, 41));
        pushButton_delAll->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix2/deleteAll.png);"));
        label_5->raise();
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
        pushButton_VMD->setText(QString());
        pushButton_FBX->setText(QString());
        pushButton_VF->setText(QString());
        pushButton_path->setText(QString());
        pushButton_del->setText(QString());
        pushButton_2->setText(QApplication::translate("TrackingWindow", "\350\277\224\345\233\236\350\217\234\345\215\225", nullptr));
        pushButton_start->setText(QApplication::translate("TrackingWindow", "\345\274\200\345\247\213\345\244\204\347\220\206", nullptr));
        pushButton_stop->setText(QApplication::translate("TrackingWindow", "\345\201\234\346\255\242", nullptr));
        pushButton_delAll->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TrackingWindow: public Ui_TrackingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACKINGWINDOW_H
