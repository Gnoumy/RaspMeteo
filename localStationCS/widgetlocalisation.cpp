#include "widgetlocalisation.h"
#include "ui_widgetlocalisation.h"
#include <QFont>
#include <QPainter>
#include "config.h"

widgetlocalisation::widgetlocalisation(QWidget *parent) :
    LocalStationWidget(parent),
    ui(new Ui::widgetlocalisation)
{
    ui->setupUi(this);
    QFont font(Config::getTableFontFamily(),Config::getTableFontSize());//font(police, taille, couleur)
    QFont header(Config::getHeaderFontFamily(),Config::getHeaderFontSize());
    ui->tableWidget->setMinimumWidth(250);
    ui->tableWidget->setFont(font);
    ui->tableWidget->setStyleSheet("color :"+Config::getTableFontColor()+";background-color :"+Config::getTableBgColor());
    ui->tableWidget->setColumnCount(1);// le nombre de colonne
    ui->tableWidget->setRowCount(6);// le nombre de ligne
    ui->tableWidget->horizontalHeader()->hide();//permet de ne pas afficher les numeros de ligne
    ui->tableWidget->verticalHeader()->hide();// permet de ne pas afficher les numeros de ligne
    ui->tableWidget->setShowGrid(false);// pour enlever les grilles dans un tableau

    ui->lineEdit->setFont(header);//taille de police du l'entete
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit->setStyleSheet("color :"+Config::getHeaderFontColor()+";background-color :"+Config::getHeaderBgColor());
    ui->lineEdit->setAlignment(Qt::AlignHCenter);
    manager = new NetworkAccessManager(this);

    QString lati = QString::number(double(Config::getLatitude()),'g',10);
    QString longi = QString::number(double(Config::getLongitude()),'g',10);

    QUrl url("https://nominatim.openstreetmap.org/reverse?format=json&lat="+lati+"&lon="+longi+"&zoom=18&addressdetails=1");
   //QUrl url("https://api.navitia.io/v1/coverage/sandbox/stop_areas/stop_area%3ARAT%3ASA%3AGDLYO/stop_schedules?items_per_schedule=2&");
    //url.setUserName("45205f1c-86f6-4740-9af7-a5dbe3fcf15d");
    //url.setPassword("dieynaba92");
    QNetworkRequest request;
    request.setUrl(url);
     //connect(manager, SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)), this, SLOT(authenticationRequired(QNetworkReply*, QAuthenticator*)));
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
    manager->get(request);

}

void widgetlocalisation::replyFinished(QNetworkReply *reply)
{
    QByteArray bytes = reply->readAll();
    QJsonParseError jsonError;
    QJsonDocument doucument =QJsonDocument::fromJson(bytes,&jsonError);
    if(jsonError.error != QJsonParseError::NoError)
    {
            qDebug()<<QStringLiteral("Parsed Json failure");
            qDebug()<<jsonError.errorString();
            return;
    }
    QJsonDocument myJson=QJsonDocument::fromJson(bytes);
    QString vil(myJson.object().toVariantMap()["address"].toMap()["town"].toString());
    QString cod(myJson.object().toVariantMap()["address"].toMap()["postcode"].toString());
    QString sta(myJson.object().toVariantMap()["address"].toMap()["state"].toString());
    QString ru(myJson.object().toVariantMap()["address"].toMap()["road"].toString());
    QString lon(myJson.object().toVariantMap()["lon"].toString());
    QString lat(myJson.object().toVariantMap()["lat"].toString());


    QTableWidgetItem *rue = new QTableWidgetItem(ru);
    ui->tableWidget->setItem(0, 0, rue);

    QTableWidgetItem *ville = new QTableWidgetItem(vil);
    ui->tableWidget->setItem(0, 1, ville);

    QTableWidgetItem *code = new QTableWidgetItem(cod);
    ui->tableWidget->setItem(0, 2, code);

    QTableWidgetItem *state = new QTableWidgetItem(sta);
    ui->tableWidget->setItem(0, 3, state);

    QTableWidgetItem *latitude = new QTableWidgetItem(lat);
    ui->tableWidget->setItem(0, 4, latitude);

    QTableWidgetItem *longitude = new QTableWidgetItem(lon);
    ui->tableWidget->setItem(0, 5, longitude);

}

/*void widgetlocalisation::resizeEvent(QResizeEvent *)
{
    ui->tableWidget->setColumnWidth(0,this->width());
}*/

void widgetlocalisation::paintEvent(QPaintEvent *)
{
    ui->tableWidget->setColumnWidth(0,this->width());
}

void widgetlocalisation::reloadData()
{
    QString lati = QString::number(double(Config::getLatitude()),'g',10);
    QString longi = QString::number(double(Config::getLongitude()),'g',10);

    QFont font(Config::getTableFontFamily(),Config::getTableFontSize());//font(police, taille, couleur)
    QFont header(Config::getHeaderFontFamily(),Config::getHeaderFontSize());
    ui->tableWidget->setMinimumWidth(250);
    ui->tableWidget->setFont(font);
    ui->lineEdit->setFont(header);
    ui->tableWidget->setStyleSheet("color :"+Config::getTableFontColor()+";background-color :"+Config::getTableBgColor());
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));

}

void widgetlocalisation::changeMode()
{

}
widgetlocalisation::~widgetlocalisation()
{
    delete ui;
}
