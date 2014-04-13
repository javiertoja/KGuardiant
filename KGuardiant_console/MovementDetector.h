/*
 * MovementDetector.h
 *
 *  Created on: 25/03/2014
 *      Author: Javier Toja Alamancos
 */

#ifndef MOVEMENTDETECTOR_H_
#define MOVEMENTDETECTOR_H_

#include "AlgorithmBase.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <iostream>

typedef std::vector<cv::Mat> ImagesType;
typedef std::vector<std::vector<cv::Point> > ContoursType;

using namespace cv;
using namespace std;

class MovementDetector: public AlgorithmBase {

private:
	cv::Mat frame;
	cv::VideoCapture capture;
	bool origin;
	char option;
public:
	MovementDetector();
	virtual ~MovementDetector();
	virtual void run();
	virtual void logParams();
	virtual void consoleInput();
	virtual void execute();
	virtual void logOutput();
};

#endif /* MOVEMENTDETECTOR_H_ */
