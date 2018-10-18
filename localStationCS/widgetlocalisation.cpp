#include "widgetlocalisation.h"
#include "ui_widgetlocalisation.h"

#include <QFont>

#include <QPainter>
#include "config.h"






widgetlocalisation::widgetlocalisation(QWidget *parent) :
    LocalStationWidget(parent),
    ui(new Ui::widgetlocalisation)
{
    ui->setupUi(this);
    manager = new NetworkAccessManager(this);


    QString lati = QString::number(Config::getLatitude(),'g',10);
    //qDebug() << lati;
    QString longi = QString::number(Config::getLongitude(),'g',10);
    //qDebug() << longi;

    QUrl url("https://nominatim.openstreetmap.org/reverse?format=json&lat="+lati+"&lon="+longi+"&zoom=18&addressdetails=1");
   //QUrl url("https://api.navitia.io/v1/coverage/sandbox/stop_areas/stop_area%3ARAT%3ASA%3AGDLYO/stop_schedules?items_per_schedule=2&");
    //url.setUserName("45205f1c-86f6-4740-9af7-a5dbe3fcf15d");
    //url.setPassword("dieynaba92");
    QNetworkRequest request;
    request.setUrl(url);
     //connect(manager, SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)), this, SLOT(authenticationRequired(QNetworkReply*, QAuthenticator*)));
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
    manager->get(request);





}

widgetlocalisation::~widgetlocalisation()
{
    delete ui;
}


//void MainWindow::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
//{
//    qDebug()<<"auth";
//    authenticator->setUser("45205f1c-86f6-4740-9af7-a5dbe3fcf15d");
//    authenticator->setPassword("dieynaba92");
//}

