/********************************************************************************
** Form generated from reading UI file 'dialogmenu.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGMENU_H
#define UI_DIALOGMENU_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogMenu
{
public:
    QFrame *frame;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_5;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_2;

    void setupUi(QDialog *DialogMenu)
    {
        if (DialogMenu->objectName().isEmpty())
            DialogMenu->setObjectName(QString::fromUtf8("DialogMenu"));
        DialogMenu->resize(721, 471);
        DialogMenu->setMinimumSize(QSize(150, 0));
        DialogMenu->setStyleSheet(QString::fromUtf8("#DialogMenu{background-image: url(:/new/prefix2/fucc);}\n"
""));
        frame = new QFrame(DialogMenu);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 701, 451));
        frame->setStyleSheet(QString::fromUtf8("#frame{border-image: url(:/new/prefix2/fucc);}\n"
""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButton_3 = new QPushButton(frame);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(580, 0, 61, 41));
        pushButton_3->setStyleSheet(QString::fromUtf8("#pushButton_3\n"
"{\n"
"    background-color: transparent;\n"
"	border-color: transparent;\n"
"}\n"
"#pushButton_3:hover\n"
"{\n"
"     background-color: red;\n"
"}\n"
"	"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix2/Buttons/min.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_3->setIcon(icon);
        pushButton_3->setIconSize(QSize(30, 30));
        pushButton_4 = new QPushButton(frame);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(640, 0, 61, 41));
        pushButton_4->setStyleSheet(QString::fromUtf8("#pushButton_4{background-color: transparent;\n"
"border-color: transparent;}\n"
"#pushButton_4:hover\n"
"{\n"
"    background-color: red;\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix2/Buttons/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_4->setIcon(icon1);
        pushButton_4->setIconSize(QSize(30, 30));
        horizontalLayoutWidget = new QWidget(frame);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 120, 702, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 5);
        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(100);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(150, 10));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"font: 63 14pt \"Segoe UI Semibold\";"));

        horizontalLayout->addWidget(label_2);

        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(150, 10));
        label->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix2/welcome.png);\n"
"background-color: rgb(255, 255, 255);\n"
"background-repeat:none;"));

        horizontalLayout->addWidget(label);

        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(label_4);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(150, 0));
        label_3->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix2/logo.png);"));

        horizontalLayout->addWidget(label_3);

        label_5 = new QLabel(horizontalLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(100, 0));
        label_5->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(label_5);

        verticalLayoutWidget = new QWidget(frame);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(210, 220, 281, 151));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setStyleSheet(QString::fromUtf8("#pushButton{\n"
"	font: 75 14pt \"Microsoft YaHei UI\";\n"
"                   background-color:rgba(100,225,100,30);\n"
"                   border-style:outset;\n"
"                   border-width:4px;\n"
"                   border-radius:10px;\n"
"                   border-color:rgba(255,255,255,30);\n"
"                \n"
"                   color:rgba(0,0,0,100);\n"
"                   padding:6px;\n"
"                   }   \n"
"                   #pushButton:pressed{\n"
"                   background-color:rgba(100,255,100,200);\n"
"                   border-color:rgba(255,255,255,30);\n"
"                   border-style:inset;\n"
"                   color:rgba(0,0,0,100);\n"
"                   }    \n"
"                   #pushButton:hover{\n"
"                   background-color:rgba(100,255,100,100);\n"
"                   border-color:rgba(255,255,255,200);\n"
"                   color:rgba(0,0,0,200);\n"
"                   }\n"
""));

        verticalLayout->addWidget(pushButton);

        verticalSpacer = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        pushButton_2->setStyleSheet(QString::fromUtf8("#pushButton_2{\n"
"                   background-color:rgba(100,225,100,30);\n"
"                   border-style:outset;\n"
"                   border-width:4px;\n"
"                   border-radius:10px;\n"
"                   border-color:rgba(255,255,255,30);\n"
"                   font: 75 14pt \"Microsoft YaHei UI\";\n"
"                   color:rgba(0,0,0,100);\n"
"                   padding:6px;\n"
"                   }   \n"
"                   #pushButton_2:pressed{\n"
"                   background-color:rgba(100,255,100,200);\n"
"                   border-color:rgba(255,255,255,30);\n"
"                   border-style:inset;\n"
"                   color:rgba(0,0,0,100);\n"
"                   }    \n"
"                   #pushButton_2:hover{\n"
"                   background-color:rgba(100,255,100,100);\n"
"                   border-color:rgba(255,255,255,200);\n"
"                   color:rgba(0,0,0,200);\n"
"                   }\n"
""));

        verticalLayout->addWidget(pushButton_2);


        retranslateUi(DialogMenu);

        QMetaObject::connectSlotsByName(DialogMenu);
    } // setupUi

    void retranslateUi(QDialog *DialogMenu)
    {
        DialogMenu->setWindowTitle(QApplication::translate("DialogMenu", "Dialog", nullptr));
        pushButton_3->setText(QString());
        pushButton_4->setText(QString());
        label_2->setText(QString());
        label->setText(QString());
        label_4->setText(QString());
        label_3->setText(QString());
        label_5->setText(QString());
        pushButton->setText(QApplication::translate("DialogMenu", "\345\212\250\344\275\234\346\215\225\346\215\211", nullptr));
        pushButton_2->setText(QApplication::translate("DialogMenu", "\345\247\277\346\200\201\345\257\271\346\257\224", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogMenu: public Ui_DialogMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGMENU_H
