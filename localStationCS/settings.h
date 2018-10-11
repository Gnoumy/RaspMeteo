#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QSettings>

#define FONT_FAMILY "font/family"
#define FONT_SIZE   "font/size"
#define FONT_COLOR  "font/color"

#define BACKGROUND_COLOR  "backgroundColor"

#define POSITION_LATITUDE   "position/latitude"
#define POSITION_LONGITUDE  "position/longitude"
#define POSITION_DISTANCE   "position/distance"
#define DEFAULT_POSITION_LATITUDE   48.8534f
#define DEFAULT_POSITION_LONGITUDE  2.3488f
#define DEFAULT_POSITION_DISTANCE   1.0f

namespace Ui {
    class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();
    QSettings qsettings ;

    void resetSettingsWidgets();

    // Getters/Setters-----------------------------------------------
    //          USELESS ???

    QString getFontStr() const;
    void setFontStr(const QString &value);

    int getFontSize() const;
    void setFontSize(int value);

    QString getFontColor() const;
    void setFontColor(const QString &value);

    QString getBgColor() const;
    void setBgColor(const QString &value);

    float getLatitude() const;
    void setLatitude(float value);

    float getLongitude() const;
    void setLongitude(float value);

    float getDistance() const;
    void setDistance(float value);

    // --------------------------------------------------------------

private slots:
    void changeConfig();
    void changeFontComboBox(const QString &value);
    void changeSpinBox(const int &value);
    void reject();

private:
    Ui::Settings *ui;
    QString fontStr ;
    int fontSize ;
    QString fontColor ;
    QString bgColor ;

    float   latitude,
            longitude,
            distance ;

    void updateLabel();
    void affectValuesToConfigStaticVars();
};

#endif // SETTINGS_H
