/*
 * Main.cpp
 *
 *  Created on: 13/03/2014
 *      Author: Javier Toja Alamancos
 */
#include <iostream>
#include "Console.h"
using namespace std;

#define MAX_INPUT_SIZE 256

int main()
{
	Console *kguardiant = new Console();
	kguardiant->run();
	return 0;
}
