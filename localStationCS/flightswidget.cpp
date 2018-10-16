#include "flightswidget.h"
#include "ui_flightswidget.h"
#include "localstationwidget.h"
#include "config.h"
#include <QUrl>
#include <QObject>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QString>
#include <QJsonArray>
#include <QLineEdit>
#include <QDateTime>
#include<QApplication>
#include <QTableWidget>

FlightsWidget::FlightsWidget(QWidget *parent) :
    LocalStationWidget(parent),
    ui(new Ui::FlightsWidget)
{
    ui->setupUi(this);

    ui->m_pTableWidget->setRowCount(10);
    ui->m_pTableWidget->setColumnCount(6);
    m_TableHeader<<"Icao"<<"Fabricant"<<"Modèle"<<"Pays"<<"Longitude"<<"Latitude";
    ui-> m_pTableWidget->setHorizontalHeaderLabels(m_TableHeader);
    ui-> m_pTableWidget->verticalHeader()->setVisible(false);
    ui->m_pTableWidget->setShowGrid(false);


    QNetworkRequest request;

    QUrl url ("https://opensky-network.org/api/states/all?lamin=45.8389&lomin=5.9962&lamax=47.8229&lomax=10.5226");

    request.setUrl(url);
    networkManager->get(request);
    connect(networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(reponseUrl(QNetworkReply *)));

}

FlightsWidget::~FlightsWidget()
{
    delete ui;
}


void FlightsWidget::reponseUrl(QNetworkReply *data){
    QJsonDocument doc = QJsonDocument::fromJson(data->readAll()) ;
    for ( int i=0;i<10 && i< doc.object().toVariantMap()["states"].toList().at(i).toList().count();i++)
    {
        QTableWidgetItem *ele1 = new QTableWidgetItem (doc.object().toVariantMap()["states"].toList().at(i).toList().at(0).toString());//icao
        ui-> m_pTableWidget->setItem(i,0, ele1);


        //Requete base de donnée pour obtenir les caractéristiques de l'avion

        QSqlQuery query;
        QString myIcao24 = doc.object().toVariantMap()["states"].toList().at(i).toList().at(0).toString();
        //qDebug()<< query.value(0).toString();//icao
        query.prepare("select icao24, manufacturername, model FROM avionmodel where icao24 = (:myIcao24)");
        // query.bindValue(":name", name);
        query.bindValue(":myIcao24", myIcao24);

        if (query.exec())
        {
            if (query.next())
            {
                QTableWidgetItem *ele5 = new QTableWidgetItem(query.value(1).toString());//fabricant
                ui-> m_pTableWidget->setItem(i,1, ele5);

                //qDebug()<< query.value(1).toString();//fabricant

                QTableWidgetItem *ele6 = new QTableWidgetItem(query.value(2).toString());//modele
                ui-> m_pTableWidget->setItem(i,2, ele6);

                //qDebug()<< query.value(2).toString();//modele
            }
        }
        QTableWidgetItem *ele2 = new QTableWidgetItem (doc.object().toVariantMap()["states"].toList().at(i).toList().at(5).toString());//longitude
        QTableWidgetItem *ele3 = new QTableWidgetItem (doc.object().toVariantMap()["states"].toList().at(i).toList().at(6).toString());//latitude
        QTableWidgetItem *ele4 = new QTableWidgetItem (doc.object().toVariantMap()["states"].toList().at(i).toList().at(2).toString());//paysorigine
        //ui-> m_pTableWidget->setItem(i,3, ele4);
        ui-> m_pTableWidget->setItem(i,4, ele2);
        ui-> m_pTableWidget->setItem(i,5, ele3);
        ui->m_pTableWidget->setItem(i,3, ele4);

    }
}
