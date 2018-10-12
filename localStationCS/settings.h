#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QSettings>

#define FONT_FAMILY "body/font/family"
#define FONT_SIZE   "body/font/size"
#define FONT_COLOR  "body/font/color"
#define BG_COLOR    "body/backgroundColor"

#define HEADER_FONT_FAMILY  "header/font/family"
#define HEADER_FONT_SIZE    "header/font/size"
#define HEADER_FONT_COLOR   "header/font/color"
#define HEADER_BG_COLOR     "header/backgroundColor"

#define FOOTER_FONT_FAMILY  "footer/font/family"
#define FOOTER_FONT_SIZE    "footer/font/size"
#define FOOTER_FONT_COLOR   "footer/font/color"
#define FOOTER_BG_COLOR     "footer/backgroundColor"

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

    QString getHeaderFontFamily() const;
    void setHeaderFontFamily(const QString &value);

    QString getHeaderFontColor() const;
    void setHeaderFontColor(const QString &value);

    QString getHeaderBgColor() const;
    void setHeaderBgColor(const QString &value);

    QString getFooterFontFamily() const;
    void setFooterFontFamily(const QString &value);

    QString getFooterFontColor() const;
    void setFooterFontColor(const QString &value);

    QString getFooterBgColor() const;
    void setFooterBgColor(const QString &value);

    int getHeaderFontSize() const;
    void setHeaderFontSize(int value);

    int getFooterFontSize() const;
    void setFooterFontSize(int value);

    // --------------------------------------------------------------

private slots:
    void changeConfig();
    void changeFontComboBox(const QString &value);
    void changeSpinBox(const int &value);
    void reject();

private:
    Ui::Settings *ui;
    QString fontStr,
            fontColor,
            bgColor,
            headerFontFamily,
            headerFontColor,
            headerBgColor ,
            footerFontFamily,
            footerFontColor,
            footerBgColor ;
    int     fontSize,
            headerFontSize,
            footerFontSize ;
    float   latitude,
            longitude,
            distance ;

    void updateLabel();
    void updateHeaderLabel();
    void updateFooterLabel();
    void affectValuesToConfigStaticVars();
    void initAllColorComboBoxes();
};

#endif // SETTINGS_H
