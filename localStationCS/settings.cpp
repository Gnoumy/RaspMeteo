#include "settings.h"
#include "ui_settings.h"

#include "config.h"
#include <QDirIterator>
#include <QMessageBox>

#define RESSOURCE_FONTS_FOLDER      ":/fonts"
#define MIN_SCROLLING_SPEED         1   // fast
#define MAX_SCROLLING_SPEED         50  // slow
#define MIN_WIDGET_MODE             0
#define MAX_WIDGET_MODE             1
#define DEFAULT_SPEED_TEXT          "Speed (Fast -> Slow) : "
#define DEFAULT_AUTO_SCROLLING_TEXT "This is an auto-scrolling label. If the text is long enough, you will see it scrolling..."


#include <QDebug>
#include <QHelpEvent>
#include <QToolTip>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    // init widgets of the .ui
    ui->setupUi(this);

    // qDebug() << "this->ui->autoScrollingLabel->width()" << this->ui->autoScrollingLabel->width() ;
    // qDebug() << "this->ui->scrollingSpeedHorizontalSlider->width()" << this->ui->scrollingSpeedHorizontalSlider->width() ;
    // qDebug() << "this->ui->scrollingSpeedLabel->width()" << this->ui->scrollingSpeedLabel->width() ;
    this->initAllColorComboBoxes() ;
    this->initAllFontComboBoxes() ;

    // init doubleSpinBoxes (for now : latitude, longitude, distance)
    // "English" => decimal separator = '.'
    // "French" => decimal separator = ','
    this->ui->latDoubleSpinBox->setLocale(QLocale::English);
    this->ui->lonDoubleSpinBox->setLocale(QLocale::English);
    this->ui->distDoubleSpinBox->setLocale(QLocale::English);


    // qDebug() << "this->ui->autoScrollingLabel->parentWidget()" << this->ui->autoScrollingLabel->parentWidget() ;
    this->initMiscellaneous() ;
    // qDebug() << "this->ui->autoScrollingLabel->parentWidget()" << this->ui->autoScrollingLabel->parentWidget() ;
    // qDebug() << "this->ui->autoScrollingLabel->width()" << this->ui->autoScrollingLabel->width() ;
    // qDebug() << "this->ui->scrollingSpeedHorizontalSlider->width()" << this->ui->scrollingSpeedHorizontalSlider->width() ;
    // qDebug() << "this->ui->scrollingSpeedLabel->width()" << this->ui->scrollingSpeedLabel->width() ;

//    qDebug()<<"aa"<<this->ui->headerFontLabel->parent()->objectName();
//    QObjectList tabs(this->ui->tabHeaderFont->parent()->children());

//    for (const QObject* qw : tabs)
//    {
//        QObjectList ch(qw->children());
//        qDebug()<<"a---------a" ;
//        for (const QObject* ww : ch)
//            qDebug()<<"aa"<<ww->objectName();
//    }




//    this->ui->labelAutoScrolling->setText("TextLabelTEXTLABEL");
//    int textPixelWidth = this->ui->labelAutoScrolling->fontMetrics().boundingRect(this->ui->labelAutoScrolling->text()).width() ;
//    int labelWidth = this->ui->labelAutoScrolling->width() ;

//    qDebug() << "textPixelWidth " << textPixelWidth ;
//    qDebug() << "labelWidth " << labelWidth ;





    // "OrganizationDomain" and "ApplicationName" related to qsettings are set in main.cpp
//    this->qsettings.setParent(this);
//    this->affectValuesToConfigStaticVars();


    QApplication::setFont(QFont( Config::getFontFamily(), Config::getFontSize() ));

    // all the connects --------------------------------------------------------------------------------------------------------

    connect(this->ui->applyPushButton, SIGNAL(released()), this, SLOT(changeConfig())) ;

