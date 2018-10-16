#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QSqlDatabase>
#include<QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QRegExp>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationDomain("LocalStationProject");
    QCoreApplication::setApplicationName("Settings");
    QSettings::setDefaultFormat(QSettings::IniFormat) ;
    QSettings settings;
    QString filedatabasename=settings.fileName().replace(QRegExp("Settings.ini$"),"avionDatabase.db");
    QSqlDatabase mydb =QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(filedatabasename);


    if (!mydb.open()){
        qDebug()<<"connection to Avion database failed";
        qDebug()<<mydb.lastError();
    }else{

     qDebug()<< "connected to Avion database "  ;}


    MainWindow w;
    w.show();

    return a.exec();
}
