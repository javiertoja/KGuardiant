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

void MovementDetector::execute() {

	namedWindow("Frame");
	namedWindow("FG Mask MOG");
	namedWindow("FG Mask MOG 2");

	Mat frame;
	Mat fgMaskMOG;
	Mat fgMaskMOG2;
	Ptr<BackgroundSubtractor> pMOG;
	Ptr<BackgroundSubtractor> pMOG2;
	int keyboard;
	RNG rng(12345);

	BackgroundSubtractorMOG MOG;
	BackgroundSubtractorMOG2 MOG2;

	int waitKeyTime=33;

	if (!origin){
		capture.open(0);
	}

	if(capture.isOpened()){
			capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
			capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
			capture.set(CV_CAP_PROP_FPS, 1);
			std::cout << "Camara correcta !." << std::endl;
	}else {
		std::cout << "Erro o abrir a camara." << std::endl;
		return;
	}


	while( (char)keyboard != 'q' && (char)keyboard != 27 ){

		if(!capture.read(frame)) {
		  cerr << "Unable to read next frame." << endl;
		  cerr << "Exiting..." << endl;
		  exit(EXIT_FAILURE);
		}

	    MOG(frame, fgMaskMOG);
	    MOG2(frame, fgMaskMOG2);

	    cv::erode(fgMaskMOG, fgMaskMOG, cv::Mat());
	    cv::dilate(fgMaskMOG, fgMaskMOG, cv::Mat());

	    cv::erode(fgMaskMOG2, fgMaskMOG2, cv::Mat());
	    cv::dilate(fgMaskMOG2, fgMaskMOG2, cv::Mat());

	    ContoursType contours;
        cv::findContours(fgMaskMOG2, contours, CV_RETR_EXTERNAL,
	                         CV_CHAIN_APPROX_NONE);

	    ContoursType contours2;
        cv::findContours(fgMaskMOG2, contours2, CV_RETR_EXTERNAL,
	                         CV_CHAIN_APPROX_NONE);

        vector<vector<Point> > contours_poly( contours.size() );
        vector<Rect> boundRect( contours.size() );
        vector<Point2f>center( contours.size() );
        vector<float>radius( contours.size() );

		for( int i = 0; i < contours.size(); i++ )
		{
			approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
			boundRect[i] = boundingRect( Mat(contours_poly[i]) );
			minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
		}

		Mat drawing = Mat::zeros( frame.size(), CV_8UC3 );
		for( int i = 0; i< contours.size(); i++ )
		{
			Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
			drawContours( frame, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
			rectangle( frame, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );

		}

	    imshow("Frame", frame);
	    imshow("FG Mask MOG", fgMaskMOG);
	    imshow("FG Mask MOG 2", fgMaskMOG2);

	    keyboard = waitKey( 30 );
	}
	  capture.release();
}

void MovementDetector::logOutput() {

}

void MovementDetector::logParams() {

}

void MovementDetector::run() {
	consoleInput();
	execute();
}
