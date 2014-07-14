#include "camvisor.h"
#include <QBuffer>


CamVisor::CamVisor(bool origin)
{
    this->stop = false;
    this->origin = origin;
}

void CamVisor::run()
{   
    cv::Mat frame;
    cv::VideoCapture capture;
    QImage img;

    qDebug() << "Iniciando Visor !";
    if(origin)
    {
        capture.open(1);
    }else
    {
        capture.open(0);
    }

    if (capture.isOpened())
    {
        capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
        capture.set(CV_CAP_PROP_FRAME_WIDTH, 480);
        capture.set(CV_CAP_PROP_FPS, 10);
        qDebug() << "Cámara correcta!";
    }else
    {
        qDebug() << "Error o abrir a camara";
        emit error(1);
        return;
    }

    while(!this->stop)
    {
        capture >> frame;
        img = ASM::cvMatToQImage(frame);

        emit resultado(QByteArray((char *)img.bits(),img.byteCount()));
    }

    capture.release();
}

void CamVisor::stopTask(bool stop)
{
    this->stop = stop;
}
