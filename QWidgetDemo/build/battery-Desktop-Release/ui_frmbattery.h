/********************************************************************************
** Form generated from reading UI file 'frmbattery.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMBATTERY_H
#define UI_FRMBATTERY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include "battery.h"

QT_BEGIN_NAMESPACE

class Ui_frmBattery
{
public:
    Battery *battery;
    QSlider *horizontalSlider;

    void setupUi(QWidget *frmBattery)
    {
        if (frmBattery->objectName().isEmpty())
            frmBattery->setObjectName(QStringLiteral("frmBattery"));
        frmBattery->resize(500, 300);
        battery = new Battery(frmBattery);
        battery->setObjectName(QStringLiteral("battery"));
        battery->setGeometry(QRect(9, 9, 482, 257));
        horizontalSlider = new QSlider(frmBattery);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(9, 272, 481, 19));
        horizontalSlider->setMaximum(100);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setInvertedControls(false);

        retranslateUi(frmBattery);

        QMetaObject::connectSlotsByName(frmBattery);
    } // setupUi

    void retranslateUi(QWidget *frmBattery)
    {
        frmBattery->setWindowTitle(QApplication::translate("frmBattery", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmBattery: public Ui_frmBattery {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMBATTERY_H
