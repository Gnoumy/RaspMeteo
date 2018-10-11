#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationDomain("LocalStationProject");
    QCoreApplication::setApplicationName("Settings");
    QSettings::setDefaultFormat(QSettings::IniFormat) ;
    MainWindow w;
    w.show();

    return a.exec();
}
