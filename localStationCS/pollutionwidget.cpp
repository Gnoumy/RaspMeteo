#include "pollutionwidget.h"
#include "ui_pollutionwidget.h"
#include "localstationwidget.h"
#include "config.h"

#include <QtNetwork>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QFont>
#include <QJsonDocument>
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QBrush>
#include <QPen>

PollutionWidget::PollutionWidget(QWidget *parent) :
    LocalStationWidget(parent),
    ui(new Ui::PollutionWidget)
{
    ui->setupUi(this);

    /*********************  PARAMETRES WIDGET  *****************************/
        //api Token:  82740759ffaf747ed45aad29febf758fffd33758
        QFont font(Config::getFontFamily(),Config::getFontSize());
        QFont footer(Config::getFooterFontFamily(),Config::getFooterFontSize());
        QFont header(Config::getHeaderFontFamily(),Config::getHeaderFontSize());

        this->setStyleSheet("color: "+Config::getFontColor()+";background-color: "+Config::getBgColor());
        this->setFont(font);

        ui->lineEdit_header->setFont(header);
        ui->lineEdit_header->setStyleSheet("color: "+Config::getHeaderFontColor()+";background-color: "+Config::getHeaderBgColor());
        ui->lineEdit_header->setText("Pollution");

        ui->label_Titre2->setFont(header);
        ui->label_Titre2->setStyleSheet("color: "+Config::getHeaderFontColor()+";background-color: "+Config::getHeaderBgColor());

        ui->label_Indice->setStyleSheet("color:"+Config::getFontColor()+";background-color: "+Config::getBgColor());

        ui->label_MinMax->setFont(footer);
        ui->label_MinMax->setStyleSheet("color:"+Config::getFooterFontColor()+";background-color: "+Config::getFooterBgColor());

        ui->label_Station->setFont(footer);
        ui->label_Station->setStyleSheet("color: "+Config::getFooterFontColor()+";background-color: "+Config::getFooterBgColor());
    /*********************   FIN PARAMETRES   *****************************/


    /**********************   REQUETE JSON   ******************************/
        QNetworkRequest request;
        QString latitude = QString::number(Config::getLatitude());
        QString longitude = QString::number(Config::getLatitude());
        QUrl url("https://api.waqi.info/feed/geo:"+latitude+";"+longitude+"/?token=82740759ffaf747ed45aad29febf758fffd33758"); //Plessis Robinson
        request.setUrl(url);
        networkManager->get(request);
        connect(networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(premierePage(QNetworkReply *)));
        connect(networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(deuxiemePage(QNetworkReply *)));
        ui->stackedWidget->setCurrentIndex(0);
    /********************   FIN REQUETE JSON   ****************************/
}

PollutionWidget::~PollutionWidget()
{
    delete ui;
}

void PollutionWidget::premierePage(QNetworkReply *data)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data->readAll());
    ui->label_Indice->setText(jsonDoc.object().value("data").toObject().toVariantMap()["aqi"].toString());
    ui->label_Station->setText(jsonDoc.object().value("data").toObject().toVariantMap()["city"].toMap()["name"].toString());
}

void PollutionWidget::deuxiemePage(QNetworkReply *data)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data->readAll());
    ui->label_Titre2->setStyleSheet("color: "+Config::getHeaderFontColor());

//    QPainter painter;
//    painter.begin(this);
//    GraphPollutionWidget::paintEvent(QPaintEvent);
//    painter.end();
}



void PollutionWidget::reloadData()
{

}
void PollutionWidget::changeFont()
{

}
