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
    void testDebugConfig();
private:
    Ui::MainWindow *ui;
    LocalStationWidget **widgets ;
    Settings *settingsWindow ;

    void initDisplay() ;
};

#endif // MAINWINDOW_H
