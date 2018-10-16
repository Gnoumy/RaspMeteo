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

private:
    Ui::RechargeVehiculeWidget *ui;
    QNetworkAccessManager *manager;
    float longitude=2.33;//2.24;
    float latitude=48.85;//48.7734;
    float disMax=6;
    int nbrBorne=0;

private slots:
    void replyFinished(QNetworkReply *reply);
};

#endif // RECHARGEVEHICULEWIDGET_H
