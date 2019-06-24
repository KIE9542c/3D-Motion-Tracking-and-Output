#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //m_titleWidget = new TitleBar(this);

   // connect(m_titleWidget, SIGNAL(customShowMinWindow()), this, SLOT(showMinimized()));
    //connect(m_titleWidget, SIGNAL(customCloseWindow()), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    QString fileName;
    fileName=QFileDialog::getOpenFileName(this,tr("打开视频文件"),"",tr("Videos (*.avi *.mp4 *.mpg)"));
    ui->lineEdit->setText(fileName);
}

void MainWindow::on_pushButton_4_clicked()
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

        QImage image(QSize(this->width(),this->height()),QImage::Format_ARGB32);
            image.fill("white");

        //将图片重新命名并保存至刚刚创建的文件夹里
        QString savePath=QString("%1//%2.jpg").arg(filePath).arg(saveName);
        image.save(savePath);//QImage保存方法
        QMessageBox::information(this,"信息","保存成功");
    }


}
