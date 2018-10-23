#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "localstationwidget.h"
#include "settings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openSettings();

    void switchModeForAllWidgets();
    void reloadDataForAllWidgets();
private:
    Ui::MainWindow *ui;
    LocalStationWidget **widgets ;
    Settings *settingsWindow ;
    int mouseClick_X_Coordinate;
    int mouseClick_Y_Coordinate;

    void initDisplay() ;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
