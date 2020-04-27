/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *menuBtn;
    QPushButton *minBtn;
    QPushButton *nomalBtn;
    QPushButton *closeBtn;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_checkUpdate;
    QLabel *label_4;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label_14;
    QWidget *page_2;
    QLabel *label_5;
    QWidget *page_3;
    QLabel *label_7;
    QLabel *label_15;
    QWidget *page_4;
    QLabel *label_8;
    QWidget *page_5;
    QLabel *label_9;
    QWidget *page_6;
    QLabel *label_10;
    QWidget *page_7;
    QLabel *label_11;
    QWidget *page_8;
    QLabel *label_12;
    QWidget *page_9;
    QLabel *label_13;
    QLabel *label_6;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(850, 600);
        MainWindow->setMinimumSize(QSize(850, 600));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        menuBtn = new QPushButton(centralWidget);
        menuBtn->setObjectName(QStringLiteral("menuBtn"));
        menuBtn->setGeometry(QRect(697, 0, 33, 18));
        menuBtn->setMinimumSize(QSize(33, 18));
        menuBtn->setMaximumSize(QSize(33, 18));
        minBtn = new QPushButton(centralWidget);
        minBtn->setObjectName(QStringLiteral("minBtn"));
        minBtn->setGeometry(QRect(732, 0, 33, 18));
        minBtn->setMinimumSize(QSize(33, 18));
        minBtn->setMaximumSize(QSize(33, 18));
        nomalBtn = new QPushButton(centralWidget);
        nomalBtn->setObjectName(QStringLiteral("nomalBtn"));
        nomalBtn->setGeometry(QRect(766, 0, 33, 18));
        nomalBtn->setMinimumSize(QSize(33, 18));
        nomalBtn->setMaximumSize(QSize(33, 18));
        closeBtn = new QPushButton(centralWidget);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));
        closeBtn->setGeometry(QRect(800, 0, 48, 18));
        closeBtn->setMinimumSize(QSize(48, 18));
        closeBtn->setMaximumSize(QSize(48, 18));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 4, 121, 21));
        label->setStyleSheet(QString::fromUtf8("font:0 9pt \"\351\273\221\344\275\223\";\n"
"font-weight: bold;\n"
"color:rgb(150, 150, 150);\n"
"\n"
""));
        label->setTextFormat(Qt::RichText);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(9, 576, 151, 21));
        label_2->setStyleSheet(QLatin1String("color:rgb(150, 150, 150);\n"
"\n"
"\n"
""));
        label_2->setTextFormat(Qt::RichText);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(141, 570, 151, 31));
        label_3->setStyleSheet(QLatin1String("color:rgb(150, 150, 150);\n"
"\n"
""));
        label_3->setTextFormat(Qt::RichText);
        label_checkUpdate = new QLabel(centralWidget);
        label_checkUpdate->setObjectName(QStringLiteral("label_checkUpdate"));
        label_checkUpdate->setGeometry(QRect(279, 575, 61, 21));
        label_checkUpdate->setStyleSheet(QStringLiteral(""));
        label_checkUpdate->setTextFormat(Qt::RichText);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(708, 36, 126, 68));
        label_4->setMinimumSize(QSize(126, 68));
        label_4->setStyleSheet(QStringLiteral("background-image: url(:/res/image/360logo.png);"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(18, 31, 680, 80));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(70, 78));
        pushButton->setMaximumSize(QSize(70, 78));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(70, 78));
        pushButton_2->setMaximumSize(QSize(70, 78));

        horizontalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(70, 78));
        pushButton_3->setMaximumSize(QSize(70, 78));

        horizontalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(layoutWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(70, 78));
        pushButton_4->setMaximumSize(QSize(70, 78));

        horizontalLayout->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(layoutWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(70, 78));
        pushButton_5->setMaximumSize(QSize(70, 78));

        horizontalLayout->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(layoutWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setMinimumSize(QSize(70, 78));
        pushButton_6->setMaximumSize(QSize(70, 78));

        horizontalLayout->addWidget(pushButton_6);

        pushButton_7 = new QPushButton(layoutWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setMinimumSize(QSize(70, 78));
        pushButton_7->setMaximumSize(QSize(70, 78));

        horizontalLayout->addWidget(pushButton_7);

        pushButton_8 = new QPushButton(layoutWidget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setMinimumSize(QSize(70, 78));
        pushButton_8->setMaximumSize(QSize(70, 78));

        horizontalLayout->addWidget(pushButton_8);

        pushButton_9 = new QPushButton(layoutWidget);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setMinimumSize(QSize(70, 78));
        pushButton_9->setMaximumSize(QSize(70, 78));

        horizontalLayout->addWidget(pushButton_9);

        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(22, 120, 831, 451));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        label_14 = new QLabel(page);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(180, 110, 261, 51));
        label_14->setStyleSheet(QLatin1String("font: 75 24pt \"Aharoni\";\n"
"color: rgb(228, 146, 255);"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        label_5 = new QLabel(page_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(150, 130, 261, 51));
        label_5->setStyleSheet(QStringLiteral("font: 75 24pt \"Aharoni\";"));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        label_7 = new QLabel(page_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(400, 160, 261, 51));
        label_15 = new QLabel(page_3);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(240, 120, 261, 51));
        label_15->setStyleSheet(QLatin1String("font: 75 24pt \"Aharoni\";\n"
"color: rgb(255, 0, 0);"));
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        label_8 = new QLabel(page_4);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(270, 170, 261, 51));
        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QStringLiteral("page_5"));
        label_9 = new QLabel(page_5);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(300, 210, 261, 51));
        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName(QStringLiteral("page_6"));
        label_10 = new QLabel(page_6);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(300, 190, 261, 51));
        stackedWidget->addWidget(page_6);
        page_7 = new QWidget();
        page_7->setObjectName(QStringLiteral("page_7"));
        label_11 = new QLabel(page_7);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(300, 210, 261, 51));
        stackedWidget->addWidget(page_7);
        page_8 = new QWidget();
        page_8->setObjectName(QStringLiteral("page_8"));
        label_12 = new QLabel(page_8);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(380, 200, 261, 51));
        stackedWidget->addWidget(page_8);
        page_9 = new QWidget();
        page_9->setObjectName(QStringLiteral("page_9"));
        label_13 = new QLabel(page_9);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(370, 210, 261, 51));
        label_6 = new QLabel(page_9);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(260, 80, 261, 51));
        label_6->setStyleSheet(QLatin1String("font: 75 24pt \"Aharoni\";\n"
"color: rgb(85, 0, 255);"));
        stackedWidget->addWidget(page_9);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);
        QObject::connect(closeBtn, SIGNAL(clicked()), MainWindow, SLOT(close()));
        QObject::connect(minBtn, SIGNAL(clicked()), MainWindow, SLOT(showMinimized()));

        stackedWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        menuBtn->setText(QString());
        minBtn->setText(QString());
        nomalBtn->setText(QString());
        closeBtn->setText(QString());
        label->setText(QApplication::translate("MainWindow", "360\345\256\211\345\205\250\345\215\253\345\243\253 8.8", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\344\270\273\347\250\213\345\272\217\347\211\210\346\234\254:8.8.0.2001", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\345\244\207\347\224\250\346\234\250\351\251\254\345\272\223: 2012-12-16", Q_NULLPTR));
        label_checkUpdate->setText(QString());
        label_4->setText(QString());
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        pushButton_4->setText(QString());
        pushButton_5->setText(QString());
        pushButton_6->setText(QString());
        pushButton_7->setText(QString());
        pushButton_8->setText(QString());
        pushButton_9->setText(QString());
        label_14->setText(QApplication::translate("MainWindow", "\347\224\265\350\204\221\344\275\223\346\243\200", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "\346\210\221\346\230\257\346\234\250\351\251\254\346\237\245\346\235\200\347\252\227\345\217\243", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "widget3", Q_NULLPTR));
        label_15->setText(QApplication::translate("MainWindow", "\346\274\217\346\264\236\344\277\256\345\244\215", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "widget4", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "widget5", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "widget6", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "widget7", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "widget8", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "widget9", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "\345\212\237\350\203\275\345\244\247\345\205\250", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
