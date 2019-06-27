#include "dialogmenu.h"
#include "ui_dialogmenu.h"
#include <QGraphicsDropShadowEffect>
DialogMenu::DialogMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMenu)
{

    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this); 
    //实例阴影shadow
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
       //设置阴影距离
    shadow->setOffset(0, 0);
       //设置阴影颜色
    shadow->setColor(Qt::black);
       //设置阴影圆角
    shadow->setBlurRadius(20);
       //给嵌套QWidget设置阴影
    //shadow_effect->setOffset(-5, 5);
    //shadow_effect->setColor(Qt::gray);
    //shadow_effect->setBlurRadius(8);
    ui->frame->setGraphicsEffect(shadow);
       //给垂直布局器设置边距(此步很重要, 设置宽度为阴影的宽度)
    //ui->lay_bg->setMargin(24);
    void (TrackingWindow::*mySignal)() = &TrackingWindow::mySignal;
      // void (MainWindow::*funSignalParm)(int, QString) = &MainWindow::mySignalParm;
    void (DialogMenu::*funSlot)() = &DialogMenu::myDealSub;
       //void (DialogMenu::*funSlotParm)(int, QString) = &DialogMenu::myDealSubParm;
    connect(&mwin, mySignal, this, funSlot);
       //connect(sw, funSignalParm, this, funSlotParm);
}
DialogMenu::~DialogMenu()
{
    delete ui;
}

void DialogMenu::on_pushButton_clicked()
{
    this->hide();
    QPropertyAnimation *animation = new QPropertyAnimation(&mwin,"windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    mwin.show();
}

void DialogMenu::on_pushButton_3_clicked()
{
    this->showMinimized();
}

void DialogMenu::on_pushButton_4_clicked()
{
    this->close();
}
void DialogMenu::mousePressEvent(QMouseEvent *event)
{
    //当鼠标左键点击时.
    if (event->button() == Qt::LeftButton)
    {
        m_move = true;
        //记录鼠标的世界坐标.
        m_startPoint = event->globalPos();
        //记录窗体的世界坐标.
        m_windowPoint = this->frameGeometry().topLeft();
    }
}
void DialogMenu::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        //移动中的鼠标位置相对于初始位置的相对位置.
        QPoint relativePos = event->globalPos() - m_startPoint;
        //然后移动窗体即可.
        this->move(m_windowPoint + relativePos );
    }
}
void DialogMenu::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //改变移动状态.
        m_move = false;
    }
}
void DialogMenu::myDealSub()
{
    mwin.hide();
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    this->show();
}
