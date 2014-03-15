/*
 * Console.cpp
 *
 *  Created on: 13/03/2014
 *      Author: Javier Toja Alamancos
 */
#include <iostream>
#include <fstream>
#include "Console.h"
#include "VisorKinnect.h"

/*
 * Constructor valeiro do obxecto console encargado de crear e inicializar
 * obxecto console para o seu uso.
 * @return Console.
 */
Console::Console() {
	std::cout << "Construindo Obxeto Console\n";
	exit = false;
}

/*
 * Destructor do obxecto console encargado de liberar a memoria alocatada polo
 * obxecto durante o seu uso.
 * @return Console.
 */
Console::~Console() {
	std::cout << "Liberando Obxeto Console\n";
}

/*
 * Metodo encargado de correr ca execución da consola, este método implementa un
 * bucle que mostra as opcións dispoñibles en cada iteracción e recoller a
 * entrada do usuario por terminal, en caso de que a opción non esté dispoñible
 * informase o usuario e volvese a mostrar a lista de opcións dispoñibles.
 */
void Console::run() {

	std::cout << "Iniciando bucle de escoita..." << std::endl;
	while (!exit){

		showOpts();
		std::cin >> option;
		parseOpts();
		log();
	}
}
/*
 * Método de Log encargado de realizar un log dos eventos e das entradas do
 * sistema - Log da opción seleccionada polo usuario na consola.
 */
void Console::log() {

	std::fstream archivo("Log.txt");

	if (archivo){
		archivo << option;
		archivo.close();
	}
}
/*
 * Método encargado de realzar un log dos eventos do sistema e das suas entradas
 * @param Char *msg - Mensaxe a gardar no Log.
 */
void Console::log(char *msg) {

	std::fstream archivo("Log.txt");

	if (archivo){
		archivo << msg;
		archivo.close();
	}
}

/*
 * Metodo encargado de amosar o usuario as opcións das que dispón.
 */
void Console::showOpts() {

	std::cout << "Benvido" << std::endl;
	std::cout << "1.- Visor." << std::endl;
	std::cout << "q.- Sair."  << std::endl;
}

/*
 * Metodo encargado de parsear a opción seleccionada polo usuario e en función
 * da mesma, invocar o algoritmo correspondente ou finalizar a aplicación.
 */
void Console::parseOpts() {

	std::cout << "Elexindo [" << option << "]" << std::endl;
	switch(option) {

	case '1':{
		VisorKinnect *visor = new VisorKinnect();
		visor->run();
		break;
	}
	case 'q':
		stop();
		break;
	default:
		return;
	}
}
/*
 * Metodo encargado de finalizar a execución do bucle de lectura da aplicación
 * e finalizar a consola.
 */
void Console::stop() {

	exit = true;
	log((char *)"Saindo da App.");
}
