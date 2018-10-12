#ifndef CONFIG_H
#define CONFIG_H

#include <QString>



class Config
{
public:
//    Config();
    static QString  fontFamily,
                    fontColor,
                    bgColor,
                    headerFontFamily,
                    headerFontColor,
                    headerBgColor ,
                    footerFontFamily,
                    footerFontColor,
                    footerBgColor ;
    static int      fontSize,
                    headerFontSize,
                    footerFontSize ;
    static float    latitude,
                    longitude,
                    distance ;


//private:

// Rest of the methods : Getters/Setters    ---------------------------------------

    static QString getFontFamily();
//        static void setFontFamily(const QString &value);

    static QString getFontColor();
//        static void setFontColor(const QString &value);

    static int getFontSize();
//        static void setFontSize(int value);

    static QString getBgColor();
//        static void setBgColor(const QString &value);

    static float getLatitude();
//    static void setLatitude(float value);

    static float getLongitude();
//    static void setLongitude(float value);

    static float getDistance();
//    static void setDistance(float value);

    static QString getHeaderFontFamily();
//    static void setHeaderFontFamily(const QString &value);

    static QString getHeaderFontColor();
//    static void setHeaderFontColor(const QString &value);

    static QString getHeaderBgColor();
//    static void setHeaderBgColor(const QString &value);

    static QString getFooterFontFamily();
//    static void setFooterFontFamily(const QString &value);

    static QString getFooterFontColor();
//    static void setFooterFontColor(const QString &value);

    static QString getFooterBgColor();
//    static void setFooterBgColor(const QString &value);

    static int getHeaderFontSize();
//    static void setHeaderFontSize(int value);

    static int getFooterFontSize();
//    static void setFooterFontSize(int value);
};

#endif // CONFIG_H
