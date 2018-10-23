#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QWidget>
#include <QQuickView>
#include <QObject>
#include <QQuickWidget>

namespace Ui { class MapWindow; }

class MapWindow : public QWidget
{
    Q_OBJECT

public:
    //explicit MapWindow( float latitude = 48.85341, float longitude = 2.3488, QWidget *parent = Q_NULLPTR );
    explicit MapWindow( QWidget *parent = Q_NULLPTR );
    ~MapWindow();

protected :
     virtual void resizeEvent( QResizeEvent* );

private:
    Ui::MapWindow *ui;
    void resizeAll( );
    QQuickView *view;
    //QWidget *container;
    QObject* object;
    QQuickWidget *container;

public slots:
    void setCoordinates( float, float );
};

#endif // MAPWINDOW_H
