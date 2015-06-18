#ifndef CONECTARDIALOG_H
#define CONECTARDIALOG_H

#include <QDialog>
#include <QDebug>
#include <configuracion.h>
#include <logger.h>
#include <QStringListModel>

namespace Ui {
class ConectarDialog;
}

class ConectarDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConectarDialog(QWidget *parent = 0);
    ~ConectarDialog();
    
private slots:
    void on_buttonBox_accepted();

signals:
    void newConnection(QString data);

private:
    Ui::ConectarDialog *ui;

    Configuracion *settings;
    Logger *log;
    QStringListModel *lstServers;


    virtual void getLstServers(QVariant lst);

};

#endif // CONECTARDIALOG_H
