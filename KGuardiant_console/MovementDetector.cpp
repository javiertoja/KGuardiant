/*
 * MovementDetector.cpp
 *
 *  Created on: 25/03/2014
 *      Author: karels
 */

#include "MovementDetector.h"

MovementDetector::MovementDetector() {
	origin = false;

}

MovementDetector::~MovementDetector() {

}

void MovementDetector::consoleInput() {

	std::cout << "Por favor, indique o dispositivo a empregar video/webcam"
			  << " [0/1]." << std::endl;
	std::cin  >> option;

	switch (option){
	case '0':
		origin = true;
		//std::cout << "Not yet Implemented !!!" << std::endl;
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

void MovementDetector::execute() {

	 /// Variables /////////////////////////////////////////////////////////
	int waitKeyTime=33;

	IplImage *iplImagen, *iplFrame, *segmentated, *labelImg;


	int picWidth, picHeight, thickness;

	CvTracks tracks;
	CvBlobs blobs;
	CvBlob* blob;

	Mat fgMaskMOG2;
	Ptr<BackgroundSubtractor> pMOG2;
	BackgroundSubtractorMOG2 MOG2;

	unsigned int result = 0;

	bool quit = false;


	cvNamedWindow("Blobs", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("Blobs", 750, 400);
	cvNamedWindow("Imagen Real", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("Imagen Real", 200, 100);


	if (origin){

		capture.open("/home/karels/Escritorio/videoExample.mp4");
	}else{
		capture.open(0);
	}

	if(capture.isOpened()){
				capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
				capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
				capture.set(CV_CAP_PROP_FPS, 30);
				std::cout << "Camara correcta !." << std::endl;
	}else {
		std::cout << "Erro o abrir a camara." << std::endl;
		return;
	}


	while (!quit) {

		capture >> frame;

		MOG2(frame, fgMaskMOG2);

		int DELAY_BLUR = 100;
		  for ( int i = 1; i < 31; i = i + 2 )
				{ GaussianBlur( fgMaskMOG2, fgMaskMOG2, Size( i, i ), 0, 0 );}

		threshold(fgMaskMOG2, fgMaskMOG2, 35, 255, CV_THRESH_BINARY);

		segmentated = new IplImage(fgMaskMOG2);
		iplFrame = new IplImage(frame);

		labelImg = cvCreateImage(cvGetSize(iplFrame), IPL_DEPTH_LABEL, 1);

		result = cvLabel(segmentated, labelImg, blobs);
		cvFilterByArea(blobs, 500, 1000000);
		cvRenderBlobs(labelImg, blobs, iplFrame, iplFrame, CV_BLOB_RENDER_COLOR, 0.5);
		cvUpdateTracks(blobs, tracks, 200., 5);
		cvRenderTracks(tracks, iplFrame, iplFrame, CV_TRACK_RENDER_BOUNDING_BOX, NULL);

		cvShowImage("Imagen Real", iplFrame);
		cvShowImage("Blobs", segmentated);

		if (cvGreaterBlob(blobs)) {
			blob = blobs[cvGreaterBlob(blobs)];
			cvShowImage("Imagen Real", iplFrame);
			cvShowImage("Blobs", segmentated);

			cout << "Blobs encontrados: " << blobs.size() << endl;
			cout << "Pixels : " << result << endl;
			cout << "centro-x: " << blob->centroid.x
			<< " centro-y: " << blob->centroid.y
			<< endl;
			cout << "offset-x: " << ((picWidth / 2)-(blob->centroid.x))
			<< " offset-y: " << (picHeight / 2)-(blob->centroid.y)
			<< endl;
			cout << "\n";
		}

		//Interacción co teclado
		char c = waitKey(waitKeyTime);
		if (c==27)
			break; //Escape->Break
		if (c=='p') { //Pause
			waitKeyTime=waitKeyTime==0?33:0;
		}

	}
	cvReleaseBlobs(blobs);

	cvReleaseImage(&labelImg);
	cvReleaseImage(&segmentated);
	cvReleaseImage(&iplFrame);
	cvReleaseImage(&iplImagen);

	cvDestroyAllWindows();

}

void MovementDetector::logOutput() {

}

void MovementDetector::logParams() {

}

void MovementDetector::run() {
	consoleInput();
	execute();
}
