#ifndef TRAFICINFOS_H
#define TRAFICINFOS_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QString>
#include <QUrl>
#include <QStandardItemModel>
#include "localstationwidget.h"

namespace Ui {
class TraficInfos;
}

class TraficInfos : public LocalStationWidget
{
    Q_OBJECT

public:
    const QString host = "http://api.openeventdatabase.org/event";
    const QString itemWhat = "what";
    const QString itemWhen = "where";

    explicit TraficInfos(QWidget *parent);
    ~TraficInfos();

    void reloadData();
    void changeFont();
    void changeMode();

private:
    Ui::TraficInfos *ui;
    QNetworkAccessManager *accesManager;
    QUrl url;
    QStandardItemModel model;

private slots:
    void replyFinished(QNetworkReply *reply);
};



#endif // TRAFICINFOS_H
