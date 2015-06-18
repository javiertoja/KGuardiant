#include "devicemgr.h"

DeviceMgr::DeviceMgr(QObject *parent) :
    QThread(parent)
{
    settings = Configuracion::Instance();
    log = Logger::Instance();
    // settings->getValue("configuracion","capture").toInt()
    cam = new cv::VideoCapture(0);


    log->log("Creando obxecto DeviceMGR.");
    //cv::namedWindow("dvcMgr");
}

/**
 * @brief DeviceMgr::~DeviceMgr
 */
DeviceMgr::~DeviceMgr()
{
    cam->release();
}

void DeviceMgr::run()
{
    exec();
}

/**
 * @brief DeviceMgr::requestImage
 */
void DeviceMgr::requestImage()
{
    cFrame.release();
    dFrame.release();
    if(cam->isOpened())
    {
        //cam->set(CV_CAP_PROP_FRAME_WIDTH, 640);
        //cam->set(CV_CAP_PROP_FRAME_HEIGHT, 480);
        //cam->set(CV_CAP_PROP_FPS, 30);

        log->log("Solicitando imaxe.");
        //qDebug() << "Grab" << cam->grab();
        if (cam->grab())
        {   //qDebug() << "Conf Kinect" <<  settings->getValue("configuracion","kinect").toInt();
            if (settings->getValue("configuracion","kinect").toBool())
            {
                cam->retrieve(cFrame,CV_CAP_OPENNI_BGR_IMAGE);
                cam->retrieve(dFrame,CV_CAP_OPENNI_DEPTH_MAP);
                //cv::imshow("dvcMgr",cFrame);
                emit newImage(cFrame,dFrame);
            }else{
                cam->retrieve(cFrame,CV_CAP_OPENNI_BGR_IMAGE);
                emit newImage(cFrame);
            }
        }


    }else
    {
        qDebug() << "Error o intentar recuperar imaxe;";
        log->log("Erro solicitando imaxe.");

    }
}