void widgetlocalisation::replyFinished(QNetworkReply *reply)
{
    QByteArray bytes = reply->readAll();
    QJsonParseError jsonError;
    QJsonDocument doucument =QJsonDocument::fromJson(bytes,&jsonError);
    if(jsonError.error != QJsonParseError::NoError)
    {
            qDebug()<<QStringLiteral("Parsed Json failure");
            qDebug()<<jsonError.errorString();
            return;
    }

    //QByteArray ret=reply->readAll();
    //qDebug()<<ret;
    QJsonDocument myJson=QJsonDocument::fromJson(bytes);



    QFont font(Config::getFontFamily(),Config::getFontSize());//font(police, taille, couleur)
    QFont header(Config::getHeaderFontFamily(),Config::getHeaderFontSize());
        ui->tableWidget->setFont(font);
        //ui->tableWidget->setStyleSheet(Config::getFontColor());
        ui->tableWidget->setStyleSheet("color :"+Config::getTableFontColor()+";background-color :"+Config::getTableBgColor());

        ui->lineEdit->setFont(header);//taille de police du l'entete
        ui->lineEdit->setStyleSheet("color :"+Config::getHeaderFontColor()+";background-color :"+Config::getHeaderBgColor());
        ui->lineEdit->setAlignment(Qt::AlignHCenter);

    //qDebug() << myJson.toObject().toVariantMap()["licence"].toMap()["lat"].toString();
    //qDebug() << myJson.array()[1].toObject().toVariantMap()["links"].toList().at(0).toMap()["href"].toString();
    //qDebug() << myJson.object().toVariantMap()["licence"].toMap()["lat"].toString();
    //qDebug() << myJson.object().toVariantMap()["licence"].toMap()["lon"].toString();
    //qDebug() << myJson.object().toVariantMap()["display_name"].toString();
    //qDebug() << myJson.object().toVariantMap()["address"].toMap()["town"].toString();
    //qDebug() << myJson.object().toVariantMap()["address"].toMap()["postcode"].toString();
    //qDebug() << myJson.object().toVariantMap()["address"].toMap()["building"].toString();
    //qDebug() << myJson.object().toVariantMap()["address"].toMap()["state"].toString();
    //qDebug() << myJson.object().toVariantMap()["address"].toMap()["country"].toString();


    QString vil(myJson.object().toVariantMap()["address"].toMap()["town"].toString());
    QString cod(myJson.object().toVariantMap()["address"].toMap()["postcode"].toString());
    QString sta(myJson.object().toVariantMap()["address"].toMap()["state"].toString());
    QString ru(myJson.object().toVariantMap()["address"].toMap()["road"].toString());
    QString lon(myJson.object().toVariantMap()["lon"].toString());
    //qDebug() << lon;
    QString lat(myJson.object().toVariantMap()["lat"].toString());
    //QString build(myJson.object().toVariantMap()["address"].toMap()["building"].toString());
    //qDebug() << build;
    //float lon=myJson.object().toVariantMap()["licence"].toMap()["lon"].toFloat();
    //QString lonst = QString::number(lon);

    /*QList<QString> list;
     list << "town" << "postecode" << "road";
     qDebug() << list;*/


    ui->tableWidget->setColumnCount(1);// le nombre de colonne
    ui->tableWidget->setRowCount(6);// le nombre de ligne
    ui->tableWidget->horizontalHeader()->hide();//permet de ne pas afficher les numeros de ligne
    ui->tableWidget->verticalHeader()->hide();// permet de ne pas afficher les numeros de ligne
    ui->tableWidget->setShowGrid(false);// pour enlever les grilles dans un tableau

    //int taillePolice = 13;

    //Config::getFontSize();

    QTableWidgetItem *rue = new QTableWidgetItem(ru);
    ui->tableWidget->setItem(0, 0, rue);
    //QBrush couleurRue("#000000");
    //rue->setForeground(couleurRue);
    //QFont fontRue("Times", taillePolice, QFont::Bold, false);
    //rue->setFont(fontRue);

    QTableWidgetItem *ville = new QTableWidgetItem(vil);
    ui->tableWidget->setItem(0, 1, ville);
    //QBrush couleurVille("#000000"); //la couleur
    //ville->setForeground(couleurVille);
    //QFont fontVille("Times", taillePolice, QFont::Bold, false);// taille de la police
    //ville->setFont(fontVille);


    QTableWidgetItem *code = new QTableWidgetItem(cod);
    ui->tableWidget->setItem(0, 2, code);
    //QBrush couleurCode("#000000");
    //code->setForeground(couleurCode);
    //QFont fontCode("Times", taillePolice, QFont::Bold, false); //bold epaisseur de la police
    //code->setFont(fontCode);





    QTableWidgetItem *state = new QTableWidgetItem(sta);
    ui->tableWidget->setItem(0, 3, state);
    /*QBrush couleurState("#000000");
    state->setForeground(couleurState);
    QFont fontState("Times", taillePolice, QFont::Bold, false); // true veut dire si on veut mettre en italique ou pas, si on veut pas on fait false.
    state->setFont(fontState );*/

    QTableWidgetItem *latitude = new QTableWidgetItem(lat);
    ui->tableWidget->setItem(0, 4, latitude);
    /*QBrush couleurLat("#000000");
    latitude->setForeground(couleurLat);
    QFont fontLat("Times", taillePolice, QFont::Bold, false);
    latitude->setFont(fontLat);*/









    //QTableWidgetItem *building = new QTableWidgetItem(build);
    //ui->tableWidget->setItem(0, 3, building);
    /*QBrush couleurBuild("#000000");
    building->setForeground(couleurBuild);
    QFont fontBuild("Times", taillePolice, QFont::Bold, false);
    building->setFont(fontBuild);*/

    QTableWidgetItem *longitude = new QTableWidgetItem(lon);
    ui->tableWidget->setItem(0, 5, longitude);
    /*QBrush couleurLon("#000000");
    longitude->setForeground(couleurLon);
    QFont fontLon("Times", taillePolice, QFont::Bold, false);
    longitude->setFont(fontLon);*/





}

void widgetlocalisation::resizeEvent(QResizeEvent *event)
{
    ui->tableWidget->setColumnWidth(0,this->width());
}
