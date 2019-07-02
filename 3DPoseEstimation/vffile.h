#pragma once
#ifndef VFFILE_H
#define VFFILE_H
#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif
#include <QDialog>
#include <QFileDialog>
#include <QStandardItemModel>
#include "fbxfile.h"
#include "vmdfile.h"

namespace Ui {
class vfFile;
}

class vfFile : public QDialog
{
    Q_OBJECT

public:
    explicit vfFile(QWidget *parent = nullptr);
    ~vfFile();
     void fileData(QString fname);
private slots:
    void on_pushButton_close_clicked();

    void on_pushButton_openfile_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_delAll_clicked();

    void on_pushButton_change_clicked();
    void on_pushButton_conf_clicked();

signals:
    void toMain(QStandardItemModel*);
private:
    Ui::vfFile *ui;
    QStandardItemModel *vfmodel= new QStandardItemModel();
    int row=0;//插入数据的行数
    QString filePath;

};

#endif // VFFILE_H
