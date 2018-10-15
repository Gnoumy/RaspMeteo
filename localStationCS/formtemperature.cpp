#include "formtemperature.h"
#include "ui_formtemperature.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFont>
#include <QWidget>
#include <QPainter>
#include <QPalette>
#include <QPen>
#include <QBrush>
#include "config.h"

FormTemperature::FormTemperature(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTemperature)
{
    ui->setupUi(this);
    setFixedSize(412, 525);
//    this->setStyleSheet("background-color: "+Config::getBgColor());
//    this->setStyleSheet("background-color: blue");
    QFont header(Config::getHeaderFontFamily(),Config::getHeaderFontSize());

//  ********  Parametre du lineEdit header  ********
    ui->lineEdit_header->setFont(header);
    ui->lineEdit_header->setStyleSheet("color: "+Config::getHeaderFontColor()+"; background-color: "+Config::getHeaderBgColor());
    ui->lineEdit_header->setReadOnly(true);

//  ********  Parametre de la table Widget  ********
    QFont font(Config::getFontFamily(),Config::getFontSize());
    ui->tableWidget_temp->setFont(font);
    ui->tableWidget_temp->setRowCount(4);
    ui->tableWidget_temp->setColumnCount(4);
    ui->tableWidget_temp->horizontalHeader()->hide();
    ui->tableWidget_temp->verticalHeader()->hide();
    ui->tableWidget_temp->setShowGrid(false);
    ui->tableWidget_temp->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget_temp->resizeColumnsToContents();
    ui->tableWidget_temp->resizeRowsToContents();
    ui->tableWidget_temp->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_temp->setStyleSheet("color: "+Config::getFontColor()+"; background-color: "+Config::getBgColor());

//  ********  Importation des données lat et lon  ********
    QString lat = QString::number(Config::getLatitude(),'g',4);
    QString lon = QString::number(Config::getLongitude(),'g',4);

//  ********  Requete API   ********
    qnam->get(QNetworkRequest(QUrl("http://api.openweathermap.org/data/2.5/weather?lat="+lat+"&lon="+lon+"&appid=3543ac0c00624ed3bb653359621e5344")));
    connect(qnam,SIGNAL(finished(QNetworkReply*)),this,SLOT(readRead(QNetworkReply*)));
}
void FormTemperature::readRead(QNetworkReply *data)
{
//  ********  Enregistrement des données à partir du Json  ********
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data->readAll());
    QString temp = QString::number(jsonDoc.object().toVariantMap()["main"].toMap()["temp"].toInt()-273);
    ui->tableWidget_temp->setItem(0,0,new QTableWidgetItem("temp"));
    ui->tableWidget_temp->setItem(0,2,new QTableWidgetItem(temp));
    ui->tableWidget_temp->setItem(0,3,new QTableWidgetItem("°C"));

    QString wind = QString::number(jsonDoc.object().toVariantMap()["wind"].toMap()["speed"].toFloat());
    ui->tableWidget_temp->setItem(1,0,new QTableWidgetItem("wind"));
    ui->tableWidget_temp->setItem(1,2,new QTableWidgetItem(wind));
    ui->tableWidget_temp->setItem(1,3,new QTableWidgetItem("m/s"));

    QString hygro = QString::number(jsonDoc.object().toVariantMap()["main"].toMap()["humidity"].toFloat());
    ui->tableWidget_temp->setItem(2,0,new QTableWidgetItem("hygro"));
    ui->tableWidget_temp->setItem(2,2,new QTableWidgetItem(hygro));
    ui->tableWidget_temp->setItem(2,3,new QTableWidgetItem("%"));

    QString press = QString::number(jsonDoc.object().toVariantMap()["main"].toMap()["pressure"].toFloat());
    ui->tableWidget_temp->setItem(3,0,new QTableWidgetItem("press"));
    ui->tableWidget_temp->setItem(3,2,new QTableWidgetItem(press));
    ui->tableWidget_temp->setItem(3,3,new QTableWidgetItem("mbar"));

//  ********  Hauteur en pixel de la jauge en fonction de la température et taille du thermometre  ********
    float temp_float = jsonDoc.object().toVariantMap()["main"].toMap()["temp"].toFloat()-273;
    float temp_px = ((50.0+temp_float)*300/110);

