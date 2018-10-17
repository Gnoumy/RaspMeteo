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
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    ui->setupUi(this);    
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this,
            SLOT(replyFinished(QNetworkReply*)));
    //connect(this, SIGNAL(QWidget::resizeEvent() ) )
    reloadData();
}

void CitiesWidget::reloadData(){
    QStringList adr = buildWebAdress(QString::number(Config::getLatitude()),
                                     QString::number(Config::getLongitude()));
    QNetworkRequest request;
    request.setUrl(QUrl(adr.join("")));
    manager->get(request);
}

void CitiesWidget::changeFont(){
    afficheAll();
}

void CitiesWidget::resizeEvent(QResizeEvent * /* event */) {
    ui->tableWidget->setColumnWidth(0, 0.75*width());
    ui->tableWidget->setColumnWidth(1, 0.25*width());
}

QStringList CitiesWidget::buildWebAdress(QString lat, QString lon) {
    QStringList adr;
    adr << "http://gd.geobytes.com/GetNearbyCities?Latitude=";
    adr += lat;
    adr.append("&Longitude=");
    adr << lon;
    return adr;
}

void CitiesWidget::replyFinished(QNetworkReply* reply){
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Probleme de connexion !! \n" ;
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    array = doc.array();
    afficheAll();
}

void CitiesWidget::afficheTableView() {
    int nbEle = array.size();
    int maxRow = 3;
    if (nbEle < maxRow)
        maxRow = nbEle;

    ui->tableWidget->setRowCount(maxRow);
    ui->tableWidget->setColumnCount(2);

    QFont apiFont(Config::getFontFamily(), Config::getFontSize(), QFont::Normal, false );

    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget->setShowGrid(false);
    QString tableSetUp = "QTableView {background-color: "
            + Config::getTableBgColor() + "; selection-background-color: red; color: "
            + Config::getTableFontColor() + ";}";
    ui->tableWidget->setStyleSheet(tableSetUp);

    //    qDebug() << "Liste de couleurs reconnus " << QColor::colorNames();

    QTableWidgetItem *ville = new QTableWidgetItem();
    QTableWidgetItem *distance = new QTableWidgetItem();

    QJsonArray innerArray;
    QString distanceSTR;
    for (int i=0; i < maxRow; i++) {
        innerArray = array[i].toArray();
        ville = new QTableWidgetItem(innerArray[1].toString());
        ville->setFont(apiFont);

        distanceSTR = innerArray[7].toString();
        distanceSTR.append(" km");
        distance = new QTableWidgetItem(distanceSTR);
        distance->setFont(apiFont);

        ui->tableWidget->setItem(i, 0, ville);
        ui->tableWidget->setItem(i, 1, distance);
    }

    if (nbEle > maxRow) {
        QString nextCitiesInfoText = "+" + QString::number(nbEle-maxRow) +
                " autres villes à moins de " +
                array[nbEle-1].toArray()[7].toString() + " km";

        ui->footerLabel->setText(nextCitiesInfoText);
    }
    else
        ui->footerLabel->hide();
}

void CitiesWidget::afficheHeader(){
    QFont headerFont(Config::getHeaderFontFamily(),
                     Config::getHeaderFontSize(),
                     QFont::Normal, false );
    ui->headerLabel->setFont(headerFont);

    ui->headerLabel->setAlignment(Qt::AlignHCenter);

    QString bcfc = "QLabel { background-color : "+Config::getHeaderBgColor()+
            "; color : " + Config::getHeaderFontColor() + ";}";
    ui->headerLabel->setStyleSheet(bcfc);
    ui->headerLabel->setText("Les villes le plus proche");
}

void CitiesWidget::afficheFooter(){
    QFont footerFont(Config::getFooterFontFamily(),
                     Config::getFooterFontSize(),
                     QFont::Normal, false );
    ui->footerLabel ->setFont(footerFont);

    QString bcfc = "QLabel { background-color : "+Config::getFooterBgColor()+
            "; color : "+Config::getFooterFontColor()+";}";
    ui->footerLabel->setStyleSheet(bcfc);
}

void CitiesWidget::afficheAll(){
    afficheHeader();
    afficheTableView();
    afficheFooter();
}

CitiesWidget::~CitiesWidget()
{
    delete ui;
}