/*

    // Body, then Header, then Footer

        // Equivalent. One with a private slot, and one with a lambda expression
        //connect(this->ui->fontComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(changeFontComboBox(QString))) ;
    connect(this->ui->fontComboBox, &QFontComboBox::currentTextChanged, this,
        [this](const QString &value)
        {
            this->fontStr = value ;
            this->updateLabel(this->ui->fontLabel,
                              this->ui->fontComboBox,
                              this->ui->fontSpinBox,
                              this->ui->fontColorComboBox,
                              this->ui->bgColorComboBox);
        }) ;


        // Equivalent. One with a private slot, and one with a lambda expression
        //connect(this->ui->fontSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeSpinBox(int))) ;
    connect(this->ui->fontSpinBox, qOverload<int>(&QSpinBox::valueChanged), this,
        [this](const int &value)
        {
            this->fontSize = value ;
            this->updateLabel(this->ui->fontLabel,
                              this->ui->fontComboBox,
                              this->ui->fontSpinBox,
                              this->ui->fontColorComboBox,
                              this->ui->bgColorComboBox);
        }) ;
            // qOverload<int>(...) is ugly but needed because there are 2 "valueChanged" SpinBox signals


        // Equivalent. One with a private slot, and one with a lambda expression
        //connect(this->ui->fontColorComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(changeFontComboBox(QString))) ;
    connect(this->ui->fontColorComboBox, &QComboBox::currentTextChanged, this,
        [this](const QString &value)
        {
            this->fontColor = value ;
            this->updateLabel(this->ui->fontLabel,
                              this->ui->fontComboBox,
                              this->ui->fontSpinBox,
                              this->ui->fontColorComboBox,
                              this->ui->bgColorComboBox);
        }) ;


        // Equivalent. One with a private slot, and one with a lambda expression
        //connect(this->ui->bgColorComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(changeFontComboBox(QString))) ;
    connect(this->ui->bgColorComboBox, &QComboBox::currentTextChanged, this,
        [this](const QString &value)
        {
            this->bgColor = value ;
            this->updateLabel(this->ui->fontLabel,
                              this->ui->fontComboBox,
                              this->ui->fontSpinBox,
                              this->ui->fontColorComboBox,
                              this->ui->bgColorComboBox);
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

*/

    this->connectFontRelatedWidgets(this->ui->fontLabel,
                                    this->ui->fontComboBox,
                                    this->ui->fontSpinBox,
                                    this->ui->fontColorComboBox,
                                    this->ui->bgColorComboBox);

    this->connectFontRelatedWidgets(this->ui->headerFontLabel,
                                    this->ui->headerFontComboBox,
                                    this->ui->headerFontSpinBox,
                                    this->ui->headerFontColorComboBox,
                                    this->ui->headerBgColorComboBox);

    this->connectFontRelatedWidgets(this->ui->footerFontLabel,
                                    this->ui->footerFontComboBox,
                                    this->ui->footerFontSpinBox,
                                    this->ui->footerFontColorComboBox,
                                    this->ui->footerBgColorComboBox);

    this->connectFontRelatedWidgets(this->ui->tableFontLabel,
                                    this->ui->tableFontComboBox,
                                    this->ui->tableFontSpinBox,
                                    this->ui->tableFontColorComboBox,
                                    this->ui->tableBgColorComboBox);
}

//void Settings::paintEvent(QPaintEvent *e)
//{

//////    this->ui->labelAutoScrolling->setText("TextLabel");
////    int textPixelWidth = this->ui->labelAutoScrolling->fontMetrics().boundingRect(this->ui->labelAutoScrolling->text()).width() ;
////    int labelWidth = this->ui->labelAutoScrolling->width() ;

////    if (labelWidth < textPixelWidth)
////    {
////        qDebug() << "Trop grand : " << labelWidth << " < " << textPixelWidth ;
////        this->ui->labelAutoScrolling->scroll(labelWidth, 0);

////    }

//////    QDialog::paintEvent(e) ;
//}



void Settings::affectValuesToConfigStaticVars()
{
    // only used in Constructor
    // affecting values / default values

    // Body ------------------------------------------------------------


    // Header ------------------------------------------------------------




    // Footer ------------------------------------------------------------




    // Position ------------------------------------------------------------





}

