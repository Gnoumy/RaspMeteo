#include "mapwindow.h"
#include "ui_mapwindow.h"

MapWindow::MapWindow( QWidget *parent, double latitude, double longitude ) : QWidget( parent ),
    ui( new Ui::MapWindow )
{
    ui->setupUi( this );
    setCoordinates( latitude, longitude );
}

MapWindow::~MapWindow()
{
    delete ui;
}

void MapWindow::resizeEvent( QResizeEvent* )
{
    resizeAll( );
    qDebug() << "Width of map " << ui->mapToDisplay->width();
    qDebug() << "Heigth of map " << ui->mapToDisplay->height();
}

void MapWindow::showEvent( QShowEvent * )
{
    resizeAll();
}

void MapWindow::resizeAll( )
{

    MapWidget *map;
    QList< QWidget* > listChildren = findChildren< QWidget* >( );

    foreach( QWidget* ptrWidget, listChildren) {
        map = qobject_cast< MapWidget * >( ptrWidget );
        if ( map )
            map->changeSize( map->size( ) );
    }
}

void MapWindow::setCoordinates( double latitude, double longitude )
{
   ui->mapToDisplay->sendCoordinates( latitude, longitude );
   this->update( );
}

