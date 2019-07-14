#include <videoPosePredictor3D.h>
#include "trackingWindow.h"
#include "ui_trackingWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include "FbxAPI.h"
#include "OpenGLAPI.h"
#include "vmdWriter.h"
#include <qprocess.h>
#include <string>

#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif


std::multimap<int, QString> TotalInputFile;



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
	delegate = new MyItemDelegate;
   // connect(m_titleWidget, SIGNAL(customShowMinWindow()), this, SLOT(showMinimized()));
    //connect(m_titleWidget, SIGNAL(customCloseWindow()), this, SLOT(close()));
    
	 //connect(ui->tableView, &QTableView::clicked,this,SLOT(view_select_check()));

	
     model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("预览")));
     model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("来源")));
     model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("输出/进度")));
        //利用setModel()方法将数据模型与QTableView绑定
     ui->tableView->setModel(model);
	 ui->tableView->setItemDelegate(delegate);
     ui->tableView->verticalHeader()->setVisible(false);
	 ui->tableView->setColumnWidth(0, 125);
	 ui->tableView->setColumnWidth(1, 500);
	 ui->tableView->setColumnWidth(2, 254);
	 ui->tableView->verticalHeader()->setSectionsClickable(false);
	 ui->tableView->verticalHeader()->setDefaultSectionSize(90);
	 ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	 ui->tableView->setIconSize(QSize(125, 75));
	 ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	 ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	
	 ui->pushButton_start->setDisabled(true);
	 ui->pushButton_del->setDisabled(true);
	 ui->pushButton_delAll->setDisabled(true);
	 
	 connect(ui->pushButton_2, &QPushButton::clicked, this, &TrackingWindow::sendSlot);
	 connect(&vmdW, SIGNAL(toMain(QStandardItemModel*,QString)), this, SLOT(fromVMD(QStandardItemModel*,QString)));
	 connect(&fbxW, SIGNAL(toMain(QStandardItemModel*, QString)), this, SLOT(fromFBX(QStandardItemModel*, QString)));
	 connect(&vfW, SIGNAL(toMain(QStandardItemModel*, QString)), this, SLOT(fromVF(QStandardItemModel*, QString)));
	 connect(ui->tableView->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex &,
		 const QModelIndex &)), this, SLOT(view_select_check()));

}

TrackingWindow::~TrackingWindow()
{
    delete ui;
}
void TrackingWindow::sendSlot()
{
    emit mySignal();
}

void TrackingWindow::mousePressEvent(QMouseEvent *event)
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

void TrackingWindow::mouseMoveEvent(QMouseEvent *event)
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
void TrackingWindow::mouseReleaseEvent(QMouseEvent *event)
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
	foreach(QModelIndex index, selected)
		rows.insert(index.row(), 0);
	QMapIterator<int, int> r(rows);
	r.toBack();
	while (r.hasPrevious()) {
		r.previous();
		model->removeRow(r.key());
	}
	if (model->rowCount() == 0)
	{
		ui->pushButton_del->setDisabled(true);
		ui->pushButton_delAll->setDisabled(true);

	}
	totalrow--;
}

void TrackingWindow::on_pushButton_delAll_clicked()
{
    model->removeRows(0,model->rowCount());
	totalrow =0;
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

    }
    else
    {
        vmdW.fileData(outputFilePath);
        fbxW.fileData(outputFilePath);
        vfW.fileData(outputFilePath);
    }
}

