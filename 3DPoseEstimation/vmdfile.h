#pragma once
#ifndef VMDFILE_H
#define VMDFILE_H
#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif
#include <QDialog>
#include <QFileDialog>
#include <QStandardItemModel>
#include <vector>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <opencv\highgui.h>
#include <opencv2\highgui.hpp>
#include <QToolTip>
extern std::vector<QString> vmdInputPath;
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

	void view_select_check();
signals:
    void toMain(QStandardItemModel*, QString);
protected:
	//拖动窗口相关
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
private:
    Ui::vmdfile *ui;
    QStandardItemModel *vmodel= new QStandardItemModel();
    int row=0;//插入数据的行数
    QString filePath;
	//拖动窗口相关
	bool m_move;
	QPoint m_startPoint;
	QPoint m_windowPoint;
};

#endif // VMDFILE_H
