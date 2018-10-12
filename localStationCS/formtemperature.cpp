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
//    setFixedSize(320, 340);
    QFont font(Config::getFontFamily(),Config::getFontSize());
    this->setStyleSheet("background-color: "+Config::bgColor);
    ui->lineEdit_header->setFont(font);
    ui->lineEdit_header->setStyleSheet("color: "+Config::fontColor);
    ui->lineEdit_header->setReadOnly(true);

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
    ui->tableWidget_temp->setStyleSheet("color: "+Config::fontColor+"; background-color: "+Config::bgColor);

    qnam->get(QNetworkRequest(QUrl("http://api.openweathermap.org/data/2.5/weather?lat=40&lon=20&appid=3543ac0c00624ed3bb653359621e5344")));
    connect(qnam,SIGNAL(finished(QNetworkReply*)),this,SLOT(readRead(QNetworkReply*)));

}

void FormTemperature::readRead(QNetworkReply *data)
{

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

    float temp_float = jsonDoc.object().toVariantMap()["main"].toMap()["temp"].toFloat()-273;
    float temp_px = ((50.0+temp_float)*360/110);

    QPixmap pixmap(500,500);
    pixmap.fill(QColor("transparent"));
    QPainter painter(&pixmap);
    QPen pen;

    pen.setColor(Config::fontColor);
    painter.setPen(pen);
    QRectF rectangle(20.0, 0.0, 30.0, 360.0);
    QRectF rectangle_temp(21,360.0-temp_px,29,temp_px);
    painter.drawRect(rectangle);

    painter.drawLine(80,15,55,15);
    painter.drawLine(65,45,55,45);
    painter.drawLine(65,75,55,75);
    painter.drawLine(65,105,55,105);
    painter.drawLine(65,135,55,135);
    painter.drawLine(65,165,55,165);
    painter.drawLine(80,195,55,195);
    painter.drawLine(65,225,55,225);
    painter.drawLine(65,255,55,255);
    painter.drawLine(65,285,55,285);
    painter.drawLine(65,315,55,315);
    painter.drawLine(80,345,55,345);

    painter.drawText(90,20,"55");
    painter.drawText(90,50,"50");
    painter.drawText(90,80,"40");
    painter.drawText(90,110,"30");
    painter.drawText(90,140,"20");
    painter.drawText(90,170,"10");
    painter.drawText(95,200,"0");
    painter.drawText(85,230,"-10");
    painter.drawText(85,260,"-20");
    painter.drawText(85,290,"-30");
    painter.drawText(85,320,"-40");
    painter.drawText(85,350,"-45");

    if (temp.toInt() < 5)
    {
        painter.setPen(pen);
        QBrush brush (Qt::blue, Qt::SolidPattern);
        pen.setColor(Config::fontColor);
        painter.setBrush(brush);
        painter.drawEllipse(5,357,60,60);
        pen.setColor(Qt::blue);
        painter.fillRect(rectangle_temp,brush);
        ui->label_temp->setPixmap(pixmap);
    }
    else if (temp.toInt() >= 5 && temp.toInt() <=25)
    {
        painter.setPen(pen);
        QBrush brush (Qt::green, Qt::SolidPattern);
        pen.setColor(Config::fontColor);
        painter.setBrush(brush);
        painter.drawEllipse(5,357,60,60);
        pen.setColor(Qt::green);
        painter.fillRect(rectangle_temp,brush);
        ui->label_temp->setPixmap(pixmap);
    }
    else if (temp.toInt() > 25)
    {
        painter.setPen(pen);
        QBrush brush (Qt::red, Qt::SolidPattern);
        pen.setColor(Config::fontColor);
        painter.setBrush(brush);
        painter.drawEllipse(5,357,60,60);
        pen.setColor(Qt::red);
        painter.fillRect(rectangle_temp,brush);
        ui->label_temp->setPixmap(pixmap);
    }
}
FormTemperature::~FormTemperature()
{
    delete ui;
}

