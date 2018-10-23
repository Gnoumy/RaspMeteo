#include "widgetsatellite.h"
#include "ui_widgetsatellite.h"

WidgetSatellite::WidgetSatellite(QWidget *parent) :
    LocalStationWidget(parent),
    ui(new Ui::WidgetSatellite)
{
    ui->setupUi(this);
    this->setMouseTracking(true);    
    this->setStyleSheet("background-color: "+Config::getBgColor());
    //  ********  Parametre du lineEdit header  ********
    QFont header(Config::getHeaderFontFamily(),Config::getHeaderFontSize());
    ui->lineEdit->setFont(header);
    ui->lineEdit->setStyleSheet("color: "+Config::getHeaderFontColor()
                             +"; background-color: "
                             +Config::getHeaderBgColor());
    ui->lineEdit->setReadOnly(true);

    //  ********  Parametre de la table Widget  ********
    QFont font(Config::getTableFontFamily(),Config::getTableFontSize());
    ui->tableWidget->setFont(font);
    ui->tableWidget->setStyleSheet("color: "+Config::getTableFontColor()
                                   +"; background-color: "+
                                   Config::getTableBgColor());

    SetSat_categories();
    //get latitude, longitude and distance from mainwindow
//    Config::setLatitude(48.78889f);
//    Config::setLongitude(2.27078f);
    QNetworkAccessManager * manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
//    QString urlalt =URLOPENELEVATIONEBASE+ui->label_lat->text()
//            +","+ui->label_lng->text();
    QString urlalt =BINGBASE+QString("%1").arg(Config::getLatitude())
               +","+QString("%1").arg(Config::getLongitude())+BINGBKEY;
    request.setUrl(QUrl(urlalt));
    manager->get(request);
    //QNetworkReply *pReplayalt = manager->get(request);
    connect (manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(Elevation(QNetworkReply*)));
   //  ********  image show  ********
    QImage img;
    img.load(":/satellites/satobservation.png");
    Showpic(img);
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
    timer->start(TIME_RESTART);
    connect(timer, SIGNAL(timeout()),this,SLOT(Slot_SatTrack()));
}

