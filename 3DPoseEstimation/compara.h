#ifndef COMPARA_H
#define COMPARA_H

#include <QDialog>
#include <QFileDialog>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <QMessageBox>
#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif
namespace Ui {
class Compara;
}

class Compara : public QDialog
{
    Q_OBJECT

public:
    explicit Compara(QWidget *parent = nullptr);
    ~Compara();
    void sendSlot();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void on_pushButton_path_clicked();

    void on_pushButton_path_2_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_help_clicked();

signals:
    void comSignal();
private:
    Ui::Compara *ui;
	QString fileName1;
	QString fileName2;
    bool m_move;
    QPoint m_startPoint;
    QPoint m_windowPoint;
};

#endif // COMPARA_H
