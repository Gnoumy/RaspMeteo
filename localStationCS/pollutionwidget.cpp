#include "pollutionwidget.h"
#include "ui_pollutionwidget.h"
#include "config.h"
#include "localstationwidget.h"

#include <QtNetwork>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QDebug>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>

PollutionWidget::PollutionWidget(QWidget *parent) :
    LocalStationWidget(parent),
    ui(new Ui::PollutionWidget)
{
    ui->setupUi(this);


    /*********************  PARAMETRES WIDGET  *****************************/
        QString background, couleur;
        background = Config::getBgColor();
        couleur = Config::getFontColor();
        qDebug()<<couleur;
        setStyleSheet("QWidget { background-color :"+ background+"; color :"+couleur+"; }");
        //api Token:  82740759ffaf747ed45aad29febf758fffd33758
    /*********************  FIN PARAMETRES  ùùù*****************************/

        QNetworkRequest request;
    //    QUrl url("https://api.waqi.info/feed/geo:48.866667;2.333333/?token=82740759ffaf747ed45aad29febf758fffd33758"); //Paris
        QUrl url("https://api.waqi.info/feed/geo:48.7833;2.2667/?token=82740759ffaf747ed45aad29febf758fffd33758"); //Plessis Robinson
        request.setUrl(url);
        networkManager->get(request);
        connect(networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(reponseUrl(QNetworkReply *)));
//        connect(networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(affichageGraphique()));
//        ui->stackedWidget->setCurrentIndex(1);

}

PollutionWidget::~PollutionWidget()
{
    delete ui;
}

void PollutionWidget::reponseUrl(QNetworkReply *data)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data->readAll());
    ui->label_Indice->setText(jsonDoc.object().value("data").toObject().toVariantMap()["aqi"].toString());
    ui->label_Station->setText(jsonDoc.object().value("data").toObject().toVariantMap()["city"].toMap()["name"].toString());
}

void PollutionWidget::affichageGraphique()
{
    ui->stackedWidget->setCurrentIndex(1);
    QPixmap pixmap(500,500);
    pixmap.fill(QColor("transparent"));
    QPainter painter(&pixmap);
    QPen pen;
    pen.setColor(Qt::white);
    painter.setPen(pen);

//    painter.drawLine(0,0,100,100);
    QRectF rectangle(0.0, 200.0, 400.0, 400.0);
//    painter.fillRect(rectangle, Qt::red);
    int startAngle = 30 * 16;
    int spanAngle = 120 * 16;

    painter.drawArc(rectangle, startAngle, spanAngle);
    painter.drawChord(rectangle, startAngle, spanAngle);

    ui->label_graph->setPixmap(pixmap);




}
void PollutionWidget::reloadData()
{

}
void PollutionWidget::changeFont()
{

}
