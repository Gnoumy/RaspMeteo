#include "config.h"

//Config::Config()
//{

//}

QString Config::fontColor("");
QString Config::getFontColor()
{
    return fontColor;
}
//void Config::setFontColor(const QString &value)
//{
//    fontColor = value;
//}

QString Config::bgColor("");
QString Config::getBgColor()
{
    return bgColor;
}
//void Config::setBgColor(const QString &value)
//{
//    bgColor = value;
//}

QString Config::fontFamily("");
QString Config::getFontFamily()
{
    return fontFamily;
}
//void Config::setFontFamily(const QString &value)
//{
//    Config::fontFamily = value;
//}

int Config::fontSize(0);
int Config::getFontSize()
{
    return fontSize;
}
//void Config::setFontSize(int value)
//{
//    Config::fontSize = value;
//}

float Config::latitude(0.0f) ;
float Config::getLatitude()
{
    return latitude;
}
//void Config::setLatitude(float value)
//{
//    latitude = value;
//}

float Config::longitude(0.0f) ;
float Config::getLongitude()
{
    return longitude;
}
//void Config::setLongitude(float value)
//{
//    longitude = value;
//}

float Config::distance(0.0f) ;
float Config::getDistance()
{
    return distance;
}
//void Config::setDistance(float value)
//{
//    distance = value;
//}

