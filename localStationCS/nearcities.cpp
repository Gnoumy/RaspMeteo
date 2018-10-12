#include "nearcities.h"
#include "ui_nearcities.h"

NearCities::NearCities(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NearCities)
{
    ui->setupUi(this);
}

NearCities::~NearCities()
{
    delete ui;
}
