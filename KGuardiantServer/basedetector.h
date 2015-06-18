#ifndef BASEDETECTOR_H
#define BASEDETECTOR_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QByteArray>
#include <logger.h>

class BaseDetector : public QThread
{
    Q_OBJECT
public:
    explicit BaseDetector(QObject *parent = 0);
    
    void run();
signals:
    
    void processedImg(QByteArray data);

public slots:
    
    virtual void processImg();

protected:
    QString name;
    Logger *log;

    virtual QByteArray setup4Send();
};

#endif // BASEDETECTOR_H
