/********************************************************************************
** Form generated from reading UI file 'frmcomtool.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMCOMTOOL_H
#define UI_FRMCOMTOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmComTool
{
public:
    QGridLayout *gridLayout_6;
    QTextEdit *txtMain;
    QWidget *widgetRight;
    QVBoxLayout *verticalLayout;
    QFrame *frameTop;
    QGridLayout *gridLayout_3;
    QLabel *labPortName;
    QComboBox *cboxPortName;
    QLabel *labBaudRate;
    QComboBox *cboxBaudRate;
    QLabel *labDataBit;
    QComboBox *cboxDataBit;
    QLabel *labParity;
    QComboBox *cboxParity;
    QLabel *labStopBit;
    QComboBox *cboxStopBit;
    QPushButton *btnOpen;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_5;
    QCheckBox *ckHexSend;
    QCheckBox *ckHexReceive;
    QCheckBox *ckDebug;
    QCheckBox *ckAutoClear;
    QGridLayout *gridLayout;
    QCheckBox *ckAutoSend;
    QComboBox *cboxSendInterval;
    QCheckBox *ckAutoSave;
    QComboBox *cboxSaveInterval;
    QPushButton *btnSendCount;
    QPushButton *btnReceiveCount;
    QPushButton *btnStopShow;
    QPushButton *btnSave;
    QPushButton *btnData;
    QPushButton *btnClear;
    QSpacerItem *verticalSpacer;
    QWidget *tab_2;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout_4;
    QLabel *labListenPort;
    QLabel *labServerIP;
    QComboBox *cboxSleepTime;
    QLineEdit *txtServerIP;
    QLabel *labServerPort;
    QLineEdit *txtServerPort;
    QLabel *labSleepTime;
    QLineEdit *txtListenPort;
    QLabel *labMode;
    QComboBox *cboxMode;
    QPushButton *btnStart;
    QSpacerItem *verticalSpacer_2;
    QCheckBox *ckAutoConnect;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QComboBox *cboxData;
    QPushButton *btnSend;

    void setupUi(QWidget *frmComTool)
    {
        if (frmComTool->objectName().isEmpty())
            frmComTool->setObjectName(QStringLiteral("frmComTool"));
        frmComTool->resize(800, 600);
        gridLayout_6 = new QGridLayout(frmComTool);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        txtMain = new QTextEdit(frmComTool);
        txtMain->setObjectName(QStringLiteral("txtMain"));
        txtMain->setEnabled(true);
        txtMain->setFrameShape(QFrame::StyledPanel);
        txtMain->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        txtMain->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        txtMain->setReadOnly(true);

        gridLayout_6->addWidget(txtMain, 0, 0, 1, 1);

        widgetRight = new QWidget(frmComTool);
        widgetRight->setObjectName(QStringLiteral("widgetRight"));
        widgetRight->setMaximumSize(QSize(200, 16777215));
        verticalLayout = new QVBoxLayout(widgetRight);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frameTop = new QFrame(widgetRight);
        frameTop->setObjectName(QStringLiteral("frameTop"));
        frameTop->setFrameShape(QFrame::Box);
        frameTop->setFrameShadow(QFrame::Sunken);
        gridLayout_3 = new QGridLayout(frameTop);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        labPortName = new QLabel(frameTop);
        labPortName->setObjectName(QStringLiteral("labPortName"));

        gridLayout_3->addWidget(labPortName, 0, 0, 1, 1);

        cboxPortName = new QComboBox(frameTop);
        cboxPortName->setObjectName(QStringLiteral("cboxPortName"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cboxPortName->sizePolicy().hasHeightForWidth());
        cboxPortName->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(cboxPortName, 0, 1, 1, 1);

        labBaudRate = new QLabel(frameTop);
        labBaudRate->setObjectName(QStringLiteral("labBaudRate"));

        gridLayout_3->addWidget(labBaudRate, 1, 0, 1, 1);

        cboxBaudRate = new QComboBox(frameTop);
        cboxBaudRate->setObjectName(QStringLiteral("cboxBaudRate"));
        sizePolicy.setHeightForWidth(cboxBaudRate->sizePolicy().hasHeightForWidth());
        cboxBaudRate->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(cboxBaudRate, 1, 1, 1, 1);

        labDataBit = new QLabel(frameTop);
        labDataBit->setObjectName(QStringLiteral("labDataBit"));

        gridLayout_3->addWidget(labDataBit, 2, 0, 1, 1);

        cboxDataBit = new QComboBox(frameTop);
        cboxDataBit->setObjectName(QStringLiteral("cboxDataBit"));
        sizePolicy.setHeightForWidth(cboxDataBit->sizePolicy().hasHeightForWidth());
        cboxDataBit->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(cboxDataBit, 2, 1, 1, 1);

        labParity = new QLabel(frameTop);
        labParity->setObjectName(QStringLiteral("labParity"));

        gridLayout_3->addWidget(labParity, 3, 0, 1, 1);

        cboxParity = new QComboBox(frameTop);
        cboxParity->setObjectName(QStringLiteral("cboxParity"));
        sizePolicy.setHeightForWidth(cboxParity->sizePolicy().hasHeightForWidth());
        cboxParity->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(cboxParity, 3, 1, 1, 1);

        labStopBit = new QLabel(frameTop);
        labStopBit->setObjectName(QStringLiteral("labStopBit"));

        gridLayout_3->addWidget(labStopBit, 4, 0, 1, 1);

        cboxStopBit = new QComboBox(frameTop);
        cboxStopBit->setObjectName(QStringLiteral("cboxStopBit"));
        sizePolicy.setHeightForWidth(cboxStopBit->sizePolicy().hasHeightForWidth());
        cboxStopBit->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(cboxStopBit, 4, 1, 1, 1);

        btnOpen = new QPushButton(frameTop);
        btnOpen->setObjectName(QStringLiteral("btnOpen"));

        gridLayout_3->addWidget(btnOpen, 5, 0, 1, 2);


        verticalLayout->addWidget(frameTop);

        tabWidget = new QTabWidget(widgetRight);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::South);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_5 = new QGridLayout(tab);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        ckHexSend = new QCheckBox(tab);
        ckHexSend->setObjectName(QStringLiteral("ckHexSend"));

        gridLayout_5->addWidget(ckHexSend, 0, 0, 1, 1);

        ckHexReceive = new QCheckBox(tab);
        ckHexReceive->setObjectName(QStringLiteral("ckHexReceive"));

        gridLayout_5->addWidget(ckHexReceive, 0, 1, 1, 1);

        ckDebug = new QCheckBox(tab);
        ckDebug->setObjectName(QStringLiteral("ckDebug"));

        gridLayout_5->addWidget(ckDebug, 1, 0, 1, 1);

        ckAutoClear = new QCheckBox(tab);
        ckAutoClear->setObjectName(QStringLiteral("ckAutoClear"));

        gridLayout_5->addWidget(ckAutoClear, 1, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        ckAutoSend = new QCheckBox(tab);
        ckAutoSend->setObjectName(QStringLiteral("ckAutoSend"));

        gridLayout->addWidget(ckAutoSend, 0, 0, 1, 1);

        cboxSendInterval = new QComboBox(tab);
        cboxSendInterval->setObjectName(QStringLiteral("cboxSendInterval"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cboxSendInterval->sizePolicy().hasHeightForWidth());
        cboxSendInterval->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(cboxSendInterval, 0, 1, 1, 1);

        ckAutoSave = new QCheckBox(tab);
        ckAutoSave->setObjectName(QStringLiteral("ckAutoSave"));

        gridLayout->addWidget(ckAutoSave, 1, 0, 1, 1);

        cboxSaveInterval = new QComboBox(tab);
        cboxSaveInterval->setObjectName(QStringLiteral("cboxSaveInterval"));
        sizePolicy1.setHeightForWidth(cboxSaveInterval->sizePolicy().hasHeightForWidth());
        cboxSaveInterval->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(cboxSaveInterval, 1, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout, 2, 0, 1, 2);

        btnSendCount = new QPushButton(tab);
        btnSendCount->setObjectName(QStringLiteral("btnSendCount"));

        gridLayout_5->addWidget(btnSendCount, 3, 0, 1, 2);

        btnReceiveCount = new QPushButton(tab);
        btnReceiveCount->setObjectName(QStringLiteral("btnReceiveCount"));

        gridLayout_5->addWidget(btnReceiveCount, 4, 0, 1, 2);

        btnStopShow = new QPushButton(tab);
        btnStopShow->setObjectName(QStringLiteral("btnStopShow"));

        gridLayout_5->addWidget(btnStopShow, 5, 0, 1, 2);

        btnSave = new QPushButton(tab);
        btnSave->setObjectName(QStringLiteral("btnSave"));

        gridLayout_5->addWidget(btnSave, 6, 0, 1, 2);

        btnData = new QPushButton(tab);
        btnData->setObjectName(QStringLiteral("btnData"));

        gridLayout_5->addWidget(btnData, 7, 0, 1, 2);

        btnClear = new QPushButton(tab);
        btnClear->setObjectName(QStringLiteral("btnClear"));

        gridLayout_5->addWidget(btnClear, 8, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer, 9, 0, 1, 2);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_2 = new QGridLayout(tab_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        labListenPort = new QLabel(tab_2);
        labListenPort->setObjectName(QStringLiteral("labListenPort"));

        gridLayout_4->addWidget(labListenPort, 3, 0, 1, 1);

        labServerIP = new QLabel(tab_2);
        labServerIP->setObjectName(QStringLiteral("labServerIP"));

        gridLayout_4->addWidget(labServerIP, 1, 0, 1, 1);

        cboxSleepTime = new QComboBox(tab_2);
        cboxSleepTime->setObjectName(QStringLiteral("cboxSleepTime"));

        gridLayout_4->addWidget(cboxSleepTime, 4, 1, 1, 1);

        txtServerIP = new QLineEdit(tab_2);
        txtServerIP->setObjectName(QStringLiteral("txtServerIP"));

        gridLayout_4->addWidget(txtServerIP, 1, 1, 1, 1);

        labServerPort = new QLabel(tab_2);
        labServerPort->setObjectName(QStringLiteral("labServerPort"));

        gridLayout_4->addWidget(labServerPort, 2, 0, 1, 1);

        txtServerPort = new QLineEdit(tab_2);
        txtServerPort->setObjectName(QStringLiteral("txtServerPort"));

        gridLayout_4->addWidget(txtServerPort, 2, 1, 1, 1);

        labSleepTime = new QLabel(tab_2);
        labSleepTime->setObjectName(QStringLiteral("labSleepTime"));

        gridLayout_4->addWidget(labSleepTime, 4, 0, 1, 1);

        txtListenPort = new QLineEdit(tab_2);
        txtListenPort->setObjectName(QStringLiteral("txtListenPort"));

        gridLayout_4->addWidget(txtListenPort, 3, 1, 1, 1);

        labMode = new QLabel(tab_2);
        labMode->setObjectName(QStringLiteral("labMode"));

        gridLayout_4->addWidget(labMode, 0, 0, 1, 1);

        cboxMode = new QComboBox(tab_2);
        cboxMode->setObjectName(QStringLiteral("cboxMode"));

        gridLayout_4->addWidget(cboxMode, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout_4, 0, 0, 1, 2);

        btnStart = new QPushButton(tab_2);
        btnStart->setObjectName(QStringLiteral("btnStart"));

        gridLayout_2->addWidget(btnStart, 2, 0, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 59, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 3, 0, 1, 2);

        ckAutoConnect = new QCheckBox(tab_2);
        ckAutoConnect->setObjectName(QStringLiteral("ckAutoConnect"));

        gridLayout_2->addWidget(ckAutoConnect, 1, 0, 1, 2);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);


        gridLayout_6->addWidget(widgetRight, 0, 1, 2, 1);

        widget = new QWidget(frmComTool);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        cboxData = new QComboBox(widget);
        cboxData->setObjectName(QStringLiteral("cboxData"));
        QSizePolicy sizePolicy2(QSizePolicy::Ignored, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cboxData->sizePolicy().hasHeightForWidth());
        cboxData->setSizePolicy(sizePolicy2);
        cboxData->setEditable(true);
        cboxData->setDuplicatesEnabled(false);

        horizontalLayout->addWidget(cboxData);

        btnSend = new QPushButton(widget);
        btnSend->setObjectName(QStringLiteral("btnSend"));
        btnSend->setMinimumSize(QSize(80, 0));
        btnSend->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(btnSend);


        gridLayout_6->addWidget(widget, 1, 0, 1, 1);


        retranslateUi(frmComTool);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(frmComTool);
    } // setupUi

    void retranslateUi(QWidget *frmComTool)
    {
        labPortName->setText(QApplication::translate("frmComTool", "\344\270\262\345\217\243\345\217\267", Q_NULLPTR));
        labBaudRate->setText(QApplication::translate("frmComTool", "\346\263\242\347\211\271\347\216\207", Q_NULLPTR));
        labDataBit->setText(QApplication::translate("frmComTool", "\346\225\260\346\215\256\344\275\215", Q_NULLPTR));
        labParity->setText(QApplication::translate("frmComTool", "\346\240\241\351\252\214\344\275\215", Q_NULLPTR));
        labStopBit->setText(QApplication::translate("frmComTool", "\345\201\234\346\255\242\344\275\215", Q_NULLPTR));
        btnOpen->setText(QApplication::translate("frmComTool", "\346\211\223\345\274\200\344\270\262\345\217\243", Q_NULLPTR));
        ckHexSend->setText(QApplication::translate("frmComTool", "Hex\345\217\221\351\200\201", Q_NULLPTR));
        ckHexReceive->setText(QApplication::translate("frmComTool", "Hex\346\216\245\346\224\266", Q_NULLPTR));
        ckDebug->setText(QApplication::translate("frmComTool", "\346\250\241\346\213\237\350\256\276\345\244\207", Q_NULLPTR));
        ckAutoClear->setText(QApplication::translate("frmComTool", "\350\207\252\345\212\250\346\270\205\347\251\272", Q_NULLPTR));
        ckAutoSend->setText(QApplication::translate("frmComTool", "\350\207\252\345\212\250\345\217\221\351\200\201", Q_NULLPTR));
        ckAutoSave->setText(QApplication::translate("frmComTool", "\350\207\252\345\212\250\344\277\235\345\255\230", Q_NULLPTR));
        btnSendCount->setText(QApplication::translate("frmComTool", "\345\217\221\351\200\201 : 0 \345\255\227\350\212\202", Q_NULLPTR));
        btnReceiveCount->setText(QApplication::translate("frmComTool", "\346\216\245\346\224\266 : 0 \345\255\227\350\212\202", Q_NULLPTR));
        btnStopShow->setText(QApplication::translate("frmComTool", "\345\201\234\346\255\242\346\230\276\347\244\272", Q_NULLPTR));
        btnSave->setText(QApplication::translate("frmComTool", "\344\277\235\345\255\230\346\225\260\346\215\256", Q_NULLPTR));
        btnData->setText(QApplication::translate("frmComTool", "\347\256\241\347\220\206\346\225\260\346\215\256", Q_NULLPTR));
        btnClear->setText(QApplication::translate("frmComTool", "\346\270\205\347\251\272\346\225\260\346\215\256", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("frmComTool", "\344\270\262\345\217\243\351\205\215\347\275\256", Q_NULLPTR));
        labListenPort->setText(QApplication::translate("frmComTool", "\347\233\221\345\220\254\347\253\257\345\217\243", Q_NULLPTR));
        labServerIP->setText(QApplication::translate("frmComTool", "\350\277\234\347\250\213\345\234\260\345\235\200", Q_NULLPTR));
        txtServerIP->setText(QString());
        labServerPort->setText(QApplication::translate("frmComTool", "\350\277\234\347\250\213\347\253\257\345\217\243", Q_NULLPTR));
        txtServerPort->setText(QString());
        labSleepTime->setText(QApplication::translate("frmComTool", "\345\273\266\346\227\266\346\227\266\351\227\264", Q_NULLPTR));
        labMode->setText(QApplication::translate("frmComTool", "\350\275\254\346\215\242\346\250\241\345\274\217", Q_NULLPTR));
        cboxMode->clear();
        cboxMode->insertItems(0, QStringList()
         << QApplication::translate("frmComTool", "Tcp_Client", Q_NULLPTR)
         << QApplication::translate("frmComTool", "Tcp_Server", Q_NULLPTR)
         << QApplication::translate("frmComTool", "Udp_Client", Q_NULLPTR)
         << QApplication::translate("frmComTool", "Udp_Server", Q_NULLPTR)
        );
        btnStart->setText(QApplication::translate("frmComTool", "\345\220\257\345\212\250", Q_NULLPTR));
        ckAutoConnect->setText(QApplication::translate("frmComTool", "\350\207\252\345\212\250\351\207\215\350\277\236\347\275\221\347\273\234", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("frmComTool", "\347\275\221\347\273\234\351\205\215\347\275\256", Q_NULLPTR));
        btnSend->setText(QApplication::translate("frmComTool", "\345\217\221\351\200\201", Q_NULLPTR));
        Q_UNUSED(frmComTool);
    } // retranslateUi

};

namespace Ui {
    class frmComTool: public Ui_frmComTool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMCOMTOOL_H
