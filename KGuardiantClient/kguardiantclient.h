#ifndef KGUARDIANTCLIENT_H
#define KGUARDIANTCLIENT_H

#include <QMainWindow>
#include <conectardialog.h>
#include <aboutdialog.h>
#include <customtab.h>
#include <QTimer>

namespace Ui {
class KGuardiantClient;
}

class KGuardiantClient : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit KGuardiantClient(QWidget *parent = 0);
    ~KGuardiantClient();
    
public slots:
    void closeTab();
    void in_alerta(QString alerta);
    void clearAlerta();
signals:

    void conectar(QString ip, QString porto);
private slots:

    void on_newConnection(QString data);
    void on_actionConectar_triggered();
    void on_actionAbout_triggered();
    void on_actionDesconectar_triggered();


private:
    Ui::KGuardiantClient *ui;
    ConectarDialog *conectarDlg;
    AboutDialog *about;
};

#endif // KGUARDIANTCLIENT_H
