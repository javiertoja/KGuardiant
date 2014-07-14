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
    QImage img;
    //ui->textBrowser->append(QString(socket->readAll()));
    qDebug() << "Imagen recibida";
    QPixmap pixmap;
    QGraphicsScene scene;
    img.fromData(socket->readAll());
    pixmap.fromImage(img);
    ui->imglbl->setPixmap(pixmap);
    ui->imglbl->show();
    scene.clear();
    scene.addPixmap(pixmap);
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->show();
    /*QGraphicsScene* scene = new QGraphicsScene();

    img.loadFromData(socket->readAll());
    scene->addPixmap(QPixmap().fromImage(img));*/

    //ui->graphicsView->setScene(scene);
}
