#ifndef NEARCITIES_H
#define NEARCITIES_H

#include <QWidget>

namespace Ui {
class NearCities;
}

class NearCities : public QWidget
{
    Q_OBJECT

public:
    explicit NearCities(QWidget *parent = 0);
    ~NearCities();

private:
    Ui::NearCities *ui;
};

#endif // NEARCITIES_H
