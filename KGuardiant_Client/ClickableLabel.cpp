#include "ClickableLabel.h"

ClickableLabel::ClickableLabel( const QString& text, QWidget * parent ) :
    QLabel(parent)
{
  this->setText(text);
}

ClickableLabel::~ClickableLabel()
{
}

void ClickableLabel::mousePressEvent ( QMouseEvent * event )

{
  emit clicked(event->pos());
}

void ClickableLabel::mouseReleaseEvent( QMouseEvent *ev )
{
    emit releaseMouse(ev->pos());
}
