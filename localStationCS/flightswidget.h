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
};

#endif // FLIGHTSWIDGET_H
