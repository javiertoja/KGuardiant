#include "conectardialog.h"
#include "ui_conectardialog.h"

ConectarDialog::ConectarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConectarDialog)
{
    settings = Configuracion::Instance();
    log = Logger::Instance();

    ui->setupUi(this);
    lstServers = new QStringListModel(parent);
    getLstServers(settings->getValue("servers","serverlist"));

    ui->lstEstacions->setModel(lstServers);
}

/**
 * @brief ConectarDialog::~ConectarDialog
 */
ConectarDialog::~ConectarDialog()
{
    delete ui;
}

/**
 * @brief ConectarDialog::getLstServers
 * @param lst
 */
void ConectarDialog::getLstServers(QVariant lst){

        lstServers->setStringList(lst.toStringList());
}

void ConectarDialog::on_buttonBox_accepted()
{
    QString selected;
    if (ui->lstEstacions->selectionModel()->selectedRows().count() == 1)
    {
        //qDebug() << "Seleccionado elemento:" << ui->lstEstacions->selectionModel()->selectedRows().first().data();
        selected = ui->lstEstacions->selectionModel()->selectedRows().first().data().toString();
        emit newConnection(selected);
    }
}
