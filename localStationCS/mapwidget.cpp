#include "mapwidget.h"

#include <QObject>
#include <QDebug>
#include <QVBoxLayout>
#include <QQuickItem>

MapWidget::MapWidget( QWidget *parent ) : QWidget( parent )
{
    view = new QQuickView( );
    container = QWidget::createWindowContainer( view, this );

    view->setSource( QUrl( QStringLiteral( "qrc:/qmlMapsOSM.qml" ) ) );
    object = view->rootObject();
}

void MapWidget::setCoordinates( double latitude, double longitude )
{
    object->setProperty( "qlatitude", latitude );
    object->setProperty( "qlongitude", longitude );
}

MapWidget::~MapWidget()
{
    delete object;
    delete view;
}

void MapWidget::changeSize( QSize size )
{
   object->setProperty( "width", size.width() );
   object->setProperty( "height", size.height() );

   container->resize( size );
}
