#include "fbxfile.h"
#include "ui_fbxfile.h"
#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif
fbxFile::fbxFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fbxFile)
{
    ui->setupUi(this);
    fmodel->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("文件名")));
    fmodel->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("文件夹")));
    fmodel->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("大小")));
    fmodel->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("持续时间")));
    fmodel->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("分辨率")));
       //利用setModel()方法将数据模型与QTableView绑定
    ui->tableView->setModel(fmodel);
    ui->lineEdit->setEnabled(false);


    ui->tableView->verticalHeader()->setVisible(false);
}

fbxFile::~fbxFile()
{
    delete ui;
}
void fbxFile::on_pushButton_close_clicked()
{
    this->close();
}
void fbxFile::fileData(QString fname)
{
    ui->lineEdit->setText(fname);
}
void fbxFile::on_pushButton_openfile_clicked()
{

        QString fileName;
        fileName=QFileDialog::getOpenFileName(this,tr("open video files"),"",tr("Videos Or Images (*.avi *.mp4 *.mpg *.png *.jpg)"));
        //ui->lineEdit->setText(fileName);

        fmodel->setItem(row, 0, new QStandardItem(fileName));
        row++;

}

void fbxFile::on_pushButton_del_clicked()
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
       fmodel->removeRow(r.key());
    }
    row--;
}

void fbxFile::on_pushButton_delAll_clicked()
{
     fmodel->removeRows(0,fmodel->rowCount());
     row=0;
}
void fbxFile::on_pushButton_change_clicked()
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

void fbxFile::on_pushButton_conf_clicked()
{
    emit toMain(fmodel);
    fmodel->removeRows(0,fmodel->rowCount());
    row=0;
    this->close();
}
