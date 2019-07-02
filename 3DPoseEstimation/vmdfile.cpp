#include "vmdfile.h"
#include "ui_vmdfile.h"
#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif

std::vector<QString> vmdInputPath;

vmdfile::vmdfile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vmdfile)
{
    ui->setupUi(this);
    vmodel->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("文件名")));
    vmodel->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("文件夹")));
    vmodel->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("大小")));
    vmodel->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("持续时间")));
    vmodel->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("分辨率")));
       //利用setModel()方法将数据模型与QTableView绑定
    ui->tableView->setModel(vmodel);
    ui->lineEdit->setEnabled(false);


    ui->tableView->verticalHeader()->setVisible(false);
}

vmdfile::~vmdfile()
{
    delete ui;
}


void vmdfile::on_pushButton_close_clicked()
{
    this->close();
}

void vmdfile::on_pushButton_openfile_clicked()
{

        QString fileName;
        fileName=QFileDialog::getOpenFileName(this,tr("open video files"),"",tr("Videos Or Images (*.avi *.mp4 *.mpg *.png *.jpg)"));
        //ui->lineEdit->setText(fileName);
		vmdInputPath.push_back(fileName);
        vmodel->setItem(row, 0, new QStandardItem(fileName));
        row++;

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
	   std::vector<QString>::iterator temp = vmdInputPath.begin();
	   *temp += r.key();
	   vmdInputPath.erase(temp);
    }
    row--;
}

void vmdfile::on_pushButton_delAll_clicked()
{
     vmodel->removeRows(0,vmodel->rowCount());
     row=0;
	 vmdInputPath.clear();
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
    emit toMain(vmodel);
    vmodel->removeRows(0,vmodel->rowCount());
    row=0;
    this->close();
}
