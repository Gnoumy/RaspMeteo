#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QWidget>

namespace Ui {
class MapWindow;
}

class MapWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MapWindow( double latitude = 48.85341, double longitude = 2.3488, QWidget *parent = Q_NULLPTR );
    ~MapWindow( );

protected :
     virtual void resizeEvent( QResizeEvent* );
     virtual void showEvent( QShowEvent * );

private:
    Ui::MapWindow *ui;
    void resizeAll( );
};

#endif // MAPWINDOW_H
