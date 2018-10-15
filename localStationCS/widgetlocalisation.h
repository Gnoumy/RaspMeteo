#ifndef NETWORKACCESSMANAGER_H
#define NETWORKACCESSMANAGER_H
#include <QNetworkAccessManager>
#include <QNetworkRequest>




class NetworkAccessManager : public QNetworkAccessManager
{
public:
    NetworkAccessManager(QObject *parent) :QNetworkAccessManager(parent) {}

protected:
    QNetworkReply * createRequest ( Operation op, const QNetworkRequest & req, QIODevice * outgoingData = 0 )
    {
    QNetworkRequest new_req(req);
    new_req.setRawHeader("User-Agent",  "projet c-s");
    return QNetworkAccessManager::createRequest(op, new_req, outgoingData);
    }
};


#endif // NETWORKACCESSMANAGER_H

#ifndef WIDGETLOCALISATION_H
#define WIDGETLOCALISATION_H

#include <QNetworkAccessManager>


#include <QWidget>
#include <QJsonArray>
#include <QVariant>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QString>
#include <QObject>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

#include "mainwindow.h"


namespace Ui {
class widgetlocalisation;
}

class widgetlocalisation : public LocalStationWidget
{
    Q_OBJECT

public:
    explicit widgetlocalisation(QWidget *parent = 0);
    ~widgetlocalisation();

private slots:
        void replyFinished(QNetworkReply *reply);



private:
    Ui::widgetlocalisation *ui;
    NetworkAccessManager *manager;
};

#endif // WIDGETLOCALISATION_H




