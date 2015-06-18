#ifndef CUSTOMTAB_H
#define CUSTOMTAB_H

#include <QWidget>
#include <QTcpSocket>
#include <QList>
#include "opencv/cv.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <qtOpencv/cvmatandqimage.h>
#include <QGraphicsPixmapItem>
#include <clickablelabel.h>

#include <addroidlg.h>
#include <roiselectordlg.h>
#include <stationdefinition.h>
#include <roidefinition.h>
#include <QDateTime>


namespace Ui {
class CustomTab;
}

class CustomTab : public QWidget
{
    Q_OBJECT

public:
    explicit CustomTab(QWidget *parent = 0, QString tabName = "");
    ~CustomTab();
    RoiDefinition *findRoi(QString alias);
public slots:

    void setupConnection(QString ip,QString porto);
    void deleteConnection();
    void readyRead();
    void newRoi(RoiDefinition *roi);
    void roiEdit(QString roiAlias);
    void roiDel(QString roiAlias);
    void disconnected();

signals:
    void closeTab();
    void alerta(QString alert);
    void clearAlerta();

private slots:
    void on_btnAddRoi_clicked();

    void on_btnEdirRoi_clicked();

    void on_btnDelRoi_clicked();

    void on_qPlay_clicked();

    void on_btnPausar_clicked();

private:
    Ui::CustomTab *ui;
    QTcpSocket *client;
    ClickableLabel *clbl;
    QGraphicsScene *scene;
    QString tabName;
    StationDefinition *connection;
    bool pause;
    QList<RoiDefinition *> *roiLst;
    QImage *imgExample;
};

#endif // CUSTOMTAB_H
