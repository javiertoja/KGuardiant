#include "addroidlg.h"
#include "ui_addroidlg.h"

AddRoiDlg::AddRoiDlg(QWidget *parent,QPixmap example) :
    QDialog(parent),
    ui(new Ui::AddRoiDlg)
{
    ui->setupUi(this);
    clbl = new ClickableLabel("",this);
    clbl->setPixmap(example);

    connect(clbl,SIGNAL(clicked(QPoint)),this,SLOT(clicked(QPoint)));
    connect(clbl,SIGNAL(releaseMouse(QPoint)),this,SLOT(releaseMouse(QPoint)));

    ui->vLayout->addWidget(clbl);
    clbl->show();

    this->actRoi = new RoiDefinition(this);
}

AddRoiDlg::~AddRoiDlg()
{
    delete ui;
}


void AddRoiDlg::clicked(QPoint pos)
{
    this->startPoint = new QPoint(pos.rx(),pos.ry());
}

void AddRoiDlg::releaseMouse(QPoint pos)
{
    this->endPoint = new QPoint(pos.rx(),pos.ry());
    qDebug() << "["<<this->startPoint->rx()<<","<<this->startPoint->ry()<<"]["<< this->endPoint->rx()<<","<< this->endPoint->ry()<<"]";

    QPainter paint;
    QPixmap px = *this->clbl->pixmap();
    paint.begin(&px);
    paint.setPen(QColor(255,34,255,255));
    QPoint tl(minimun(this->startPoint->rx(),this->endPoint->rx()),minimun(this->startPoint->ry(),this->endPoint->ry()));
    QPoint br(maximun(this->startPoint->rx(),this->endPoint->rx()),maximun(this->startPoint->ry(),this->endPoint->ry()));
    paint.drawRect(QRect(tl, br));
    paint.end();
    clbl->setPixmap(px);
}

void AddRoiDlg::on_buttonBox_accepted()
{

    this->actRoi->setAlias(ui->lineEdit->text());
    this->actRoi->setColor(new QColor(255,255,255,255));
    QPoint tl(minimun(this->startPoint->rx(),this->endPoint->rx()),minimun(this->startPoint->ry(),this->endPoint->ry()));
    QPoint br(maximun(this->startPoint->rx(),this->endPoint->rx()),maximun(this->startPoint->ry(),this->endPoint->ry()));
    this->actRoi->setBoundRect(new QRect(tl, br));
    emit newRoi(this->actRoi);
}

int AddRoiDlg::minimun(int a1, int a2)
{
    if (a1 <= a2){
        return a1;
    }else{
        return a2;
    }
}

int AddRoiDlg::maximun(int a1, int a2)
{
    if (a1 >= a2){
        return a1;
    }else{
        return a2;
    }
}
