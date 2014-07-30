#ifndef KGUARDIANTCLIENT_H
#define KGUARDIANTCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "logger.h"
#include "camvisor.h"
#include "constants.h"
#include "opencv/cv.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

class KGuardiantClient : public QObject
{
    Q_OBJECT
public:
    explicit KGuardiantClient(qintptr descriptor,cv::VideoCapture *capture, QObject *parent = 0);

signals:
    void endAlgoritm(bool stop);
    void error(QTcpSocket::SocketError socketerror);
public slots:
    void connected();
    void disconnected();
    void readyRead();

    void resultAlgDetector(int number);
    void resultAlgVisor(QByteArray img);
    void errorAlg(int code);
private:
    cv::VideoCapture *capture;

    QTcpSocket *socket;
    int stop;
    qintptr socketDescriptor;
    CamVisor *camVisor;


};

#endif // KGUARDIANTCLIENT_H
