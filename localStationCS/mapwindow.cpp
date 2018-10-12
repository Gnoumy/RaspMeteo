#include "mapwindow.h"
#include "ui_mapwindow.h"

MapWindow::MapWindow( double latitude, double longitude, QWidget *parent ) : QWidget( parent ),
    ui( new Ui::MapWindow )
{
    ui->setupUi( this );
    ui->mapToDisplay->setCoordinates( latitude, longitude );
}

MapWindow::~MapWindow()
{
    delete ui;
}

void MapWindow::resizeEvent( QResizeEvent* )
{
    resizeAll( );
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
