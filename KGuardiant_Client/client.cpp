#include "client.h"
#include "ui_client.h"



Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

    dirConf = new QDir();
    conf = new QSettings(dirConf->absolutePath() + "/client.ini",
                         QSettings::IniFormat,
                         this);

    socket = new QTcpSocket();
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));

}

Client::~Client()
{
    delete ui;
}

void Client::readyRead()
{
    QByteArray data = socket->readAll();
    cv::Mat matImage = byteArray2Mat(data);

    if (matImage.isContinuous()){
        QImage imagen = QtOcv::mat2Image(cv::imdecode(matImage,CV_LOAD_IMAGE_COLOR));

        ui->imglbl->setPixmap(QPixmap::fromImage(imagen));

    }else{
        qDebug() << "no continua";
    }
    matImage.release();
}

cv::Mat Client::byteArray2Mat(const QByteArray &byteArray)
{
    QDataStream stream(byteArray);
    int matType, rows, cols;
    QByteArray data;
    stream >> matType;
    stream >> rows;
    stream >> cols;
    stream >> data;
    cv::Mat mat( rows, cols, matType, (void *)data.data());
    return mat.clone();
}

void Client::on_btnStartVisor_clicked()
{
    socket->write(QByteArray("1",1));
}

void Client::on_btnConectar_clicked()
{
    socket->connectToHost("127.0.0.1",1234);
}

void Client::on_btnStopVisor_clicked()
{
    socket->write(QByteArray("2",1));
    ui->imglbl->setPixmap(QPixmap());
}
