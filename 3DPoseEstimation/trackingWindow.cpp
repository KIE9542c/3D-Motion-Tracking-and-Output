#include <videoPosePredictor3D.h>
#include "trackingWindow.h"
#include "ui_trackingWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include "FbxAPI.h"
#include <string>

#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif
//#include <opencv2/opencv.hpp>
//using namespace cv;
TrackingWindow::TrackingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrackingWindow)
{
    QStringList headers;
    headers << QStringLiteral("预览") << QStringLiteral("来源") << QStringLiteral("输出/进度");
    //ui->tableWidget->setHorizontalHeaderLabels(headers);


    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    //实例阴影shadow
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    QGraphicsDropShadowEffect *vshadow = new QGraphicsDropShadowEffect(this);
    QGraphicsDropShadowEffect *fshadow = new QGraphicsDropShadowEffect(this);
    QGraphicsDropShadowEffect *vfshadow = new QGraphicsDropShadowEffect(this);
       //设置阴影距离
    shadow->setOffset(0, 0);
       //设置阴影颜色
    shadow->setColor(Qt::black);
       //设置阴影圆角
    shadow->setBlurRadius(20);
       //给嵌套QWidget设置阴影
    //设置阴影距离
    vshadow->setOffset(0, 0);
    //设置阴影颜色
    vshadow->setColor(Qt::black);
    //设置阴影圆角
    vshadow->setBlurRadius(10);
    //给嵌套QWidget设置阴影
 //设置阴影距离
    fshadow->setOffset(0, 0);
 //设置阴影颜色
    fshadow->setColor(Qt::black);
 //设置阴影圆角
    fshadow->setBlurRadius(10);
 //给嵌套QWidget设置阴影
//设置阴影距离
    vfshadow->setOffset(0, 0);
//设置阴影颜色
    vfshadow->setColor(Qt::black);
//设置阴影圆角
    vfshadow->setBlurRadius(10);
//给嵌套QWidget设置阴影
    ui->frame->setGraphicsEffect(shadow);
    ui->pushButton_VMD->setGraphicsEffect(vshadow);
    ui->pushButton_FBX->setGraphicsEffect(fshadow);
    ui->pushButton_VF->setGraphicsEffect(vfshadow);

    //m_titleWidget = new TitleBar(this);

   // connect(m_titleWidget, SIGNAL(customShowMinWindow()), this, SLOT(showMinimized()));
    //connect(m_titleWidget, SIGNAL(customCloseWindow()), this, SLOT(close()));
     connect(ui->pushButton_2, &QPushButton::clicked, this, &TrackingWindow::sendSlot);
     connect(&vmdW,SIGNAL(toMain(QStandardItemModel*)),this,SLOT(fromVMD(QStandardItemModel*)));
     connect(&fbxW,SIGNAL(toMain(QStandardItemModel*)),this,SLOT(fromFBX(QStandardItemModel*)));
     connect(&vfW,SIGNAL(toMain(QStandardItemModel*)),this,SLOT(fromVF(QStandardItemModel*)));

     model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("预览")));
     model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("来源")));
     model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("输入/进度")));
        //利用setModel()方法将数据模型与QTableView绑定
     ui->tableView->setModel(model);
     ui->tableView->verticalHeader()->setVisible(false);
}

