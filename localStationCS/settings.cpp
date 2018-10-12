#include "settings.h"
#include "ui_settings.h"

#include "config.h"
#include <QDirIterator>
#include <QMessageBox>

#define RESSOURCE_FONTS_FOLDER  ":/fonts"


#include <QDebug>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{QFontDatabase::addApplicationFont(":/fonts/LLDOT2.TTF");
    // init widgets of the .ui
    ui->setupUi(this);
    this->initAllColorComboBoxes() ;
    this->ui->comboBox->addItem("LLDot");



    QStringList familyList ;
    familyList.reserve(QDir(RESSOURCE_FONTS_FOLDER).count());
//    qDebug()<<QDir(RESSOURCE_FONTS_FOLDER).count()<<"qqqq";
    QDirIterator it(RESSOURCE_FONTS_FOLDER, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        // tester sur fichiers hidden ?????
//        qDebug() << "------------------------";
//        qDebug() << it.fileName();
        int id = QFontDatabase::addApplicationFont(it.next());
        familyList.append(QFontDatabase::applicationFontFamilies(id));
    }

    this->ui->fontComboBox->clear();
    this->ui->fontComboBox->addItems(familyList);
    this->ui->headerFontComboBox->clear();
    this->ui->headerFontComboBox->addItems(familyList);
    this->ui->footerFontComboBox->clear();
    this->ui->footerFontComboBox->addItems(familyList);



    // "OrganizationDomain" and "ApplicationName" related to qsettings are set in main.cpp
    this->qsettings.setParent(this);
    this->affectValuesToConfigStaticVars();


    QApplication::setFont(QFont(Config::fontFamily, Config::fontSize));


    // all the connects --------------------------------------------------------------------------------------------------------

    connect(this->ui->applyPushButton, SIGNAL(released()), this, SLOT(changeConfig())) ;

    // Body, then Header, then Footer

        // Equivalent. One with a private slot, and one with a lambda expression
        //connect(this->ui->fontComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(changeFontComboBox(QString))) ;
    connect(this->ui->fontComboBox, &QFontComboBox::currentTextChanged, this,
        [this](const QString &value)
        {
            this->fontStr = value ;
            this->updateLabel();
        }) ;


        // Equivalent. One with a private slot, and one with a lambda expression
        //connect(this->ui->fontSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeSpinBox(int))) ;
    connect(this->ui->fontSpinBox, qOverload<int>(&QSpinBox::valueChanged), this,
        [this](const int &value)
        {
            this->fontSize = value ;
            this->updateLabel();
        }) ;
            // qOverload<int>(...) is ugly but needed because there are 2 "valueChanged" SpinBox signals


        // Equivalent. One with a private slot, and one with a lambda expression
        //connect(this->ui->fontColorComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(changeFontComboBox(QString))) ;
    connect(this->ui->fontColorComboBox, &QComboBox::currentTextChanged, this,
        [this](const QString &value)
        {
            this->fontColor = value ;
            this->updateLabel();
        }) ;


        // Equivalent. One with a private slot, and one with a lambda expression
        //connect(this->ui->bgColorComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(changeFontComboBox(QString))) ;
    connect(this->ui->bgColorComboBox, &QComboBox::currentTextChanged, this,
        [this](const QString &value)
        {
            this->bgColor = value ;
            this->updateLabel();
        }) ;





        // Equivalent. One with a private slot, and one with a lambda expression
        //connect(this->ui->headerFontComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(changeHeaderFontComboBox(QString))) ;
    connect(this->ui->headerFontComboBox, &QFontComboBox::currentTextChanged, this,
        [this](const QString &value)
        {
            this->headerFontFamily = value ;
            this->updateHeaderLabel();
        }) ;


        // Equivalent. One with a private slot, and one with a lambda expression
        //connect(this->ui->headerFontSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeHeaderFontSpinBox(int))) ;
    connect(this->ui->headerFontSpinBox, qOverload<int>(&QSpinBox::valueChanged), this,
        [this](const int &value)
        {
            this->headerFontSize = value ;
            this->updateHeaderLabel();
        }) ;
            // qOverload<int>(...) is ugly but needed because there are 2 "valueChanged" SpinBox signals


        // Equivalent. One with a private slot, and one with a lambda expression
        //connect(this->ui->headerFontColorComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(changeHeaderFontColorComboBox(QString))) ;
    connect(this->ui->headerFontColorComboBox, &QComboBox::currentTextChanged, this,
        [this](const QString &value)
        {
            this->headerFontColor = value ;
            this->updateHeaderLabel();
        }) ;


        // Equivalent. One with a private slot, and one with a lambda expression
        //connect(this->ui->headerBgColorComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(changeHeaderBgColorComboBox(QString))) ;
    connect(this->ui->headerBgColorComboBox, &QComboBox::currentTextChanged, this,
        [this](const QString &value)
        {
            this->headerBgColor = value ;
            this->updateHeaderLabel();
        }) ;





    // Equivalent. One with a private slot, and one with a lambda expression
    //connect(this->ui->footerFontComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(changeFooterFontComboBox(QString))) ;
    connect(this->ui->footerFontComboBox, &QFontComboBox::currentTextChanged, this,
    [this](const QString &value)
    {
        this->footerFontFamily = value ;
        this->updateFooterLabel();
    }) ;


    // Equivalent. One with a private slot, and one with a lambda expression
    //connect(this->ui->footerFontSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeFooterFontSpinBox(int))) ;
    connect(this->ui->footerFontSpinBox, qOverload<int>(&QSpinBox::valueChanged), this,
    [this](const int &value)
    {
        this->footerFontSize = value ;
        this->updateFooterLabel();
    }) ;
        // qOverload<int>(...) is ugly but needed because there are 2 "valueChanged" SpinBox signals


    // Equivalent. One with a private slot, and one with a lambda expression
    //connect(this->ui->footerFontColorComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(changeFooterFontColorComboBox(QString))) ;
    connect(this->ui->footerFontColorComboBox, &QComboBox::currentTextChanged, this,
    [this](const QString &value)
    {
        this->footerFontColor = value ;
        this->updateFooterLabel();
    }) ;


    // Equivalent. One with a private slot, and one with a lambda expression
    //connect(this->ui->footerBgColorComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(changeFooterBgColorComboBox(QString))) ;
    connect(this->ui->footerBgColorComboBox, &QComboBox::currentTextChanged, this,
    [this](const QString &value)
    {
        this->footerBgColor = value ;
        this->updateFooterLabel();
    }) ;





    // -------------------------------------------------------------------------------------------------------------------------

}



