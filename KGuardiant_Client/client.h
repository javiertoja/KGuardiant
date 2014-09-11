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
#include <QRect>
#include <QFrame>
#include <QPainter>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

#include "opencv/cv.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "qtOpencv/cvmatandqimage.h"
#include "ClickableLabel.h"

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
public slots:
    void clabel_mouse_pressed(QPoint punto);
    void clabel_mouse_released(QPoint released);

private slots:
    void readyRead();
    void on_btnConectar_clicked();
    void on_btnDesconectar_clicked();

    void on_btnVisorStart_clicked();

    void on_btnVisorStop_clicked();

private:
    QPixmap drawImage(const QImage *imagen);
    int minimun(int a1, int a2);
    void checkRois();
    ClickableLabel *clabel;
    Ui::Client  *ui;

    QTcpSocket  *socket;
    QDir        *dirConf;
    QSettings   *conf;
    QList<QRect> *rois;
    QList<QRect> *rois_user;
    QPoint origin;
};

#endif // CLIENT_H