void TrackingWindow::fromVMD(QStandardItemModel *vmodel,QString filepath)
{
	outputFilePath = filepath;
	int row = vmodel->rowCount();
	for (int i = 0; i < row; i++)
	{
		QModelIndex index = vmodel->index(i, 0, QModelIndex());
		QModelIndex index1 = vmodel->index(i, 1, QModelIndex());
		QString str1 = index1.data().toString()+"/"+ index.data().toString();
		//fileName = str1;
		TotalInputFile.insert(make_pair(0, str1));
		cv::Mat frame;
		string s = str1.toStdString();
		cv::VideoCapture capture(s);
		capture.set(CV_CAP_PROP_POS_FRAMES, 0);
		if (!capture.grab()) {
			cout << "grab in opencv failed!" << endl;

		}
		capture >> frame;
		cv::cvtColor(frame, frame, CV_BGR2RGB);
		QImage frameImg = QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
		QImage img = frameImg.scaled(125, 75);
		QIcon *icon=new QIcon(QPixmap::fromImage(img));
		model->setItem(i + totalrow, 0, new QStandardItem(*icon,QString("")));
		model->setItem(i+totalrow, 1, new QStandardItem(str1));
		QVBoxLayout * layout = new QVBoxLayout();
		QLabel *vmdLabel = new QLabel(QString("->VMD"));
		QProgressBar *m_pConnectProBar = new QProgressBar;
		
		m_pConnectProBar->setRange(0, 100); //设置进度条最小值和最大值(取值范围)
		m_pConnectProBar->setValue(0);  //设置当前的运行值
		m_pConnectProBar->setAlignment(Qt::AlignVCenter);  // 对齐方式 
		m_pConnectProBar->setFixedSize(220, 25);   //进度条固定大小
		
		totalBar.push_back(m_pConnectProBar);
		layout->addWidget(vmdLabel);
		layout->addWidget(totalBar[i + totalrow]);
		layout->setContentsMargins(10, 20, 10, 20);
		QWidget *widget = new QWidget;
		widget->setLayout(layout);
		ui->tableView->setIndexWidget(model->index(i + totalrow, 2), widget);
	}
	totalrow += row;
	if (!TotalInputFile.empty())
	{
		ui->pushButton_start->setDisabled(false);
		ui->pushButton_delAll->setDisabled(false);
	}
}
void TrackingWindow::fromFBX(QStandardItemModel *fmodel,QString filepath)
{
	outputFilePath = filepath;
	int row = fmodel->rowCount();
	for (int i = 0; i < row; i++)
	{
		QModelIndex index = fmodel->index(i, 0, QModelIndex());
		QModelIndex index1 = fmodel->index(i, 1, QModelIndex());
		QString str1 = index1.data().toString() + "/" + index.data().toString();
		//fileName = str1;
		TotalInputFile.insert(make_pair(1, str1));
		cv::Mat frame;
		string s = str1.toStdString();
		cv::VideoCapture capture(s);
		capture.set(CV_CAP_PROP_POS_FRAMES, 0);
		if (!capture.grab()) {
			cout << "grab in opencv failed!" << endl;

		}
		capture >> frame;
		cv::cvtColor(frame, frame, CV_BGR2RGB);
		QImage frameImg = QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
		QImage img = frameImg.scaled(125, 75);
		QIcon *icon = new QIcon(QPixmap::fromImage(img));
		model->setItem(i + totalrow, 0, new QStandardItem(*icon, QString("")));
		model->setItem(i + totalrow, 1, new QStandardItem(str1));
		QVBoxLayout * layout = new QVBoxLayout();
		QLabel *vmdLabel = new QLabel(QString("->FBX"));
		QProgressBar *m_pConnectProBar = new QProgressBar;

		m_pConnectProBar->setRange(0, 100); //设置进度条最小值和最大值(取值范围)
		m_pConnectProBar->setValue(0);  //设置当前的运行值
		m_pConnectProBar->setAlignment(Qt::AlignVCenter);  // 对齐方式 
		m_pConnectProBar->setFixedSize(220, 25);   //进度条固定大小

		totalBar.push_back(m_pConnectProBar);
		layout->addWidget(vmdLabel);
		layout->addWidget(totalBar[i + totalrow]);
		layout->setContentsMargins(10, 20, 10, 20);
		QWidget *widget = new QWidget;
		widget->setLayout(layout);
		ui->tableView->setIndexWidget(model->index(i + totalrow, 2), widget);
	}
	totalrow += row;
	if (!TotalInputFile.empty())
	{
		ui->pushButton_start->setDisabled(false);
		ui->pushButton_delAll->setDisabled(false);
	}
}
void TrackingWindow::fromVF(QStandardItemModel *vfmodel, QString filepath)
{
	outputFilePath = filepath;
	int row = vfmodel->rowCount();
	for (int i = 0; i < row; i++)
	{
		QModelIndex index = vfmodel->index(i, 0, QModelIndex());
		QModelIndex index1 = vfmodel->index(i, 1, QModelIndex());
		QString str1 = index1.data().toString() + "/" + index.data().toString();
		//fileName = str1;
		TotalInputFile.insert(make_pair(2, str1));
		cv::Mat frame;
		string s = str1.toStdString();
		cv::VideoCapture capture(s);
		capture.set(CV_CAP_PROP_POS_FRAMES, 0);
		if (!capture.grab()) {
			cout << "grab in opencv failed!" << endl;

		}
		capture >> frame;
		cv::cvtColor(frame, frame, CV_BGR2RGB);
		QImage frameImg = QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
		QImage img = frameImg.scaled(125, 75);
		QIcon *icon = new QIcon(QPixmap::fromImage(img));
		model->setItem(i + totalrow, 0, new QStandardItem(*icon, QString("")));
		model->setItem(i + totalrow, 1, new QStandardItem(str1));
		QVBoxLayout * layout = new QVBoxLayout();
		QLabel *vmdLabel = new QLabel(QString("->VMD+FBX"));
		QProgressBar *m_pConnectProBar = new QProgressBar;

		m_pConnectProBar->setRange(0, 100); //设置进度条最小值和最大值(取值范围)
		m_pConnectProBar->setValue(0);  //设置当前的运行值
		m_pConnectProBar->setAlignment(Qt::AlignVCenter);  // 对齐方式 
		m_pConnectProBar->setFixedSize(220, 25);   //进度条固定大小

		totalBar.push_back(m_pConnectProBar);
		layout->addWidget(vmdLabel);
		layout->addWidget(totalBar[i + totalrow]);
		layout->setContentsMargins(10, 20, 10, 20);
		QWidget *widget = new QWidget;
		widget->setLayout(layout);
		ui->tableView->setIndexWidget(model->index(i + totalrow, 2), widget);
	}
	totalrow += row;
	if (!TotalInputFile.empty())
	{
		ui->pushButton_start->setDisabled(false);
		ui->pushButton_delAll->setDisabled(false);
	}
}
void TrackingWindow::on_pushButton_start_clicked()
{
    //TODO：依次处理视频
	ui->pushButton_start->setDisabled(true);
	ui->pushButton_delAll->setDisabled(true);
	ui->pushButton_VMD->setDisabled(true);
	ui->pushButton_FBX->setDisabled(true);
	ui->pushButton_VF->setDisabled(true);
	ui->pushButton_path->setDisabled(true);
	ui->pushButton_2->setDisabled(true);
	if (outputFilePath == NULL || outputFilePath == "未选择输出路径")
	{
		QMessageBox::information(this, "提示", "未选择输出路径");
	}
	else
	{
		if (ui->comboBox->currentIndex() == 1)
		{
			mVideoPosePredictor3D predictor("./vnect_model.caffemodel", "./vnect_net.prototxt");
			//QMessageBox::information(this, "提示", "v");
			int i = 0;
			for (multimap<int, QString>::iterator it = TotalInputFile.begin();
				it != TotalInputFile.end();
				)
			{
				if (it->first == 0)
				{
					//输出vmd
					totalBar[i]->setValue(5);
					std::vector<std::vector<float>> output;
					totalBar[i]->setValue(7);

					std::string stdInputFileString = it->second.toStdString();
					totalBar[i]->setValue(11);

					predictor.predict(stdInputFileString, "./shader", "./model", output, false);
					totalBar[i]->setValue(26);

					std::string outputFileName = stdInputFileString.substr(stdInputFileString.rfind("/") + 1, stdInputFileString.rfind(".") - stdInputFileString.rfind("/") - 1);
					totalBar[i]->setValue(38);

					predictor.writePositionToJson(outputFilePath.toStdString() + "/" + outputFileName + ".json", output);
					totalBar[i]->setValue(58);

					vmdWriter writer(outputFilePath.toStdString() + "/" + outputFileName + ".json", "Hatsune Miku", false);
					totalBar[i]->setValue(74);

					writer.writeFile(outputFilePath.toStdString() + "/" + outputFileName + ".vmd");
					totalBar[i++]->setValue(100);

					if (ui->checkBox->isChecked() == true)
					{
						//渲染
						OpenGLAPI temp((outputFilePath.toStdString() + "/" + outputFileName + ".json").c_str());
						temp.singleVideo_Vnect();
					}
					model->removeRow(0);
					it = TotalInputFile.erase(it);
				}
				if (it->first == 1)
				{
					//输出fbx
					totalBar[i]->setValue(5);
					std::vector<std::vector<float>> output;
					totalBar[i]->setValue(11);

					std::string stdInputFileString = it->second.toStdString();
					totalBar[i]->setValue(18);

					predictor.predict(stdInputFileString, "./shader", "./model", output, false);
					totalBar[i]->setValue(30);

					std::string outputFileName = stdInputFileString.substr(stdInputFileString.rfind("/") + 1, stdInputFileString.rfind(".") - stdInputFileString.rfind("/") - 1);
					totalBar[i]->setValue(35);

					predictor.writePositionToJson(outputFilePath.toStdString() + "/" + outputFileName + ".json", output);
					totalBar[i]->setValue(49);

					FbxAPI test((outputFilePath.toStdString() + "/" + outputFileName + ".json").c_str());
					totalBar[i]->setValue(66);

					test.ProcessFrameVnect();
					totalBar[i]->setValue(82);

					test.Export((outputFilePath.toStdString() + "/" + outputFileName + ".FBX").c_str());
					totalBar[i]->setValue(86);

					test.Destory();
					totalBar[i++]->setValue(100);
					if (ui->checkBox->isChecked() == true)
					{
						OpenGLAPI temp((outputFilePath.toStdString() + "/" + outputFileName + ".json").c_str());
						temp.singleVideo_Vnect();
					}
					model->removeRow(0);
					it = TotalInputFile.erase(it);
				}
				if (it->first == 2)
				{
					//输出vmd+fbx
					totalBar[i]->setValue(5);

					std::vector<std::vector<float>> output;
					totalBar[i]->setValue(12);

					std::string stdInputFileString = it->second.toStdString();
					totalBar[i]->setValue(14);

					predictor.predict(stdInputFileString, "./shader", "./model", output, false);
					totalBar[i]->setValue(22);

					std::string outputFileName = stdInputFileString.substr(stdInputFileString.rfind("/") + 1, stdInputFileString.rfind(".") - stdInputFileString.rfind("/") - 1);
					totalBar[i]->setValue(26);

					predictor.writePositionToJson(outputFilePath.toStdString() + "/" + outputFileName + ".json", output);
					totalBar[i]->setValue(43);

					FbxAPI test((outputFilePath.toStdString() + "/" + outputFileName + ".json").c_str());
					totalBar[i]->setValue(46);

					test.ProcessFrameVnect();
					totalBar[i]->setValue(64);

					test.Export((outputFilePath.toStdString() + "/" + outputFileName + ".FBX").c_str());
					totalBar[i]->setValue(69);

					test.Destory();
					totalBar[i]->setValue(70);

					vmdWriter writer(outputFilePath.toStdString() + "/" + outputFileName + ".json", "Hatsune Miku", false);
					totalBar[i]->setValue(82);

					writer.writeFile(outputFilePath.toStdString() + "/" + outputFileName + ".vmd");
					totalBar[i++]->setValue(100);
					if (ui->checkBox->isChecked() == true)
					{
						OpenGLAPI temp((outputFilePath.toStdString() + "/" + outputFileName + ".json").c_str());
						temp.singleVideo_Vnect();
					}
					model->removeRow(0);
					it = TotalInputFile.erase(it);
				}

			}
		}
		else
		{
			int i = 0;
			//QMessageBox::information(this, "提示", "open");
			for (multimap<int, QString>::iterator it = TotalInputFile.begin();
				it != TotalInputFile.end();
				)
			{
				if (it->first == 0)
				{
					//输出vmd
					totalBar[i]->setValue(5);

					std::string stdInputFileString = it->second.toStdString();
					totalBar[i]->setValue(9);

					std::string outputFileName = stdInputFileString.substr(stdInputFileString.rfind("/") + 1, stdInputFileString.rfind(".") - stdInputFileString.rfind("/") - 1);
					totalBar[i]->setValue(13);
					
					QDir dir(outputFilePath+ "/"+QString::fromStdString(outputFileName));
					dir.mkdir(outputFilePath + "/" + QString::fromStdString(outputFileName));
					QString fullpath= outputFilePath + "/" + QString::fromStdString(outputFileName);
					std::string fullCommand = "python demo.py --inputpath=" + stdInputFileString + " --outputpath=" + fullpath.toStdString() + " --jsonpath=" + fullpath.toStdString() + "/" + outputFileName + ".json";
					totalBar[i]->setValue(18);

					QProcess::execute(QString::fromStdString(fullCommand));
					totalBar[i]->setValue(56);

					vmdWriter writer(fullpath.toStdString() + "/" + outputFileName + ".json", "Hatsune Miku",true);
					totalBar[i]->setValue(78);

					writer.writeFile(fullpath.toStdString() + "/" + outputFileName + ".vmd");
					totalBar[i++]->setValue(100);

					if (ui->checkBox->isChecked() == true)
					{
						OpenGLAPI temp((fullpath.toStdString() + "/" + outputFileName + ".json").c_str());
						temp.singleVideo_OpenMMD();
					}
					model->removeRow(0);
					it = TotalInputFile.erase(it);
				}
				if (it->first == 1)
				{
					//输出fbx
					totalBar[i]->setValue(5);

					std::string stdInputFileString = it->second.toStdString();
					totalBar[i]->setValue(9);

					std::string outputFileName = stdInputFileString.substr(stdInputFileString.rfind("/") + 1, stdInputFileString.rfind(".") - stdInputFileString.rfind("/") - 1);
					totalBar[i]->setValue(14);

					QString fullpath = outputFilePath + "/" + QString::fromStdString(outputFileName);
					QDir dir(fullpath);
					dir.mkdir(fullpath);

					std::string fullCommand = "python demo.py --inputpath=" + stdInputFileString + " --outputpath=" + fullpath.toStdString() + " --jsonpath=" + fullpath.toStdString() + "/" + outputFileName + ".json";
					totalBar[i]->setValue(19);

					QProcess::execute(QString::fromStdString(fullCommand));
					totalBar[i]->setValue(47);

					FbxAPI test((fullpath.toStdString() + "/" + outputFileName + ".json").c_str());
					totalBar[i]->setValue(66);

					test.ProcessFrameOpenMMD();
					totalBar[i]->setValue(77);

					test.Export((fullpath.toStdString() + "/" + outputFileName + ".FBX").c_str());
					totalBar[i]->setValue(85);

					test.Destory();
					totalBar[i++]->setValue(100);

					if (ui->checkBox->isChecked() == true)
					{
						OpenGLAPI temp((fullpath.toStdString() + "/" + outputFileName + ".json").c_str());
						temp.singleVideo_OpenMMD();
					}
					model->removeRow(0);
					it = TotalInputFile.erase(it);
				}
				if (it->first == 2)
				{
					//输出vmd+fbx
					totalBar[i]->setValue(4);

					std::string stdInputFileString = it->second.toStdString();
					totalBar[i]->setValue(13);

					std::string outputFileName = stdInputFileString.substr(stdInputFileString.rfind("/") + 1, stdInputFileString.rfind(".") - stdInputFileString.rfind("/") - 1);
					totalBar[i]->setValue(22);

					QString fullpath = outputFilePath + "/" + QString::fromStdString(outputFileName);
					QDir dir(fullpath);
					dir.mkdir(fullpath);

					std::string fullCommand = "python demo.py --inputpath=" + stdInputFileString + " --outputpath=" + fullpath.toStdString() + " --jsonpath=" + fullpath.toStdString() + "/" + outputFileName + ".json";
					totalBar[i]->setValue(25);

					QProcess::execute(QString::fromStdString(fullCommand));
					totalBar[i]->setValue(52);

					FbxAPI test((fullpath.toStdString() + "/" + outputFileName + ".json").c_str());
					totalBar[i]->setValue(66);

					test.ProcessFrameOpenMMD();
					totalBar[i]->setValue(69);

					test.Export((fullpath.toStdString() + "/" + outputFileName + ".FBX").c_str());
					totalBar[i]->setValue(73);

					test.Destory();
					totalBar[i]->setValue(75);

					vmdWriter writer(fullpath.toStdString() + "/" + outputFileName + ".json", "Hatsune Miku", true);
					totalBar[i]->setValue(82);

					writer.writeFile(fullpath.toStdString() + "/" + outputFileName + ".vmd");
					totalBar[i]->setValue(100);

					if (ui->checkBox->isChecked() == true)
					{
						OpenGLAPI temp((fullpath.toStdString() + "/" + outputFileName + ".json").c_str());
						temp.singleVideo_OpenMMD();
					}
					model->removeRow(0);
					it = TotalInputFile.erase(it);
				}
			}
		}
		if (TotalInputFile.empty())
		{
			ui->pushButton_start->setDisabled(true);
			ui->pushButton_delAll->setDisabled(true);
		}
		totalrow = 0;

	}
	ui->pushButton_VMD->setDisabled(false);
	ui->pushButton_FBX->setDisabled(false);
	ui->pushButton_VF->setDisabled(false);
	ui->pushButton_path->setDisabled(false);
	ui->pushButton_2->setDisabled(false);
	/*
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
			OpenGLAPI temp((outputFilePath.toStdString() + "/" + outputFileName + ".json").c_str());
			temp.singleVideo_Vnect();
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
			test.ProcessFrameOpenMMD();
			test.Export((outputFilePath.toStdString() + "/" + outputFileName + ".FBX").c_str());
			test.Destory();
			
			OpenGLAPI temp((outputFilePath.toStdString() + "/" + outputFileName + ".json").c_str());
			temp.singleVideo_OpenMMD();
		}
		
	}
	*/
}

