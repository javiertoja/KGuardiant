/*
 * Console.cpp
 *
 *  Created on: 13/03/2014
 *      Author: karels
 */
#include <iostream>
#include "Console.h"

/*
 * Constructor valeiro do obxecto console encargado de crear e inicializar
 * obxecto console para o seu uso.
 * @return Console.
 */
Console::Console() {
	std::cout << "Creando Obxeto Console\n" << std::endl;
}

/*
 * Destructor do obxecto console encargado de liberar a memoria alocatada polo
 * obxecto durante o seu uso.
 * @return Console.
 */
Console::~Console() {
	std::cout << "Liberando Obxeto Console\n" << std::endl;
}

void Console::run() {

}