//void Settings::changeFontComboBox(const QString &value)
//{
//    this->fontStr = value ;
//    this->updateLabel(this->ui->fontLabel,
//                      this->ui->fontComboBox,
//                      this->ui->fontSpinBox,
//                      this->ui->fontColorComboBox,
//                      this->ui->bgColorComboBox);
//}

//void Settings::changeSpinBox(const int &value)
//{
//    this->fontSize = value ;
//    this->updateLabel(this->ui->fontLabel,
//                      this->ui->fontComboBox,
//                      this->ui->fontSpinBox,
//                      this->ui->fontColorComboBox,
//                      this->ui->bgColorComboBox);
//}

void Settings::changeLabelStyleSheet(QLabel *qlabel,
                                     const QComboBox *comboBoxWithFontColor,
                                     const QComboBox *comboBoxWithBgColor)
{
    qlabel->setStyleSheet(
                QString(
                    "QLabel { color : %1; background-color : %2; }"
                    ).arg(comboBoxWithFontColor->currentText())
                     .arg(comboBoxWithBgColor->currentText())) ;
}

void Settings::updateLabel(QLabel *qlabel,
                           const QFontComboBox  *qfontcombobox,
                           const QSpinBox       *fontSizeSpinBox,
                           const QComboBox      *comboBoxWithFontColor,
                           const QComboBox      *comboBoxWithBgColor)
{
//    this->ui->fontComboBox->setCurrentText(this->fontStr);
//    this->ui->fontSpinBox->setValue(this->fontSize);
//    this->ui->fontLabel->setFont(QFont(
//                                     this->ui->fontComboBox->currentText(),
//                                     this->ui->fontSpinBox->value()));
    qlabel->setFont(QFont(
                       qfontcombobox->currentText(),
                       fontSizeSpinBox->value()));

//    this->ui->fontColorComboBox->setCurrentText(this->fontColor);
//    this->ui->bgColorComboBox->setCurrentText(this->bgColor);
//    this->changeLabelStyleSheet(this->ui->fontLabel,
//                                this->ui->fontColorComboBox,
//                                this->ui->bgColorComboBox);
    this->changeLabelStyleSheet(qlabel,
                                comboBoxWithFontColor,
                                comboBoxWithBgColor);

}

//void Settings::updateHeaderLabel()
//{
////    this->ui->headerFontComboBox->setCurrentText(this->headerFontFamily);
////    this->ui->headerFontSpinBox->setValue(this->headerFontSize);
//    this->ui->headerFontLabel->setFont(QFont(
//                                     this->ui->headerFontComboBox->currentText(),
//                                     this->ui->headerFontSpinBox->value()));

////    this->ui->headerFontColorComboBox->setCurrentText(this->headerFontColor);
////    this->ui->headerBgColorComboBox->setCurrentText(this->headerBgColor);
//    this->changeLabelStyleSheet(this->ui->headerFontLabel,
//                                this->ui->headerFontColorComboBox,
//                                this->ui->headerBgColorComboBox);

//}

//void Settings::updateFooterLabel()
//{
//    this->ui->footerFontComboBox->setCurrentText(this->footerFontFamily);
//    this->ui->footerFontSpinBox->setValue(this->footerFontSize);
//    this->ui->footerFontLabel->setFont(QFont(this->footerFontFamily, this->footerFontSize));

////    this->ui->footerFontColorComboBox->setCurrentText(this->footerFontColor);
////    this->ui->footerBgColorComboBox->setCurrentText(this->footerBgColor);
//    this->changeLabelStyleSheet(this->ui->footerFontLabel,
//                                this->ui->footerFontColorComboBox,
//                                this->ui->footerBgColorComboBox);

//}

