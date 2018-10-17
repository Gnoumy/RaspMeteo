#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QQuickView>
#include <QWidget>
#include <QObject>

class MapWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapWidget( QWidget *parent = Q_NULLPTR );
    ~MapWidget( );
    void changeSize( QSize size );
    void sendCoordinates( double, double );

private:
    QQuickView *view;
    QWidget* container;
    QObject *object;

};

#endif // MAPWIDGET_H
