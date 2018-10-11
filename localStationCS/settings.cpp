#include "settings.h"
#include "ui_settings.h"

#include "config.h"
#include <QDebug>
#include <QMessageBox>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->ui->fontColorComboBox->addItems(QColor::colorNames());
    this->ui->bgColorComboBox->addItems(QColor::colorNames());

    // "OrganizationDomain" and "ApplicationName" related to qsettings are set in main.cpp
    this->qsettings.setParent(this);
    this->affectValuesToConfigStaticVars();


    QApplication::setFont(QFont(this->fontStr, this->fontSize));



    connect(this->ui->applyPushButton, SIGNAL(released()), this, SLOT(changeConfig())) ;

    // Equivalent. One with a private slot, and one with a lambda expression
  //connect(this->ui->fontComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(changeFontComboBox(QString))) ;
    connect(this->ui->fontComboBox, &QFontComboBox::currentTextChanged,
            [this](const QString &value){
        this->fontStr = value ;
        this->updateLabel();}) ;


    // Equivalent. One with a private slot, and one with a lambda expression
  //connect(this->ui->fontSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeSpinBox(int))) ;
    connect(this->ui->fontSpinBox, qOverload<int>(&QSpinBox::valueChanged),
            [this](const int &value){
        this->fontSize = value ;
        this->updateLabel();}) ;
    // qOverload<int>(...) is ugly but needed because there are 2 "valueChanged" SpinBox signals



    // Equivalent. One with a private slot, and one with a lambda expression
  //connect(this->ui->fontColorComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(changeFontComboBox(QString))) ;
    connect(this->ui->fontColorComboBox, &QComboBox::currentTextChanged,
            [this](const QString &value){
        this->fontColor = value ;
        this->updateLabel();}) ;

    // Equivalent. One with a private slot, and one with a lambda expression
  //connect(this->ui->bgColorComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(changeFontComboBox(QString))) ;
    connect(this->ui->bgColorComboBox, &QComboBox::currentTextChanged,
            [this](const QString &value){
        this->bgColor = value ;
        this->updateLabel();}) ;

}



void Settings::affectValuesToConfigStaticVars()
{
    // only used in Constructor
    // affecting values / default values

    Config::fontFamily = this->qsettings.value(FONT_FAMILY).toString() ;
    if(Config::fontFamily=="")
        Config::fontFamily = this->ui->fontLabel->font().family() ;

    Config::fontSize = this->qsettings.value(FONT_SIZE).toInt() ;
    if(Config::fontSize==0)
        Config::fontSize = this->ui->fontLabel->font().pointSize() ;

    Config::fontColor = this->qsettings.value(FONT_COLOR).toString() ;
    Config::bgColor = this->qsettings.value(BACKGROUND_COLOR).toString() ;

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

    Config::fontFamily = this->ui->fontComboBox->currentText();
    this->qsettings.setValue(FONT_FAMILY, Config::fontFamily);

    Config::fontSize = this->ui->fontSpinBox->value();
    this->qsettings.setValue(FONT_SIZE, Config::fontSize);

    Config::fontColor = this->ui->fontColorComboBox->currentText();
    this->qsettings.setValue(FONT_COLOR, Config::fontColor);

    Config::bgColor = this->ui->bgColorComboBox->currentText();
    this->qsettings.setValue(BACKGROUND_COLOR, Config::bgColor);


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

void Settings::resetSettingsWidgets()
{
    // every Settings member gets the value of the corresponding static variable

    this->fontStr = Config::fontFamily ;
    this->fontSize = Config::fontSize ;

    this->fontColor = Config::fontColor ;
    this->bgColor = Config::bgColor ;

    this->updateLabel();

    this->latitude = Config::latitude ;
    this->ui->latDoubleSpinBox->setValue(this->latitude);

    this->longitude = Config::longitude ;
    this->ui->lonDoubleSpinBox->setValue(this->longitude);

    this->distance = Config::distance ;
    this->ui->distDoubleSpinBox->setValue(this->distance);

}

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
