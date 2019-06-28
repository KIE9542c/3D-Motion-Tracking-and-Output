#include <videoPosePredictor3D.h>
#include "trackingWindow.h"
#include "ui_trackingWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include "FbxAPI.h"

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
	inputFileName=QFileDialog::getOpenFileName(this, tr("Open video or image") ,"",tr("Videos or Images (*.avi *.mp4 *.mpg *.png *.jpg)"));

    ui->lineEdit->setText(inputFileName);
}

void TrackingWindow::on_pushButton_4_clicked()
{

	outputFileName = QFileDialog::getOpenFileName(this, tr("Output File"), "", tr("fbx or vmd (*.fbx *.vmd)"));
	ui->lineEdit_3->setText(inputFileName);

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
	mVideoPosePredictor3D predictor("./vnect_model.caffemodel", "./vnect_net.prototxt");
	std::vector<std::vector<float>> output;
	predictor.predict(inputFileName.toStdString(),"./shader","./model", output, false,true);
	std::string stdOutputFileString = outputFileName.toStdString();
	std::string dir = stdOutputFileString.substr(0, stdOutputFileString.rfind(".FBX"));
	predictor.writePositionToJson(dir+".json",output);
	FbxAPI test((dir+".json").c_str());
	test.ProcessFrameVnect();
	test.Export(stdOutputFileString.c_str());
	test.Destory();
		 
}
