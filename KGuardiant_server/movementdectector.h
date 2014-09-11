#ifndef MOVEMENTDECTECTOR_H
#define MOVEMENTDECTECTOR_H

#include <QThread>
#include <QDebug>
#include <QDataStream>
#include <QByteArray>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "cvblob.h"

using namespace cv;
using namespace cvb;

class MovementDectector : public QThread
{
    Q_OBJECT
public:
    explicit MovementDectector(bool origin,cv::VideoCapture *capture);
    ~MovementDectector();
    void run();
    QByteArray mat2ByteArray(const cv::Mat &image);
signals:
    void resultado(QByteArray img);
    void error(int code);
public slots:
    void stopTask(bool stop);

private:
    cv::VideoCapture *capture;
    int stop;
    bool origin;
};

#endif // MOVEMENTDECTECTOR_H
