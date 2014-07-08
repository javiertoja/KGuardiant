#include "logger.h"
Logger* Logger::pinstance = 0;

//Método para recuperar a instancia do singleton
Logger* Logger::Instance()
{
    static QMutex mutex;
    if (pinstance == 0){

        mutex.lock();
        if (pinstance ==0){
            pinstance = new Logger();
        }
        mutex.unlock();
    }
    return pinstance;
}


//Constructor
Logger::Logger(QObject *parent) :
    QObject(parent)
{
    Configuracion* instance = Configuracion::Instance();

    logDir = new QDir(instance->getValueConfig("log","ruta"));
    if (logDir->exists()
            && logDir->isReadable()){

        logFile = new QFile(logDir->absolutePath()+"/server.log");
        //Se o arquivo non existe creamolo
        if (!logFile->open(QIODevice::Append | QIODevice::Text)){
            throw EX_NO_WRITE;
        }

    }else{
        throw EX_NO_WRITE;
    }
}

// Metodo para guardar logs
void Logger::log(QString logData){

    QDateTime fecha = QDateTime::currentDateTime();
    QTextStream out(logFile);
    out << "\n["<< fecha.toString("dd/MM/yyyy HH:mm")<< "]"
        << logData.toUtf8();
}


void Logger::logImage(QImage* logImage){

QDateTime fecha = QDateTime::currentDateTime();

    QFile * newImage = new QFile(logDir->absolutePath()
                                 +"/img"+fecha.toString("ddMM_yyyy_HH_mm.jpeg"));

    if (!newImage->open(QIODevice::WriteOnly | QIODevice::Text)){
        throw EX_NO_WRITE;
    }
}
