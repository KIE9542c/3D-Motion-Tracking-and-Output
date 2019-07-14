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
	void (Compara::*comSignal)() = &Compara::comSignal;
	// void (MainWindow::*funSignalParm)(int, QString) = &MainWindow::mySignalParm;
	void (DialogMenu::*comSlot)() = &DialogMenu::myComSub;
	//void (DialogMenu::*funSlotParm)(int, QString) = &DialogMenu::myDealSubParm;
	connect(&mcom, comSignal, this, comSlot);
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
void DialogMenu::myComSub()
{
    mcom.hide();
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    this->show();
}

void DialogMenu::on_pushButton_2_clicked()
{
    this->hide();
    QPropertyAnimation *animation = new QPropertyAnimation(&mcom,"windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    mcom.show();
}

void DialogMenu::on_pushButton_help_clicked()
{

	QMessageBox::information(this, "使用帮助", QString("1. 输入视频中目标人物所占画面比例要合适，亮度要适中，画面没有严重抖动，至少要达到人物在画面中是清晰的。\n") +
		QString("2. 较亮灯光环境下，目标人物距离摄像头2-5米时，检测效果较好。\n") +
		QString("3. 视频画面中只能有目标人物一个人出现，且人物动作不能发生遮挡，目标人物需要全身出现在视频画面中。\n") +
		QString("4.Vnect算法对于背向摄像头动作，转向动作，以及遮挡情况准确率较差。\n") +
		QString("5.OpenMMD算法对于背向摄像头动作以及遮挡情况的准确率较差，但对于转向动作的处理较为准确。\n"));
}
