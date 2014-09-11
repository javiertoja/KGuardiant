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

    clabel = new ClickableLabel();
    clabel->setGeometry(10,30,640,480);
    clabel->setFrameShape(QFrame::Box);

    connect(clabel,SIGNAL(clicked(QPoint)),this,SLOT(clabel_mouse_pressed(QPoint)));
    connect(clabel,SIGNAL(releaseMouse(QPoint)),this,SLOT(clabel_mouse_released(QPoint)));

    this->rois_user = new QList<QRect>;
    ui->vl->addWidget(clabel);
    ui->txtEstado->setText(QString("DESCONECTADO."));
}

Client::~Client()
{
    delete ui;
}

void Client::clabel_mouse_pressed(QPoint punto)
{
   this->origin.setX(punto.x());
   this->origin.setY(punto.y());
   qDebug() << "ORIGIN ["<<this->origin.x()<<","<<this->origin.y()<<"].";
}

void Client::clabel_mouse_released(QPoint released)
{
    int center_x , center_y, width, height = 0;

    width = abs(this->origin.x() - released.x());
    height = abs(this->origin.y() - released.y());

    center_x = minimun(this->origin.x(),released.x());
    //center_x = center_x - this->clabel->geometry().left();
    center_y = minimun(this->origin.y(),released.y());
    //center_y = center_y - this->clabel->geometry().top();

    //QRect * rec = new QRect(center_x,
    //                        center_y,
    //                        width,
    //                        height);
    qDebug() << "RELEASED ["<<center_x<<","<<center_y<<"],["<<width << ","<<height << "].";
    this->rois_user->append(QRect(center_x,
                                  center_y,
                                  width,
                                  height));
}

int Client::minimun(int a1, int a2)
{
    if (a1 > a2){
        return a1;
    }else{
        return a2;
    }
}

void Client::readyRead()
{
    QByteArray data = socket->readAll();
    QDataStream stream(data);
    QString origin;

    stream >> origin;
    if (origin.compare(QString("CAMVISOR"),Qt::CaseInsensitive) == 0){
        //qDebug() << "Camvisor!";
    }else{
        //qDebug() << "MovementDetector!.!";
    }
    cv::Mat matImage = byteArray2Mat(data);

    if (matImage.isContinuous()){


        QImage imagen = QtOcv::mat2Image(cv::imdecode(matImage,CV_LOAD_IMAGE_COLOR)); 
        clabel->setPixmap(QPixmap(drawImage(&imagen)));

    }else{
        qDebug() << "no continua";
    }
    matImage.release();
}

QPixmap Client::drawImage(const QImage *imagen)
{
    QPixmap pix = QPixmap::fromImage(*imagen);
    QPainter paint;
    paint.begin(&pix);
    paint.setPen(QColor(255,34,255,255));

    foreach(QRect rec , *this->rois_user){

        paint.drawRect(rec.topLeft().x(),rec.topLeft().y(),rec.width(),rec.height());
        qDebug() << "["<<rec.topLeft().x()<<","<<rec.topLeft().y()<<"],["<<rec.width() << ","<<rec.height() << "].";
        //paint.drawRect(0,0,150,150);
   }
    paint.end();
    checkRois();
return pix;

}

void Client::checkRois()
{
    foreach (QRect r1,*this->rois){
        foreach(QRect r2,*this->rois_user){

            if (!(r1 & r2).isEmpty()){
                ui->txtLogBrowser->append(QString("Alarma Disparada."));
                qDebug() << "ALARMA ["<< r2.center().x() << "," << r2.center().y()<< "]";
            }
        }
    }

}

cv::Mat Client::byteArray2Mat(const QByteArray &byteArray)
{
    QDataStream stream(byteArray);
    QString origin;
    QList<QRect> rois;
    int matType, rows, cols;
    QByteArray data;
    stream >> origin;
    stream >> rois;
    this->rois = new QList<QRect>(rois);
    stream >> matType;
    stream >> rows;
    stream >> cols;
    stream >> data;
    cv::Mat mat( rows, cols, matType, (void *)data.data());
    return mat.clone();
}

void Client::on_btnConectar_clicked()
{
    socket->connectToHost("127.0.0.1",1234);
    if ((socket->isWritable())){
        ui->txtEstado->setText(QString("CONECTADO !!"));
    }else{
        ui->txtEstado->setText(QString("DESCONECTADO."));
    }
}

void Client::on_btnDesconectar_clicked()
{
    socket->disconnectFromHost();
    if ((socket->isWritable())){
        ui->txtEstado->setText(QString("CONECTADO !!"));
    }else{
        ui->txtEstado->setText(QString("DESCONECTADO."));
    }
}

void Client::on_btnVisorStart_clicked()
{
    socket->write(QByteArray("1",1));
}

void Client::on_btnVisorStop_clicked()
{
    socket->write(QByteArray("2",1));
    clabel->setPixmap(QPixmap());
}
