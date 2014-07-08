#ifndef MOVEMENTDETECTOR_H_
#define MOVEMENTDETECTOR_H_

#include "algorithmbase.h"
#include "constants.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <iostream>
#include "cvblob.h"
#include "logger.h"

typedef std::vector<cv::Mat> ImagesType;
typedef std::vector<std::vector<cv::Point> > ContoursType;

using namespace cv;
using namespace std;
using namespace cvb;

class MovementDetector: public AlgorithmBase {

private:
    cv::Mat frame;
    cv::VideoCapture capture;

    bool origin;
    char option;
public:
    MovementDetector();
    virtual ~MovementDetector();
    virtual void logParams();

    virtual void execute();
    virtual void logOutput();
    void setParam(QMap<QString, QString> map);

signals:
    void resultado(int number);
protected:
    virtual void run();
public slots:
    void stopTask(int id);

};

#endif /* MOVEMENTDETECTOR_H_ */
