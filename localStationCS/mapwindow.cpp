#include "mapwindow.h"
#include "ui_mapwindow.h"
#include <QQuickView>
#include <QQuickItem>
#include <QUrl>
#include <QtDebug>
#include <QGeoRectangle>
#include <QVariant>
#include "config.h"

//MapWindow::MapWindow( float latitude, float longitude, QWidget *parent ) : QWidget(parent), ui(new Ui::MapWindow)
MapWindow::MapWindow( QWidget *parent ) : QWidget(parent), ui(new Ui::MapWindow)
{
    ui->setupUi(this);

    //Loading qml plugin for OSM maps
    //view = new QQuickView();
    //container = QWidget::createWindowContainer(view, this);

    container = new QQuickWidget;
    container->setResizeMode(QQuickWidget::SizeRootObjectToView);

    //view->setSource(QUrl( QStringLiteral( "qrc:/qmlMapsOSM.qml" )));
    container->setSource(QUrl( QStringLiteral( "qrc:/qmlMapsOSM.qml" )));

    //object = view->rootObject();
    object = container->rootObject();

    setCoordinates( Config::getLatitude(), Config::getLongitude() );
    ui->verticalLayout->addWidget(container);

}

MapWindow::~MapWindow()
{
    //delete view;
    delete container;
    delete ui;
}

void MapWindow::resizeEvent( QResizeEvent* )
{

    object->setProperty( "width", this->size().width() );
    object->setProperty(  "height", this->size().height() );

    container->resize( this->size( ) );
}


void MapWindow::setCoordinates( float latitude, float longitude )
{
   object->setProperty( "qlatitude", latitude );
   object->setProperty( "qlongitude", longitude );

   this->update( );
}
