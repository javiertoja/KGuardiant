
#include <QCoreApplication>
#include <QTimer>
#include "kguardiantserver.h"
#include <QDebug>


#include <opencv2/opencv.hpp>
#include <iostream>
/**
 * @brief Clase principal que representa á aplicación
 * Nela créanse as instancias das demáis clases
 * necesarias para ofrecer a funcionalidade do sistema.
 * @param argc - número de argumentos da consola.
 * @param argv - lista de argumentos da consola.
 * @return - valor que indica se o programa rematou con éxito.
 */
int main(int argc, char *argv[])
{

/*

        cv::VideoCapture sensor1;
        sensor1.open(CV_CAP_OPENNI);

        if( !sensor1.isOpened() ){
            std::cout << "Can not open capture object 1." << std::endl;
            return -1;
        }

        for(;;){
            cv::Mat depth1;

            if( !sensor1.grab() ){
                std::cout << "Sensor1 can not grab images." << std::endl;
                return -1;
            }else if( sensor1.retrieve( depth1, CV_CAP_OPENNI_BGR_IMAGE ) ) cv::imshow("depth1",depth1);

            if( cv::waitKey( 30 ) == 27 )   break;//ESC to exit

       }
*/



    //Contén a información relativa a aplicación
    QCoreApplication app(argc, argv);
    
    KGuardiantServer kgServer;

    QObject::connect(&kgServer,
                     SIGNAL(finished()),
                     &app,
                     SLOT(quit()));

    QObject::connect(&app,
                     SIGNAL(aboutToQuit()),
                     &kgServer,
                     SLOT(aboutToQuitApp()));

    QTimer::singleShot(10, &kgServer, SLOT(run()));
    //Inicia o bucle de eventos do sistema.
    return app.exec();

}
