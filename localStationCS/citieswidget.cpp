#include "citieswidget.h"
#include "ui_citieswidget.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QStringList>
#include <QFont>
#include <QBrush>
#include <QDesktopWidget>
#include <QLabel>
#include <QDebug>
#include <config.h>
#include <localstationwidget.h>
CitiesWidget::CitiesWidget(QWidget *parent) :
    LocalStationWidget(parent), ui(new Ui::CitiesWidget)
{
    ui->setupUi(this);    
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
//    setLatLon("48.866667", "2.333333");
    reloadData();
}

void CitiesWidget::reloadData(){
    setLatLon(QString::number(Config::getLatitude()),
              QString::number(Config::getLongitude()));
}

void CitiesWidget::changeFont(){
    reloadData();
}

QStringList CitiesWidget::buildWebAdress(QString lat, QString lon) {
    QStringList adr;
    adr << "http://gd.geobytes.com/GetNearbyCities?Latitude=";
    adr += lat;
    adr.append("&Longitude=");
    adr << lon;
    return adr;
}

void CitiesWidget::setLatLon(QString lat, QString lon){
    QStringList adr = buildWebAdress(lat, lon);
    QNetworkRequest request;
    request.setUrl(QUrl(adr.join("")));
    manager->get(request);
}

void CitiesWidget::replyFinished(QNetworkReply* reply){
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Probleme de connexion !! \n" ;
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    array = doc.array();
    afficheTableView();
}

void CitiesWidget::afficheTableView() {
    int nbEle = array.size();
    int maxRow = 3;
    if (nbEle < maxRow)
        maxRow = nbEle;

    ui->tableWidget->setRowCount(maxRow);
    ui->tableWidget->setColumnCount(2);

    // SET labels of the header
    QStringList labels;
    labels << "Villes le plus proche" << "Distance (en km)";
    ui->tableWidget->setHorizontalHeaderLabels(labels);

    // SET font (family, size and color)
    QColor fc;  // foreGroundCouleur
    fc.setNamedColor(Config::getFontColor());
    QBrush *fcQBrush = new QBrush( fc, Qt::SolidPattern);

    QColor bc;  // foreGroundCouleur
    bc.setNamedColor(Config::getBgColor());
    QBrush *bcQBrush = new QBrush( bc, Qt::SolidPattern);

    int taillePolice = Config::getFontSize();
    QString fontFamily = Config::getFontFamily();
    QFont apiFont(fontFamily, taillePolice, QFont::Bold, false );    // italic = true

    // SET font, backgroundCouleur and foregroundCouleur of the 1st header
    QTableWidgetItem *h1 = new QTableWidgetItem();
    h1 = ui->tableWidget->horizontalHeaderItem(0);
    h1->setFont(apiFont);
    h1->setBackground(*bcQBrush);
    h1->setForeground(*fcQBrush);

    // SET the font backgroundCouleur and foregroundCouleur of the 2nd header
    h1 = ui->tableWidget->horizontalHeaderItem(1);
    h1->setFont(apiFont);
    h1->setBackground(*bcQBrush);
    h1->setForeground(*fcQBrush);

    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget->setShowGrid(false);

    ui->tableWidget->setStyleSheet("QTableView {selection-background-color: red;}");

    //    qDebug() << "Liste de couleurs reconnus " << QColor::colorNames();

    QTableWidgetItem *ville = new QTableWidgetItem();
    QTableWidgetItem *distance = new QTableWidgetItem();

    QJsonArray innerArray;
    for (int i=0; i < maxRow; i++) {
        innerArray = array[i].toArray();
        ville = new QTableWidgetItem(innerArray[1].toString());
        ville->setFont(apiFont);
        ville->setBackground(*bcQBrush );
        ville->setForeground(*fcQBrush );

        distance = new QTableWidgetItem(innerArray[7].toString());
        distance->setFont(apiFont);
        distance->setBackground(*bcQBrush);
        distance->setForeground(*fcQBrush);

        ui->tableWidget->setItem(i, 0, ville);
        ui->tableWidget->setItem(i, 1, distance);
    }

    if (nbEle > maxRow) {
        QString nextCitiesInfoText = "+";
        nextCitiesInfoText.append(QString::number(nbEle-maxRow));
        nextCitiesInfoText.append(" autres villes à moins de ");

        nextCitiesInfoText.append(array[nbEle-1].toArray()[7].toString());
        nextCitiesInfoText.append(" km");

        ui->label->setText(nextCitiesInfoText);
        ui->label->setFont(apiFont);

//        QString tmp = QString::number(myInt)
//        QString tmp = tr("%1").arg(myInt)
    }
    else
        ui->label->hide();

}

CitiesWidget::~CitiesWidget()
{
    delete ui;
}
