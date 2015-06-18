#include "roiselectordlg.h"
#include "ui_roiselectordlg.h"

RoiSelectorDlg::RoiSelectorDlg(QWidget *parent,QList<RoiDefinition *> *lst,QString operacion) :
    QDialog(parent),
    ui(new Ui::RoiSelectorDlg)
{
    ui->setupUi(this);
    this->lstRoi = lst;

    this->operacion = operacion;

    for(int i=0;i<lst->count();i++)
    {
        ui->listWidget->addItem(lst->value(i)->getAlias());
    }


}

RoiSelectorDlg::~RoiSelectorDlg()
{
    delete ui;
}

void RoiSelectorDlg::on_buttonBox_accepted()
{
    if(this->operacion=="MODIFICACION")
    {
        emit edit(ui->listWidget->selectionModel()->selectedRows().first().data().toString());
    }else
    {
        emit del(ui->listWidget->selectionModel()->selectedRows().first().data().toString());
    }
}
