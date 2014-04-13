/*
 * Console.h
 *
 *  Created on: 13/03/2014
 *      Author: Javier Toja Alamancos
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <iostream>
#include <fstream>
#include "VisorKinnect.h"
#include "PeopleDetector2d.h"
#include "MovementDetector.h"

class Console {

private:
	bool exit_console;
	char option;
public:
	Console();
	virtual ~Console();
	void run();
	void showOpts();
	void stop();
	void log();
	void log(char *msg);
	void parseOpts();
};

#endif /* CONSOLE_H_ */
