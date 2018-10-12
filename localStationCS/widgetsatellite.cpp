#include "widgetsatellite.h"
#include "ui_widgetsatellite.h"

WidgetSatellite::WidgetSatellite(QWidget *parent) :
    LocalStationWidget(parent),
    ui(new Ui::WidgetSatellite)
{
    ui->setupUi(this);
    QFont font(Config::getFontFamily(),Config::getFontSize());
    this->setStyleSheet("background-color: "+Config::bgColor);
    ui->label->setFont(font);
    ui->label->setStyleSheet("background-color: "+Config::bgColor);
    ui->tableWidget->setFont(font);
    ui->tableWidget->setStyleSheet("color: "+Config::fontColor+"; background-color: "+Config::bgColor);

    ui->progressBar->setValue(0);
    SetSat_categories();
    // get latitude, longitude and distance from mainwindow
    Config::latitude=48.78889;
    Config::longitude=2.27078f;
    QNetworkAccessManager * manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
//    QString urlalt =URLOPENELEVATIONEBASE+ui->label_lat->text()
//            +","+ui->label_lng->text();
    QString urlalt =BINGBASE+QString("%1").arg(Config::getLatitude())
               +","+QString("%1").arg(Config::getLongitude())+BINGBKEY;
    qDebug()<<urlalt;
    request.setUrl(QUrl(urlalt));
    QNetworkReply *pReplayalt = manager->get(request);
    connect ( manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(Elevation(QNetworkReply*)));
    QTimer * timer = new QTimer(this);
    timer->start(60000);
    connect(timer, SIGNAL(timeout()),this,SLOT(Slot_SatTrack()));
 }

WidgetSatellite::~WidgetSatellite()
{
    delete ui;
}


void WidgetSatellite::Elevation(QNetworkReply* pReplayalt)
{
    QByteArray bytes = pReplayalt->readAll();
     qDebug()<<bytes;
    QJsonParseError jsonError;
    QJsonDocument doucument =QJsonDocument::fromJson(bytes,&jsonError);
    if(jsonError.error != QJsonParseError::NoError)
    {
        qDebug()<<QStringLiteral("Parsed Json failure");
        qDebug()<<jsonError.errorString();
        return;
    }
    if(doucument.isObject())
    {
    QJsonObject obj =doucument.object();
    QVariantMap data = doucument.toVariant().toMap();
   /* QVariantMap list = data["results"].toList().at(0).toMap();
        //https://api.open-elevation.com/api/v1/lookup?locations=
    QString alt = list["elevation"].toString();
    ui->label_alt->setText(alt);*/
    QVariantMap resourceSets = data["resourceSets"].toList().at(0).toMap();
    QVariantMap resources = resourceSets["resources"].toList().at(0).toMap();
    this->alt = resources["offsets"].toList().at(0).toString();
    }
    Slot_SatTrack();
    QTimer * timer = new QTimer(this);
    timer->start(60000);
    connect(timer, SIGNAL(timeout()),this,SLOT(Slot_SatTrack()));
}

void WidgetSatellite::Slot_SatTrack()
{
    SatelliteList.clear();
    CleanTable();
    qDebug()<<"begin a new satellite list"<<SatelliteList.size();
    QNetworkAccessManager * manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    ui->progressBar->setValue(0);
    ui->progressBar->setRange(0,Sat_categories.size());
    for(int i=0; i<Sat_categories.size();i++)
    {
        QString url=URLN2YOBASE+QString("%1").arg(Config::getLatitude())+"/"
                +QString("%1").arg(Config::getLongitude())
                +"/"+alt+"/10/";
        url=url+QString::number(Sat_categories.values().at(i))+N2YOKEY;
        qDebug()<<url;
        request.setUrl(QUrl(url));
        QNetworkReply *pReplay = manager->get(request);
        QEventLoop eventLoop;
        QObject::connect(manager,&QNetworkAccessManager::finished,
                         &eventLoop,&QEventLoop::quit);
        eventLoop.exec();
        SatlistTrack(pReplay);
        ui->progressBar->setValue(i+1);
    }
    qDebug()<<"SatelliteList has  "<<SatelliteList.size()<< "  satellites !";
    FillTable();
}

