/*
 * VisorKinnect.cpp
 *
 *  Created on: 14/03/2014
 *      Author: karels
 */

#include "VisorKinnect.h"
/*
 * Constructor valeiro da clase VisorKinnect
 */
VisorKinnect::VisorKinnect() {
	origin = false;
}
/*
 * Destructor da clase VisorKinnect
 */
VisorKinnect::~VisorKinnect() {

}
/*
 * Método encargado da iteracción do algoritmo co usuario en tod o o relativo
 * a obtención de parámetros iniciais necesarios para arrancar o algoritmo.
 */
void VisorKinnect::consoleInput() {

	std::cout << "Por favor, indique o dispositivo a empregar Kinnect/webcam"
			  << " [0/1]." << std::endl;
	std::cin  >> option;

	switch (option){
	case '0':
		std::cout << "Not yet Implemented !!!" << std::endl;
		break;
	case '1':
		origin = false;
		break;
	default:
		std::cout << "Entrada non recoñecida, por favor elixa uha entrada"
				  << " válida." << std::endl;
		consoleInput();
		break;
	}

}
/*
 * Método encargado de executar o algoritmo, esta clase implementa un visor da
 * webcam ou do kinnect:
 * 		1. Encuestase o usuario sobre o dispositivo a utilizar para realizar
 * 		   a captura kinnect/webcam [0/1].
 * 		2. Recuperase a imaxe do dispositivo e mostrase nunha ventá.
 */
void VisorKinnect::execute() {

	//Contador de frames
	int nframe=0;
	//Variable para escribir texto na imaxe.
	char text[5];
	//Variable que indica os milisegundos que pasan entre cada captura
	int waitKeyTime=33;

	if (!origin){
		capture.open(0);
	}

	if(capture.isOpened()){
			capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
			capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
			capture.set(CV_CAP_PROP_FPS, 30); //30 fps
			std::cout << "Camara correcta !." << std::endl;
	}else {
		std::cout << "Erro o abrir a camara." << std::endl;
		return;
	}

	for(;;){
		//Leemos a imaxe da camara
		capture >> frame;

		sprintf(text,"%d",nframe);
		cv::putText(frame, text, cvPoint(10,frame.size().height-40), cv::FONT_HERSHEY_COMPLEX_SMALL,1.0, cvScalarAll(0));

		//Amosa o resulado
		imshow( "Camara", frame );
		nframe++;

		//Interacción co teclado
		char c = cv::waitKey(waitKeyTime);
		if (c==27)
			break; //Escape->Break
		if (c=='p') { //Pause
			waitKeyTime=waitKeyTime==0?33:0;
		}
	}

	cvDestroyAllWindows();
}
/*
 * Método encargado de realizar un log da saida do sistema no caso de que exista
 */
void VisorKinnect::logOutput() {

}
/*
 * Método encargado de realizar un log dos parámetros de entrada introducidos
 * polo usuario.
 */
void VisorKinnect::logParams() {

}
/*
 * Método encargado de controlar toda a orquestración do algoritmo ca axuda
 * dos métodos anteriores.
 */
void VisorKinnect::run() {

	consoleInput();
	execute();
}