void Settings::affectValuesToConfigStaticVars()
{
    // only used in Constructor
    // affecting values / default values

    // Body ------------------------------------------------------------

    Config::fontFamily = this->qsettings.value(FONT_FAMILY).toString() ;
    if(Config::fontFamily=="")
        Config::fontFamily = this->ui->fontLabel->font().family() ;

    Config::fontSize = this->qsettings.value(FONT_SIZE).toInt() ;
    if(Config::fontSize==0)
        Config::fontSize = this->ui->fontLabel->font().pointSize() ;

    Config::fontColor = this->qsettings.value(FONT_COLOR).toString() ;
    Config::bgColor = this->qsettings.value(BG_COLOR).toString() ;

    // Header ------------------------------------------------------------

    Config::headerFontFamily = this->qsettings.value(HEADER_FONT_FAMILY).toString() ;
    if(Config::headerFontFamily=="")
        Config::headerFontFamily = this->ui->headerFontLabel->font().family() ;

    Config::headerFontSize = this->qsettings.value(HEADER_FONT_SIZE).toInt() ;
    if(Config::headerFontSize==0)
        Config::headerFontSize = this->ui->headerFontLabel->font().pointSize() ;

    Config::headerFontColor = this->qsettings.value(HEADER_FONT_COLOR).toString() ;
    Config::headerBgColor = this->qsettings.value(HEADER_BG_COLOR).toString() ;

    // Footer ------------------------------------------------------------

    Config::footerFontFamily = this->qsettings.value(FOOTER_FONT_FAMILY).toString() ;
    if(Config::footerFontFamily=="")
        Config::footerFontFamily = this->ui->footerFontLabel->font().family() ;

    Config::footerFontSize = this->qsettings.value(FOOTER_FONT_SIZE).toInt() ;
    if(Config::footerFontSize==0)
        Config::footerFontSize = this->ui->footerFontLabel->font().pointSize() ;

    Config::footerFontColor = this->qsettings.value(FOOTER_FONT_COLOR).toString() ;
    Config::footerBgColor = this->qsettings.value(FOOTER_BG_COLOR).toString() ;

    // Position ------------------------------------------------------------

    Config::latitude = this->qsettings.value(POSITION_LATITUDE).toFloat() ;
    if(Config::latitude == 0.0f )
        Config::latitude = DEFAULT_POSITION_LATITUDE ;

    Config::longitude = this->qsettings.value(POSITION_LONGITUDE).toFloat() ;
    if(Config::longitude == 0.0f )
        Config::longitude = DEFAULT_POSITION_LONGITUDE ;

    Config::distance = this->qsettings.value(POSITION_DISTANCE).toFloat() ;
    if(Config::distance == 0.0f )
        Config::distance = DEFAULT_POSITION_DISTANCE ;


}

