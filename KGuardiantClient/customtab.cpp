#include "customtab.h"
#include "ui_customtab.h"

CustomTab::CustomTab(QWidget *parent, QString tabName) :
    QWidget(parent),
    ui(new Ui::CustomTab)
{
    ui->setupUi(this);
    this->pause = false;
    client = new QTcpSocket(this);
    this->tabName = tabName;
    //clbl = new ClickableLabel();
    //clbl->setGeometry(10,30,640,480);
    //clbl->setFrameShape(QFrame::Box);
    //ui->gpVisor->layout()->addWidget(clbl);
    connect(client,SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(client,SIGNAL(disconnected()),this,SLOT(disconnected()));
    this->roiLst = new QList<RoiDefinition*>();
}

/**
 * @brief CustomTab::disconnected
 */
void CustomTab::disconnected()
{
    ui->lblEstado->setText("ESTADO: DESCONECTADO");
}

/**
 * @brief CustomTab::setupConnection
 * @param ip
 * @param porto
 */
void CustomTab::setupConnection(QString ip, QString porto)
{
    this->connection = new StationDefinition(this,this->tabName,porto.toUShort(),ip,this->client);
    client->connectToHost(ip,porto.toUShort());
    if (client->isReadable() && client->isWritable())
    {
        ui->lblEstado->setText(QString("ESTADO: CONECTADO"));

    }
}


void CustomTab::deleteConnection()
{
    this->client->disconnectFromHost();
    this->client->close();
    emit closeTab();
}

void CustomTab::readyRead()
{

    if (!this->pause)
    {

        QByteArray data = client->readAll();
        QDataStream stream(data);

        QList<QRect> mvObj;
        int matType, rows, cols;
        QByteArray imageData;
        stream >> matType;
        stream >> rows;
        stream >> cols;
        stream >> imageData;
        stream >> mvObj;
        cv::Mat mat( rows, cols, matType, (void *)imageData.data());
        //qDebug() << "Type["<< matType<<"] rows["<< rows<<"] cols [" << cols<<"]";

        if (mat.isContinuous()){
            emit clearAlerta();
            //qDebug() << "Imaxe leida !!!";
            QImage imagen = QtOcv::mat2Image(cv::imdecode(mat,CV_LOAD_IMAGE_COLOR));

            QPixmap pix = QPixmap::fromImage(imagen);

            this->scene = new QGraphicsScene(this);


            if (mvObj.count()>0)
            {

                QPainter paint;
                paint.begin(&pix);
                paint.setPen(QColor(255,34,255,255));
                foreach(QRect rec , mvObj){
                    paint.drawRect(rec.topLeft().x(),rec.topLeft().y(),rec.width(),rec.height());

                }
                paint.end();


            }

            if (this->roiLst->count()>0)
            {

                QPainter paint;
                paint.begin(&pix);

                for (int i=0; i<this->roiLst->count();i++)
                {
                    RoiDefinition *act = this->roiLst->value(i);

                    paint.setPen(*(act->getColor()));
                    paint.drawRect(act->getBoundRect()->topLeft().x(),act->getBoundRect()->topLeft().y(),act->getBoundRect()->width(),act->getBoundRect()->height());
                    paint.drawText(act->getBoundRect()->center(),act->getAlias());
                }

                paint.end();


            }

            if (this->roiLst->count() > 0 && mvObj.count() > 0)
            {
                QPainter paint;
                paint.begin(&pix);
                paint.setBrush(Qt::DiagCrossPattern);
                paint.setPen(QColor(51, 153, 255));
                for(int i=0;i<this->roiLst->count();i++)
                {
                    foreach(QRect rec , mvObj)
                    {
                        if (rec.intersects(*(this->roiLst->value(i)->getBoundRect())))
                        {
                            QRect isec = rec.intersected(*(this->roiLst->value(i)->getBoundRect()));
                            paint.fillRect(isec,QBrush(QColor(51, 153, 255),Qt::DiagCrossPattern));
                            emit alerta(QString("[%1 : %2]").arg(this->tabName,this->roiLst->value(i)->getAlias()));
                            imagen.save(this->tabName+"_"+this->roiLst->value(i)->getAlias().trimmed()+"_"+QDateTime::currentDateTime().toString("ddMM_yyyy_HH_mm"),"PNG");

                        }
                    }
                }

            }


            this->scene->addItem(new QGraphicsPixmapItem(pix));

            ui->graphicsView->setScene(this->scene);
            ui->graphicsView->show();
        }
    }
}



/**
 * @brief CustomTab::~CustomTab
 */
CustomTab::~CustomTab()
{
    client->close();
    delete ui;
}

void CustomTab::on_btnAddRoi_clicked()
{
    QPixmap img(((QGraphicsPixmapItem *)ui->graphicsView->scene()->items().first())->pixmap());
    AddRoiDlg *dlg = new AddRoiDlg(this,img);
    connect(dlg,SIGNAL(newRoi(RoiDefinition*)),this,SLOT(newRoi(RoiDefinition*)));
    dlg->show();
}

void CustomTab::newRoi(RoiDefinition *roi)
{
    this->roiLst->append(roi);
}


void CustomTab::on_btnEdirRoi_clicked()
{
    RoiSelectorDlg *dlg = new RoiSelectorDlg(this,this->roiLst,QString("MODIFICACION"));
    connect(dlg,SIGNAL(edit(QString)),this,SLOT(roiEdit(QString)));
    dlg->show();
}

void CustomTab::on_btnDelRoi_clicked()
{
    RoiSelectorDlg *dlg = new RoiSelectorDlg(this,this->roiLst);
    connect(dlg,SIGNAL(del(QString)),this,SLOT(roiDel(QString)));
    dlg->show();
}


void CustomTab::roiEdit(QString roiAlias)
{

    RoiDefinition *selected = findRoi(roiAlias);
    this->roiLst->removeOne(selected);
    ui->btnAddRoi->click();
}


RoiDefinition * CustomTab::findRoi(QString alias)
{
    for (int i=0;i<this->roiLst->count();i++){
        if (this->roiLst->value(i)->getAlias() == alias)
        {
            return this->roiLst->value(i);
        }
    }
    return new RoiDefinition();
}


void CustomTab::roiDel(QString roiAlias)
{

    RoiDefinition *selected = findRoi(roiAlias);
    this->roiLst->removeOne(selected);
}

void CustomTab::on_qPlay_clicked()
{
    this->pause = false;
}

void CustomTab::on_btnPausar_clicked()
{
    this->pause = true;
}
