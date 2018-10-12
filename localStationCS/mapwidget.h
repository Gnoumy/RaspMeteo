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

private:
    QQuickView *view;
    QWidget* container;
    QObject *object;

public slots:
    void setCoordinates( double, double );

};

#endif // MAPWIDGET_H