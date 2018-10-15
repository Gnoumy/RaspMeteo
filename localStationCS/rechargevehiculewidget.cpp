#include "rechargevehiculewidget.h"
#include "ui_rechargevehiculewidget.h"
#include "localstationwidget.h"
#include "config.h"

RechargeVehiculeWidget::RechargeVehiculeWidget(QWidget *parent) :
    LocalStationWidget(parent),
    ui(new Ui::RechargeVehiculeWidget)
{
    ui->setupUi(this);
    //-------------------- requete------------------------------------//
        //QString pol
        manager = new QNetworkAccessManager(this);
        QUrl url("https://api.openchargemap.io/v2/poi/?output=json&maxresults=10&latitude=48.85&longitude=2.33&&distance=2&distanceunit=KM");
        QNetworkRequest request; //on declare une variable pour l'envoi de notre requete
        request.setUrl(url);//on fait un set avec l'url
        QNetworkReply* currentReply = manager->get(request); //get
        connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
}

RechargeVehiculeWidget::~RechargeVehiculeWidget()
{
    delete ui;
}

void RechargeVehiculeWidget::replyFinished(QNetworkReply *reply)
{
    QByteArray ret=reply->readAll();
    QJsonDocument myJson=QJsonDocument::fromJson(ret);

    QFont font(Config::getFontFamily(),Config::getFontSize(),QFont::Black);//font(police, taille, couleur)
    QFont footer(Config::getFooterFontFamily(),Config::getFooterFontSize(),QFont::Black);
    QFont header(Config::getHeaderFontFamily(),Config::getHeaderFontSize(),QFont::Black);

    ui->tableWidget->setFont(font);
    ui->tableWidget->setStyleSheet("color: "+Config::getFontColor());
    ui->tableWidget->setStyleSheet("background-color: "+Config::getBgColor());

    ui->label->setFont(header);//taille de police du l'entete
    ui->label->setStyleSheet("color:"+Config::getHeaderFontColor()); //couleur de police
    ui->label->setStyleSheet("background-color: "+Config::getHeaderBgColor());//couleur de font
    //ui->label->setStyleSheet("background-color: yellow");//couleur de fond en local

    ui->label_2->setFont(footer); //taille du bas
    ui->label_2->setStyleSheet("color:"+Config::getFooterFontColor());
    ui->label_2->setStyleSheet("background-color: "+Config::getFooterBgColor());

    ui->tableWidget->setColumnCount(3); //nombre de colonne;
    ui->tableWidget->setShowGrid(false);
    ui->tableWidget->horizontalHeader()->hide();//pour cacher le nom ou numero des ligne
    ui->tableWidget->verticalHeader()->hide();//pour cacher le nom ou numero des colonne

    if (myJson.array().count() >3) { //alors on affiche le nombre des autres bornes et la distance de celle la plus proche
        for (int i=0; i<3; i++) {
            ui->tableWidget->setRowCount(i+1);  //nombre de lignes
            QString addresse(myJson.array()[i].toObject().toVariantMap()["AddressInfo"].toMap()["AddressLine1"].toString());
            QString ville(myJson.array()[i].toObject().toVariantMap()["AddressInfo"].toMap()["Town"].toString());
            QString distan(myJson.array()[i].toObject().toVariantMap()["AddressInfo"].toMap()["Distance"].toString());

            latitude=myJson.array()[i].toObject().toVariantMap()["AddressInfo"].toMap()["Latitude"].toFloat();
            longitude=myJson.array()[i].toObject().toVariantMap()["AddressInfo"].toMap()["Longitude"].toFloat();
            qDebug() << latitude;
            qDebug() << longitude;
            QString distance=distan.left(4); //je recupere les 4premiers chiffre
            QString distance1=distance.append("km");//on ajoute km à distance on aussi faire QString distance1=distance+"km";

            ui->tableWidget->setRowCount(i+1);  //nombre de lignes
            QTableWidgetItem *item1= new QTableWidgetItem(addresse); //item1 pour recuperer l'adresse
            ui->tableWidget->setItem(i,0,item1);//on rajoute item1 à la colonne 1, ligne i

            QTableWidgetItem *item2= new QTableWidgetItem(ville);//item1 pour recuperer la ville
            ui->tableWidget->setItem(i,1,item2);

            QTableWidgetItem *item3= new QTableWidgetItem(distance1);//item1 pour recuperer la distance
            ui->tableWidget->setItem(i,2,item3);
        }

        int rest= myJson.array().count()-3;
        QString autresBornes=QString::number(rest);//on convertit un double en QString*/
        QString distance(myJson.array()[myJson.array().count()-1].toObject().toVariantMap()["AddressInfo"].toMap()["Distance"].toString());
        QString dist=distance.left(4);

        ui->label_2->setText("+"+autresBornes+ " autres bornes à moins de " +dist+"km");

    } else {
        for(int i=0; i<myJson.array().count(); i++){
            ui->tableWidget->setRowCount(i+1);  //nombre de lignes
            QString addresse(myJson.array()[i].toObject().toVariantMap()["AddressInfo"].toMap()["AddressLine1"].toString());
            QString ville(myJson.array()[i].toObject().toVariantMap()["AddressInfo"].toMap()["Town"].toString());
            QString distan(myJson.array()[i].toObject().toVariantMap()["AddressInfo"].toMap()["Distance"].toString());

            QString distance=distan.left(4);
            QString distance1=distance.append("km");
            qDebug() << distance1;

            ui->tableWidget->setRowCount(i+1);  //nombre de lignes
            QTableWidgetItem *item1= new QTableWidgetItem(addresse); //item1 pour recuperer l'adresse
            ui->tableWidget->setItem(i,0,item1);

            QTableWidgetItem *item2= new QTableWidgetItem(ville);//item1 pour recuperer la ville
            ui->tableWidget->setItem(i,1,item2);

            QTableWidgetItem *item3= new QTableWidgetItem(distance1);//item1 pour recuperer la distance
            ui->tableWidget->setItem(i,2,item3);
        }
    }
}

