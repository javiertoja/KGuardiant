#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QDir>
#include <QSettings>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT
    
public:
    explicit Client(QWidget *parent = 0);
    ~Client();
    
private slots:
    void on_lineEdit_returnPressed();
    void readyRead();
private:
    Ui::Client  *ui;

    QTcpSocket  *socket;
    QDir        *dirConf;
    QSettings   *conf;
};

#endif // CLIENT_H
