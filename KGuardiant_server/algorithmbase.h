#ifndef ALGORITHMBASE_H
#define ALGORITHMBASE_H

#include <QString>

class AlgorithmBase
{
protected:
    QString *algorithmName;
    QString *parameters;

public:
    AlgorithmBase();
    virtual ~AlgorithmBase();
    virtual void run();
    virtual void logParams();
    virtual void consoleInput();
    virtual void execute();
    virtual void logOutput();

};

#endif // ALGORITHMBASE_H
