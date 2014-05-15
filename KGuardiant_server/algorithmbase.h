#ifndef ALGORITHMBASE_H
#define ALGORITHMBASE_H

#include <QString>
#include <QMap>

class AlgorithmBase
{
protected:
    QString *algorithmName;
    QMap<QString, QString> *parameters;

public:
    AlgorithmBase();
    virtual ~AlgorithmBase();
    virtual void run();
    virtual void logParams();
    virtual void execute();
    virtual void logOutput();

};

#endif // ALGORITHMBASE_H
