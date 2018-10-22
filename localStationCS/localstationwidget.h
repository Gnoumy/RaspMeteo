#ifndef LOCALSTATIONWIDGET_H
#define LOCALSTATIONWIDGET_H

#include <QWidget>

class LocalStationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LocalStationWidget(QWidget *parent = nullptr);
    virtual void reloadData() = 0 ; // recupere les donnees pour actualiser le widget
    virtual void changeFont() ;//= 0 ; // changer la police (style, taille, etc...)
    virtual void changeMode() = 0 ; // changer le mode du widget (recuperer le mode avec Config::getMode())

signals:

public slots:
};

#endif // LOCALSTATIONWIDGET_H