void Settings::connectFontRelatedWidgets(QLabel *qlabel,
                                         const QFontComboBox  *qfontcombobox,
                                         const QSpinBox       *fontSizeSpinBox,
                                         const QComboBox      *comboBoxWithFontColor,
                                         const QComboBox      *comboBoxWithBgColor)
{

        // Equivalent. One with a private slot, and one with a lambda expression
        //this->connect(qfontcombobox, SIGNAL(currentTextChanged(QString)), this, SLOT(changeFontComboBox(QString))) ;
    this->connect(qfontcombobox, &QFontComboBox::currentTextChanged, this,
        [=]
        {
            // this->fontStr = value ;
            this->updateLabel(qlabel,
                              qfontcombobox,
                              fontSizeSpinBox,
                              comboBoxWithFontColor,
                              comboBoxWithBgColor);
        }) ;


        // Equivalent. One with a private slot, and one with a lambda expression
        //this->connect(fontSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeSpinBox(int))) ;
    this->connect(fontSizeSpinBox, qOverload<int>(&QSpinBox::valueChanged), this,
        [=]
        {
            // this->fontSize = value ;
            this->updateLabel(qlabel,
                              qfontcombobox,
                              fontSizeSpinBox,
                              comboBoxWithFontColor,
                              comboBoxWithBgColor);
        }) ;
            // qOverload<int>(...) is ugly but needed because there are 2 "valueChanged" SpinBox signals


        // Equivalent. One with a private slot, and one with a lambda expression
        //this->connect(comboBoxWithFontColor, SIGNAL(currentTextChanged(QString)), this, SLOT(changeFontComboBox(QString))) ;
    this->connect(comboBoxWithFontColor, &QComboBox::currentTextChanged, this,
        [=]
        {
            // this->fontColor = value ;
            this->updateLabel(qlabel,
                              qfontcombobox,
                              fontSizeSpinBox,
                              comboBoxWithFontColor,
                              comboBoxWithBgColor);
        }) ;


        // Equivalent. One with a private slot, and one with a lambda expression
        //this->connect(comboBoxWithBgColor, SIGNAL(currentTextChanged(QString)), this, SLOT(changeFontComboBox(QString))) ;
    this->connect(comboBoxWithBgColor, &QComboBox::currentTextChanged, this,
        [=]
        {
//            this->bgColor = value ;
            this->updateLabel(qlabel,
                              qfontcombobox,
                              fontSizeSpinBox,
                              comboBoxWithFontColor,
                              comboBoxWithBgColor);
        }) ;


}

void Settings::resetWidget(QFontComboBox *qfontcombobox, const QString &value)
{
    qfontcombobox->setCurrentText(value);
}

void Settings::resetWidget(QComboBox *qcombobox, const QString &value)
{
    qcombobox->setCurrentText(value);
}

void Settings::resetWidget(QSpinBox *qspinBox, const int &value)
{
    qspinBox->setValue(value);
}

void Settings::resetWidget(QDoubleSpinBox *qdoublespinBox, const float &value)
{
    qdoublespinBox->setValue(value);
}

void Settings::resetFontRelatedWidgets(QLabel *qlabel,
                                       QFontComboBox  *qfontcombobox,
                                       QSpinBox       *fontSizeSpinBox,
                                       QComboBox      *comboBoxWithFontColor,
                                       QComboBox      *comboBoxWithBgColor,
                                       const QString  &valueforqfontcombobox,
                                       const int      &valueforfontSizeSpinBox,
                                       const QString  &valueforcomboBoxWithFontColor,
                                       const QString  &valueforcomboBoxWithBgColor)
{
    this->resetWidget(qfontcombobox,        valueforqfontcombobox);
    this->resetWidget(fontSizeSpinBox,      valueforfontSizeSpinBox);
    this->resetWidget(comboBoxWithFontColor,valueforcomboBoxWithFontColor);
    this->resetWidget(comboBoxWithBgColor,  valueforcomboBoxWithBgColor);

    this->updateLabel(qlabel,
                      qfontcombobox,
                      fontSizeSpinBox,
                      comboBoxWithFontColor,
                      comboBoxWithBgColor);
}

