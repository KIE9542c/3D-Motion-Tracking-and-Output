#include "vmdfile.h"
#include "ui_vmdfile.h"
#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif

//std::vector<QString> vmdInputPath;

vmdfile::vmdfile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vmdfile)
{
    ui->setupUi(this);
    vmodel->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("文件名")));
    vmodel->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("文件夹")));
    vmodel->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("大小")));
    vmodel->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("持续时间")));
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlags(Qt::FramelessWindowHint);
	//实例阴影shadow
	QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
	//设置阴影距离
	shadow->setOffset(0, 0);
	//设置阴影颜色
	shadow->setColor(Qt::black);
	//设置阴影圆角
	shadow->setBlurRadius(20);
	ui->frame->setGraphicsEffect(shadow);
       //利用setModel()方法将数据模型与QTableView绑定
    ui->tableView->setModel(vmodel);
    ui->lineEdit->setEnabled(false);
	ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);



    ui->tableView->verticalHeader()->setVisible(false);
	ui->tableView->setColumnWidth(0, 300);
	ui->tableView->setColumnWidth(1, 250);
	ui->tableView->setColumnWidth(2, 74);
	ui->tableView->setColumnWidth(3, 74);
	ui->tableView->verticalHeader()->setSectionsClickable(false);
	ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

	ui->pushButton_del->setDisabled(true);
	ui->pushButton_delAll->setDisabled(true);

	connect(ui->tableView->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex &,
		const QModelIndex &)), this, SLOT(view_select_check()));
	
}

vmdfile::~vmdfile()
{
    delete ui;
}

void vmdfile::mousePressEvent(QMouseEvent *event)
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
void vmdfile::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		//移动中的鼠标位置相对于初始位置的相对位置.
		QPoint relativePos = event->globalPos() - m_startPoint;
		//然后移动窗体即可.
		this->move(m_windowPoint + relativePos);
	}
}
void vmdfile::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		//改变移动状态.
		m_move = false;
	}
}
void vmdfile::on_pushButton_close_clicked()
{
    this->close();
}

void vmdfile::on_pushButton_openfile_clicked()
{
	
	
        QString fileName;
		
        fileName=QFileDialog::getOpenFileName(this,tr("open video files"),"",tr("Videos(*.avi *.mp4 *.mpg)"));
		if (!fileName.isEmpty())
		{
			//ui->lineEdit->setText(fileName);
			//vmdInputPath.push_back(fileName);

			QFileInfo info(fileName);
			std::string s = fileName.toStdString();
			vmodel->setItem(row, 0, new QStandardItem(info.fileName()));
			vmodel->setItem(row, 1, new QStandardItem(info.absolutePath()));
			QString filesize;
			if (info.size() < 1024)
				filesize = QString::number(info.size()) + "B";
			if (info.size() >= 1024 && info.size() < 1024 * 1024)
				filesize = QString::number(info.size() / 1024) + "Kb";
			if (info.size() > 1024 * 1024)
				filesize = QString::number(info.size() / (1024 * 1024)) + "Mb";
			vmodel->setItem(row, 2, new QStandardItem(filesize));
			cv::VideoCapture capture(s);
			double fbs = capture.get(CV_CAP_PROP_FPS);
			double fnumber = capture.get(CV_CAP_PROP_FRAME_COUNT);
			int totalSecond = int(fnumber / fbs);
			vmodel->setItem(row, 3, new QStandardItem(QString::number(totalSecond / 60) + ":" + QString::number(totalSecond - totalSecond / 60 * 60)));
			row++;
			//if (!vmdInputPath.empty())
			ui->pushButton_delAll->setDisabled(false);
		}
}

void vmdfile::on_pushButton_del_clicked()
{
    QItemSelectionModel *selections = ui->tableView->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();
    QMap<int, int> rows;
    foreach (QModelIndex index, selected)
       rows.insert(index.row(), 0);
    QMapIterator<int, int> r(rows);
    r.toBack();
    while (r.hasPrevious()) {
           r.previous();
       vmodel->removeRow(r.key());
	   //std::vector<QString>::iterator temp = vmdInputPath.begin();
	  // *temp += r.key();
	   //vmdInputPath.erase(temp);
    }
	if (vmodel->rowCount() == 0)
	{
		ui->pushButton_del->setDisabled(true);
		ui->pushButton_delAll->setDisabled(true);
	}
    row--;
	
}

void vmdfile::on_pushButton_delAll_clicked()
{
     vmodel->removeRows(0,vmodel->rowCount());
     row=0;
	// vmdInputPath.clear();
	 ui->pushButton_del->setDisabled(true);
	 ui->pushButton_delAll->setDisabled(true);
}
void vmdfile::fileData(QString fname)
{
    ui->lineEdit->setText(fname);
}

void vmdfile::on_pushButton_change_clicked()
{
    QString saveName="output";//保存图片名字
    filePath = QFileDialog::getExistingDirectory(this,"");//获取文件夹路径
   // ui->lineEdit_3->setText(filePath);
    if(filePath.isEmpty())
    {
        //QMessageBox::information(this,"信息","保存失败");
    }
    else
    {
        ui->lineEdit->setText(filePath);
    }
}

void vmdfile::on_pushButton_conf_clicked()
{
	QString outpath;
	outpath = ui->lineEdit->text();
    emit toMain(vmodel, outpath);
    vmodel->removeRows(0,vmodel->rowCount());
    row=0;
    this->close();
}
void vmdfile::view_select_check()
{
	ui->pushButton_del->setDisabled(false);

}




