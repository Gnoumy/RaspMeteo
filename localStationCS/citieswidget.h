#ifndef CITIESWIDGET_H
#define CITIESWIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTableWidget>
#include <QJsonArray>
#include <localstationwidget.h>

namespace Ui {
class CitiesWidget;
}

class CitiesWidget : public LocalStationWidget
{
    Q_OBJECT

public:
    explicit CitiesWidget(QWidget *parent = nullptr);
    ~CitiesWidget();

private:
    Ui::CitiesWidget *ui;
    QNetworkAccessManager *manager;
    QJsonArray array;

    QStringList buildWebAdress(QString, QString);
    void reloadData();
    void changeFont();
    void changeMode();
    void resizeEvent(QResizeEvent * /* event */);

    void afficheHeader();
    void afficheFooter();
    void afficheTableView();
    void afficheAll();

private slots:
    void replyFinished(QNetworkReply*);
};

#endif // CITIESWIDGET_H