void TrackingWindow::view_select_check()
{
	ui->pushButton_del->setDisabled(false);
}
MyItemDelegate::MyItemDelegate(QObject * parent)
	:QItemDelegate(parent)
{
	
}
/*
void MyItemDelegate::paint(QPainter * painter,
	const QStyleOptionViewItem & option,
	const QModelIndex & index) const
{
	if (index.column() != 0) {
		QItemDelegate::paint(painter, option, index);
		return;
	}
	const QAbstractItemModel * model = index.model();
	QVariant var = model->data(index, Qt::CheckStateRole);
	if (var.isNull()) var = false;
	const QPixmap & star = QPixmap(":/new/prefix2/VMD.png");

	int width = star.width();
	int height = star.height();
	QRect rect = option.rect;
	int x = rect.x() + rect.width() / 2 - width / 2;
	int y = rect.y() + rect.height() / 2 - height / 2;

	painter->drawPixmap(x, y, star);
	
	cv::Mat frame;
	string s = vmdInputPath[0].toStdString();
	cv::VideoCapture capture(s);
	capture.set(CV_CAP_PROP_POS_FRAMES, 0);
	if (!capture.grab()) {
		cout << "grab in opencv failed!" << endl;
		
	}
	capture >> frame;

	cv::cvtColor(frame, frame, CV_BGR2RGB);
	QImage frameImg = QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
	QImage img = frameImg.scaled(125, 75);
	if (index.column() != 0)
	{
		return QItemDelegate::paint(painter, option, index);
	}
	//保存一下原本的painter便于操作完后恢复，减少影响
	painter->save();
	if (index.column() == 0)
	{//第一栏设置图片
		int width = img.width();
		int height = img.height();
		QRect rect = option.rect;
		int x = rect.x() + rect.width() / 2 - width / 2;
		int y = rect.y() + rect.height() / 2 - height / 2;
		painter->drawImage(x,y, img);
	}

}
*/
/*
QVariant MyStandardItemModel::data(const QModelIndex &index, int role) const
{
	int column = index.column();

	if (role == Qt::DisplayRole && column != 0)
		return column + 1;
	if (role == Qt::ToolTipRole && column == 0)
		return tr("love");
	return QStandardItemModel::data(index, role);

}
QVariant MyStandardItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (section == 0 && orientation == Qt::Horizontal) {
		if (role == Qt::DecorationRole)
			//return QIcon(":/favourite.png");
		if (role == Qt::DisplayRole)
			return "";
		if (role == Qt::ToolTipRole)
			return tr("love");
	}
	return QStandardItemModel::headerData(section, orientation, role);

	

}*/

void TrackingWindow::on_pushButton_help_clicked()
{
    QMessageBox::information(this, "使用帮助", QString("1. 输入视频中目标人物所占画面比例要合适，亮度要适中，画面没有严重抖动，至少要达到人物在画面中是清晰的。\n")+
                                QString("2. 较亮灯光环境下，目标人物距离摄像头2-5米时，检测效果较好。\n")+
                                QString("3. 视频画面中只能有目标人物一个人出现，且人物动作不能发生遮挡，目标人物需要全身出现在视频画面中。\n")+
           QString("4.Vnect算法对于背向摄像头动作，转向动作，以及遮挡情况准确率较差。\n")+
           QString("5.OpenMMD算法对于背向摄像头动作以及遮挡情况的准确率较差，但对于转向动作的处理较为准确。\n"));
}