void WidgetSatellite::Slot_SatTrack()
{
    SatelliteList.clear();
    QNetworkAccessManager * manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    this->setCursor(Qt::WaitCursor);
//    Config::setDistance(300.0f);
    double degree=atan(Config::getDistance()*FACTOR_DISTANCE/MINI_SATALT)*180/PI;
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
    QImage img;
    img.load(":/satellites/satobservation.png");
    DrawSatellites(&img);
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
    double radLat2=getRad(lat2);
    double a=radLat1-radLat2;
    double b=getRad(lng1)-getRad(lng2);
    double s=EARTH_RADIUS*2;
    s*=asin(sqrt(pow(sin(a/2),2)+cos(radLat1)*cos(radLat2)*pow(sin(b/2),2)));
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
    col_labels<<"ID"<<"Name"<<"Launch Date"
             <<"Cate"<<"Lat"<<"Lng"
             <<"Alt(km)";
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setRowCount(SatelliteList.size());
    ui->tableWidget->setHorizontalHeaderLabels(col_labels);
    for(int i=0;i<SatelliteList.size();i++)
    {
        Satellite sat = SatelliteList.at(i);
        ui->tableWidget->setItem(i,0,
                                 new QTableWidgetItem(QString::number(sat.Get_satid())));
      //  ui->tableWidget->setItem(i,1,new QTableWidgetItem(sat.Get_satname()));
        //ui->tableWidget->setCellWidget(i,1,new QLabel(sat.Get_satname()));
         AutoScrollingLabel *label_sat_name= new AutoScrollingLabel(this);
         label_sat_name->setText(sat.Get_satname());
         ui->tableWidget->setCellWidget(i,1,label_sat_name);

//        ui->tableWidget->setItem(i,2,
//                                 new QTableWidgetItem(sat.Get_intDesignator()));
        ui->tableWidget->setItem(i,2,
                                 new QTableWidgetItem(sat.Get_launchDate()));
        AutoScrollingLabel *label_sat_cat= new AutoScrollingLabel(this);
        label_sat_cat->setText(sat.Get_category());
        ui->tableWidget->setCellWidget(i,3,label_sat_cat);
//        ui->tableWidget->setItem(i,3,
//                                 new QTableWidgetItem(sat.Get_category()));
        ui->tableWidget->setItem(i,4,
                                 new QTableWidgetItem(QString::number(sat.Get_satlat())));
        ui->tableWidget->setItem(i,5,
                                 new QTableWidgetItem(QString::number(sat.Get_satlng())));
        ui->tableWidget->setItem(i,6,
                                 new QTableWidgetItem(QString::number(sat.Get_satalt())));
    }
 //   ui->tableWidget->resizeColumnsToContents();
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

void WidgetSatellite::Showpic(QImage & img)
{
    QImage scaledimg;
    ui->label->setGeometry(0,0,600,300);
    int Owidth=img.width();
    int Oheight=img.height() ;
    int Fwidth, Fheight,Mul;
    if((Owidth/ui->label->geometry().width())
            >=(Oheight/ui->label->geometry().height()))
    {
        Mul=Owidth/ui->label->geometry().width();
    }
    else
    {
        Mul=Oheight/ui->label->geometry().height();
    }
    Fwidth=Owidth/Mul;
    Fheight=Oheight/Mul;
    scaledimg=img.scaled(Fwidth,Fheight,Qt::KeepAspectRatio);
    ui->label->resize(scaledimg.width(),scaledimg.height());
    ui->label->setPixmap(QPixmap::fromImage(scaledimg));
    ui->label->show();
}

void WidgetSatellite::DrawSatellites(QImage * img)
{
    QPainter p(img);
    QFont font(Config::getFontFamily(),Config::getFontSize());
    p.setFont(font);
    for(int i=0;i<SatelliteList.size();i++)
    {
        Satellite sat = SatelliteList.at(i);
        QImage imgSat;
        if(i<10)
        {
        imgSat.load(":/satellites/sat"+QString::number(i+1)+".png");
        int satalt;
        if(sat.Get_satalt()>HIGHTALT)
        {
            satalt=0;
        }else if(sat.Get_satalt()>MEDIENALT)
        {
            satalt=50;
        }else
        {
            satalt=100;
        }
        p.drawPixmap(i*70,satalt,50,50,QPixmap::fromImage(imgSat));
        p.drawText(i*70,satalt+60,sat.Get_satname());
        }
        else
        {
        imgSat.load(":/satellites/sat"+QString::number(i-9)+".png");
        int satalt;
        if(sat.Get_satalt()>HIGHTALT)
        {
            satalt=70;
        }else if(sat.Get_satalt()>MEDIENALT)
        {
            satalt=95;
        }else
        {
            satalt=120;
        }
        p.drawPixmap((i-10)*70,satalt,50,50,QPixmap::fromImage(imgSat));
        p.drawText((i-10)*70,satalt+60,sat.Get_satname());
        }
    }
    QString msg=" I can see ";
    msg=msg+QString::number(SatelliteList.size());
    msg=msg+" satellite(s)";
    p.drawText(350,270,msg);
    Showpic(*img);
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

void WidgetSatellite::reloadData()
{
    QNetworkAccessManager * manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    QString urlalt =BINGBASE+QString("%1").arg(Config::getLatitude())
               +","+QString("%1").arg(Config::getLongitude())+BINGBKEY;
    request.setUrl(QUrl(urlalt));
    manager->get(request);
    //QNetworkReply *pReplayalt = manager->get(request);
    connect (manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(Elevation(QNetworkReply*)));
}

void WidgetSatellite::changeMode()
{

}
