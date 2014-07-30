#ifndef KGUARDIANTSERVER_H
#define KGUARDIANTSERVER_H

#include <QTcpServer>
#include <QSettings>
#include <QDir>
#include "configuracion.h"
#include "logger.h"
#include "opencv/cv.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

class KGuardiantServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit KGuardiantServer(QObject *parent = 0);
    ~KGuardiantServer();
    void startServer();

signals:

public slots:

protected:
    void incomingConnection(qintptr socketDescriptor);
private:
    cv::VideoCapture capture;
};

#endif // KGUARDIANTSERVER_H
