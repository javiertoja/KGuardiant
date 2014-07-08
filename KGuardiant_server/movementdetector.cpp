#include "movementdetector.h"

MovementDetector::MovementDetector() {
    origin = false;

}

MovementDetector::~MovementDetector() {

}


void MovementDetector::execute() {


    int waitKeyTime=parameters->value(QString("waittime")).toInt();

    IplImage *iplImagen, *iplFrame, *segmentated, *labelImg;

    int picWidth, picHeight;

    CvTracks tracks;
    CvBlobs blobs;
    CvBlob* blob;

    Mat fgMaskMOG2;
    Ptr<BackgroundSubtractor> pMOG2;
    BackgroundSubtractorMOG2 MOG2;

    unsigned int result = 0;

    bool quit = false;

    origin = (parameters->value(QString("devicetype")) == KINNECT);

    capture.open(parameters->value(QString("inputdevice")).toInt());

    if(capture.isOpened()){
        capture.set(CV_CAP_PROP_FRAME_WIDTH,
                    parameters->value(QString("with")).toInt());
        capture.set(CV_CAP_PROP_FRAME_HEIGHT,
                    parameters->value(QString("height")).toInt());
        capture.set(CV_CAP_PROP_FPS,
                    parameters->value(QString("fps")).toInt());

        Logger::Instance()->log(QString("Cámara Correcta [MovementDetector]"));

    }else {
        Logger::Instance()->log(QString("[ERROR]Non ha sido posible abrir o dispositivo [MovementDetector]"));
        throw EX_ER_MVDETEC;
        return;
    }


    while (!quit && this->stop ==0) {
        //emit resultado(4);
        capture >> frame;

        MOG2(frame, fgMaskMOG2);


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

    execute();
}

void MovementDetector::stopTask(int number)
{
    stop = 1;
}
