/*
 * VisorKinnect.h
 *
 *  Created on: 14/03/2014
 *      Author: Javier Toja Alamancos
 */

#ifndef VISORKINNECT_H_
#define VISORKINNECT_H_

#include "AlgorithmBase.h"
#include "opencv/cv.h"
#include "opencv/cvaux.h"
#include "opencv/highgui.h"
#include <sys/time.h>
#include <iostream>
#include <cstdio>

class VisorKinnect: public AlgorithmBase {
private:
	cv::Mat frame;
	cv::VideoCapture capture;
	bool origin;
	char option;
public:
	VisorKinnect();
	virtual ~VisorKinnect();
	void run();
	void logParams();
	void consoleInput();
	void execute();
	void logOutput();
};

#endif /* VISORKINNECT_H_ */
