#include "config.h"
#include <QSettings>

#define WIDGET_MODE             "widgetMode"
#define DEFAULT_WIDGET_MODE     0

#define SCROLLING_SPEED         "speed/scrolling"
#define DEFAULT_SCROLLING_SPEED 10

#define DEFAULT_FONT_FAMILY     "Cantarell"
#define DEFAULT_FONT_SIZE       11
#define DEFAULT_FONT_COLOR      "black"
#define DEFAULT_BG_COLOR        "white"

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

#define TABLE_FONT_FAMILY  "table/font/family"
#define TABLE_FONT_SIZE    "table/font/size"
#define TABLE_FONT_COLOR   "table/font/color"
#define TABLE_BG_COLOR     "table/backgroundColor"

#define POSITION_LATITUDE   "position/latitude"
#define POSITION_LONGITUDE  "position/longitude"
#define POSITION_DISTANCE   "position/distance"
#define DEFAULT_POSITION_LATITUDE   48.8534f
#define DEFAULT_POSITION_LONGITUDE  2.3488f
#define DEFAULT_POSITION_DISTANCE   1.0f

//Config::Config()
//{

//}

//int Config::widgetMode(0);
int Config::getWidgetMode()
{
    QSettings qsettings ;
    int widgetMode = qsettings.value(WIDGET_MODE).toInt() ;
    if(widgetMode==0)
        widgetMode = DEFAULT_WIDGET_MODE ;
    return widgetMode;
}
void Config::setWidgetMode(const int &value)
{
    if ( value != Config::getWidgetMode() )
    {
        QSettings qsettings ;
        qsettings.setValue(WIDGET_MODE, value);
//        emit widgetModeChanged(value);
    }
}

//int Config::scrollingSpeed(0);
int Config::getScrollingSpeed()
{
    QSettings qsettings ;
    int scrollingSpeed = qsettings.value(SCROLLING_SPEED).toInt() ;
    if(scrollingSpeed==0)
        scrollingSpeed = DEFAULT_SCROLLING_SPEED ;
    return scrollingSpeed;
}
void Config::setScrollingSpeed(const int &value)
{
    if ( value != Config::getScrollingSpeed() )
    {
        QSettings qsettings ;
        qsettings.setValue(SCROLLING_SPEED, value);
    }
}

//QString Config::fontColor("");
QString Config::getFontColor()
{
    QSettings qsettings ;
    QString fontColor = qsettings.value(FONT_COLOR).toString() ;
    if(fontColor=="")
        fontColor = DEFAULT_FONT_COLOR ;
    return fontColor;
}
void Config::setFontColor(const QString &value)
{
    if ( value != Config::getFontColor() )
    {
        QSettings qsettings ;
        qsettings.setValue(FONT_COLOR, value);
    }
}

//QString Config::bgColor("");
QString Config::getBgColor()
{
    QSettings qsettings ;
    QString bgColor = qsettings.value(BG_COLOR).toString() ;
    if(bgColor=="")
        bgColor = DEFAULT_BG_COLOR ;
    return bgColor;
}
void Config::setBgColor(const QString &value)
{
    if ( value != Config::getBgColor() )
    {
        QSettings qsettings ;
        qsettings.setValue(BG_COLOR, value);
    }
}

//QString Config::fontFamily("");
QString Config::getFontFamily()
{
    QSettings qsettings ;
    QString fontFamily = qsettings.value(FONT_FAMILY).toString() ;
    if(fontFamily=="")
        fontFamily = DEFAULT_FONT_FAMILY ;
    return fontFamily;
}
void Config::setFontFamily(const QString &value)
{
    if ( value != Config::getFontFamily() )
    {
        QSettings qsettings ;
        qsettings.setValue(FONT_FAMILY, value);
    }
}

//int Config::fontSize(0);
int Config::getFontSize()
{
    QSettings qsettings ;
    int fontSize = qsettings.value(FONT_SIZE).toInt() ;
    if(fontSize==0)
        fontSize = DEFAULT_FONT_SIZE ;
    return fontSize;
}
void Config::setFontSize(const int &value)
{
    if ( value != Config::getFontSize() )
    {
        QSettings qsettings ;
        qsettings.setValue(FONT_SIZE, value);
    }
}

