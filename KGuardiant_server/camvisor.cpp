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
    cv::vector<int> params;
    cv::vector<uchar> compressed;

    params.push_back(CV_IMWRITE_JPEG_QUALITY);
    params.push_back(85);

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
        capture.set(CV_CAP_PROP_FPS, 30);
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

        //imshow("test",frame);
        cv::imencode(".jpg",frame,compressed,params);

        emit resultado(mat2ByteArray(cv::Mat(compressed)));
    }

    capture.release();
}

void CamVisor::stopTask(bool stop)
{
    this->stop = stop;
}

QByteArray CamVisor::mat2ByteArray(const cv::Mat &image)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray,QIODevice::WriteOnly);
    stream << image.type();
    stream << image.rows;
    stream << image.cols;
    const size_t data_size = image.cols * image.rows * image.elemSize();
    QByteArray data = QByteArray::fromRawData((const char*)image.ptr(),data_size);
    stream << data;
    return byteArray;
}
