#ifndef STATIONDEFINITION_H
#define STATIONDEFINITION_H

#include <QObject>
#include <QString>
#include <QTcpSocket>

class StationDefinition : public QObject
{
    Q_OBJECT
public:
    explicit StationDefinition(QObject *parent = 0, QString alias = "", qintptr porto = 0, QString host = "", QTcpSocket *client = 0);
    QString getAlias();
    QString getHost();
    qintptr getPorto();
    QTcpSocket *getClient();
private:
    QString alias;
    qintptr porto;
    QString host;
    QTcpSocket *client;

};

#endif // STATIONDEFINITION_H