void Settings::changeConfig()
{
//    this->setFont(settings->value("font").value<QFont>());
//    qDebug() << this->ui->fontComboBox->currentText() ;

    // Body ------------------------------------------------------------

    Config::fontFamily = this->ui->fontComboBox->currentText();
    this->qsettings.setValue(FONT_FAMILY, Config::fontFamily);

    Config::fontSize = this->ui->fontSpinBox->value();
    this->qsettings.setValue(FONT_SIZE, Config::fontSize);

    Config::fontColor = this->ui->fontColorComboBox->currentText();
    this->qsettings.setValue(FONT_COLOR, Config::fontColor);

    Config::bgColor = this->ui->bgColorComboBox->currentText();
    this->qsettings.setValue(BG_COLOR, Config::bgColor);

    // Header ------------------------------------------------------------

    Config::headerFontFamily = this->ui->headerFontComboBox->currentText();
    this->qsettings.setValue(HEADER_FONT_FAMILY, Config::headerFontFamily);

    Config::headerFontSize = this->ui->headerFontSpinBox->value();
    this->qsettings.setValue(HEADER_FONT_SIZE, Config::headerFontSize);

    Config::headerFontColor = this->ui->headerFontColorComboBox->currentText();
    this->qsettings.setValue(HEADER_FONT_COLOR, Config::headerFontColor);

    Config::headerBgColor = this->ui->headerBgColorComboBox->currentText();
    this->qsettings.setValue(HEADER_BG_COLOR, Config::headerBgColor);

    // Footer ------------------------------------------------------------

    Config::footerFontFamily = this->ui->footerFontComboBox->currentText();
    this->qsettings.setValue(FOOTER_FONT_FAMILY, Config::footerFontFamily);

    Config::footerFontSize = this->ui->footerFontSpinBox->value();
    this->qsettings.setValue(FOOTER_FONT_SIZE, Config::footerFontSize);

    Config::footerFontColor = this->ui->footerFontColorComboBox->currentText();
    this->qsettings.setValue(FOOTER_FONT_COLOR, Config::footerFontColor);

    Config::footerBgColor = this->ui->footerBgColorComboBox->currentText();
    this->qsettings.setValue(FOOTER_BG_COLOR, Config::footerBgColor);

    // Position ------------------------------------------------------------

    Config::latitude = this->ui->latDoubleSpinBox->value();
    this->qsettings.setValue(POSITION_LATITUDE, Config::latitude);

    Config::longitude = this->ui->lonDoubleSpinBox->value();
    this->qsettings.setValue(POSITION_LONGITUDE, Config::longitude);

    Config::distance = this->ui->distDoubleSpinBox->value();
    this->qsettings.setValue(POSITION_DISTANCE, Config::distance);

    // Apply to the whole project
    QApplication::setFont(QFont(this->ui->fontComboBox->currentText(),this->ui->fontSpinBox->value()));
    this->hide();
}

void Settings::changeFontComboBox(const QString &value)
{
    this->fontStr = value ;
    this->updateLabel();
}

void Settings::changeSpinBox(const int &value)
{
    this->fontSize = value ;
    this->updateLabel();
}

void Settings::updateLabel()
{
    this->ui->fontComboBox->setCurrentText(this->fontStr);
    this->ui->fontSpinBox->setValue(this->fontSize);
    this->ui->fontLabel->setFont(QFont(this->fontStr, this->fontSize));

    this->ui->fontColorComboBox->setCurrentText(this->fontColor);
    this->ui->bgColorComboBox->setCurrentText(this->bgColor);
    this->ui->fontLabel->setStyleSheet(QString("QLabel { color : %1; background-color : %2; })").arg(this->fontColor).arg(this->bgColor)) ;

}

void Settings::updateHeaderLabel()
{
    this->ui->headerFontComboBox->setCurrentText(this->headerFontFamily);
    this->ui->headerFontSpinBox->setValue(this->headerFontSize);
    this->ui->headerFontLabel->setFont(QFont(this->headerFontFamily, this->headerFontSize));

    this->ui->headerFontColorComboBox->setCurrentText(this->headerFontColor);
    this->ui->headerBgColorComboBox->setCurrentText(this->headerBgColor);
    this->ui->headerFontLabel->setStyleSheet(QString("QLabel { color : %1; background-color : %2; })").arg(this->headerFontColor).arg(this->headerBgColor)) ;

}

void Settings::updateFooterLabel()
{
    this->ui->footerFontComboBox->setCurrentText(this->footerFontFamily);
    this->ui->footerFontSpinBox->setValue(this->footerFontSize);
    this->ui->footerFontLabel->setFont(QFont(this->footerFontFamily, this->footerFontSize));

    this->ui->footerFontColorComboBox->setCurrentText(this->footerFontColor);
    this->ui->footerBgColorComboBox->setCurrentText(this->footerBgColor);
    this->ui->footerFontLabel->setStyleSheet(QString("QLabel { color : %1; background-color : %2; })").arg(this->footerFontColor).arg(this->footerBgColor)) ;

}

