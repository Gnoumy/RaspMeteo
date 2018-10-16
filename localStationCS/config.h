#ifndef CONFIG_H
#define CONFIG_H

#include <QString>



class Config
{
public:
//    Config();
//    static QString  fontFamily,
//                    fontColor,
//                    bgColor,
//                    headerFontFamily,
//                    headerFontColor,
//                    headerBgColor ,
//                    footerFontFamily,
//                    footerFontColor,
//                    footerBgColor,
//                    // Suppr en fin de projet ??? Oui
//                    // otherN : another QFontComboBox, QComboBox, QSpinBox, QDoubleSpinBox
//                    // To replace :
//                        // copy all other1 to other9
//                        // replace all (other9, ...)
//                    // To modify getter/setter : replace (etOther9, ...)
//                    other1,
//                    other2 ;
//    static int      fontSize,
//                    headerFontSize,
//                    footerFontSize,
//                    other3 ;
//    static float    latitude,
//                    longitude,
//                    distance,
//                    other4 ;


//private:

// Rest of the methods : Getters/Setters    ---------------------------------------

    static int getWidgetMode();
    static void setWidgetMode(const int &value);

    static int getScrollingSpeed();
    static void setScrollingSpeed(const int &value);

    static QString getFontFamily();
        static void setFontFamily(const QString &value);

    static QString getFontColor();
        static void setFontColor(const QString &value);

    static int getFontSize();
        static void setFontSize(const int &value);

    static QString getBgColor();
        static void setBgColor(const QString &value);

    static float getLatitude();
    static void setLatitude(const float &value);

    static float getLongitude();
    static void setLongitude(const float &value);

    static float getDistance();
    static void setDistance(const float &value);

    static QString getHeaderFontFamily();
    static void setHeaderFontFamily(const QString &value);

    static QString getHeaderFontColor();
    static void setHeaderFontColor(const QString &value);

    static QString getHeaderBgColor();
    static void setHeaderBgColor(const QString &value);

    static QString getFooterFontFamily();
    static void setFooterFontFamily(const QString &value);

    static QString getFooterFontColor();
    static void setFooterFontColor(const QString &value);

    static QString getFooterBgColor();
    static void setFooterBgColor(const QString &value);

    static int getHeaderFontSize();
    static void setHeaderFontSize(const int &value);

    static int getFooterFontSize();
    static void setFooterFontSize(const int &value);

    static QString getTableFontFamily();
    static void setTableFontFamily(const QString &value);

    static QString getTableFontColor();
    static void setTableFontColor(const QString &value);

    static QString getTableBgColor();
    static void setTableBgColor(const QString &value);

    static int getTableFontSize();
    static void setTableFontSize(const int &value);

//    static QString getOther_1();
//    static void setOther_1(const QString &value);

//    static QString getOther_2();
//    static void setOther_2(const QString &value);

//    static int getOther_3();
//    static void setOther_3(const int &value);

//    static float getOther_4();
//    static void setOther_4(const float &value);
};

#endif // CONFIG_H
