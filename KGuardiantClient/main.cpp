#include "kguardiantclient.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QStyle>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationDisplayName("KGClient");
    a.setApplicationName("KGClient");
    a.setApplicationVersion("1.0");

    KGuardiantClient w;
    w.window()->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, w.window()->size(), a.desktop()->availableGeometry()));
    w.show();
    
    return a.exec();
}