void Settings::resetSettingsWidgets()
{
    // every Settings member gets the value of the corresponding static variable

    // Body ------------------------------------------------------------

//    this->fontStr = Config::getFontFamily() ;
//    this->fontSize = Config::getFontSize() ;
//    this->fontColor = Config::getFontColor() ;
//    this->bgColor = Config::getBgColor() ;
//    this->ui->fontComboBox->setCurrentText      (Config::getFontFamily());
//    this->ui->fontSpinBox->setValue             (Config::getFontSize());
//    this->ui->fontColorComboBox->setCurrentText (Config::getFontColor());
//    this->ui->bgColorComboBox->setCurrentText   (Config::getBgColor());

//    this->updateLabel(this->ui->fontLabel,
//                      this->ui->fontComboBox,
//                      this->ui->fontSpinBox,
//                      this->ui->fontColorComboBox,
//                      this->ui->bgColorComboBox);
    this->resetFontRelatedWidgets(this->ui->fontLabel,
                                  this->ui->fontComboBox,
                                  this->ui->fontSpinBox,
                                  this->ui->fontColorComboBox,
                                  this->ui->bgColorComboBox,
                                  Config::getFontFamily(),
                                  Config::getFontSize(),
                                  Config::getFontColor(),
                                  Config::getBgColor());

    // Header ------------------------------------------------------------

//    this->headerFontFamily = Config::getHeaderFontFamily() ;
//    this->headerFontSize = Config::getHeaderFontSize() ;
//    this->headerFontColor = Config::getHeaderFontColor() ;
//    this->headerBgColor = Config::getHeaderBgColor() ;
//    this->ui->headerFontComboBox->setCurrentText        (Config::getHeaderFontFamily());
//    this->ui->headerFontSpinBox->setValue               (Config::getHeaderFontSize());
//    this->ui->headerFontColorComboBox->setCurrentText   (Config::getHeaderFontColor());
//    this->ui->headerBgColorComboBox->setCurrentText     (Config::getHeaderBgColor());

//    this->updateHeaderLabel();
    this->resetFontRelatedWidgets(this->ui->headerFontLabel,
                                  this->ui->headerFontComboBox,
                                  this->ui->headerFontSpinBox,
                                  this->ui->headerFontColorComboBox,
                                  this->ui->headerBgColorComboBox,
                                  Config::getHeaderFontFamily(),
                                  Config::getHeaderFontSize(),
                                  Config::getHeaderFontColor(),
                                  Config::getHeaderBgColor());

    // Footer ------------------------------------------------------------

//    this->footerFontFamily = Config::getFooterFontFamily() ;
//    this->footerFontSize = Config::getFooterFontSize() ;
//    this->footerFontColor = Config::getFooterFontColor() ;
//    this->footerBgColor = Config::getFooterBgColor() ;
//    this->ui->footerFontComboBox->setCurrentText        (Config::getFooterFontFamily());
//    this->ui->footerFontSpinBox->setValue               (Config::getFooterFontSize());
//    this->ui->footerFontColorComboBox->setCurrentText   (Config::getFooterFontColor());
//    this->ui->footerBgColorComboBox->setCurrentText     (Config::getFooterBgColor());

//    this->updateFooterLabel();
    this->resetFontRelatedWidgets(this->ui->footerFontLabel,
                                  this->ui->footerFontComboBox,
                                  this->ui->footerFontSpinBox,
                                  this->ui->footerFontColorComboBox,
                                  this->ui->footerBgColorComboBox,
                                  Config::getFooterFontFamily(),
                                  Config::getFooterFontSize(),
                                  Config::getFooterFontColor(),
                                  Config::getFooterBgColor());

    // Table ------------------------------------------------------------

    this->resetFontRelatedWidgets(this->ui->tableFontLabel,
                                  this->ui->tableFontComboBox,
                                  this->ui->tableFontSpinBox,
                                  this->ui->tableFontColorComboBox,
                                  this->ui->tableBgColorComboBox,
                                  Config::getTableFontFamily(),
                                  Config::getTableFontSize(),
                                  Config::getTableFontColor(),
                                  Config::getTableBgColor());

    // Position ------------------------------------------------------------

    this->ui->latDoubleSpinBox->setValue(Config::getLatitude());
    this->ui->lonDoubleSpinBox->setValue(Config::getLongitude());
    this->ui->distDoubleSpinBox->setValue(Config::getDistance());

    // Miscellaneous ------------------------------------------------------------

    this->ui->scrollingSpeedHorizontalSlider->setValue(Config::getScrollingSpeed());
    this->ui->scrollingSpeedLabel->setText(DEFAULT_SPEED_TEXT
                + QString::number(this->ui->scrollingSpeedHorizontalSlider->value()));
    this->ui->widgetModeSpinBox->setValue(Config::getWidgetMode());

}

