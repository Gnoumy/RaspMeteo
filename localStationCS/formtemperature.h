#ifndef FORMTEMPERATURE_H
#define FORMTEMPERATURE_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFontDatabase>

namespace Ui {
class FormTemperature;
}

class FormTemperature : public QWidget
{
    Q_OBJECT

public:
    explicit FormTemperature(QWidget *parent = 0);
    QNetworkAccessManager *qnam = new QNetworkAccessManager(this);

    ~FormTemperature();

private slots:
    void readRead(QNetworkReply *);

private:
    Ui::FormTemperature *ui;
};

#endif // FORMTEMPERATURE_H