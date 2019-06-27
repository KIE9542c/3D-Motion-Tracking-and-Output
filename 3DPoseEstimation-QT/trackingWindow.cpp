#include "trackingWindow.h"
#include "ui_trackingWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
//#include <opencv2/opencv.hpp>
//using namespace cv;
TrackingWindow::TrackingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrackingWindow)
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
    ui->frame->setGraphicsEffect(shadow);
    //m_titleWidget = new TitleBar(this);

   // connect(m_titleWidget, SIGNAL(customShowMinWindow()), this, SLOT(showMinimized()));
    //connect(m_titleWidget, SIGNAL(customCloseWindow()), this, SLOT(close()));
     connect(ui->pushButton_2, &QPushButton::clicked, this, &TrackingWindow::sendSlot);
}

TrackingWindow::~TrackingWindow()
{
    delete ui;
}

void TrackingWindow::on_pushButton_3_clicked()
{
    QString fileName;
    fileName=QFileDialog::getOpenFileName(this,tr("打开视频或图像"),"",tr("Videos Or Images (*.avi *.mp4 *.mpg *.png *.jpg)"));
    ui->lineEdit->setText(fileName);
}

void TrackingWindow::on_pushButton_4_clicked()
{

    QString dirPath;//创建文件夹路径
    QString filePath;//存储保存路径
    QString saveName="output";//保存图片名字
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyyMMdd_hhmmss"); //设置显示格式
    filePath = QFileDialog::getExistingDirectory(this,"");//获取文件夹路径
    ui->lineEdit_3->setText(filePath);
    if(filePath.isEmpty())
    {
        QMessageBox::information(this,"信息","保存失败");
    }
    else
    {
        //存储文件
        QImage image(QSize(this->width(),this->height()),QImage::Format_ARGB32);
            image.fill("white");

        //将图片重新命名并保存至刚刚创建的文件夹里
        QString savePath=QString("%1//%2.jpg").arg(filePath).arg(saveName);
        image.save(savePath);//QImage保存方法
        QMessageBox::information(this,"信息","保存成功");
    }


}
void TrackingWindow::sendSlot()
{
    emit mySignal();
    emit mySignalParm(300, QString::fromLocal8Bit("已经切换到主窗口"));
}
void TrackingWindow::mousePressEvent(QMouseEvent *event)
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
void TrackingWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        //移动中的鼠标位置相对于初始位置的相对位置.
        QPoint relativePos = event->globalPos() - m_startPoint;
        //然后移动窗体即可.
        this->move(m_windowPoint + relativePos );
    }
}
void TrackingWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //改变移动状态.
        m_move = false;
    }
}

void TrackingWindow::on_pushButton_clicked()
{
    //处理视频的代码api
}
