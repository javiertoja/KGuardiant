/*
 * HandDetector.h
 *
 *  Created on: 19/03/2014
 *      Author: Javier Toja Alamancos
 */

#ifndef HANDDETECTOR_H_
#define HANDDETECTOR_H_

#include "AlgorithmBase.h"

class HandDetector: public AlgorithmBase {
public:
	HandDetector();
	virtual ~HandDetector();
	void run();
	void logParams();
	void consoleInput();
	void execute();
	void logOutput();
};

#endif /* HANDDETECTOR_H_ */
