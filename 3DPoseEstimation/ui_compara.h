/********************************************************************************
** Form generated from reading UI file 'compara.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPARA_H
#define UI_COMPARA_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Compara
{
public:
    QFrame *frame;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_path;
    QPushButton *pushButton_2;
    QPushButton *pushButton_start;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *comboBox;
    QLabel *label_8;
    QPushButton *pushButton_path_2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QFrame *line;
    QLabel *label_preview1;
    QFrame *line_2;
    QSpacerItem *horizontalSpacer;
    QFrame *line_4;
    QLabel *label_path1;
    QFrame *line_3;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QFrame *line_5;
    QLabel *label_preview2;
    QFrame *line_7;
    QSpacerItem *horizontalSpacer_3;
    QFrame *line_6;
    QLabel *label_path2;
    QFrame *line_8;
    QFrame *line_9;
    QFrame *line_10;
    QFrame *line_11;
    QFrame *line_12;

    void setupUi(QDialog *Compara)
    {
        if (Compara->objectName().isEmpty())
            Compara->setObjectName(QString::fromUtf8("Compara"));
        Compara->resize(1101, 701);
        frame = new QFrame(Compara);
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
        pushButton_path = new QPushButton(frame);
        pushButton_path->setObjectName(QString::fromUtf8("pushButton_path"));
        pushButton_path->setGeometry(QRect(160, 190, 131, 41));
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
        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(820, 60, 101, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        pushButton_2->setFont(font1);
        pushButton_2->setStyleSheet(QString::fromUtf8("#pushButton_2{background-color: transparent;}\n"
"#pushButton_2:hover{border-image: url(:/new/prefix2/grey.png);}\n"
""));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/prefix2/return.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon3);
        pushButton_2->setIconSize(QSize(30, 30));
        pushButton_start = new QPushButton(frame);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));
        pushButton_start->setGeometry(QRect(470, 520, 101, 41));
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
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/new/prefix2/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_start->setIcon(icon4);
        pushButton_start->setIconSize(QSize(30, 30));
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
        comboBox->setGeometry(QRect(170, 65, 111, 22));
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
        label_8 = new QLabel(frame);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 70, 121, 16));
        label_8->setFont(font1);
        pushButton_path_2 = new QPushButton(frame);
        pushButton_path_2->setObjectName(QString::fromUtf8("pushButton_path_2"));
        pushButton_path_2->setGeometry(QRect(160, 370, 131, 41));
        sizePolicy.setHeightForWidth(pushButton_path_2->sizePolicy().hasHeightForWidth());
        pushButton_path_2->setSizePolicy(sizePolicy);
        pushButton_path_2->setFont(font);
        pushButton_path_2->setStyleSheet(QString::fromUtf8("#pushButton_path_2{background-color:transparent;}\n"
"#pushButton_path_2:hover{border-image: url(:/new/prefix2/grey.png);}\n"
""));
        pushButton_path_2->setIcon(icon2);
        pushButton_path_2->setIconSize(QSize(30, 30));
        horizontalLayoutWidget = new QWidget(frame);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(430, 580, 201, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font1);

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(horizontalLayoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setFont(font1);

        horizontalLayout->addWidget(lineEdit);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);

        horizontalLayout->addWidget(label_2);

        horizontalLayoutWidget_2 = new QWidget(frame);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(340, 140, 651, 131));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(5);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        line = new QFrame(horizontalLayoutWidget_2);
        line->setObjectName(QString::fromUtf8("line"));
        QFont font3;
        font3.setBold(false);
        font3.setWeight(50);
        line->setFont(font3);
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(1);
        line->setMidLineWidth(1);
        line->setFrameShape(QFrame::VLine);

        horizontalLayout_2->addWidget(line);

        label_preview1 = new QLabel(horizontalLayoutWidget_2);
        label_preview1->setObjectName(QString::fromUtf8("label_preview1"));
        label_preview1->setMinimumSize(QSize(129, 129));
        label_preview1->setMaximumSize(QSize(129, 129));
        label_preview1->setFont(font1);
        label_preview1->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_preview1);

        line_2 = new QFrame(horizontalLayoutWidget_2);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFont(font3);
        line_2->setFrameShadow(QFrame::Plain);
        line_2->setLineWidth(1);
        line_2->setMidLineWidth(1);
        line_2->setFrameShape(QFrame::VLine);

        horizontalLayout_2->addWidget(line_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        line_4 = new QFrame(horizontalLayoutWidget_2);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFont(font3);
        line_4->setFrameShadow(QFrame::Plain);
        line_4->setLineWidth(1);
        line_4->setMidLineWidth(1);
        line_4->setFrameShape(QFrame::VLine);

        horizontalLayout_2->addWidget(line_4);

        label_path1 = new QLabel(horizontalLayoutWidget_2);
        label_path1->setObjectName(QString::fromUtf8("label_path1"));
        label_path1->setMinimumSize(QSize(450, 0));
        label_path1->setMaximumSize(QSize(450, 16777215));
        label_path1->setFont(font1);

        horizontalLayout_2->addWidget(label_path1);

        line_3 = new QFrame(horizontalLayoutWidget_2);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFont(font3);
        line_3->setFrameShadow(QFrame::Plain);
        line_3->setLineWidth(1);
        line_3->setMidLineWidth(1);
        line_3->setFrameShape(QFrame::VLine);

        horizontalLayout_2->addWidget(line_3);

        horizontalLayoutWidget_3 = new QWidget(frame);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(340, 330, 651, 131));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setSpacing(5);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        line_5 = new QFrame(horizontalLayoutWidget_3);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFont(font3);
        line_5->setFrameShadow(QFrame::Plain);
        line_5->setLineWidth(1);
        line_5->setMidLineWidth(1);
        line_5->setFrameShape(QFrame::VLine);

        horizontalLayout_3->addWidget(line_5);

        label_preview2 = new QLabel(horizontalLayoutWidget_3);
        label_preview2->setObjectName(QString::fromUtf8("label_preview2"));
        label_preview2->setMinimumSize(QSize(129, 129));
        label_preview2->setMaximumSize(QSize(129, 129));
        label_preview2->setFont(font1);
        label_preview2->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_preview2);

        line_7 = new QFrame(horizontalLayoutWidget_3);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        line_7->setFont(font3);
        line_7->setFrameShadow(QFrame::Plain);
        line_7->setLineWidth(1);
        line_7->setMidLineWidth(1);
        line_7->setFrameShape(QFrame::VLine);

        horizontalLayout_3->addWidget(line_7);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        line_6 = new QFrame(horizontalLayoutWidget_3);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setFont(font3);
        line_6->setFrameShadow(QFrame::Plain);
        line_6->setLineWidth(1);
        line_6->setMidLineWidth(1);
        line_6->setFrameShape(QFrame::VLine);

        horizontalLayout_3->addWidget(line_6);

        label_path2 = new QLabel(horizontalLayoutWidget_3);
        label_path2->setObjectName(QString::fromUtf8("label_path2"));
        label_path2->setMinimumSize(QSize(450, 0));
        label_path2->setMaximumSize(QSize(450, 16777215));
        label_path2->setFont(font1);

        horizontalLayout_3->addWidget(label_path2);

        line_8 = new QFrame(horizontalLayoutWidget_3);
        line_8->setObjectName(QString::fromUtf8("line_8"));
        line_8->setFont(font3);
        line_8->setFrameShadow(QFrame::Plain);
        line_8->setLineWidth(1);
        line_8->setMidLineWidth(1);
        line_8->setFrameShape(QFrame::VLine);

        horizontalLayout_3->addWidget(line_8);

        line_9 = new QFrame(frame);
        line_9->setObjectName(QString::fromUtf8("line_9"));
        line_9->setGeometry(QRect(340, 320, 651, 20));
        line_9->setFrameShadow(QFrame::Plain);
        line_9->setMidLineWidth(1);
        line_9->setFrameShape(QFrame::HLine);
        line_10 = new QFrame(frame);
        line_10->setObjectName(QString::fromUtf8("line_10"));
        line_10->setGeometry(QRect(340, 450, 651, 20));
        line_10->setFrameShadow(QFrame::Plain);
        line_10->setMidLineWidth(1);
        line_10->setFrameShape(QFrame::HLine);
        line_11 = new QFrame(frame);
        line_11->setObjectName(QString::fromUtf8("line_11"));
        line_11->setGeometry(QRect(340, 260, 651, 20));
        line_11->setFrameShadow(QFrame::Plain);
        line_11->setMidLineWidth(1);
        line_11->setFrameShape(QFrame::HLine);
        line_12 = new QFrame(frame);
        line_12->setObjectName(QString::fromUtf8("line_12"));
        line_12->setGeometry(QRect(340, 130, 651, 20));
        line_12->setFrameShadow(QFrame::Plain);
        line_12->setMidLineWidth(1);
        line_12->setFrameShape(QFrame::HLine);
        label_6->raise();
        pushButton_6->raise();
        pushButton_7->raise();
        pushButton_path->raise();
        pushButton_2->raise();
        pushButton_start->raise();
        label_5->raise();
        comboBox->raise();
        label_8->raise();
        pushButton_path_2->raise();
        horizontalLayoutWidget->raise();
        horizontalLayoutWidget_2->raise();
        horizontalLayoutWidget_3->raise();
        line_9->raise();
        line_10->raise();
        line_11->raise();
        line_12->raise();

        retranslateUi(Compara);

        QMetaObject::connectSlotsByName(Compara);
    } // setupUi

    void retranslateUi(QDialog *Compara)
    {
        Compara->setWindowTitle(QApplication::translate("Compara", "Dialog", nullptr));
        pushButton_6->setText(QString());
        pushButton_7->setText(QString());
        pushButton_path->setText(QApplication::translate("Compara", "\351\200\211\346\213\251\350\247\206\351\242\221\344\270\200", nullptr));
        pushButton_2->setText(QApplication::translate("Compara", "\350\277\224\345\233\236\350\217\234\345\215\225", nullptr));
        pushButton_start->setText(QApplication::translate("Compara", "\345\257\271\346\257\224", nullptr));
        label_5->setText(QString());
        label_6->setText(QString());
        comboBox->setItemText(0, QApplication::translate("Compara", "OpenMMD", nullptr));
        comboBox->setItemText(1, QApplication::translate("Compara", "VNect", nullptr));

        label_8->setText(QApplication::translate("Compara", "\351\200\211\346\213\251\344\270\211\347\273\264\351\207\215\345\273\272\347\256\227\346\263\225", nullptr));
        pushButton_path_2->setText(QApplication::translate("Compara", "\351\200\211\346\213\251\350\247\206\351\242\221\344\272\214", nullptr));
        label->setText(QApplication::translate("Compara", "\345\207\206\347\241\256\347\216\207\357\274\232", nullptr));
        label_2->setText(QApplication::translate("Compara", "%", nullptr));
        label_preview1->setText(QApplication::translate("Compara", "\351\242\204\350\247\210\345\233\276", nullptr));
        label_path1->setText(QApplication::translate("Compara", "\350\247\206\351\242\221\346\226\207\344\273\266\350\267\257\345\276\204", nullptr));
        label_preview2->setText(QApplication::translate("Compara", "\351\242\204\350\247\210\345\233\276", nullptr));
        label_path2->setText(QApplication::translate("Compara", "\350\247\206\351\242\221\346\226\207\344\273\266\350\267\257\345\276\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Compara: public Ui_Compara {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPARA_H
