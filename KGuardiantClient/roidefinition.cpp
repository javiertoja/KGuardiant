#include "roidefinition.h"

RoiDefinition::RoiDefinition(QObject *parent) :
    QObject(parent)
{
}

void RoiDefinition::setAlias(QString alias)
{
    this->alias = alias;
}


void RoiDefinition::setBoundRect(QRect *rec)
{
    this->boundRect = rec;
}

 void RoiDefinition::setColor(QColor *cor)
 {
     this->cor = cor;
 }

 QString RoiDefinition::getAlias()
 {
     return this->alias;
 }

 QRect *RoiDefinition::getBoundRect()
 {
     return this->boundRect;
 }

 QColor *RoiDefinition::getColor()
 {
     return this->cor;
 }
