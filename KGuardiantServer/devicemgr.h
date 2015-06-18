#ifndef DEVICEMGR_H
#define DEVICEMGR_H

#include <QObject>
#include <QThread>
#include <configuracion.h>
#include <logger.h>


#include <opencv2/opencv.hpp>



class DeviceMgr : public QThread
{
    Q_OBJECT
public:
    explicit DeviceMgr(QObject *parent = 0);
    
    ~DeviceMgr();
private:

    Configuracion *settings;
    Logger *log;
    cv::VideoCapture *cam;
    cv::Mat cFrame;
    cv::Mat dFrame;
signals:
    void newImage(cv::Mat &cFrame);
    void newImage(cv::Mat &cFrame, cv::Mat &dFrame);
public slots:
    void requestImage();
    void run();
};

#endif // DEVICEMGR_H
