#pragma once
#ifndef FBXFILE_H
#define FBXFILE_H
#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif
#include <QDialog>
#include <QFileDialog>
#include <QStandardItemModel>
#include <vector>


extern std::vector<QString> fbxInputPath;
namespace Ui {
class fbxFile;
}

class fbxFile : public QDialog
{
    Q_OBJECT

public:
    explicit fbxFile(QWidget *parent = nullptr);
    ~fbxFile();
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
    Ui::fbxFile *ui;
    QStandardItemModel *fmodel= new QStandardItemModel();
    int row=0;//插入数据的行数
    QString filePath;

};

#endif // FBXFILE_H
