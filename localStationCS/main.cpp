#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QSqlDatabase>
#include<QSqlQuery>
#include <QSqlError>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationDomain("LocalStationProject");
    QCoreApplication::setApplicationName("Settings");
    QSettings::setDefaultFormat(QSettings::IniFormat) ;
    QSettings settings;
    settings.setValue("database_path", "/home/formation/.config/LocalStationProject/avionDatabase.db");
    QSqlDatabase mydb =QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(settings.value("database_path").toString());
    //qDebug()<<settings.fileName();
    MainWindow w;
    w.show();

    return a.exec();
}
