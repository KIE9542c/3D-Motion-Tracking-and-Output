#ifndef TRACKINGWINDOW_H
#define TRACKINGWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QStandardItemModel>
#include <QMouseEvent>
#include "vmdfile.h"
#include "fbxfile.h"
#include "vffile.h"
#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif
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

    void fromVMD(QStandardItemModel *vmodel);
    void fromFBX(QStandardItemModel *fmodel);
    void fromVF(QStandardItemModel *vfmodel);
    void on_pushButton_start_clicked();

    void on_pushButton_stop_clicked();

signals:
    void mySignal();
    void mySignalParm(int, QString);
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
    QStandardItemModel *model = new QStandardItemModel();
    QString filePath;//存储保存路径
    int row=0;//插入的行数
};

#endif // MAINWINDOW_H
