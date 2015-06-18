#ifndef ROISELECTORDLG_H
#define ROISELECTORDLG_H

#include <QDialog>
#include <QList>
#include <roidefinition.h>
#include <QStringListModel>
#include <QListIterator>

namespace Ui {
class RoiSelectorDlg;
}

class RoiSelectorDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit RoiSelectorDlg(QWidget *parent = 0,QList<RoiDefinition *> *lst= 0,QString operacion = "");
    ~RoiSelectorDlg();

signals:
    void edit(QString alias);
    void del(QString alias);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::RoiSelectorDlg *ui;
    QList<RoiDefinition *> *lstRoi;
    QString operacion;
};

#endif // ROISELECTORDLG_H
