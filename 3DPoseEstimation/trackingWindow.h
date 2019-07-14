#pragma once
#ifndef TRACKINGWINDOW_H
#define TRACKINGWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QStandardItemModel>
#include <QMouseEvent>
#include <QItemDelegate>
#include <QPainter>
#include <QPixmap>
#include <map>
#include <QProgressBar>
#include <QLayout>
#include <QItemSelectionModel>
#include "vmdfile.h"
#include "fbxfile.h"
#include "vffile.h"
extern std::multimap<int, QString> TotalInputFile;
#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif
class MyItemDelegate;
//class MyStandardItemModel;
namespace Ui {
class TrackingWindow;
}

class TrackingWindow : public QMainWindow
{
    Q_OBJECT

public:
    TrackingWindow(QWidget *parent = nullptr);
    ~TrackingWindow();
    void sendSlot();
	

private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_delAll_clicked();

    void on_pushButton_VMD_clicked();

    void on_pushButton_FBX_clicked();

    void on_pushButton_VF_clicked();

    void on_pushButton_path_clicked();

    void fromVMD(QStandardItemModel *vmodel,QString filepath);
    void fromFBX(QStandardItemModel *fmodel, QString filepath);
    void fromVF(QStandardItemModel *vfmodel, QString filepath);
    void on_pushButton_start_clicked();

	void view_select_check();

    void on_pushButton_help_clicked();

signals:
    void mySignal();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    Ui::TrackingWindow *ui;
    //TitleBar* m_titleWidget;
    vmdfile vmdW;
    fbxFile fbxW;
    vfFile vfW;
    bool m_move;
    QPoint m_startPoint;
    QPoint m_windowPoint;
	QStandardItemModel *model=new QStandardItemModel();
    QString outputFilePath;//存储保存路径
	//QString fileName;
    int totalrow=0;//插入的行数
	MyItemDelegate * delegate;//委托
	//QItemSelectionModel * md;
	std::vector<QProgressBar*> totalBar;
};

class MyItemDelegate :public QItemDelegate
{
public:
	MyItemDelegate(QObject * parent = 0);
	virtual ~MyItemDelegate() {};
	//void paint(QPainter * painter,
	//	const QStyleOptionViewItem & option,
	//	const QModelIndex & index) const;
	
private:
	
};/*
class MyStandardItemModel :public QStandardItemModel
{
public:
	MyStandardItemModel(QObject * parent = 0)
		:QStandardItemModel(parent) {}
	virtual ~MyStandardItemModel() {}
	QVariant data(const QModelIndex & index,
		int role = Qt::DisplayRole) const;
	QVariant headerData(int section,
		Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;
};*/
#endif // MAINWINDOW_H
