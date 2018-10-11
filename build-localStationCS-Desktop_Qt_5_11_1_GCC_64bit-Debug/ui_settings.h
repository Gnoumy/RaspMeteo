/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Settings
{
public:
    QSpinBox *fontSpinBox;
    QFontComboBox *fontComboBox;
    QPushButton *applyPushButton;
    QLabel *fontLabel;
    QComboBox *fontColorComboBox;
    QComboBox *bgColorComboBox;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *latLabel;
    QDoubleSpinBox *latDoubleSpinBox;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *lonLabel;
    QDoubleSpinBox *lonDoubleSpinBox;
    QWidget *widget2;
    QVBoxLayout *verticalLayout_3;
    QLabel *distLabel;
    QDoubleSpinBox *distDoubleSpinBox;

    void setupUi(QDialog *Settings)
    {
        if (Settings->objectName().isEmpty())
            Settings->setObjectName(QStringLiteral("Settings"));
        Settings->resize(577, 587);
        fontSpinBox = new QSpinBox(Settings);
        fontSpinBox->setObjectName(QStringLiteral("fontSpinBox"));
        fontSpinBox->setGeometry(QRect(20, 190, 50, 29));
        fontComboBox = new QFontComboBox(Settings);
        fontComboBox->setObjectName(QStringLiteral("fontComboBox"));
        fontComboBox->setGeometry(QRect(0, 60, 168, 28));
        applyPushButton = new QPushButton(Settings);
        applyPushButton->setObjectName(QStringLiteral("applyPushButton"));
        applyPushButton->setGeometry(QRect(370, 510, 80, 28));
        fontLabel = new QLabel(Settings);
        fontLabel->setObjectName(QStringLiteral("fontLabel"));
        fontLabel->setGeometry(QRect(11, 11, 151, 31));
        fontColorComboBox = new QComboBox(Settings);
        fontColorComboBox->setObjectName(QStringLiteral("fontColorComboBox"));
        fontColorComboBox->setGeometry(QRect(0, 110, 79, 28));
        bgColorComboBox = new QComboBox(Settings);
        bgColorComboBox->setObjectName(QStringLiteral("bgColorComboBox"));
        bgColorComboBox->setGeometry(QRect(0, 140, 79, 28));
        widget = new QWidget(Settings);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(70, 230, 161, 57));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        latLabel = new QLabel(widget);
        latLabel->setObjectName(QStringLiteral("latLabel"));

        verticalLayout->addWidget(latLabel);

        latDoubleSpinBox = new QDoubleSpinBox(widget);
        latDoubleSpinBox->setObjectName(QStringLiteral("latDoubleSpinBox"));
        latDoubleSpinBox->setDecimals(4);

        verticalLayout->addWidget(latDoubleSpinBox);

        widget1 = new QWidget(Settings);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(240, 230, 141, 57));
        verticalLayout_2 = new QVBoxLayout(widget1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lonLabel = new QLabel(widget1);
        lonLabel->setObjectName(QStringLiteral("lonLabel"));

        verticalLayout_2->addWidget(lonLabel);

        lonDoubleSpinBox = new QDoubleSpinBox(widget1);
        lonDoubleSpinBox->setObjectName(QStringLiteral("lonDoubleSpinBox"));
        lonDoubleSpinBox->setDecimals(4);

        verticalLayout_2->addWidget(lonDoubleSpinBox);

        widget2 = new QWidget(Settings);
        widget2->setObjectName(QStringLiteral("widget2"));
        widget2->setGeometry(QRect(393, 230, 161, 57));
        verticalLayout_3 = new QVBoxLayout(widget2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        distLabel = new QLabel(widget2);
        distLabel->setObjectName(QStringLiteral("distLabel"));

        verticalLayout_3->addWidget(distLabel);

        distDoubleSpinBox = new QDoubleSpinBox(widget2);
        distDoubleSpinBox->setObjectName(QStringLiteral("distDoubleSpinBox"));
        distDoubleSpinBox->setDecimals(4);

        verticalLayout_3->addWidget(distDoubleSpinBox);


        retranslateUi(Settings);

        QMetaObject::connectSlotsByName(Settings);
    } // setupUi

    void retranslateUi(QDialog *Settings)
    {
        Settings->setWindowTitle(QApplication::translate("Settings", "Dialog", nullptr));
        applyPushButton->setText(QApplication::translate("Settings", "Apply", nullptr));
        fontLabel->setText(QApplication::translate("Settings", "Font", nullptr));
        latLabel->setText(QApplication::translate("Settings", "Latitude", nullptr));
        lonLabel->setText(QApplication::translate("Settings", "Longitude", nullptr));
        distLabel->setText(QApplication::translate("Settings", "Distance", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Settings: public Ui_Settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
