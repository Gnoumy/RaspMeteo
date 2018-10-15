#include "traficinfos.h"
#include "ui_traficinfos.h"
#include <QUrlQuery>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardItemModel>

TraficInfos::TraficInfos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TraficInfos)
{
    ui->setupUi(this);

    QUrlQuery query = QUrlQuery();
    query.addQueryItem(TraficInfos::itemWhat, "traffic");
    query.addQueryItem(TraficInfos::itemWhen, "2018-10-01");

    this->url = QUrl(TraficInfos::host);
    this->url.setQuery(query);

    this->accesManager = new QNetworkAccessManager(this);
    connect(this->accesManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    this->accesManager->get(QNetworkRequest(this->url));
}

TraficInfos::~TraficInfos()
{
    delete ui;
}

/**
 * @brief TraficInfos::replyFinished
 * @param QNetworkReply reply
 */
void TraficInfos::replyFinished(QNetworkReply *reply)
{
    QJsonDocument itemDoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject responseObject = itemDoc.object();
    QJsonArray features = responseObject["features"].toArray();
    int count = responseObject["count"].toInt();

    for (int i=0; i<features.size(); i++) {
        QList<QStandardItem *> row;

        QJsonObject geometry = features[i].toObject()["geometry"].toObject();
        QJsonObject properties = features[i].toObject()["properties"].toObject();

        foreach (QString title, properties.keys()) {
            QStandardItem *item = new QStandardItem(
                        properties[title].toString());
            row.append(item);
        }

        row.append(new QStandardItem(geometry["coordinates"].toArray()[0].toDouble()));
        row.append(new QStandardItem(geometry["coordinates"].toArray()[1].toDouble()));
        this->model.appendRow(row);
    }
    ui->tableViewTrafic->setModel(&model);
}
