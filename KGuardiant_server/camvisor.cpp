#include "camvisor.h"
#include <QBuffer>


CamVisor::CamVisor(bool origin,cv::VideoCapture *capture)
{
    this->stop = false;
    this->origin = origin;
    this->capture = capture;
}

void CamVisor::run()
{   
    cv::Mat frame;
    cv::vector<int> params;
    cv::vector<uchar> compressed;

    params.push_back(CV_IMWRITE_JPEG_QUALITY);
    params.push_back(85);

    qDebug() << "Iniciando Visor !";
    while(!this->stop && capture->isOpened())
    {
        QThread::sleep(0.3);
        *capture >> frame;

        cv::imencode(".jpg",frame,compressed,params);
        emit resultado(mat2ByteArray(cv::Mat(compressed)));
    }

    qDebug() << "Visor Parado";

    //exec();
}

void CamVisor::stopTask(bool stop)
{
    qDebug() << "Parando Visor";
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

CamVisor::~CamVisor()
{
    qDebug() << "Destruyendo thread de camvisor";
}
