#ifndef CAMVISOR_H
#define CAMVISOR_H

#include <QThread>
#include <QDebug>
#include "opencv/cv.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "asmopencv.h"

class CamVisor : public QThread
{
    Q_OBJECT
public:
    explicit CamVisor(bool origin);
    void run();

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
