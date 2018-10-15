#ifndef TRAFICINFOS_H
#define TRAFICINFOS_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QString>
#include <QUrl>
#include <QStandardItemModel>

namespace Ui {
class TraficInfos;
}

class TraficInfos : public QWidget
{
    Q_OBJECT

public:
    const QString host = "http://api.openeventdatabase.org/event";
    const QString itemWhat = "what";
    const QString itemWhen = "where";

    explicit TraficInfos(QWidget *parent = 0);
    ~TraficInfos();

private:
    Ui::TraficInfos *ui;
    QNetworkAccessManager *accesManager;
    QUrl url;
    QStandardItemModel model;

private slots:
    void replyFinished(QNetworkReply *reply);
};



#endif // TRAFICINFOS_H
