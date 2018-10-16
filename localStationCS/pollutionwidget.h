#ifndef POLLUTIONWIDGET_H
#define POLLUTIONWIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "localstationwidget.h"
#include "config.h"
#include <QPen>
#include <QPainter>
#include <QPaintEvent>
namespace Ui {
class PollutionWidget;
}

class GraphPollutionWidget: public QWidget
{
    explicit GraphPollutionWidget(QWidget *parent = 0):QWidget(parent){}
    void paintEvent(QPaintEvent *)
    {
            QPainter painter(this);
            QBrush brush (Qt::blue, Qt::SolidPattern);
            QPen pen;
            pen.setColor(Config::getFontColor());
            painter.setPen(pen);
            painter.setBrush(brush);
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setRenderHint(QPainter::SmoothPixmapTransform);
            painter.setRenderHint(QPainter::HighQualityAntialiasing);

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

            //Configuration des indices
            painter.drawText(30,400,"0");
            painter.drawText(100,220,"75");
            painter.drawText(240,185,"150");
            painter.drawText(380,220,"225");
            painter.drawText(460,400,"300");

            //Configuration de l'aiguille
        //    int position = jsonDoc.object().value("data").toObject().toVariantMap()["aqi"].toInt()+20;
        //    int position = 150;

            //Dessin de l'aiguille
            QPoint points[3]={
                QPoint(235,370), //gauche
                QPoint(265,370), //droite
                QPoint(250,220), //haut
            };

//            QPainter aiguille(this);
//            aiguille.setPen(pen);
//            aiguille.setBrush(brush);
//            aiguille.drawPolygon(points,3);


        //    aiguille.end();
        //    painter.end();
        }
    };


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
    QPen *pen = new QPen(Config::getFontColor());


private slots:
    void premierePage(QNetworkReply *data);
    void deuxiemePage(QNetworkReply *data);
};

#endif // POLLUTIONWIDGET_H
