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
#include <QPushButton>

PollutionWidget::PollutionWidget(QWidget *parent) :
    LocalStationWidget(parent),
    ui(new Ui::PollutionWidget)
{
    ui->setupUi(this);

    /*********************  PARAMETRES WIDGET  *****************************/
        QFont font(Config::getTableFontFamily(),Config::getFontSize());
        QFont footer(Config::getFooterFontFamily(),Config::getFooterFontSize());
        QFont header(Config::getHeaderFontFamily(),Config::getHeaderFontSize());

        ui->lineEdit_header->setFont(header);
        ui->lineEdit_header->setStyleSheet("color: "+Config::getHeaderFontColor()+";background-color: "+Config::getHeaderBgColor());
        ui->lineEdit_header->setText("Pollution");

        ui->label_Indice->setFont(font);
        ui->label_Indice->setStyleSheet("color:"+Config::getTableFontColor()+";background-color: "+Config::getTableBgColor());

        ui->label_MinMax->setFont(footer);
        ui->label_MinMax->setStyleSheet("color:"+Config::getFooterFontColor()+";background-color: "+Config::getFooterBgColor());

        ui->label_Station->setFont(footer);
        ui->label_Station->setStyleSheet("color: "+Config::getFooterFontColor()+";background-color: "+Config::getFooterBgColor());
    /*********************   FIN PARAMETRES   *****************************/

    /**********************   REQUETE JSON   ******************************/
        QNetworkRequest request;
        QString latitude = QString::number(Config::getLatitude());
        QString longitude = QString::number(Config::getLongitude());
        QUrl url("https://api.waqi.info/feed/geo:"+latitude+";"+longitude+"/?token=82740759ffaf747ed45aad29febf758fffd33758"); //Plessis Robinson
        request.setUrl(url);
        networkManager->get(request);
        connect(networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(premierePage(QNetworkReply *)));
    /********************   FIN REQUETE JSON   ****************************/
}
void PollutionWidget::premierePage(QNetworkReply *data)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data->readAll());
    QJsonParseError jsonError;
    if(jsonError.error != QJsonParseError::NoError)
    {
        qDebug()<<QStringLiteral("Parsed Json failure PollutionWidget");
        return;
    }
    ui->label_Indice->setText(jsonDoc.object().value("data").toObject().toVariantMap()["aqi"].toString());
    ui->label_Station->setText(jsonDoc.object().value("data").toObject().toVariantMap()["city"].toMap()["name"].toString());
}
void PollutionWidget::reloadData()
{
    QFont font(Config::getTableFontFamily(),Config::getFontSize());
    QFont footer(Config::getFooterFontFamily(),Config::getFooterFontSize());
    QFont header(Config::getHeaderFontFamily(),Config::getHeaderFontSize());

    ui->lineEdit_header->setFont(header);
    ui->lineEdit_header->setStyleSheet("color: "+Config::getHeaderFontColor()+";background-color: "+Config::getHeaderBgColor());
    ui->label_Indice->setFont(font);
    ui->label_Indice->setStyleSheet("color:"+Config::getTableFontColor()+";background-color: "+Config::getTableBgColor());
    ui->label_MinMax->setFont(footer);
    ui->label_MinMax->setStyleSheet("color:"+Config::getFooterFontColor()+";background-color: "+Config::getFooterBgColor());
    ui->label_Station->setFont(footer);
    ui->label_Station->setStyleSheet("color: "+Config::getFooterFontColor()+";background-color: "+Config::getFooterBgColor());

    QNetworkRequest request2;
    QString latitude = QString::number(Config::getLatitude());
    QString longitude = QString::number(Config::getLongitude());
    QUrl url("https://api.waqi.info/feed/geo:"+latitude+";"+longitude+"/?token=82740759ffaf747ed45aad29febf758fffd33758"); //Plessis Robinson
    request2.setUrl(url);
    networkManager->get(request2);
    connect(networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(premierePage(QNetworkReply *)));
}
void PollutionWidget::changeMode()
{

}
PollutionWidget::~PollutionWidget()
{
    delete ui;
}
