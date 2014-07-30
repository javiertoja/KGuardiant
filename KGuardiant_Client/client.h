#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QDir>
#include <QSettings>
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>
#include <QImage>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

#include "opencv/cv.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "qtOpencv/cvmatandqimage.h"

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT
    
public:
    explicit Client(QWidget *parent = 0);
    ~Client();
    cv::Mat byteArray2Mat(const QByteArray &byteArray);
private slots:
    void readyRead();
    void on_btnStartVisor_clicked();
    void on_btnConectar_clicked();
    void on_btnStopVisor_clicked();

private:
    Ui::Client  *ui;

    QTcpSocket  *socket;
    QDir        *dirConf;
    QSettings   *conf;
};

#endif // CLIENT_H
