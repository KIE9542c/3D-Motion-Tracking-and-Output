#pragma once
#ifndef DIALOGMENU_H
#define DIALOGMENU_H

#include <QDialog>
#include "trackingWindow.h"
#include <QMouseEvent>
//#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QtMath>
namespace Ui {
class DialogMenu;
}

class DialogMenu : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMenu(QWidget *parent = nullptr);
    ~DialogMenu();
    //void paintEvent(QPaintEvent *event);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();
public slots:
    void myDealSub();
private:
    Ui::DialogMenu *ui;
    TrackingWindow mwin;
    bool m_move;
    QPoint m_startPoint;
    QPoint m_windowPoint;
};

#endif // DIALOGMENU_H
