#include "stationdefinition.h"

/**
 * @brief StationDefinition::StationDefinition
 * @param parent
 * @param alias
 * @param porto
 * @param host
 * @param client
 */
StationDefinition::StationDefinition(QObject *parent, QString alias, qintptr porto, QString host, QTcpSocket *client) :
    QObject(parent)
{
    this->alias = alias;
    this->host = host;
    this->porto = porto;
    this->client = client;
}

/**
 * @brief StationDefinition::getAlias
 * @return
 */
QString StationDefinition::getAlias()
{
    return this->alias;
}

/**
 * @brief StationDefinition::getHost
 * @return
 */
QString StationDefinition::getHost()
{
    return this->host;
}

/**
 * @brief StationDefinition::getPorto
 * @return
 */
qintptr StationDefinition::getPorto()
{
    return this->porto;
}

QTcpSocket *StationDefinition::getClient()
{
    return this->client;
}
