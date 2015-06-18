#include "logger.h"

//Inicializamos a instancia do logger;
Logger* Logger::pinstance = 0;

/**
 * @brief Logger::Instance
 * @return
 */
Logger* Logger::Instance()
{
    static QMutex mutex;
    if (pinstance == 0)
    {
        mutex.lock();
        if (pinstance ==0)
        {
            pinstance = new Logger();
        }
        mutex.unlock();
    }
return pinstance;
}



Logger::Logger(QObject *parent) :
    QObject(parent)
{
   settings = Configuracion::Instance();
   logDir = new QDir(settings->getValue("log","ruta").toString());
   if (logDir->exists()
        && logDir->isReadable())
   {
        logFile = new QFile(logDir->absolutePath()+"/server.log");
        //Se o arquivo non existe creamolo
        if (!logFile->open(QIODevice::Append | QIODevice::Text))
        {
    //            throw EX_NO_WRITE;
        }
   }
}

/**
 * @brief Logger::log
 * @param logData
 */
void Logger::log(QString logData){
    QDateTime fecha = QDateTime::currentDateTime();
    QTextStream out(logFile);
        out << "\n["<< fecha.toString("dd/MM/yyyy HH:mm:ss")<< "]"
            << logData.toUtf8();
}

/**
 * @brief Logger::logImage
 * @param logImage
 */
void Logger::logImage(QImage* logImage){
    QDateTime fecha = QDateTime::currentDateTime();
    QFile * newImage = new QFile(logDir->absolutePath()
                                 +"/img"+fecha.toString("ddMM_yyyy_HH_mm.jpeg"));
    if (!newImage->open(QIODevice::WriteOnly | QIODevice::Text)){
        //throw EX_NO_WRITE;
    }
}