void WidgetSatellite::SatlistTrack(QNetworkReply* pReplay)
{
    QByteArray bytes = pReplay->readAll();
    qDebug()<<bytes ;
    QJsonParseError jsonError;
    QJsonDocument doucument =QJsonDocument::fromJson(bytes,&jsonError);
    if(jsonError.error != QJsonParseError::NoError)
    {
        qDebug()<<QStringLiteral("Parsed Json failure");
        return;
    }
    if(doucument.isObject())
    {
        QJsonObject obj =doucument.object();
        QVariantMap data = doucument.toVariant().toMap();
        QVariantMap info =data["info"].toMap();
        int num_Satelllite =info["satcount"].toInt();
        if(num_Satelllite>0)
        {
            QVariantList  SatelliteListIN=data["above"].toList();
            for(int i=0; i<num_Satelllite;i++)
            {
                QVariantMap SatelliteIN=SatelliteListIN.at(i).toMap();
                Satellite sat(SatelliteIN["satid"].toInt(),
                              SatelliteIN["satname"].toString(),
                        SatelliteIN["intDesignator"].toString(),
                        SatelliteIN["launchDate"].toString(),
                        SatelliteIN["satlat"].toFloat(),
                        SatelliteIN["satlng"].toFloat(),
                        SatelliteIN["satalt"].toFloat(),
                        info["category"].toString()
                        );
                SatelliteList.prepend(sat);
            }
        }
      }

}

void WidgetSatellite::FillTable()
{
    QStringList col_labels;
    col_labels<<"Sat ID"<<"Sat Name"<<"International Designator"
             <<"Launch Date"<<"Category";
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setRowCount(SatelliteList.size());
    ui->tableWidget->setHorizontalHeaderLabels(col_labels);
    for(int i=0;i<SatelliteList.size();i++)
    {
        Satellite sat = SatelliteList.at(i);
        ui->tableWidget->setItem(i,0,
                                 new QTableWidgetItem(QString::number(sat.Get_satid())));
        ui->tableWidget->setItem(i,1,
                                 new QTableWidgetItem(sat.Get_satname()));
        ui->tableWidget->setItem(i,2,
                                 new QTableWidgetItem(sat.Get_intDesignator()));
        ui->tableWidget->setItem(i,3,
                                 new QTableWidgetItem(sat.Get_launchDate()));
        ui->tableWidget->setItem(i,4,
                                 new QTableWidgetItem(sat.Get_category()));
    }
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
 }

void WidgetSatellite::CleanTable()
{
    for(int i=ui->tableWidget->rowCount();i>0;i--)
    {
        ui->tableWidget->removeRow(0);
    }
}

void WidgetSatellite::SetSat_categories()
{
    Sat_categories.insert("Amateur radio",18);
    Sat_categories.insert("Beidou Navigation System",35);
    Sat_categories.insert("Brightest",1);
    Sat_categories.insert("Celestis",45);
    Sat_categories.insert("CubeSats",32);
    Sat_categories.insert("Disaster monitoring",8);
    Sat_categories.insert("Earth resources",6);
    Sat_categories.insert("Education",29);
    Sat_categories.insert("Engineering",28);
    Sat_categories.insert("Experimental",19);
    Sat_categories.insert("Flock",48);
    Sat_categories.insert("Galileo",22);
    Sat_categories.insert("Geodetic",27);
    Sat_categories.insert("Geostationary",10);
    Sat_categories.insert("GPS Constellation",50);
    Sat_categories.insert("GPS Operational",20);
    Sat_categories.insert("Globalstar",17);
    Sat_categories.insert("Glonass Operational",21);
    Sat_categories.insert("GOES",5);
    Sat_categories.insert("Gonets",40);
    Sat_categories.insert("Gorizont",12);
    Sat_categories.insert("Intelsat",11);
    Sat_categories.insert("Iridium",15);
    Sat_categories.insert("IRNSS",46);
    Sat_categories.insert("ISS",2);
    Sat_categories.insert("Lemur",49);
    Sat_categories.insert("Military",30);
    Sat_categories.insert("Molniya",14);
    Sat_categories.insert("Navy Navigation Satellite System",24);
    Sat_categories.insert("NOAA",4);
    Sat_categories.insert("O3B Networks",43);
    Sat_categories.insert("Orbcomm",16);
    Sat_categories.insert("Parus",38);
    Sat_categories.insert("QZSS",47);
    Sat_categories.insert("Radar Calibration",31);
    Sat_categories.insert("Raduga",13);
    Sat_categories.insert("Russian LEO Navigation",25);
    Sat_categories.insert("Satellite-Based Augmentation System",23);
    Sat_categories.insert("Search & rescue",7);
    Sat_categories.insert("Space & Earth Science",26);
    Sat_categories.insert("Strela",39);
    Sat_categories.insert("Tracking and Data Relay Satellite System",9);
    Sat_categories.insert("Tselina",44);
    Sat_categories.insert("Tsikada",42);
    Sat_categories.insert("Tsiklon",41);
    Sat_categories.insert("TV",34);
    Sat_categories.insert("Weather",3);
    Sat_categories.insert("Westford Needles",37);
    Sat_categories.insert("XM and Sirius",33);
    Sat_categories.insert("Yaogan",36);
}
