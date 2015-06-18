#include "basedetector.h"

BaseDetector::BaseDetector(QObject *parent) :
    QThread(parent)
{
    log = Logger::Instance();
}

/**
 * @brief BaseDetector::run
 */
void BaseDetector::run()
{
    exec();
}


/**
 * @brief BaseDetector::processImg
 */
void BaseDetector::processImg(){

    emit processedImg(setup4Send());
}

/**
 * @brief BaseDetector::setup4Send
 * @return
 */
QByteArray BaseDetector::setup4Send(){

    QByteArray a;
    return a;
}
