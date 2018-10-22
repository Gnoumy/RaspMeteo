#ifndef FLIGHTSWIDGET_H
#define FLIGHTSWIDGET_H
#include "localstationwidget.h"
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include<QNetworkRequest>
#include<QtSql>
#include <QTableWidget>
#include <QDebug>
#include "config.h"
#include "localstationwidget.h"
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include<QNetworkRequest>
#include<QtSql>
#include <QTableWidget>
#include <QDebug>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariantMap>
#include <QVariantList>
#include <math.h>

#define PI 3.14159265
#define ARC_MER 111110,0//en metres: 1° de latitude (arc de méridien) vaut 40 000/ 360
#define EARTH_RADIUS 6378.137
#define URLSTATESALL "https://opensky-network.org/api/states/all?"
namespace Ui {
class FlightsWidget;
}

class FlightsWidget : public LocalStationWidget
{
    Q_OBJECT

public:
    explicit FlightsWidget(QWidget *parent = 0);
    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    ~FlightsWidget();

private slots:
  void reponseUrl(QNetworkReply *data);


private:
    Ui::FlightsWidget *ui;
    QSqlDatabase mydb;
    QTableWidget* m_pTableWidget;
    QStringList m_TableHeader;


    void reloadData() ;//= 0 ; // recupere les donnees pour actualiser le widget
    void changeFont() ;//= 0 ; // changer la police (style, taille, etc...)

};

#endif // FLIGHTSWIDGET_H
