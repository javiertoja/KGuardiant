#ifndef CAMVISOR_H
#define CAMVISOR_H

#include <QThread>
#include <QDebug>
#include <QDataStream>
#include <QByteArray>
#include "opencv/cv.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

class CamVisor : public QThread
{
    Q_OBJECT
public:
    explicit CamVisor(bool origin);
    void run();
    QByteArray mat2ByteArray(const cv::Mat &image);
signals:
    void resultado(QByteArray img);
    void error(int code);
public slots:
    void stopTask(bool stop);

private:
    int stop;
    bool origin;
};

#endif // CAMVISOR_H
