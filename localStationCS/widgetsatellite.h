#ifndef QWIDGETSATELLITE_H
#define QWIDGETSATELLITE_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariantMap>
#include <QLatin1String>
#include <QJsonArray>
#include <QMap>
#include <QVariantList>
#include <QTimer>
#include <QMetaEnum>
#include <QStringList>
#include <math.h>
#include <QPainter>
#include "localstationwidget.h"
#include "config.h"

#define PI 3.14159265
#define EARTH_RADIUS 6378.137
#define TIME_RESTART 60000
#define MINI_SATALT 1000
#define FACTOR_DISTANCE 20
#define N2YOKEY "/&apiKey=UWRBCN-GBFDZC-W3RCP5-3WA0"
#define URLN2YOBASE "https://www.n2yo.com/rest/v1/satellite/above/"
#define URLOPENELEVATIONEBASE "https://api.open-elevation.com/api/v1/lookup?locations="
#define BINGBASE "http://dev.virtualearth.net/REST/v1/Elevation/SeaLevel?points="
//http://dev.virtualearth.net/REST/v1/Elevation/List?points=35.89431,-110.72522,35.89393,-110.72578,35.89374,-110.72606,35.89337,-110.72662&key=AreNudZpwsgCVThO3D03mhq6DcWVKu2JYWqstZeoIsAbePVfU1gEczU0WrT6LYJg
#define BINGBKEY "&key=AreNudZpwsgCVThO3D03mhq6DcWVKu2JYWqstZeoIsAbePVfU1gEczU0WrT6LYJg"


class Satellite
{
public:
    Satellite(int vid=-1, QString satn="NC", QString desig="NC",
                         QString laudate="NC", float lat=0.0, float lng=0.0,
                         float alt=0.0, QString catg="NC")
    {
        Set_satid(vid);
        Set_satname(satn);
        Set_intDesignator(desig);
        Set_launchDate(laudate);
        Set_satalt(alt);
        Set_satlng(lng);
        Set_satlat(lat);
        Set_category(catg);
    }
    int Get_satid(){return satid;}
    void Set_satid(int v){ satid=v;}
    QString Get_satname(){return satname;}
    void Set_satname(QString v){ satname=v;}
    QString Get_intDesignator(){return intDesignator;}
    void Set_intDesignator(QString v){ intDesignator=v;}
    QString Get_launchDate(){return launchDate;}
    void Set_launchDate(QString v){ launchDate=v;}
    float Get_satlat(){return satlat;}
    void Set_satlat(float v){ satlat=v;}
    float Get_satlng(){return satlng;}
    void Set_satlng(float v){ satlng=v;}
    float Get_satalt(){return satalt;}
    void Set_satalt(float v){ satalt=v;}
    QString Get_category(){return category;}
    void Set_category(QString v){ category=v;}
private:
    int satid;
    QString satname;
    QString intDesignator;
    QString launchDate;
    float satlat;
    float satlng;
    float satalt;
    QString category;
};

namespace Ui {
class WidgetSatellite;
}

class WidgetSatellite : public LocalStationWidget
{
    Q_OBJECT

public:
    explicit WidgetSatellite(QWidget *parent=0);
    ~WidgetSatellite();

    void SetSat_categories();

private slots:
    void Slot_SatTrack();
    void Elevation(QNetworkReply *pReplayalt);
private:
    Ui::WidgetSatellite *ui;
    QList<Satellite> SatelliteList;
    QMap<QString, int> Sat_categories;
    QString alt;
    void SatlistTrack(QNetworkReply *pReplay);
    void FillTable();
    void CleanTable();
    double getDistance(double, double, double, double);
    double getRad(float);
    void Showpic(QImage &img);
    void DrawSatellites(QImage *img);
};

#endif // QWIDGETSATELLITE_H
