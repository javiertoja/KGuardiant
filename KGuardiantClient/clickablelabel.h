
#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QPoint>

class ClickableLabel : public QLabel
{
Q_OBJECT

public:
explicit ClickableLabel( const QString& text ="", QWidget * parent = 0 );
    ~ClickableLabel();

signals:
    void clicked(QPoint pos);
    void releaseMouse(QPoint pos);

protected:
    void mousePressEvent ( QMouseEvent * event ) ;
    void mouseReleaseEvent (QMouseEvent *ev);
};
#endif // CLICKABLELABEL_H
