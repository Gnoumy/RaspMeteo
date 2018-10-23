#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"


#include "pollutionwidget.h"
#include "rechargevehiculewidget.h"

#include <QDesktopWidget>
#include <QDebug>
#include <QShortcut>

#define NUMBER_OF_WIDGETS       8
#define SCREEN_GEOMETRY_RATIO   0.5   // 1 pour 100% de l'ecran, 0.5 pour la moitie

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initDisplay();
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setContentsMargins(0,0,0,0);
    this->ui->horizontalLayout->setContentsMargins(0,0,0,0);
    this->ui->horizontalLayout->setSpacing(0);
    this->ui->horizontalLayout_2->setContentsMargins(0,0,0,0);
    this->ui->horizontalLayout_2->setSpacing(0);

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close()));

    this->settingsWindow = new Settings(this) ;
    this->connect(this->ui->actionSettings, SIGNAL(triggered(bool)), this, SLOT(openSettings())) ;

    this->connect(this->settingsWindow, SIGNAL(widgetModeChanged()), this, SLOT(switchModeForAllWidgets())) ;

    this->connect(this->settingsWindow, SIGNAL(positionChanged()), this, SLOT(reloadDataForAllWidgets())) ;

    //this->connect(this->ui->testPushButton, SIGNAL(clicked(bool)), this, SLOT(testDebugConfig())) ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reloadDataForAllWidgets()
{
    const QList<LocalStationWidget *> &allLocalStationWidgets(this->findChildren<LocalStationWidget *>());

    for(LocalStationWidget *child : allLocalStationWidgets)
        child->reloadData();
}

void MainWindow::switchModeForAllWidgets()
{
    const QList<LocalStationWidget *> &allLocalStationWidgets(this->findChildren<LocalStationWidget *>());

    for(LocalStationWidget *child : allLocalStationWidgets)
        child->changeMode();
}

void MainWindow::openSettings()
{
    this->settingsWindow->resetSettingsWidgets();
    this->settingsWindow->exec();
}

void MainWindow::initDisplay()
{
    // dimensions de mon pc = 1680:1050
    resize(QDesktopWidget().availableGeometry(this).size() * SCREEN_GEOMETRY_RATIO);


//    this->widgets = new LocalStationWidget*[NUMBER_OF_WIDGETS] ;

//    this->widgets[0] = new PollutionWidget(this);
//    this->widgets[0]->setParent(this) ;
//    this->widgets[0]->setCursor(Qt::CrossCursor);
//    this->widgets[0]->setGeometry(QRect(50,50,500,500));
//    this->widgets[0]->show();

//    /*-------------Recharge batterie vehicule électrique-----------*/
//    this->widgets[1]=new RechargeVehiculeWidget(this);
//    this->widgets[1]->setParent(this) ;
//    this->widgets[1]->setCursor(Qt::CrossCursor);
//    this->widgets[1]->setGeometry(QRect(50,50,500,500));
//    this->widgets[1]->show();
}



void MainWindow::mousePressEvent(QMouseEvent *event) {
    this->mouseClick_X_Coordinate = event->x();
    this->mouseClick_Y_Coordinate = event->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX() - this->mouseClick_X_Coordinate,
         event->globalY() - this->mouseClick_Y_Coordinate);
}


