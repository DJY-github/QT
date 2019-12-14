/********************************************************************************
** Form generated from reading UI file 'testdialog2.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTDIALOG2_H
#define UI_TESTDIALOG2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_testDialog2
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLabel *label;

    void setupUi(QDialog *testDialog2)
    {
        if (testDialog2->objectName().isEmpty())
            testDialog2->setObjectName(QStringLiteral("testDialog2"));
        testDialog2->resize(482, 300);
        widget = new QWidget(testDialog2);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 100, 344, 27));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        horizontalLayout->addWidget(lineEdit_2);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);


        retranslateUi(testDialog2);

        QMetaObject::connectSlotsByName(testDialog2);
    } // setupUi

    void retranslateUi(QDialog *testDialog2)
    {
        testDialog2->setWindowTitle(QApplication::translate("testDialog2", "Dialog", Q_NULLPTR));
        label_2->setText(QApplication::translate("testDialog2", "TextLabel", Q_NULLPTR));
        label->setText(QApplication::translate("testDialog2", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class testDialog2: public Ui_testDialog2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTDIALOG2_H