//  ********  Dessin du thermometre  ********
    QPixmap pixmap(500,500);
    pixmap.fill(QColor("transparent"));
    QPainter painter(&pixmap);
    QPen pen;
    pen.setColor(Config::getFontColor());
    painter.setPen(pen);
    QRectF rectangle(20.0, 20.0, 30.0, 300.0);
    QRectF rectangle_temp(21,320.0-temp_px,29,temp_px);
    painter.drawRect(rectangle);

    painter.drawLine(80,30,55,30);
    painter.drawLine(65,55,55,55);
    painter.drawLine(65,80,55,80);
    painter.drawLine(65,105,55,105);
    painter.drawLine(65,130,55,130);
    painter.drawLine(65,155,55,155);
    painter.drawLine(80,180,55,180);
    painter.drawLine(65,205,55,205);
    painter.drawLine(65,230,55,230);
    painter.drawLine(65,255,55,255);
    painter.drawLine(65,280,55,280);
    painter.drawLine(80,305,55,305);

    painter.drawText(17,15,"Temp °C");
    painter.drawText(90,35,"55");
    painter.drawText(90,60,"50");
    painter.drawText(90,85,"40");
    painter.drawText(90,110,"30");
    painter.drawText(90,135,"20");
    painter.drawText(90,160,"10");
    painter.drawText(95,185,"0");
    painter.drawText(85,210,"-10");
    painter.drawText(85,235,"-20");
    painter.drawText(85,260,"-30");
    painter.drawText(85,285,"-40");
    painter.drawText(85,310,"-45");

//  ********  Couleur de la jauge en fonction de la temperature  ********
    if (temp.toInt() < 5)
    {
        painter.setPen(pen);
        QBrush brush (Qt::blue, Qt::SolidPattern);
        pen.setColor(Config::getFontColor());
        painter.setBrush(brush);
        painter.drawEllipse(25,317,60,60);
        pen.setColor(Qt::blue);
        painter.fillRect(rectangle_temp,brush);
        ui->label_temp->setFixedWidth(125);
        ui->label_temp->setFixedHeight(500);
    }
    else if (temp.toInt() >= 5 && temp.toInt() <=25)
    {
        painter.setPen(pen);
        QBrush brush (Qt::green, Qt::SolidPattern);
        pen.setColor(Config::getFontColor());
        painter.setBrush(brush);
        painter.drawEllipse(10,315,50,50);
        pen.setColor(Qt::green);
        painter.fillRect(rectangle_temp,brush);

        ui->label_temp->setPixmap(pixmap);
        ui->label_temp->setFixedWidth(125);
        ui->label_temp->setFixedHeight(500);


    }
    else if (temp.toInt() > 25)
    {
        painter.setPen(pen);
        QBrush brush (Qt::red, Qt::SolidPattern);
        pen.setColor(Config::getFontColor());
        painter.setBrush(brush);
        painter.drawEllipse(25,317,60,60);
        pen.setColor(Qt::red);
        painter.fillRect(rectangle_temp,brush);
        ui->label_temp->setFixedWidth(125);
        ui->label_temp->setFixedHeight(500);
    }

//  ********  Hauteur en pixel de la jauge en fonction de la température et taille du thermometre  ********
    float hygro_float = jsonDoc.object().toVariantMap()["main"].toMap()["humidity"].toFloat();
    float hygro_px = ((hygro_float)*340/100);

//  ********  Dessin de l'hygrometre  ********
    QPixmap pixmap2(300,500);
    pixmap2.fill(QColor("transparent"));
    QPainter painter2(&pixmap2);
    QPen pen2;
    pen2.setColor(Config::getFontColor());
    painter2.setPen(pen2);
    QRectF rectangle2(10.0, 40.0, 30.0, 300.0);
    QRectF rectangle_hygro(11,340.0-hygro_px,29,hygro_px);
    painter2.drawRect(rectangle2);
    QBrush brush (Qt::red, Qt::SolidPattern);
    pen2.setColor(Qt::red);
    painter2.fillRect(rectangle_hygro,brush);

    painter2.drawText(7,15,"Hygro %");
    painter2.drawText(65,50,"100");
    painter2.drawText(65,200,"50");
    painter2.drawText(70,340,"0");

    painter2.drawLine(60,45,45,45);
    painter2.drawLine(60,195,45,195);
    painter2.drawLine(60,335,45,335);

    ui->label_hygro->setPixmap(pixmap2);
    ui->label_hygro->setFixedWidth(100);
    ui->label_hygro->setFixedHeight(500);
}
FormTemperature::~FormTemperature()
{
    delete ui;
}

