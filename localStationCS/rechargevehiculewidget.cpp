#include "rechargevehiculewidget.h"
#include "ui_rechargevehiculewidget.h"
#include "localstationwidget.h"
#include "config.h"

RechargeVehiculeWidget::RechargeVehiculeWidget(QWidget *parent) :
    LocalStationWidget(parent),
    ui(new Ui::RechargeVehiculeWidget)
{
    ui->setupUi(this);
    //-------------------- reload pour la requête ------------------------------------//
        reloadData();
        connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
        changeFont();
}

RechargeVehiculeWidget::~RechargeVehiculeWidget()
{
    delete ui;
}

/**********   reloadData pour l'actualisation   ************/
void RechargeVehiculeWidget::reloadData()
{
    QString urlvar("https://api.openchargemap.io/v2/poi/?output=json&maxresults="+QString::number(nbrBorne)+"&latitude="+QString::number(latitude)
                  +"&longitude="+QString::number(longitude)+"&&distance="+QString::number(disMax)+"&distanceunit=KM");
    manager = new QNetworkAccessManager(this);
    QUrl url(urlvar);
    QNetworkRequest request; //on declare une variable pour l'envoi de notre requete
    request.setUrl(urlvar); //on fait une requête
    QNetworkReply* currentReply = manager->get(request);
}

/**********   pour la police et fond   ************/
void RechargeVehiculeWidget::changeFont()
{
    QFont font(Config::getTableFontFamily(),Config::getTableFontSize());//font(taille police corps de texte)
    QFont footer(Config::getFooterFontFamily(),Config::getFooterFontSize());//font(taille police bas de texte)
    QFont header(Config::getHeaderFontFamily(),Config::getHeaderFontSize());//font(taille police entête)

    ui->tableWidget->setFont(font); //appel police et police
    ui->tableWidget->setStyleSheet("color: "+Config::getTableFontColor()+"; background-color: "+Config::getTableBgColor());
    ui->tableWidget->setMinimumWidth(500);

    ui->lineEdit->setFont(header); //taille de police du l'entete
    ui->lineEdit->setStyleSheet("color:"+Config::getHeaderFontColor()+"; background-color: "+Config::getHeaderBgColor());

    ui->label_2->setFont(footer); //taille du bas
    ui->label_2->setStyleSheet("color:"+Config::getFooterFontColor()+"; background-color: "+Config::getFooterBgColor());

    ui->tableWidget->setColumnCount(3); //nombre de colonne;
    ui->tableWidget->setShowGrid(false); //pour supprimer les grilles du tableau
    ui->tableWidget->horizontalHeader()->hide(); //pour cacher le nom ou numero des ligne
    ui->tableWidget->verticalHeader()->hide(); //pour cacher le nom ou numero des colonne

    //ajutser le tableau par rapport à qtablewidget
    QHeaderView* ajusteColonne = ui->tableWidget->horizontalHeader();//ajustage des colonnes
    ajusteColonne->setSectionResizeMode(QHeaderView::Stretch);
}

/**********   changement mode   ************/
void RechargeVehiculeWidget::changeMode()
{

}

void RechargeVehiculeWidget::replyFinished(QNetworkReply *reply)
{
    QByteArray ret=reply->readAll();

    QHeaderView* ajusteColonne = ui->tableWidget->horizontalHeader();//ajustage des colonnes
    ajusteColonne->setSectionResizeMode(QHeaderView::Stretch);
    //QHeaderView* ajusteLigne = ui->tableWidget->verticalHeader();
    //ajusteLigne->setSectionResizeMode(QHeaderView::Stretch);*/

    QJsonParseError jsonError;
    //QJsonDocument doc =QJsonDocument::fromJson(ret,&jsonError);
    QJsonDocument myJson =QJsonDocument::fromJson(ret,&jsonError);
    if(jsonError.error != QJsonParseError::NoError)
    {
        //qDebug()<<QStringLiteral("Recharge Parsed Json failure");
        //qDebug()<<jsonError.errorString();
        QString message0("Erreur de connexion, veuillez reessayer plus tard");
        ui->tableWidget->setRowCount(12);
        ui->tableWidget->setColumnCount(1);
        QTableWidgetItem *item0= new QTableWidgetItem(message0);
        ui->tableWidget->setItem(5,0,item0);
        return;
    }

    if (myJson.array().count()==0) {
        QString message0("PAS DE BORNE DE RECHARGE POUR CETTE POSITION DONNEE");
        ui->tableWidget->setRowCount(12);
        ui->tableWidget->setColumnCount(1);
        QTableWidgetItem *item0= new QTableWidgetItem(message0);
        ui->tableWidget->setItem(5,0,item0);
    }

    if (myJson.array().count() >3) { //alors on affiche le nombre des autres bornes et la distance de celle la plus proche
        for (int i=0; i<3; i++) {
            ui->tableWidget->setRowCount(i+1);  //numéro de lignes
            QString addresse(myJson.array()[i].toObject().toVariantMap()["AddressInfo"].toMap()["AddressLine1"].toString());
            QString ville(myJson.array()[i].toObject().toVariantMap()["AddressInfo"].toMap()["Town"].toString());
            QString distan(myJson.array()[i].toObject().toVariantMap()["AddressInfo"].toMap()["Distance"].toString());

            latitude=myJson.array()[i].toObject().toVariantMap()["AddressInfo"].toMap()["Latitude"].toFloat();
            longitude=myJson.array()[i].toObject().toVariantMap()["AddressInfo"].toMap()["Longitude"].toFloat();
            //qDebug() << latitude;
            //qDebug() << longitude;
            QString distance=distan.left(4); //je recupere les 4premiers chiffre
            QString distance1=distance.append("km");//on ajoute km à distance on aussi faire QString distance1=distance+"km";

            ui->tableWidget->setRowCount(i+1);  //numero de lignes

//            AutoScrollingLabel *item1= new AutoScrollingLabel(this);
//            item1->setText(addresse);
//            ui->tableWidget->setCellWidget(i,0,item1);

            QTableWidgetItem *item1= new QTableWidgetItem(addresse); //item1 pour recuperer l'adresse
            ui->tableWidget->setItem(i,0,item1);//on rajoute item1 à la colonne 1, ligne i

            QTableWidgetItem *item2= new QTableWidgetItem(ville);//item1 pour recuperer la ville
            ui->tableWidget->setItem(i,1,item2);

            QTableWidgetItem *item3= new QTableWidgetItem(distance1);//item1 pour recuperer la distance
            //ui->tableWidget->setItem(i,2,item3);
            if (distan==""){//on rajoute une condition pour gerer les distance non definie
                QString distNonDefini="distance non définie";
                QTableWidgetItem *item3= new QTableWidgetItem(distNonDefini);//item1 pour recuperer la distance
                ui->tableWidget->setItem(i,2,item3);
            }else{
                ui->tableWidget->setItem(i,2,item3);
            }
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
            //ui->tableWidget->setItem(i,2,item3);
            if (distan==""){ //on rajoute une condition pour gerer les distance non definie
                QString distNonDefini="distance non définie";
                QTableWidgetItem *item3= new QTableWidgetItem(distNonDefini);//item1 pour recuperer la distance
                ui->tableWidget->setItem(i,2,item3);
            }else{
                ui->tableWidget->setItem(i,2,item3);
            }
        }
    }
}

