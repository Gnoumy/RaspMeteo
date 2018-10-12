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
    QFont font(Config::getFontFamily(),Config::getFontSize(),QFont::Black);
//    QFont header("JD LED5",50);
    this->setStyleSheet("background-color: "+Config::bgColor);
    ui->lineEdit_header->setFont(font);
    ui->lineEdit_header->setStyleSheet("color: "+Config::fontColor);
    ui->lineEdit_header->setReadOnly(true);

    ui->tableWidget_temp->setFont(font);
    ui->tableWidget_temp->setRowCount(4);
    ui->tableWidget_temp->setColumnCount(5);
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

    QPixmap pixmap(500,500);
    pixmap.fill(QColor("transparent"));
    QPainter painter(&pixmap);
    QPen pen;

    pen.setColor(Qt::white);
    painter.setPen(pen);
    QRectF rectangle(0.0, 0.0, 20.0, 300.0);
    QRectF rectangle_temp(1,220,19,80);
    painter.drawRect(rectangle);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    QBrush brush (Qt::red, Qt::SolidPattern);
    painter.fillRect(rectangle_temp,brush);


    ui->label_paint->setPixmap(pixmap);

}

void FormTemperature::readRead(QNetworkReply *data)
{

    QJsonDocument jsonDoc = QJsonDocument::fromJson(data->readAll());
    QString temp = QString::number(jsonDoc.object().toVariantMap()["main"].toMap()["temp"].toInt()-273);
    ui->tableWidget_temp->setItem(0,1,new QTableWidgetItem("temp"));
    ui->tableWidget_temp->setItem(0,3,new QTableWidgetItem(temp));
    ui->tableWidget_temp->setItem(0,4,new QTableWidgetItem("°C"));

//    QPixmap pixmap(500,500);
//    pixmap.fill(QColor("transparent"));
//    QPainter painter(&pixmap);
//    QPen pen;

//    pen.setColor(Qt::white);
//    painter.setPen(pen);
//    QRectF rectangle(0.0, 0.0, 20.0, 300.0);
//    QRectF rectangle_temp(1,220,19,80);
//    painter.drawRect(rectangle);

//    if (temp.toInt() > 15)
//    {
//        pen.setColor(Qt::blue);
//        painter.setPen(pen);
//        QBrush brush (Qt::blue, Qt::SolidPattern);
//        painter.fillRect(rectangle_temp,brush);
//        ui->label_paint->setPixmap(pixmap);
//    }

    QString wind = QString::number(jsonDoc.object().toVariantMap()["wind"].toMap()["speed"].toFloat());
    ui->tableWidget_temp->setItem(1,1,new QTableWidgetItem("wind"));
    ui->tableWidget_temp->setItem(1,3,new QTableWidgetItem(wind));
    ui->tableWidget_temp->setItem(1,4,new QTableWidgetItem("m/s"));

    QString hygro = QString::number(jsonDoc.object().toVariantMap()["main"].toMap()["humidity"].toFloat());
    ui->tableWidget_temp->setItem(2,1,new QTableWidgetItem("hygro"));
    ui->tableWidget_temp->setItem(2,3,new QTableWidgetItem(hygro));
    ui->tableWidget_temp->setItem(2,4,new QTableWidgetItem("%"));

    QString press = QString::number(jsonDoc.object().toVariantMap()["main"].toMap()["pressure"].toFloat());
    ui->tableWidget_temp->setItem(3,1,new QTableWidgetItem("press"));
    ui->tableWidget_temp->setItem(3,3,new QTableWidgetItem(press));
    ui->tableWidget_temp->setItem(3,4,new QTableWidgetItem("mbar"));
}
FormTemperature::~FormTemperature()
{
    delete ui;
}
