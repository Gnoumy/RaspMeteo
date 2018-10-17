#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QWidget>

namespace Ui { class MapWindow; }

class MapWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MapWindow( QWidget *parent = Q_NULLPTR, double latitude = 48.85341, double longitude = 2.3488 );  //
    virtual ~MapWindow( );

protected :
     virtual void resizeEvent( QResizeEvent* );
     virtual void showEvent( QShowEvent * );

private:
    Ui::MapWindow *ui;
    void resizeAll( );

public slots:
    void setCoordinates( double, double );
};

#endif // MAPWINDOW_H