void Settings::changeConfig()
{
//    this->setFont(settings->value("font").value<QFont>());
//    qDebug() << this->ui->fontComboBox->currentText() ;

    // Body ------------------------------------------------------------

    Config::setFontFamily( this->ui->fontComboBox->currentText() ) ;

    Config::setFontSize( this->ui->fontSpinBox->value() ) ;

    Config::setFontColor( this->ui->fontColorComboBox->currentText() ) ;

    Config::setBgColor( this->ui->bgColorComboBox->currentText() ) ;

    // Header ------------------------------------------------------------

    Config::setHeaderFontFamily( this->ui->headerFontComboBox->currentText() ) ;

    Config::setHeaderFontSize( this->ui->headerFontSpinBox->value() ) ;

    Config::setHeaderFontColor( this->ui->headerFontColorComboBox->currentText() ) ;

    Config::setHeaderBgColor( this->ui->headerBgColorComboBox->currentText() ) ;

    // Footer ------------------------------------------------------------

    Config::setFooterFontFamily( this->ui->footerFontComboBox->currentText() ) ;

    Config::setFooterFontSize( this->ui->footerFontSpinBox->value() ) ;

    Config::setFooterFontColor( this->ui->footerFontColorComboBox->currentText() ) ;

    Config::setFooterBgColor( this->ui->footerBgColorComboBox->currentText() ) ;

    // Table ------------------------------------------------------------

    Config::setTableFontFamily( this->ui->tableFontComboBox->currentText() ) ;

    Config::setTableFontSize( this->ui->tableFontSpinBox->value() ) ;

    Config::setTableFontColor( this->ui->tableFontColorComboBox->currentText() ) ;

    Config::setTableBgColor( this->ui->tableBgColorComboBox->currentText() ) ;

    // Position ------------------------------------------------------------

    Config::setLatitude( this->ui->latDoubleSpinBox->value() ) ;

    Config::setLongitude( this->ui->lonDoubleSpinBox->value() ) ;

    Config::setDistance( this->ui->distDoubleSpinBox->value() ) ;

    // Miscellaneous ------------------------------------------------------------

    Config::setScrollingSpeed( this->ui->scrollingSpeedHorizontalSlider->value() ) ;

    Config::setWidgetMode( this->ui->widgetModeSpinBox->value() ) ;

    // Apply to the whole project
    QApplication::setFont(QFont(this->ui->fontComboBox->currentText(),this->ui->fontSpinBox->value()));
    this->hide();
}

void Settings::initAllColorComboBoxes()
{
    // color names that we will insert
    // in fontColor ComboBoxes and bgColor ComboBoxes
    QStringList colors(QColor::colorNames()) ;
    QString fontColorToolTip    = "Font Color" ;
    QString bgColorToolTip      = "Background Color" ;

    this->ui->fontColorComboBox         ->addItems(colors);
    this->ui->fontColorComboBox         ->setToolTip(fontColorToolTip);

    this->ui->bgColorComboBox           ->addItems(colors);
    this->ui->bgColorComboBox           ->setToolTip(bgColorToolTip);

    this->ui->headerFontColorComboBox   ->addItems(colors);
    this->ui->headerFontColorComboBox   ->setToolTip(fontColorToolTip);

    this->ui->headerBgColorComboBox     ->addItems(colors);
    this->ui->headerBgColorComboBox     ->setToolTip(bgColorToolTip);

    this->ui->footerFontColorComboBox   ->addItems(colors);
    this->ui->footerFontColorComboBox   ->setToolTip(fontColorToolTip);

    this->ui->footerBgColorComboBox     ->addItems(colors);
    this->ui->footerBgColorComboBox     ->setToolTip(bgColorToolTip);

    this->ui->tableFontColorComboBox    ->addItems(colors);
    this->ui->tableFontColorComboBox    ->setToolTip(fontColorToolTip);

    this->ui->tableBgColorComboBox      ->addItems(colors);
    this->ui->tableBgColorComboBox      ->setToolTip(bgColorToolTip);

    this->ui->other2_ComboBox->addItems(colors);

}