//float Config::latitude(0.0f) ;
float Config::getLatitude()
{
    QSettings qsettings ;
    float latitude = qsettings.value(POSITION_LATITUDE).toFloat() ;
    if(latitude == 0.0f )
        latitude = DEFAULT_POSITION_LATITUDE ;
    return latitude;
}
void Config::setLatitude(const float &value)
{
    if ( value != Config::getLatitude() )
    {
        QSettings qsettings ;
        qsettings.setValue(POSITION_LATITUDE, value);
    }
}

//float Config::longitude(0.0f) ;
float Config::getLongitude()
{
    QSettings qsettings ;
    float longitude = qsettings.value(POSITION_LONGITUDE).toFloat() ;
    if(longitude == 0.0f )
        longitude = DEFAULT_POSITION_LONGITUDE ;
    return longitude;
}
void Config::setLongitude(const float &value)
{
    if ( value != Config::getLongitude() )
    {
        QSettings qsettings ;
        qsettings.setValue(POSITION_LONGITUDE, value);
    }
}

//float Config::distance(0.0f) ;
float Config::getDistance()
{
    QSettings qsettings ;
    float distance = qsettings.value(POSITION_DISTANCE).toFloat() ;
    if(distance == 0.0f )
        distance = DEFAULT_POSITION_DISTANCE ;
    return distance;
}
void Config::setDistance(const float &value)
{
    if ( value != Config::getDistance() )
    {
        QSettings qsettings ;
        qsettings.setValue(POSITION_DISTANCE, value);
    }
}

//QString Config::headerFontFamily("");
QString Config::getHeaderFontFamily()
{
    QSettings qsettings ;
    QString headerFontFamily = qsettings.value(HEADER_FONT_FAMILY).toString() ;
    if(headerFontFamily=="")
        headerFontFamily = DEFAULT_FONT_FAMILY ;
    return headerFontFamily;
}
void Config::setHeaderFontFamily(const QString &value)
{
    if ( value != Config::getHeaderFontFamily() )
    {
        QSettings qsettings ;
        qsettings.setValue(HEADER_FONT_FAMILY, value);
    }
}

//QString Config::headerFontColor("");
QString Config::getHeaderFontColor()
{
    QSettings qsettings ;
    QString headerFontColor = qsettings.value(HEADER_FONT_COLOR).toString() ;
    if(headerFontColor=="")
        headerFontColor = DEFAULT_FONT_COLOR ;
    return headerFontColor;
}
void Config::setHeaderFontColor(const QString &value)
{
    if ( value != Config::getHeaderFontColor() )
    {
        QSettings qsettings ;
        qsettings.setValue(HEADER_FONT_COLOR, value);
    }
}

//QString Config::headerBgColor("");
QString Config::getHeaderBgColor()
{
    QSettings qsettings ;
    QString headerBgColor = qsettings.value(HEADER_BG_COLOR).toString() ;
    if(headerBgColor=="")
        headerBgColor = DEFAULT_BG_COLOR ;
    return headerBgColor;
}
void Config::setHeaderBgColor(const QString &value)
{
    if ( value != Config::getHeaderBgColor() )
    {
        QSettings qsettings ;
        qsettings.setValue(HEADER_BG_COLOR, value);
    }
}

//QString Config::footerFontFamily("");
QString Config::getFooterFontFamily()
{
    QSettings qsettings ;
    QString footerFontFamily = qsettings.value(FOOTER_FONT_FAMILY).toString() ;
    if(footerFontFamily=="")
        footerFontFamily = DEFAULT_FONT_FAMILY ;
    return footerFontFamily;
}
void Config::setFooterFontFamily(const QString &value)
{
    if ( value != Config::getFooterFontFamily() )
    {
        QSettings qsettings ;
        qsettings.setValue(FOOTER_FONT_FAMILY, value);
    }
}

//QString Config::footerFontColor("");
QString Config::getFooterFontColor()
{
    QSettings qsettings ;
    QString footerFontColor = qsettings.value(FOOTER_FONT_COLOR).toString() ;
    if(footerFontColor=="")
        footerFontColor = DEFAULT_FONT_COLOR ;
    return footerFontColor;
}
void Config::setFooterFontColor(const QString &value)
{
    if ( value != Config::getFooterFontColor() )
    {
        QSettings qsettings ;
        qsettings.setValue(FOOTER_FONT_COLOR, value);
    }
}

