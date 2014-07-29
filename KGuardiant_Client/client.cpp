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
    socket->connectToHost("127.0.0.1",1234);
}

Client::~Client()
{
    delete ui;
}

void Client::on_lineEdit_returnPressed()
{
    socket->write(ui->lineEdit->text().toLatin1());
    ui->lineEdit->setText("");
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
