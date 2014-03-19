/*
 * PeopleDetector2d.cpp
 *
 *  Created on: 15/03/2014
 *      Author: karels
 */

#include "PeopleDetector2d.h"
/*
 * Constructor valeiro da clase PeopleDetector2d
 */
PeopleDetector2d::PeopleDetector2d() {

}
/*
 * Destructor da clase PeopleDetector2d
 */
PeopleDetector2d::~PeopleDetector2d() {

}
/*
 * Constructor Sobrecargado da clase PeopleDetector2d que recibe como argumento
 * o nome dun arquivo que pode ser un vídeo ou unha imaxe para analizar.
 */
PeopleDetector2d::PeopleDetector2d(char *filename) {

}
/*
 * Método encargado de recoller por consola a entrada do usuario no caso de que
 * exista.
 */
void PeopleDetector2d::consoleInput() {

}
/*
 * Método encargado de executar o algoritmo propiamente dito, este mentodo
 * implementa o detector de persoas empregando un descriptor HoG.
 */
void PeopleDetector2d::execute() {


	cv::Mat frame;
	//Contador de frames
	int nframe=0;
	//Variable para escribir texto na imaxe.
	char text[5];
	//Variable que indica os milisegundos que pasan entre cada captura
	int waitKeyTime=33;

	cv::VideoCapture capture;
	capture.open(0);

    cv::HOGDescriptor hog;
    hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
    cv::namedWindow("people detector", 1);


	if(capture.isOpened()){
			capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
			capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
			capture.set(CV_CAP_PROP_FPS, 30);
			std::cout << "Camara correcta !." << std::endl;
	}else {
		std::cout << "Erro o abrir a camara." << std::endl;
		return;
	}

	for(;;){
		//Leemos a imaxe da camara
		capture >> frame;

		//sprintf(text,"%d",nframe);
		//cv::putText(frame, text, cvPoint(10,frame.size().height-40), cv::FONT_HERSHEY_COMPLEX_SMALL,1.0, cvScalarAll(0));

		//Amosamos o resulado nunha nova ventá con nome "Camara" frame a frame
		imshow( "Camara", frame );

        cv::vector<cv::Rect> found, found_filtered;
        double t = (double)cv::getTickCount();
        // run the detector with default parameters. to get a higher hit-rate
        // (and more false alarms, respectively), decrease the hitThreshold and
        // groupThreshold (set groupThreshold to 0 to turn off the grouping completely).
        hog.detectMultiScale(frame, found, 0, cv::Size(8,8), cv::Size(32,32), 1.05, 2);
        t = (double)cv::getTickCount() - t;
        printf("tdetection time = %gms\n", t*1000./cv::getTickFrequency());
        size_t i, j;
        for( i = 0; i < found.size(); i++ )
        {
        	cv::Rect r = found[i];
            for( j = 0; j < found.size(); j++ )
                if( j != i && (r & found[j]) == r)
                    break;
            if( j == found.size() )
                found_filtered.push_back(r);
        }
        for( i = 0; i < found_filtered.size(); i++ )
        {
        	cv::Rect r = found_filtered[i];
            // the HOG detector returns slightly larger rectangles than the real objects.
            // so we slightly shrink the rectangles to get a nicer output.
            r.x += cvRound(r.width*0.1);
            r.width = cvRound(r.width*0.8);
            r.y += cvRound(r.height*0.07);
            r.height = cvRound(r.height*0.8);
            cv::rectangle(frame, r.tl(), r.br(), cv::Scalar(0,255,0), 3);
        }
        cv::imshow("people detector", frame);


		nframe++;

		//Interacción co teclado
		char c = cv::waitKey(waitKeyTime);
		if (c==27)
			break; //Escape->Break
		if (c=='p') { //Pause
			waitKeyTime=waitKeyTime==0?33:0;
		}
	}
}
/*
 * Método encargado de rexitrar a saida do algoritmo.
 */
void PeopleDetector2d::logOutput() {

}
/*
 * Método encargado de rexitrar a entrada do algoritmo para motivos de log.
 */
void PeopleDetector2d::logParams() {

}
/*
 * Método que orquestra globalmente o funcionamento do algortimo.
 */
void PeopleDetector2d::run() {

}