//QString Config::footerBgColor("");
QString Config::getFooterBgColor()
{
    QSettings qsettings ;
    QString footerBgColor = qsettings.value(FOOTER_BG_COLOR).toString() ;
    if(footerBgColor=="")
        footerBgColor = DEFAULT_BG_COLOR ;
    return footerBgColor;
}
void Config::setFooterBgColor(const QString &value)
{
    if ( value != Config::getFooterBgColor() )
    {
        QSettings qsettings ;
        qsettings.setValue(FOOTER_BG_COLOR, value);
    }
}

//int Config::headerFontSize(0);
int Config::getHeaderFontSize()
{
    QSettings qsettings ;
    int headerFontSize = qsettings.value(HEADER_FONT_SIZE).toInt() ;
    if(headerFontSize==0)
        headerFontSize = DEFAULT_FONT_SIZE ;
    return headerFontSize;
}
void Config::setHeaderFontSize(const int &value)
{
    if ( value != Config::getHeaderFontSize() )
    {
        QSettings qsettings ;
        qsettings.setValue(HEADER_FONT_SIZE, value);
    }
}

//int Config::footerFontSize(0);
int Config::getFooterFontSize()
{
    QSettings qsettings ;
    int footerFontSize = qsettings.value(FOOTER_FONT_SIZE).toInt() ;
    if(footerFontSize==0)
        footerFontSize = DEFAULT_FONT_SIZE ;
    return footerFontSize;
}
void Config::setFooterFontSize(const int &value)
{
    if ( value != Config::getFooterFontSize() )
    {
        QSettings qsettings ;
        qsettings.setValue(FOOTER_FONT_SIZE, value);
    }
}

//QString Config::tableFontFamily("");
QString Config::getTableFontFamily()
{
    QSettings qsettings ;
    QString tableFontFamily = qsettings.value(TABLE_FONT_FAMILY).toString() ;
    if(tableFontFamily=="")
        tableFontFamily = DEFAULT_FONT_FAMILY ;
    return tableFontFamily;
}
void Config::setTableFontFamily(const QString &value)
{
    if ( value != Config::getTableFontFamily() )
    {
        QSettings qsettings ;
        qsettings.setValue(TABLE_FONT_FAMILY, value);
    }
}

//QString Config::tableFontColor("");
QString Config::getTableFontColor()
{
    QSettings qsettings ;
    QString tableFontColor = qsettings.value(TABLE_FONT_COLOR).toString() ;
    if(tableFontColor=="")
        tableFontColor = DEFAULT_FONT_COLOR ;
    return tableFontColor;
}
void Config::setTableFontColor(const QString &value)
{
    if ( value != Config::getTableFontColor() )
    {
        QSettings qsettings ;
        qsettings.setValue(TABLE_FONT_COLOR, value);
    }
}

//QString Config::tableBgColor("");
QString Config::getTableBgColor()
{
    QSettings qsettings ;
    QString tableBgColor = qsettings.value(TABLE_BG_COLOR).toString() ;
    if(tableBgColor=="")
        tableBgColor = DEFAULT_BG_COLOR ;
    return tableBgColor;
}
void Config::setTableBgColor(const QString &value)
{
    if ( value != Config::getTableBgColor() )
    {
        QSettings qsettings ;
        qsettings.setValue(TABLE_BG_COLOR, value);
    }
}

//int Config::tableFontSize(0);
int Config::getTableFontSize()
{
    QSettings qsettings ;
    int tableFontSize = qsettings.value(TABLE_FONT_SIZE).toInt() ;
    if(tableFontSize==0)
        tableFontSize = DEFAULT_FONT_SIZE ;
    return tableFontSize;
}
void Config::setTableFontSize(const int &value)
{
    if ( value != Config::getTableFontSize() )
    {
        QSettings qsettings ;
        qsettings.setValue(TABLE_FONT_SIZE, value);
    }
}

////QString Config::other_1("");
//QString Config::getOther_1()
//{
//    return other_1;
//}
//void Config::setOther_1(const QString &value)
//{
//    other_1 = value;
//}

////QString Config::other_2("");
//QString Config::getOther_2()
//{
//    return other_2;
//}
//void Config::setOther_2(const QString &value)
//{
//    other_2 = value;
//}

////int Config::other_3(0);
//int Config::getOther_3()
//{
//    return other_3;
//}
//void Config::setOther_3(const int &value)
//{
//    other_3 = value;
//}

////float Config::other_4(0.0f) ;
//float Config::getOther_4()
//{
//    return other_4;
//}
//void Config::setOther_4(const float &value)
//{
//    other_4 = value;
//}
