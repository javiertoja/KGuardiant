#ifndef MOVEMENTDETECTOR_H
#define MOVEMENTDETECTOR_H

#include <QObject>
#include <basedetector.h>
#include <logger.h>
#include <QList>
#include <QRect>
#include <QPoint>
#include <opencv2/opencv.hpp>


class MovementDetector : public BaseDetector
{
    Q_OBJECT
public:
    explicit MovementDetector(QObject *parent = 0);
    ~MovementDetector();
signals:
    
    void processedImg(QByteArray data);

public slots:

    void processImg(cv::Mat &cframe);
    void processImg(cv::Mat &cframe, cv::Mat &dFrame);

private:
    cv::BackgroundSubtractorMOG2 *bg;

    Logger *log;

    int thresh;
    int max_thresh;
    cv::RNG *rng;

    virtual QByteArray setup4Send(const cv::Mat image, QList<QRect> lstRec);
};

#endif // MOVEMENTDETECTOR_H
