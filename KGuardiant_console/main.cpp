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

bool exit = false;

int main()
{
	cout << "Hola Mundo.\n";

	Console *sistema = new Console();
	sistema->run();
	return 0;
}
