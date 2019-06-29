#include "dialogmenu.h"
#include <QApplication>
#include <QFile>
#include <QFrame>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*
    QFrame *frame = new QFrame;
    frame->resize(400,700);
    QPixmap pixmap(":/Buttons/timg.jpg");
    QPalette   palette;
    palette.setBrush(frame->backgroundRole(),QBrush(pixmap));
    frame->setPalette(palette);

    frame->setAutoFillBackground(true);
    frame->show();
    */
    QFile qss(":/stylesheet.qss");
    if(qss.open(QFile::ReadOnly))
    {
        qDebug("open success");
        QString style=QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }
    else {
        qDebug("open failed");
    }
    DialogMenu d;
    d.show();
    return a.exec();
}
