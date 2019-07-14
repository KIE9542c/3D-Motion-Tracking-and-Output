#include <videoPosePredictor3D.h>
#include "compara.h"
#include "ui_compara.h"
#include "OpenGLAPI.h"
#include <qprocess.h>


Compara::Compara(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Compara)
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

    connect(ui->pushButton_2, &QPushButton::clicked, this, &Compara::sendSlot);
}

Compara::~Compara()
{
    delete ui;
}
void Compara::sendSlot()
{
    emit comSignal();
}
void Compara::mousePressEvent(QMouseEvent *event)
{
    //当鼠标左键点击时.
    if (event->button() == Qt::LeftButton)
    {
        if (ui->label_6->geometry().contains(this->mapFromGlobal(QCursor::pos())))
        {
            m_move = true;
            //记录鼠标的世界坐标.
            m_startPoint = event->globalPos();
            //记录窗体的世界坐标.
            m_windowPoint = this->frameGeometry().topLeft();
        }

    }
}

void Compara::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if (ui->label_6->geometry().contains(this->mapFromGlobal(QCursor::pos())))
        {
            //移动中的鼠标位置相对于初始位置的相对位置.
            QPoint relativePos = event->globalPos() - m_startPoint;
            //然后移动窗体即可.
            this->move(m_windowPoint + relativePos);
        }
    }
}
void Compara::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (ui->label_6->geometry().contains(this->mapFromGlobal(QCursor::pos())))
        {
            //改变移动状态.
            m_move = false;
        }
    }
}


void Compara::on_pushButton_path_clicked()
{

	//文件一
	fileName1 = QFileDialog::getOpenFileName(this, tr("open video files"), "", tr("Videos(*.avi *.mp4 *.mpg)"));
	//ui->lineEdit->setText(fileName);
	if (!fileName1.isEmpty())
	{

		cv::Mat frame;
		std::string s = fileName1.toStdString();
		cv::VideoCapture capture(s);
		capture.set(CV_CAP_PROP_POS_FRAMES, 0);
		if (!capture.grab()) {


		}
		capture >> frame;
		cv::cvtColor(frame, frame, CV_BGR2RGB);
		QImage frameImg = QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
		QImage img = frameImg.scaled(125, 75);
		ui->label_preview1->setText("");
		ui->label_preview1->setPixmap(QPixmap::fromImage(img));
		ui->label_path1->setText(fileName1);
		//QFileInfo info(fileName1);
		//std::string s = fileName1.toStdString();
	}

}

void Compara::on_pushButton_path_2_clicked()
{
	//文件二
	fileName2 = QFileDialog::getOpenFileName(this, tr("open video files"), "", tr("Videos(*.avi *.mp4 *.mpg)"));
	//ui->lineEdit->setText(fileName);
	if (!fileName2.isEmpty())
	{
		cv::Mat frame;
		std::string s = fileName2.toStdString();
		cv::VideoCapture capture(s);
		capture.set(CV_CAP_PROP_POS_FRAMES, 0);
		if (!capture.grab()) {


		}
		capture >> frame;
		cv::cvtColor(frame, frame, CV_BGR2RGB);
		QImage frameImg = QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
		QImage img = frameImg.scaled(125, 75);
		ui->label_preview2->setText("");
		ui->label_preview2->setPixmap(QPixmap::fromImage(img));
		ui->label_path2->setText(fileName2);
	}
	//QFileInfo info(fileName2);
	//std::string s = fileName.toStdString();
}

void Compara::on_pushButton_start_clicked()
{
	//TODO：开始对比fileName1和fileName2
	if (fileName1.isEmpty() || fileName2.isEmpty())
	{
		QMessageBox::information(this, "提示", "请选择两个视频文件");
	}
	else
	{
		if (ui->comboBox->currentIndex() == 0)
		{
			//openmmd
			//fileName1
			std::string fileName1_short = fileName1.toStdString().substr(fileName1.toStdString().rfind("/") + 1, fileName1.toStdString().rfind(".") - fileName1.toStdString().rfind("/") - 1);
			std::string jsonPath1 = "./temp/" + fileName1_short + ".json";
			std::string fullCommand = "python demo.py --inputpath=" + fileName1.toStdString() + " --outputpath=./temp" + " --jsonpath=" + jsonPath1;
			QProcess::execute(QString::fromStdString(fullCommand));

			//fileName2
			std::string fileName2_short = fileName2.toStdString().substr(fileName2.toStdString().rfind("/") + 1, fileName2.toStdString().rfind(".") - fileName2.toStdString().rfind("/") - 1);
			std::string jsonPath2 = "./temp2/" + fileName2_short + ".json";
			fullCommand = "python demo.py --inputpath=" + fileName2.toStdString() + " --outputpath=./temp2" + " --jsonpath=" + jsonPath2;
			QProcess::execute(QString::fromStdString(fullCommand));

			//opengl动画
			OpenGLAPI openglapi(jsonPath1.c_str(), jsonPath2.c_str());
			openglapi.doubleVideo_OpenMMD();
			double accurate = openglapi.getMotionContrastor().getcontrastPoint();
			ui->lineEdit->setText(QString::number(accurate, 10, 2));
		}
		if (ui->comboBox->currentIndex() == 1)
		{
			//vnect
			mVideoPosePredictor3D predictor2("./vnect_model.caffemodel", "./vnect_net.prototxt");
			std::vector<std::vector<float>> output;
			//fileName1
			predictor2.predict(fileName1.toStdString(), "./shader", "./model", output, false);
			std::string fileName1_short = fileName1.toStdString().substr(fileName1.toStdString().rfind("/") + 1, fileName1.toStdString().rfind(".") - fileName1.toStdString().rfind("/") - 1);
			std::string jsonPath1 = "./temp/" + fileName1_short + ".json";
			predictor2.writePositionToJson(jsonPath1, output);
			output.clear();
			//fileName2
			predictor2.predict(fileName2.toStdString(), "./shader", "./model", output, false);
			std::string fileName2_short = fileName2.toStdString().substr(fileName2.toStdString().rfind("/") + 1, fileName2.toStdString().rfind(".") - fileName2.toStdString().rfind("/") - 1);
			std::string jsonPath2 = "./temp/" + fileName2_short + ".json";
			predictor2.writePositionToJson(jsonPath2, output);
			//opengl动画
			OpenGLAPI openglapi(jsonPath1.c_str(), jsonPath2.c_str());
			openglapi.doubleVideo_Vnect();
			double accurate = openglapi.getMotionContrastor().getcontrastPoint();
			ui->lineEdit->setText(QString::number(accurate, 10, 2));
		}
	}
}

void Compara::on_pushButton_6_clicked()
{
    this->showMinimized();
}

void Compara::on_pushButton_7_clicked()
{
    this->close();
}

void Compara::on_pushButton_help_clicked()
{
	QMessageBox::information(this, "使用帮助", QString("1. 输入视频中目标人物所占画面比例要合适，亮度要适中，画面没有严重抖动，至少要达到人物在画面中是清晰的。\n") +
		QString("2. 较亮灯光环境下，目标人物距离摄像头2-5米时，检测效果较好。\n") +
		QString("3. 视频画面中只能有目标人物一个人出现，且人物动作不能发生遮挡，目标人物需要全身出现在视频画面中。\n") +
		QString("4.Vnect算法对于背向摄像头动作，转向动作，以及遮挡情况准确率较差。\n") +
		QString("5.OpenMMD算法对于背向摄像头动作以及遮挡情况的准确率较差，但对于转向动作的处理较为准确。\n"));
}