void Settings::initAllFontComboBoxes()
{

    QStringList familyList ;
    familyList.reserve(QDir(RESSOURCE_FONTS_FOLDER).count());
    //    qDebug()<<QDir(RESSOURCE_FONTS_FOLDER).count()<<"qqqq";
    QDirIterator it(RESSOURCE_FONTS_FOLDER, QDirIterator::Subdirectories);

    // tester aussi sur fichiers hidden ?????
    while (it.hasNext()) {
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

    this->ui->tableFontComboBox->clear();
    this->ui->tableFontComboBox->addItems(familyList);

    this->ui->other1_FontComboBox->clear();
    this->ui->other1_FontComboBox->addItems(familyList);

}

void Settings::initMiscellaneous()
{
    if ( QString(this->ui->autoScrollingLabel->metaObject()->className()) != "AutoScrollingLabel" )
        qDebug() << "Warning : the class of autoScrollingLabel is not AutoScrollingLabel" ;

    this->ui->autoScrollingLabel->setFixedWidth(this->width()>>1);
    this->ui->verticalLayoutMiscellaneous->setAlignment(this->ui->autoScrollingLabel, Qt::AlignCenter);
    this->ui->autoScrollingLabel->setText(DEFAULT_AUTO_SCROLLING_TEXT);

    this->ui->scrollingSpeedHorizontalSlider->setRange(MIN_SCROLLING_SPEED, MAX_SCROLLING_SPEED);
    this->connect(this->ui->scrollingSpeedHorizontalSlider, &QSlider::valueChanged, this,
                  [this](const int &value)
                {
                    this->ui->autoScrollingLabel->setTimerInterval(value);
                    this->ui->scrollingSpeedLabel->setText(DEFAULT_SPEED_TEXT
                                                           + QString::number(value));

//                    this->ui->scrollingSpeedHorizontalSlider->setToolTip(QString::number(value));
//                    QHelpEvent toolTipEvent(QEvent::ToolTip, this->ui->scrollingSpeedHorizontalSlider->pos(), this->ui->scrollingSpeedHorizontalSlider->pos());
//                    QApplication::sendEvent(this->ui->scrollingSpeedHorizontalSlider, &toolTipEvent);

//                  QToolTip::showText(this->ui->scrollingSpeedHorizontalSlider->pos(), QString::number(this->ui->scrollingSpeedHorizontalSlider->value()),
//                           this->ui->scrollingSpeedHorizontalSlider,
//                           this->ui->scrollingSpeedHorizontalSlider->rect());
                });


    this->ui->widgetModeSpinBox->setRange(MIN_WIDGET_MODE, MAX_WIDGET_MODE);
}

// ameliorer ???
// override reject() virtual method (closing dialog event)
void Settings::reject()
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "",
                                        tr("Are you sure?\n"),
                                        QMessageBox::Cancel | QMessageBox::Yes,
                                        QMessageBox::Yes);

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

float Settings::getOther4() const
{
    return other4;
}

void Settings::setOther4(float value)
{
    other4 = value;
}

int Settings::getOther3() const
{
    return other3;
}

void Settings::setOther3(int value)
{
    other3 = value;
}

QString Settings::getOther2() const
{
    return other2;
}

void Settings::setOther2(const QString &value)
{
    other2 = value;
}

QString Settings::getOther1() const
{
    return other1;
}

void Settings::setOther1(const QString &value)
{
    other1 = value;
}
