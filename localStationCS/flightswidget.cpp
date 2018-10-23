#include "flightswidget.h"
#include "ui_flightswidget.h"
#include "localstationwidget.h"
#include "config.h"
#include "autoscrollinglabel.h"
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





    //  ********  Parametre de la table Widget  ********


    QFont font(Config::getFontFamily(),Config::getFontSize());//font(police, taille)
    QFont footer(Config::getFooterFontFamily(),Config::getFooterFontSize());
    QFont header(Config::getHeaderFontFamily(),Config::getHeaderFontSize());

    ui->m_pTableWidget->setRowCount(10);
    ui->m_pTableWidget->setColumnCount(6);
    m_TableHeader<<"Icao"<<"Modèle"<<"Pays"<<"Altitude"<<"Longitude"<<"Latitude";
    ui-> m_pTableWidget->setHorizontalHeaderLabels(m_TableHeader);
    ui-> m_pTableWidget->verticalHeader()->setVisible(false);
    ui->m_pTableWidget->setShowGrid(false);
    ui->m_pTableWidget->setFont(font);//appel police et police
    ui->m_pTableWidget->setStyleSheet("color: "+Config::getTableFontColor()+"; background-color: "+Config::getTableBgColor());

    ui->lineEdit->setFont(header);//taille de police du l'entete
    ui->lineEdit->setStyleSheet("color:"+Config::getHeaderFontColor()+"; background-color: "+Config::getHeaderBgColor());


    //  ********  Requete API  ********

    //QUrl urlPlanesBox ("https://opensky-network.org/api/states/all?lamin="+latiMini+"&lomin="+longiMini+"&lamax="+latiMaxi+"&lomax="+longiMaxi+"\"");
    QUrl url ("https://opensky-network.org/api/states/all?lamin=45.8389&lomin=5.9962&lamax=47.8229&lomax=10.5226");

    QNetworkRequest request;
    request.setUrl(url);

    networkManager->get(request);
    connect(networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(reponseUrl(QNetworkReply *)));

}

FlightsWidget::~FlightsWidget()
{
    delete ui;
}

void FlightsWidget::reloadData() {}//= 0 ; // recupere les donnees pour actualiser le widget
void FlightsWidget::changeFont() {}

void FlightsWidget::changeMode()
{

}





void FlightsWidget::reponseUrl(QNetworkReply *data){
    QJsonParseError jsonError;

    QJsonDocument doc = QJsonDocument::fromJson(data->readAll(), &jsonError) ;

    if(jsonError.error != QJsonParseError::NoError)
    {
        qDebug()<<QStringLiteral("thisParsed Json failure on FlightsWidget");
        qDebug()<<jsonError.errorString();
        return;
    }else{

        qDebug()<<QStringLiteral(" ok ParsedJson on FlightsWidget");

    }
    if (doc.isObject())
    {

        for ( int i=0;i<10 && i< doc.object().toVariantMap()["states"].toList().at(i).toList().count();i++)
        {
            QTableWidgetItem *icao = new QTableWidgetItem (doc.object().toVariantMap()["states"].toList().at(i).toList().at(0).toString());//icao

            ui-> m_pTableWidget->setItem(i,0, icao);


            //  ********  Requete a la Base  de donnée pour obtenir le modèle de l'avion********/
            QSqlQuery query;
            QString myIcao24 = doc.object().toVariantMap()["states"].toList().at(i).toList().at(0).toString();

            query.prepare("select icao24, manufacturername, model FROM avionmodel where icao24 = (:myIcao24)");

            query.bindValue(":myIcao24", myIcao24);

            if (query.exec())
            {
                if (query.next())
                {

                    AutoScrollingLabel *modelFly = new AutoScrollingLabel(this);
                    modelFly->setText(query.value(2).toString());
                    ui-> m_pTableWidget->setCellWidget(i,1, modelFly);
                    qDebug()<< query.value(2).toString();//modele
                }
            }
            QTableWidgetItem *longit= new QTableWidgetItem (doc.object().toVariantMap()["states"].toList().at(i).toList().at(5).toString());//longitude
            QTableWidgetItem *lat = new QTableWidgetItem (doc.object().toVariantMap()["states"].toList().at(i).toList().at(6).toString());//latitude
            QTableWidgetItem *country = new QTableWidgetItem (doc.object().toVariantMap()["states"].toList().at(i).toList().at(2).toString());//paysorigine
            QTableWidgetItem *altit = new QTableWidgetItem (doc.object().toVariantMap()["states"].toList().at(i).toList().at(7).toString());//altitude

            //ui-> m_pTableWidget->setItem(i,3, ele4);
            ui-> m_pTableWidget->setItem(i,4,longit);//longitude
            ui-> m_pTableWidget->setItem(i,5, lat);//latitude
            ui->m_pTableWidget->setItem(i,2, country);//pays
            ui->m_pTableWidget->setItem(i,3, altit);//altitude

            ui->m_pTableWidget->resizeColumnsToContents();
            ui->m_pTableWidget->resizeRowsToContents();
            ui->m_pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

        }
    }
}
