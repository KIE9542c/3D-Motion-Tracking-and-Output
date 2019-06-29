#ifndef VMDFILE_H
#define VMDFILE_H
#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif
#include <QDialog>
#include <QFileDialog>
#include <QStandardItemModel>
namespace Ui {
class vmdfile;
}

class vmdfile : public QDialog
{
    Q_OBJECT

public:
    explicit vmdfile(QWidget *parent = nullptr);
    ~vmdfile();
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
    Ui::vmdfile *ui;
    QStandardItemModel *vmodel= new QStandardItemModel();
    int row=0;//插入数据的行数
    QString filePath;
};

#endif // VMDFILE_H
