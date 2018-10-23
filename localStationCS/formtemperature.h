#ifndef FORMTEMPERATURE_H
#define FORMTEMPERATURE_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include "localstationwidget.h"
#include <QPushButton>
#include "config.h"

namespace Ui {
class FormTemperature;
}

class FormTemperature : public LocalStationWidget
{
    Q_OBJECT

public:
    explicit FormTemperature(QWidget *parent = 0);
    QNetworkAccessManager *qnam = new QNetworkAccessManager(this);
    void reloadData() ;
    void changeMode() ;
    ~FormTemperature();

private slots:
    void readRead(QNetworkReply *);

private:
    Ui::FormTemperature *ui;
};

#endif // FORMTEMPERATURE_H
