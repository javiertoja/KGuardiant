/*
 * AlgorithmBase.h
 *
 *  Created on: 14/03/2014
 *      Author: karels
 */

#ifndef ALGORITHMBASE_H_
#define ALGORITHMBASE_H_

class AlgorithmBase {
protected:
	char *algorithmName;
	char *parameters;

public:
	AlgorithmBase();
	virtual ~AlgorithmBase();
	virtual void run();
	virtual void logParams();
	virtual void consoleInput();
	virtual void execute();
	virtual void logOutput();
};

#endif /* ALGORITHMBASE_H_ */
