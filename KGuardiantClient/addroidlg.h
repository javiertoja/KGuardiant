#ifndef ADDROIDLG_H
#define ADDROIDLG_H

#include <QDialog>
#include <clickablelabel.h>
#include <roidefinition.h>
#include <QDebug>
#include <QPainter>


namespace Ui {
class AddRoiDlg;
}

class AddRoiDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddRoiDlg(QWidget *parent = 0,QPixmap example=QPixmap());
    ~AddRoiDlg();
    int minimun(int a1, int a2);
    int maximun(int a1, int a2);
public slots:
    void clicked(QPoint pos);
    void releaseMouse(QPoint pos);

signals:
    void newRoi(RoiDefinition *def);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddRoiDlg *ui;
    QPoint *startPoint;
    QPoint *endPoint;
    RoiDefinition *actRoi;
    ClickableLabel *clbl;
};

#endif // ADDROIDLG_H
