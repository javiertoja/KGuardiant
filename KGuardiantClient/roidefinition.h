#ifndef ROIDEFINITION_H
#define ROIDEFINITION_H

#include <QObject>
#include <QRect>
#include <QString>
#include <QColor>

class RoiDefinition : public QObject
{
    Q_OBJECT
public:
    explicit RoiDefinition(QObject *parent = 0);

    void setBoundRect(QRect *rec);
    void setAlias(QString alias);
    void setColor(QColor *cor);

    QRect *getBoundRect();
    QString getAlias();
    QColor *getColor();

private:
    QRect *boundRect;
    QString alias;
    QColor *cor;
};

#endif // ROIDEFINITION_H
