#include "widgetsatellite.h"
#include "ui_widgetsatellite.h"

WidgetSatellite::WidgetSatellite(QWidget *parent) :
    LocalStationWidget(parent),
    ui(new Ui::WidgetSatellite)
{
    ui->setupUi(this);
    this->setMouseTracking(true);
    QFont font(Config::getFontFamily(),Config::getFontSize());
    this->setStyleSheet("background-color: "+Config::getBgColor());
    ui->label->setFont(font);
    ui->label->setStyleSheet("background-color: "+Config::getBgColor());
    ui->tableWidget->setFont(font);
    ui->tableWidget->setStyleSheet("color: "+Config::getFontColor()+"; background-color: "+Config::getBgColor());

    SetSat_categories();
    // get latitude, longitude and distance from mainwindow
    Config::setLatitude(48.78889f);
    Config::setLongitude(2.27078f);
    QNetworkAccessManager * manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
//    QString urlalt =URLOPENELEVATIONEBASE+ui->label_lat->text()
//            +","+ui->label_lng->text();
    QString urlalt =BINGBASE+QString("%1").arg(Config::getLatitude())
               +","+QString("%1").arg(Config::getLongitude())+BINGBKEY;
    request.setUrl(QUrl(urlalt));
    QNetworkReply *pReplayalt = manager->get(request);
    connect (manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(Elevation(QNetworkReply*)));
 }

WidgetSatellite::~WidgetSatellite()
{
    delete ui;
}


void WidgetSatellite::Elevation(QNetworkReply* pReplayalt)
{
    QByteArray bytes = pReplayalt->readAll();
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
    timer->start(120000);
    connect(timer, SIGNAL(timeout()),this,SLOT(Slot_SatTrack()));
}

void WidgetSatellite::Slot_SatTrack()
{
    SatelliteList.clear();
    QNetworkAccessManager * manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    this->setCursor(Qt::WaitCursor);
    Config::setDistance(100.0f);
    double degree=atan(Config::getDistance()/100)*180/PI;
    for(int i=0; i<Sat_categories.size();i++)
    {
        QString url=URLN2YOBASE+QString("%1").arg(Config::getLatitude())+"/"
                +QString("%1").arg(Config::getLongitude())
                +"/"+alt;
        url+="/"+QString::number(degree)+"/";
        url+=QString::number(Sat_categories.values().at(i))+N2YOKEY;
        request.setUrl(QUrl(url));
        QNetworkReply *pReplay = manager->get(request);
        QEventLoop eventLoop;
        QObject::connect(manager,&QNetworkAccessManager::finished,
                         &eventLoop,&QEventLoop::quit);
        eventLoop.exec();
        SatlistTrack(pReplay);
    }
    this->setCursor(Qt::ArrowCursor);
    CleanTable();
    qDebug()<<"SatelliteList has  "<<SatelliteList.size()<< "  satellites !";
    FillTable();
}

void WidgetSatellite::SatlistTrack(QNetworkReply* pReplay)
{
    QByteArray bytes = pReplay->readAll();
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
                if(getDistance(SatelliteIN["satlat"].toFloat(),
                               SatelliteIN["satlng"].toFloat(),
                               Config::getLatitude(),
                               Config::getLongitude())<=Config::getDistance())
                 {
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

}

double WidgetSatellite::getDistance(double lat1, double lng1, double lat2, double lng2)
{
    double radLat1=getRad(lat1);
    double radLng1=getRad(lng1);
    double radLat2=getRad(lat2);
    double radLng2=getRad(lng2);
    double a=radLat1-radLat2;
    double b=getRad(lat1)-getRad(lat2);
    double s=EARTH_RADIUS*2*asin(sqrt(pow(sin(a/2),2)+cos(radLat1)*cos(radLat2)*pow(sin(b/2),2)));
    s=round(s*10000)/10000;
    return s;
}

double WidgetSatellite::getRad(float degree)
{
    return degree*PI/180.0;
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
