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

    static int      getWidgetMode();
    static int      getScrollingSpeed();

    static float    getLatitude();
    static float    getLongitude();
    static float    getDistance();

    static QString  getFontFamily();
    static QString  getFontColor();
    static QString  getBgColor();
    static int      getFontSize();

    static QString  getHeaderFontFamily();
    static QString  getHeaderFontColor();
    static QString  getHeaderBgColor();
    static int      getHeaderFontSize();

    static QString  getFooterFontFamily();
    static QString  getFooterFontColor();
    static QString  getFooterBgColor();
    static int      getFooterFontSize();

    static QString  getTableFontFamily();
    static QString  getTableFontColor();
    static QString  getTableBgColor();
    static int      getTableFontSize();

friend class Settings ;
protected:

    static void setWidgetMode       (const int &value);
    static void setScrollingSpeed   (const int &value);

    static void setLatitude         (const float &value);
    static void setLongitude        (const float &value);
    static void setDistance         (const float &value);

    static void setFontFamily       (const QString &value);
    static void setFontColor        (const QString &value);
    static void setBgColor          (const QString &value);
    static void setFontSize         (const int &value);

    static void setHeaderFontFamily (const QString &value);
    static void setHeaderFontColor  (const QString &value);
    static void setHeaderBgColor    (const QString &value);
    static void setHeaderFontSize   (const int &value);

    static void setFooterFontFamily (const QString &value);
    static void setFooterFontColor  (const QString &value);
    static void setFooterBgColor    (const QString &value);
    static void setFooterFontSize   (const int &value);

    static void setTableFontFamily  (const QString &value);
    static void setTableFontColor   (const QString &value);
    static void setTableBgColor     (const QString &value);
    static void setTableFontSize    (const int &value);
};

#endif // CONFIG_H
