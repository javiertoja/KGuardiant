#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QThread>
#include <QHash>
#include <QHashIterator>
#include <iostream>
#include <QSocketNotifier>
#include <unistd.h>

#include <tcpconnection.h>

class Console : public QThread
{
    Q_OBJECT
public:
    explicit Console(QObject *parent = 0);
    
signals:
    void checkClients();
    void stopServer();
    void startServer();
    void reloadConfig();
    void finish();
    void textReceived(QString message);
public slots:
    void printClients(QHash<qintptr, TCPConnection *> *clients);
    void result(QString msg);
    void startC();
    void stopC();
    void run();
    void text();

private:
    bool out;
    char option;
    QSocketNotifier *notifier;

    void showOpts();
    void parseOpts();
};

#endif // CONSOLE_H
