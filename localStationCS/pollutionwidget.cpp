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
        this->setStyleSheet("background-color: "+Config::getBgColor());
        this->setStyleSheet("color: "+Config::getFontColor());
//        this->setFont(font);

//        ui->label_Titre->setFont(header);
//        ui->label_Titre2->setFont(header);

        ui->label_Titre->setStyleSheet("color: "+Config::getHeaderFontColor());
        ui->label_Titre2->setStyleSheet("color: "+Config::getHeaderFontColor());
        ui->label_Indice->setStyleSheet("color:"+Config::getFontColor());
        ui->label_Titre2->setStyleSheet("background-color: "+Config::getHeaderBgColor());

        ui->label_MinMax->setStyleSheet("color: "+Config::getFontColor());
        ui->label_Station->setStyleSheet("color: "+Config::getFontColor());

        ui->label_MinMax->setStyleSheet("background-color: "+Config::getFooterBgColor());
        ui->label_Station->setStyleSheet("background-color: "+Config::getFooterBgColor());
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
        ui->stackedWidget->setCurrentIndex(1);
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
//        PollutionWidget::paintEvent();
//    painter.end();
}



void PollutionWidget::reloadData()
{

}
void PollutionWidget::changeFont()
{

}
