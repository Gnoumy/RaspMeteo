#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopWidget>
#include <QDebug>

#define NUMBER_OF_WIDGETS       8
#define SCREEN_GEOMETRY_RATIO   1   // 1 pour 100% de l'ecran, 0.5 pour la moitie

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initDisplay();

    this->settingsWindow = new Settings(this) ;
    this->connect(this->ui->actionSettings, SIGNAL(triggered(bool)), this, SLOT(openSettings())) ;


    this->connect(this->ui->testPushButton, SIGNAL(clicked(bool)), this, SLOT(testDebugConfig())) ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openSettings()
{
    this->settingsWindow->resetSettingsWidgets();
    this->settingsWindow->show();
}

void MainWindow::initDisplay()
{
    // dimensions de mon pc = 1680:1050
    resize(QDesktopWidget().availableGeometry(this).size() * SCREEN_GEOMETRY_RATIO);

    const int W = QDesktopWidget().availableGeometry(this).size().width(),
              H = QDesktopWidget().availableGeometry(this).size().height()  ;


    this->widgets = new LocalStationWidget*[NUMBER_OF_WIDGETS] ;

    this->widgets[0] = new LocalStationWidget(this);
    this->widgets[0]->setParent(this) ;
    this->widgets[0]->setCursor(Qt::CrossCursor);
    this->widgets[0]->setGeometry(QRect(50,50,500,500));
    this->widgets[0]->show();
}

#include <config.h>
void MainWindow::testDebugConfig()
{
    qDebug() << "\nfontFamily" << Config::fontFamily ;
    qDebug() << "fontColor" << Config::fontColor ;
    qDebug() << "bgColor" << Config::bgColor ;
    qDebug() << "fontSize" << Config::fontSize ;
    qDebug() << "\nheaderFontFamily" << Config::headerFontFamily ;
    qDebug() << "headerFontColor" << Config::headerFontColor ;
    qDebug() << "headerBgColor" << Config::headerBgColor ;
    qDebug() << "headerFontSize" << Config::headerFontSize ;
    qDebug() << "\nfooterFontFamily" << Config::footerFontFamily ;
    qDebug() << "footerFontColor" << Config::footerFontColor ;
    qDebug() << "footerBgColor" << Config::footerBgColor ;
    qDebug() << "footerFontSize" << Config::footerFontSize ;
    qDebug() << "\nlatitude" << Config::latitude ;
    qDebug() << "longitude" << Config::longitude ;
    qDebug() << "distance" << Config::distance ;
}
