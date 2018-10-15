#include "pollutionwidget.h"
#include "ui_pollutionwidget.h"
#include "localstationwidget.h"
#include "config.h"

#include <QtNetwork>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QFont>
#include <QJsonDocument>
#include <QDebug>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBrush>
#include <QPen>
#include <QFrame>

PollutionWidget::PollutionWidget(QWidget *parent) :
    LocalStationWidget(parent),
    ui(new Ui::PollutionWidget)
{
    ui->setupUi(this);


    /*********************  PARAMETRES WIDGET  *****************************/
        //api Token:  82740759ffaf747ed45aad29febf758fffd33758
        QFont font(Config::getFontFamily(),Config::getFontSize(),QFont::Black);
        QFont footer(Config::getFooterFontFamily(),Config::getFooterFontSize(),QFont::Black);
        QFont header(Config::getHeaderFontFamily(),Config::getHeaderFontSize(),QFont::Black);
        this->setStyleSheet("background-color: "+Config::getBgColor());
        this->setFont(font);

        ui->label_Titre->setFont(header);
        ui->label_MinMax->setFont(footer);
        ui->label_Station->setFont(footer);

    /*********************   FIN PARAMETRES   *****************************/

        QNetworkRequest request;
        QUrl url("https://api.waqi.info/feed/geo:48.7833;2.2667/?token=82740759ffaf747ed45aad29febf758fffd33758"); //Plessis Robinson
        request.setUrl(url);
        networkManager->get(request);
//        connect(networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(reponseUrl(QNetworkReply *)));
        connect(networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(affichageGraphique(QNetworkReply *)));
        ui->stackedWidget->setCurrentIndex(1);


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

void PollutionWidget::affichageGraphique(QNetworkReply *data)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data->readAll());

    //Initialisation du graphique
    QPixmap pixmap(500,500);
    pixmap.fill(QColor("transparent"));
    QPainter painter(&pixmap);
    QBrush brush (Qt::blue, Qt::SolidPattern);
    QPen pen;
    pen.setColor(Config::getFontColor());
    painter.setPen(pen);
    painter.setBrush(brush);

    //Configuration du grand cercle
    QRectF rectangle(50, 200, 400, 400);
    int startAngle = 0 * 16;
    int spanAngle = 180 * 16;
    painter.drawArc(rectangle, startAngle, spanAngle);
    painter.drawChord(rectangle, startAngle, spanAngle);

    //Configuration du petit cercle
    QRectF rectangle2(175, 325, 150, 150);
    int startAngle2 = 0 * 16;
    int spanAngle2 = 180 * 16;
    painter.drawArc(rectangle2, startAngle2, spanAngle2);

//    painter.fillRect(rectangle, Qt::red);


    painter.drawText(30,400,"0");
    painter.drawText(100,220,"75");
    painter.drawText(240,185,"150");
    painter.drawText(380,220,"225");
    painter.drawText(460,400,"300");
//    painter.fillRect(rectangle2,brush);

    //Configuration de l'aiguille
    int position = jsonDoc.object().value("data").toObject().toVariantMap()["aqi"].toInt();
    QLine line(250, 375, 400, position);
    painter.drawLine(line);


    ui->label_graph->setPixmap(pixmap);
}
void PollutionWidget::reloadData()
{

}
void PollutionWidget::changeFont()
{

}
