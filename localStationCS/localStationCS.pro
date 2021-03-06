#-------------------------------------------------
#
# Project created by QtCreator 2018-10-10T09:44:00
#
#-------------------------------------------------

QT       += core gui network sql quick positioning location quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = localStationCS
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    localstationwidget.cpp \
    settings.cpp \
    config.cpp \
    pollutionwidget.cpp \
    formtemperature.cpp \
    rechargevehiculewidget.cpp \
    widgetsatellite.cpp \
    widgetlocalisation.cpp \
    traficinfos.cpp \
    citieswidget.cpp \
    flightswidget.cpp \
    mapwindow.cpp \
    autoscrollinglabel.cpp

HEADERS += \
        mainwindow.h \
    localstationwidget.h \
    settings.h \
    config.h \
    pollutionwidget.h \
    formtemperature.h \
    rechargevehiculewidget.h \
    widgetsatellite.h \
    widgetlocalisation.h \
    traficinfos.h \
    citieswidget.h \
    flightswidget.h \
    mapwindow.h \
    autoscrollinglabel.h

FORMS += \
        mainwindow.ui \
    settings.ui \
    pollutionwidget.ui \
    formtemperature.ui \
    rechargevehiculewidget.ui \
    widgetsatellite.ui \
    widgetlocalisation.ui \
    traficinfos.ui \
    citieswidget.ui \
    flightswidget.ui \
    mapwindow.ui

RESOURCES += \
    qmlmap.qrc \
    ressources.qrc
