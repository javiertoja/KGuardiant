/*
 * Console.h
 *
 *  Created on: 13/03/2014
 *      Author: karels
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

class Console {
public:
	Console();
	virtual ~Console();
	void run();
	void showOpts();
	void stop();
	void log();
};

#endif /* CONSOLE_H_ */