TrackingWindow::~TrackingWindow()
{
    delete ui;
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
void TrackingWindow::on_pushButton_6_clicked()
{
    this->showMinimized();
}

void TrackingWindow::on_pushButton_7_clicked()
{
    this->close();
}
void TrackingWindow::on_pushButton_del_clicked()
{
	//TODO:: 
    QItemSelectionModel *selections = ui->tableView->selectionModel();
        QModelIndexList selected = selections->selectedIndexes();
        QMap<int, int> rows;
        foreach (QModelIndex index, selected)
           rows.insert(index.row(), 0);
        QMapIterator<int, int> r(rows);
        r.toBack();
        while (r.hasPrevious()) {
               r.previous();
           model->removeRow(r.key());
        }
        row--;
}

void TrackingWindow::on_pushButton_delAll_clicked()
{
    model->removeRows(0,model->rowCount());
    row=0;
}

void TrackingWindow::on_pushButton_VMD_clicked()
{
    vmdW.setWindowModality(Qt::ApplicationModal);
    vmdW.show();
}

void TrackingWindow::on_pushButton_FBX_clicked()
{
    fbxW.setWindowModality(Qt::ApplicationModal);
    fbxW.show();
}

void TrackingWindow::on_pushButton_VF_clicked()
{
    vfW.setWindowModality(Qt::ApplicationModal);
    vfW.show();
}

void TrackingWindow::on_pushButton_path_clicked()
{
    QString saveName="output";//保存图片名字
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyyMMdd_hhmmss"); //设置显示格式
    outputFilePath = QFileDialog::getExistingDirectory(this,"");//获取文件夹路径
   // ui->lineEdit_3->setText(filePath);
    if(outputFilePath.isEmpty())
    {
        QMessageBox::information(this,"信息","保存失败");
    }
    else
    {
        vmdW.fileData(outputFilePath);
        fbxW.fileData(outputFilePath);
        vfW.fileData(outputFilePath);
    }
}
//需重写
void TrackingWindow::fromVMD(QStandardItemModel *vmodel)
{
    QModelIndex index=vmodel->index(0,0,QModelIndex());
    QString str1= index.data().toString();
    model->setItem(row, 0, new QStandardItem(str1));
    row++;
}
void TrackingWindow::fromFBX(QStandardItemModel *fmodel)
{
    QModelIndex index=fmodel->index(0,0,QModelIndex());
    QString str1= index.data().toString();
    model->setItem(row, 0, new QStandardItem(str1));
    row++;
}
void TrackingWindow::fromVF(QStandardItemModel *vfmodel)
{
    QModelIndex index=vfmodel->index(0,0,QModelIndex());
    QString str1= index.data().toString();
    model->setItem(row, 0, new QStandardItem(str1));
    row++;
}
void TrackingWindow::on_pushButton_start_clicked()
{
    //TODO：依次处理视频
	if (!fbxInputPath.empty()) {
		mVideoPosePredictor3D predictor("./vnect_model.caffemodel", "./vnect_net.prototxt");
		for (size_t i = 0; i < fbxInputPath.size(); i++)
		{
			std::vector<std::vector<float>> output;
			std::string stdInputFileString = fbxInputPath[i].toStdString();
			predictor.predict(stdInputFileString, "./shader", "./model", output, false);
			std::string outputFileName = stdInputFileString.substr(stdInputFileString.rfind("/") + 1, stdInputFileString.rfind(".") - stdInputFileString.rfind("/")-1);
			predictor.writePositionToJson(outputFilePath.toStdString()+"/" + outputFileName+ ".json", output);
			FbxAPI test((outputFilePath.toStdString()+"/" + outputFileName + ".json").c_str());
			test.ProcessFrameVnect();
			test.Export((outputFilePath.toStdString()+"/" + outputFileName + ".FBX").c_str());
			test.Destory();
		}
	}
	if (!vmdInputPath.empty())
	{
		for (size_t i = 0; i < vmdInputPath.size(); i++)
		{
			std::string stdInputFileString = vmdInputPath[i].toStdString();
			std::string outputFileName = stdInputFileString.substr(stdInputFileString.rfind("/") + 1, stdInputFileString.rfind(".") - stdInputFileString.rfind("/")-1);
			std::string fullCommand = "python demo.py --inputpath=" + stdInputFileString + " --outputpath=" + outputFilePath.toStdString() + " --jsonpath=" + outputFilePath.toStdString() + "/" + outputFileName + ".json";
			system(fullCommand.c_str());
			FbxAPI test((outputFilePath.toStdString() + "/" + outputFileName + ".json").c_str());
			test.ProcessFrameVnect();
			test.Export((outputFilePath.toStdString() + "/" + outputFileName + ".FBX").c_str());
			test.Destory();
		}
		
	}
}

void TrackingWindow::on_pushButton_stop_clicked()
{

}
