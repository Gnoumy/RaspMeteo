#ifndef POLLUTIONWIDGET_H
#define POLLUTIONWIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "localstationwidget.h"

namespace Ui {
class PollutionWidget;
}

class PollutionWidget : public LocalStationWidget
{
    Q_OBJECT

public:
    explicit PollutionWidget(QWidget *parent = 0);
    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    void reloadData() ;//= 0 ; // recupere les donnees pour actualiser le widget
    void changeFont(  ) ;//= 0 ; // changer la police (style, taille, etc...)
    ~PollutionWidget();

private:
    Ui::PollutionWidget *ui;
private slots:
    void premierePage(QNetworkReply *data);
    void deuxiemePage(QNetworkReply *data);
};

#endif // POLLUTIONWIDGET_H