void Settings::resetSettingsWidgets()
{
    // every Settings member gets the value of the corresponding static variable

    // Body ------------------------------------------------------------

    this->fontStr = Config::fontFamily ;
    this->fontSize = Config::fontSize ;
    this->fontColor = Config::fontColor ;
    this->bgColor = Config::bgColor ;

    this->updateLabel();

    // Header ------------------------------------------------------------

    this->headerFontFamily = Config::headerFontFamily ;
    this->headerFontSize = Config::headerFontSize ;
    this->headerFontColor = Config::headerFontColor ;
    this->headerBgColor = Config::headerBgColor ;

    this->updateHeaderLabel();

    // Footer ------------------------------------------------------------

    this->footerFontFamily = Config::footerFontFamily ;
    this->footerFontSize = Config::footerFontSize ;
    this->footerFontColor = Config::footerFontColor ;
    this->footerBgColor = Config::footerBgColor ;

    this->updateFooterLabel();

    // Position ------------------------------------------------------------

    this->latitude = Config::latitude ;
    this->ui->latDoubleSpinBox->setValue(this->latitude);

    this->longitude = Config::longitude ;
    this->ui->lonDoubleSpinBox->setValue(this->longitude);

    this->distance = Config::distance ;
    this->ui->distDoubleSpinBox->setValue(this->distance);

}

void Settings::initAllColorComboBoxes()
{
    // it's the color names
    QStringList colors(QColor::colorNames()) ;

    this->ui->fontColorComboBox->addItems(colors);
    this->ui->bgColorComboBox->addItems(colors);
    this->ui->headerFontColorComboBox->addItems(colors);
    this->ui->headerBgColorComboBox->addItems(colors);
    this->ui->footerFontColorComboBox->addItems(colors);
    this->ui->footerBgColorComboBox->addItems(colors);

}

// ameliorer ???
// override reject() virtual method (closing dialog event)
void Settings::reject()
{
    QMessageBox::StandardButton resBtn = QMessageBox::Yes;
    if (1) {
        resBtn = QMessageBox::question( this, "APP_NAME",
                                        tr("Are you sure?\n"),
                                        QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                        QMessageBox::Yes);
    }
    if (resBtn == QMessageBox::Yes) {
        QDialog::reject();
    }
}

// Rest of the code : Destructor, Getters and Setters -----------------------------------------------------------------------

Settings::~Settings()
{
    delete ui;
}

int Settings::getFontSize() const
{
    return fontSize;
}

void Settings::setFontSize(int value)
{
    fontSize = value;
}

QString Settings::getFontStr() const
{
    return fontStr;
}

void Settings::setFontStr(const QString &value)
{
    fontStr = value;
}

QString Settings::getBgColor() const
{
    return bgColor;
}

void Settings::setBgColor(const QString &value)
{
    bgColor = value;
}

QString Settings::getFontColor() const
{
    return fontColor;
}

void Settings::setFontColor(const QString &value)
{
    fontColor = value;
}

float Settings::getDistance() const
{
    return distance;
}

void Settings::setDistance(float value)
{
    distance = value;
}

float Settings::getLongitude() const
{
    return longitude;
}

void Settings::setLongitude(float value)
{
    longitude = value;
}

float Settings::getLatitude() const
{
    return latitude;
}

void Settings::setLatitude(float value)
{
    latitude = value;
}

int Settings::getFooterFontSize() const
{
    return footerFontSize;
}

void Settings::setFooterFontSize(int value)
{
    footerFontSize = value;
}

int Settings::getHeaderFontSize() const
{
    return headerFontSize;
}

void Settings::setHeaderFontSize(int value)
{
    headerFontSize = value;
}

QString Settings::getFooterBgColor() const
{
    return footerBgColor;
}

void Settings::setFooterBgColor(const QString &value)
{
    footerBgColor = value;
}

QString Settings::getFooterFontColor() const
{
    return footerFontColor;
}

void Settings::setFooterFontColor(const QString &value)
{
    footerFontColor = value;
}

QString Settings::getFooterFontFamily() const
{
    return footerFontFamily;
}

void Settings::setFooterFontFamily(const QString &value)
{
    footerFontFamily = value;
}

QString Settings::getHeaderBgColor() const
{
    return headerBgColor;
}

void Settings::setHeaderBgColor(const QString &value)
{
    headerBgColor = value;
}

QString Settings::getHeaderFontColor() const
{
    return headerFontColor;
}

void Settings::setHeaderFontColor(const QString &value)
{
    headerFontColor = value;
}

QString Settings::getHeaderFontFamily() const
{
    return headerFontFamily;
}

void Settings::setHeaderFontFamily(const QString &value)
{
    headerFontFamily = value;
}
