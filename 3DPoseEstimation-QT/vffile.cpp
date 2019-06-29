#include "vffile.h"
#include "ui_vffile.h"
#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif
vfFile::vfFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vfFile)
{
    ui->setupUi(this);
    vfmodel->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("文件名")));
    vfmodel->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("文件夹")));
    vfmodel->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("大小")));
    vfmodel->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("持续时间")));
    vfmodel->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("分辨率")));
       //利用setModel()方法将数据模型与QTableView绑定
    ui->tableView->setModel(vfmodel);
    ui->lineEdit->setEnabled(false);


    ui->tableView->verticalHeader()->setVisible(false);
}

vfFile::~vfFile()
{
    delete ui;
}
void vfFile::on_pushButton_close_clicked()
{
    this->close();
}

void vfFile::on_pushButton_openfile_clicked()
{

        QString fileName;
        fileName=QFileDialog::getOpenFileName(this,tr("open video files"),"",tr("Videos Or Images (*.avi *.mp4 *.mpg *.png *.jpg)"));
        //ui->lineEdit->setText(fileName);

        vfmodel->setItem(row, 0, new QStandardItem(fileName));
        row++;

}
void vfFile::fileData(QString fname)
{
    ui->lineEdit->setText(fname);
}
void vfFile::on_pushButton_del_clicked()
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
       vfmodel->removeRow(r.key());
    }
    row--;
}

void vfFile::on_pushButton_delAll_clicked()
{
     vfmodel->removeRows(0,vfmodel->rowCount());
     row=0;
}
void vfFile::on_pushButton_change_clicked()
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
