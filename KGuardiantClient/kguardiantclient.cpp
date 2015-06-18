#include "kguardiantclient.h"
#include "ui_kguardiantclient.h"

KGuardiantClient::KGuardiantClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KGuardiantClient)
{
    ui->setupUi(this);
    conectarDlg = new ConectarDialog(this);
    about = new AboutDialog(this);

    connect(conectarDlg,SIGNAL(newConnection(QString)),this,SLOT(on_newConnection(QString)));
}

/**
 * @brief KGuardiantClient::on_newConnection
 * @param data
 */
void KGuardiantClient::on_newConnection(QString data)
{
    QString name = data.split("|").first();
    QString ip = data.split("|").back().split(":").first();
    QString porto = data.split("|").back().split(":").back();
    CustomTab *newTab = new CustomTab(this,name);

    ui->tabWidget->setCurrentIndex(ui->tabWidget->addTab(newTab, QIcon(),name));
    connect(this,SIGNAL(conectar(QString,QString)),newTab,SLOT(setupConnection(QString,QString)));
    connect(newTab,SIGNAL(closeTab()),this,SLOT(closeTab()));
    connect(newTab,SIGNAL(alerta(QString)),this,SLOT(in_alerta(QString)));
    connect(newTab,SIGNAL(clearAlerta()),this,SLOT(clearAlerta()));

    emit conectar(ip,porto);
}

/**
 * @brief KGuardiantClient::closeTab
 * @param tabName
 */
void KGuardiantClient::closeTab()
{
    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
}

/**
 * @brief KGuardiantClient::~KGuardiantClient
 */
KGuardiantClient::~KGuardiantClient()
{
    delete ui;
}

/**
 * @brief KGuardiantClient::on_actionConectar_triggered
 */
void KGuardiantClient::on_actionConectar_triggered()
{
    conectarDlg->show();
}

/**
 * @brief KGuardiantClient::on_actionAbout_triggered
 */
void KGuardiantClient::on_actionAbout_triggered()
{
    about->show();
}


/**
 * @brief KGuardiantClient::on_actionDesconectar_triggered
 */
void KGuardiantClient::on_actionDesconectar_triggered()
{
    QTimer::singleShot(10,ui->tabWidget->widget(ui->tabWidget->currentIndex()),SLOT(deleteConnection()));
}

/**
 * @brief KGuardiantClient::in_alerta
 * @param alerta
 */
void KGuardiantClient::in_alerta(QString alerta)
{
    if (!ui->lblAlertas->text().contains(alerta))
    {
        ui->lblAlertas->setText(ui->lblAlertas->text()+alerta);
    }
}

/**
 * @brief KGuardiantClient::clearAlerta
 */
void KGuardiantClient::clearAlerta()
{
    ui->lblAlertas->setText("");
}
