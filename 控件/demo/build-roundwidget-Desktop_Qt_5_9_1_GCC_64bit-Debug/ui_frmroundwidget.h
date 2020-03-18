/********************************************************************************
** Form generated from reading UI file 'frmroundwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMROUNDWIDGET_H
#define UI_FRMROUNDWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "roundwidget.h"

QT_BEGIN_NAMESPACE

class Ui_frmRoundWidget
{
public:
    QVBoxLayout *verticalLayout;
    RoundWidget *roundWidget;

    void setupUi(QWidget *frmRoundWidget)
    {
        if (frmRoundWidget->objectName().isEmpty())
            frmRoundWidget->setObjectName(QStringLiteral("frmRoundWidget"));
        frmRoundWidget->resize(500, 300);
        verticalLayout = new QVBoxLayout(frmRoundWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        roundWidget = new RoundWidget(frmRoundWidget);
        roundWidget->setObjectName(QStringLiteral("roundWidget"));

        verticalLayout->addWidget(roundWidget);


        retranslateUi(frmRoundWidget);

        QMetaObject::connectSlotsByName(frmRoundWidget);
    } // setupUi

    void retranslateUi(QWidget *frmRoundWidget)
    {
        frmRoundWidget->setWindowTitle(QApplication::translate("frmRoundWidget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmRoundWidget: public Ui_frmRoundWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMROUNDWIDGET_H
