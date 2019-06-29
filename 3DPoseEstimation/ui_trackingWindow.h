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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TrackingWindow
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit;
    QPushButton *pushButton_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_4;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QLabel *label_4;
    QLabel *label_5;
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
        horizontalLayoutWidget_4 = new QWidget(frame);
        horizontalLayoutWidget_4->setObjectName(QString::fromUtf8("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(340, 370, 252, 80));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(horizontalLayoutWidget_4);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_5->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        pushButton_2 = new QPushButton(horizontalLayoutWidget_4);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_5->addWidget(pushButton_2);

        verticalLayoutWidget = new QWidget(frame);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(230, 200, 561, 131));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_8->addWidget(label);

        horizontalSpacer = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer);

        lineEdit = new QLineEdit(verticalLayoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_8->addWidget(lineEdit);

        pushButton_3 = new QPushButton(verticalLayoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_8->addWidget(pushButton_3);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(label_2);

        horizontalSpacer_4 = new QSpacerItem(46, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);

        comboBox = new QComboBox(verticalLayoutWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_6->addWidget(comboBox);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_7->addWidget(label_3);

        horizontalSpacer_3 = new QSpacerItem(75, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);

        lineEdit_3 = new QLineEdit(verticalLayoutWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        horizontalLayout_7->addWidget(lineEdit_3);

        pushButton_4 = new QPushButton(verticalLayoutWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        horizontalLayout_7->addWidget(pushButton_4);


        verticalLayout->addLayout(horizontalLayout_7);

        pushButton_6 = new QPushButton(frame);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(960, 0, 61, 41));
        pushButton_6->setStyleSheet(QString::fromUtf8("#pushButton_6:hover\n"
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
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(0, 45, 301, 91));
        label_4->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix2/logo3.png);"));
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(0, 0, 1081, 41));
        label_5->setStyleSheet(QString::fromUtf8("\n"
"background-image: url(:/new/prefix2/frame.jpg);"));
        label_5->raise();
        horizontalLayoutWidget_4->raise();
        verticalLayoutWidget->raise();
        label_4->raise();
        pushButton_6->raise();
        pushButton_7->raise();
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
        pushButton->setText(QCoreApplication::translate("TrackingWindow", "\345\244\204\347\220\206", nullptr));
        pushButton_2->setText(QCoreApplication::translate("TrackingWindow", "\350\277\224\345\233\236\350\217\234\345\215\225", nullptr));
        label->setText(QCoreApplication::translate("TrackingWindow", "\350\276\223\345\205\245\350\247\206\351\242\221\346\210\226\345\233\276\345\203\217", nullptr));
        pushButton_3->setText(QCoreApplication::translate("TrackingWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        label_2->setText(QCoreApplication::translate("TrackingWindow", "\351\200\211\346\213\251\350\276\223\345\207\272\346\240\274\345\274\217", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("TrackingWindow", ".fbx", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("TrackingWindow", ".vmd", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("TrackingWindow", ".fbx\345\222\214.vmd\346\226\207\344\273\266", nullptr));

        label_3->setText(QCoreApplication::translate("TrackingWindow", "\350\276\223\345\207\272\350\267\257\345\276\204", nullptr));
        pushButton_4->setText(QCoreApplication::translate("TrackingWindow", "\346\211\223\345\274\200\346\226\207\344\273\266\345\244\271", nullptr));
        pushButton_6->setText(QString());
        pushButton_7->setText(QString());
        label_4->setText(QString());
        label_5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TrackingWindow: public Ui_TrackingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACKINGWINDOW_H
