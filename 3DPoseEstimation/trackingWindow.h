#ifndef TRACKINGWINDOW_H
#define TRACKINGWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>

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
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();
    void on_pushButton_clicked();

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
    bool m_move;
    QPoint m_startPoint;
    QPoint m_windowPoint;
	QString fileName;
};

#endif // MAINWINDOW_H
