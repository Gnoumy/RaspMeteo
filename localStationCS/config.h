#ifndef CONFIG_H
#define CONFIG_H

#include <QString>



class Config
{
public:
//    Config();
    static QString  fontFamily,
                    fontColor,
                    bgColor ;
    static int     fontSize ;
    static float    latitude,
                    longitude,
                    distance ;


//private:
    static QString getFontFamily();
    //    static void setFontFamily(const QString &value);

    static QString getFontColor();
    //    static void setFontColor(const QString &value);

    static int getFontSize();
    //    static void setFontSize(int value);

    static QString getBgColor();
    //    static void setBgColor(const QString &value);

    static float getLatitude();
//    static void setLatitude(float value);

    static float getLongitude();
//    static void setLongitude(float value);

    static float getDistance();
//    static void setDistance(float value);
};

#endif // CONFIG_H
