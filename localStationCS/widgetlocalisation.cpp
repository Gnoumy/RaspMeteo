#include "widgetlocalisation.h"
#include "ui_widgetlocalisation.h"

#include <QPainter>


widgetlocalisation::widgetlocalisation(QWidget *parent) :
    LocalStationWidget(parent),
    ui(new Ui::widgetlocalisation)
{
    ui->setupUi(this);
    manager = new NetworkAccessManager(this);
    //******************----------------------***************
    /*QString background, couleur;
     *
    background = Config::getBgColor();
    couleur = Config::getFontColor();
    qDebug()<<couleur;
    setStyleSheet("QWidget { background-color :"+ background+"; color :"+couleur+"; }");
    //******************----------------------**************
    */


    QUrl url("https://nominatim.openstreetmap.org/reverse?format=json&lat=48.773218&lon=2.244258&zoom=18&addressdetails=1");
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

    QByteArray ret=reply->readAll();
    //qDebug()<<ret;
    QJsonDocument myJson=QJsonDocument::fromJson(ret);

    //qDebug() << myJson.toObject().toVariantMap()["licence"].toMap()["lat"].toString();
    //qDebug() << myJson.array()[1].toObject().toVariantMap()["links"].toList().at(0).toMap()["href"].toString();
    //qDebug() << myJson.object().toVariantMap()["licence"].toMap()["lat"].toString();
    //qDebug() << myJson.object().toVariantMap()["licence"].toMap()["lon"].toString();
    qDebug() << myJson.object().toVariantMap()["display_name"].toString();
    qDebug() << myJson.object().toVariantMap()["address"].toMap()["town"].toString();
    qDebug() << myJson.object().toVariantMap()["address"].toMap()["postcode"].toString();
    qDebug() << myJson.object().toVariantMap()["address"].toMap()["building"].toString();
    qDebug() << myJson.object().toVariantMap()["address"].toMap()["state"].toString();
    qDebug() << myJson.object().toVariantMap()["address"].toMap()["country"].toString();


    QString vil(myJson.object().toVariantMap()["address"].toMap()["town"].toString());
    QString cod(myJson.object().toVariantMap()["address"].toMap()["postcode"].toString());
    QString sta(myJson.object().toVariantMap()["address"].toMap()["state"].toString());

    ui->tableWidget->setColumnCount(1);// le nombre de colonne
    ui->tableWidget->setRowCount(4);// le nombre de ligne
    ui->tableWidget->horizontalHeader()->hide();//permet de ne pas afficher les numeros de ligne
    ui->tableWidget->verticalHeader()->hide();// permet de ne pas afficher les numeros de ligne

    QTableWidgetItem *ville = new QTableWidgetItem(vil);
    ui->tableWidget->setItem(0, 0, ville);

    QTableWidgetItem *code = new QTableWidgetItem(cod);
    ui->tableWidget->setItem(0, 1, code);

    QTableWidgetItem *state = new QTableWidgetItem(sta);
    ui->tableWidget->setItem(0, 2, state);



}
