#include "movementdetector.h"

MovementDetector::MovementDetector(QObject *parent) :
    BaseDetector(parent)
{
    //qDebug() << "Creado fío para detectar movemento";
    this->name = "MV_DETECTOR";
    log = Logger::Instance();
    bg = new cv::BackgroundSubtractorMOG2();
    bg->setBool("detectShadows",false);
    bg->setInt("nmixtures",3);

    cv::namedWindow( "Back", cv::WINDOW_AUTOSIZE );// Create a window for display.
    rng = new cv::RNG(12345);
    thresh = 100;
    max_thresh = 255;

    log->log("Creado fío para detectar movemento");
}

MovementDetector::~MovementDetector(){

}

/**
 * @brief getSigned
 * @param x
 * @return
 */
int getSigned(unsigned x)
{
    if (x <= INT_MAX)
        return static_cast<int>(x);

    if (x >= INT_MIN)
        return static_cast<int>(x - INT_MIN) + INT_MIN;

    throw x;
}




/**
 * @brief BaseDetector::processImg
 */
void MovementDetector::processImg(cv::Mat &cframe){

    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::Mat back;
    cv::Mat fore;
    QList<QRect> lstrec;
    //qDebug() << "Procesando imaxe.";
    cv::vector<int> params;
    cv::vector<uchar> compressed;
    params.push_back(CV_IMWRITE_JPEG_QUALITY);
    params.push_back(85);


    log->log("Procesando imaxe.");

    lstrec.clear();
    cv::erode(cframe,cframe,cv::Mat());
    cv::dilate(cframe,cframe,cv::Mat());
    bg->operator ()(cframe,fore);

    bg->getBackgroundImage(back);

    cv::imshow("Back",fore);


    for ( int i = 1; i < 31; i = i + 2 )
    {
        cv::GaussianBlur( fore, fore, cv::Size( i, i ), 0, 0 );
    }


    cv::threshold(fore,fore,thresh,max_thresh,CV_THRESH_BINARY);
    //cv::cvtColor(fore,fore, CV_RGB2GRAY);
    cv::findContours( fore, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

    std::vector<std::vector<cv::Point> > contours_poly( contours.size() );
    std::vector<cv::Rect> boundRect( contours.size() );

    for( int i = 0; i < getSigned(contours.size()); i++ )
    { cv::approxPolyDP( cv::Mat(contours[i]), contours_poly[i], 3, true );
         boundRect[i] = cv::boundingRect( cv::Mat(contours_poly[i]) );
         lstrec.append(QRect(QPoint(boundRect[i].tl().x,boundRect[i].tl().y),QPoint(boundRect[i].br().x,boundRect[i].br().y)));
    }


    //cv::imshow( "Display window", cframe );
    cv::imencode(".jpg",cframe,compressed,params);
    emit processedImg(setup4Send(cv::Mat(compressed),lstrec));
}


/**
 * @brief MovementDetector::processImg
 * @param cframe
 * @param dFrame
 */
void MovementDetector::processImg(cv::Mat &cframe, cv::Mat &dframe){

    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::Mat back;
    cv::Mat fore;
    QList<QRect> lstrec;
    //qDebug() << "Procesando imaxe.";
    cv::vector<int> params;
    cv::vector<uchar> compressed;
    params.push_back(CV_IMWRITE_JPEG_QUALITY);
    params.push_back(85);


    log->log("Procesando imaxe.");

    lstrec.clear();
    cv::erode(cframe,cframe,cv::Mat());
    cv::dilate(cframe,cframe,cv::Mat());
    bg->operator ()(cframe,fore);

    //bg->getBackgroundImage(back);

    cv::imshow("Back",fore);


    for ( int i = 1; i < 31; i = i + 2 )
    {
        cv::GaussianBlur( fore, fore, cv::Size( i, i ), 0, 0 );
    }


    cv::threshold(fore,fore,thresh,max_thresh,CV_THRESH_BINARY);
    //cv::cvtColor(fore,fore, CV_RGB2GRAY);
    cv::findContours( fore, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

    std::vector<std::vector<cv::Point> > contours_poly( contours.size() );
    std::vector<cv::Rect> boundRect( contours.size() );

    for( int i = 0; i < getSigned(contours.size()); i++ )
    { cv::approxPolyDP( cv::Mat(contours[i]), contours_poly[i], 3, true );
         boundRect[i] = cv::boundingRect( cv::Mat(contours_poly[i]) );
         lstrec.append(QRect(QPoint(boundRect[i].tl().x,boundRect[i].tl().y),QPoint(boundRect[i].br().x,boundRect[i].br().y)));
    }


    //cv::imshow( "Display window", cframe );
    cv::imencode(".jpg",cframe,compressed,params);
    emit processedImg(setup4Send(cv::Mat(compressed),lstrec));
}




/**
 * @brief BaseDetector::setup4Send
 * @return
 */
QByteArray MovementDetector::setup4Send(const cv::Mat image, QList<QRect> lstRec){

   QByteArray byteArray;
   QDataStream stream(&byteArray,QIODevice::WriteOnly);
   stream << image.type();
   stream << image.rows;
   stream << image.cols;
   //qDebug() << "Type["<< image.type()<<"] rows["<< image.rows<<"] cols [" << image.cols<<"] Blobs [" << lstRec.count() <<"]";
   const size_t data_size = image.cols * image.rows * image.elemSize();
   QByteArray data = QByteArray::fromRawData((const char*)image.ptr(),data_size);
   stream << data;
   stream << lstRec;
   return byteArray;
}
