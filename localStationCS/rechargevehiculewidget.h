#ifndef RECHARGEVEHICULEWIDGET_H
#define RECHARGEVEHICULEWIDGET_H

#include <QWidget>
#include "localstationwidget.h"
#include "config.h"

#include <QNetworkReply>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <QUrlQuery>
#include <QLineEdit>
#include <QFont>


namespace Ui {
class RechargeVehiculeWidget;
}

class RechargeVehiculeWidget : public LocalStationWidget
{   
    Q_OBJECT


public:
    explicit RechargeVehiculeWidget(QWidget *parent = 0);
    ~RechargeVehiculeWidget();
    void reloadData();
    void changeFont();
    void changeMode();

private:
    Ui::RechargeVehiculeWidget *ui;
    QNetworkAccessManager *manager;
    float longitude=2.24;
    float latitude=48.7734;
    float disMax=2;
    int nbrBorne=10;


private slots:
    void replyFinished(QNetworkReply *reply);
};

#endif // RECHARGEVEHICULEWIDGET_H
