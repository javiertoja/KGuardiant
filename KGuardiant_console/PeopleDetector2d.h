/*
 * PeopleDetector2d.h
 *
 *  Created on: 15/03/2014
 *      Author: Javier Toja Alamancos
 */

#ifndef PEOPLEDETECTOR2D_H_
#define PEOPLEDETECTOR2D_H_

#include "AlgorithmBase.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

class PeopleDetector2d: public AlgorithmBase {
public:
	PeopleDetector2d();
	PeopleDetector2d(char *filename);
	virtual ~PeopleDetector2d();
	virtual void run();
	virtual void logParams();
	virtual void consoleInput();
	virtual void execute();
	virtual void logOutput();
};

#endif /* PEOPLEDETECTOR2D_H_ */
