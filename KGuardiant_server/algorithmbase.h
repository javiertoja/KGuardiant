#ifndef ALGORITHMBASE_H
#define ALGORITHMBASE_H

#include <QString>
#include <QMap>
#include <QThread>

class AlgorithmBase : public QThread
{
    Q_OBJECT
protected:
    QString *algorithmName;
    QMap<QString, QString> *parameters;

public:
    AlgorithmBase();
    virtual ~AlgorithmBase();

    virtual void logParams();
    virtual void execute();
    virtual void logOutput();

protected:
    virtual void run();
    int stop;
public slots:
    void stopTask(int number);
signals:
    void resultado(int number);
};

#endif // ALGORITHMBASE_H
