#include "movementdectector.h"

MovementDectector::MovementDectector(bool origin, cv::VideoCapture *capture)
{
    this->stop = false;
    this->origin = origin;
    this->capture = capture;
}

void MovementDectector::stopTask(bool stop)
{
    qDebug() << "Parando Visor";
    this->stop = stop;
}

QByteArray MovementDectector::mat2ByteArray(const cv::Mat &image)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray,QIODevice::WriteOnly);
    stream << image.type();
    stream << image.rows;
    stream << image.cols;
    const size_t data_size = image.cols * image.rows * image.elemSize();
    QByteArray data = QByteArray::fromRawData((const char*)image.ptr(),data_size);
    stream << data;
    return byteArray;
}

MovementDectector::~MovementDectector()
{
    qDebug() << "Destruyendo thread de camvisor";
}

void MovementDectector::run()
{
    IplImage *iplImagen, *iplFrame, *segmentated, *labelImg;
    int picWidth, picHeight, thickness;

    CvTracks tracks;
    CvBlobs blobs;
    CvBlob* blob;

    Mat fgMaskMOG2;
    Mat frame;

    BackgroundSubtractorMOG2 MOG2;

    unsigned int result = 0;

    while (this->capture->isOpened() && !this->stop) {

        *capture >> frame;

        MOG2(frame, fgMaskMOG2);

       for ( int i = 1; i < 31; i = i + 2 )
       {
           GaussianBlur( fgMaskMOG2, fgMaskMOG2, Size( i, i ), 0, 0 );
       }

        threshold(fgMaskMOG2, fgMaskMOG2, 35, 255, CV_THRESH_BINARY);

        segmentated = new IplImage(fgMaskMOG2);
        iplFrame = new IplImage(frame);

        labelImg = cvCreateImage(cvGetSize(iplFrame), IPL_DEPTH_LABEL, 1);

        result = cvLabel(segmentated, labelImg, blobs);
        cvFilterByArea(blobs, 500, 1000000);
        cvRenderBlobs(labelImg, blobs, iplFrame, iplFrame, CV_BLOB_RENDER_COLOR, 0.5);
        cvUpdateTracks(blobs, tracks, 200., 5);
        cvRenderTracks(tracks, iplFrame, iplFrame, CV_TRACK_RENDER_BOUNDING_BOX, NULL);

        if (cvGreaterBlob(blobs)) {
            blob = blobs[cvGreaterBlob(blobs)];

            qDebug() << "Blobs encontrados: " << blobs.size() << endl;
            qDebug() << "Pixels : " << result << endl;
            qDebug() << "centro-x: " << blob->centroid.x
            << " centro-y: " << blob->centroid.y
            << endl;
            qDebug() << "offset-x: " << ((picWidth / 2)-(blob->centroid.x))
            << " offset-y: " << (picHeight / 2)-(blob->centroid.y)
            << endl;
            qDebug() << "\n";
        }
    }
}
