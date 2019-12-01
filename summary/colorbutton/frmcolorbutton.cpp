#pragma execution_character_set("utf-8")

#include "frmcolorbutton.h"
#include "ui_frmcolorbutton.h"
#include "qfontdatabase.h"
#include "qdebug.h"

frmColorButton::frmColorButton(QWidget *parent) : QWidget(parent), ui(new Ui::frmColorButton)
{
    ui->setupUi(this);
    this->initForm();
}

frmColorButton::~frmColorButton()
{
    delete ui;
}

void frmColorButton::initForm()
{
    ui->colorButton1->setTextAlign(ColorButton::TextAlign_Center_Center);
    ui->colorButton1->setText("Groups\nWorkspace");
    ui->colorButton1->setNormalColor(QColor("#C62F2F"));
    ui->colorButton1->setBorderColor(QColor(255, 107, 107));

    ui->colorButton2->setText("Groups\nWorkspace");
    ui->colorButton2->setColorMode(ColorButton::ColorMode_Replace);
    ui->colorButton2->setBorderColor(QColor(180, 180, 180));

    ui->colorButton3->setText("Workspace");
    ui->colorButton3->setColorMode(ColorButton::ColorMode_Shade);
    ui->colorButton3->setBorderColor(QColor(180, 180, 180));
    ui->colorButton3->setNormalColor(QColor("#2BB669"));
    ui->colorButton3->setPressedColor(QColor("#159C77"));
    ui->colorButton3->setBorderColor(QColor("#1D9E74"));

    ui->colorButton4->setText("Workspace");
    ui->colorButton4->setColorMode(ColorButton::ColorMode_Shade);
    ui->colorButton4->setBorderColor(QColor(100, 100, 100));
    ui->colorButton4->setBorderWidth(2);
    ui->colorButton4->setBorderRadius(5);

    ui->colorButton5->setText("Position");
    ui->colorButton5->setColorMode(ColorButton::ColorMode_Replace);
    ui->colorButton5->setBorderColor(QColor(200, 200, 200));
    ui->colorButton5->setNormalColor(QColor("#2BB669"));
    ui->colorButton5->setPressedColor(QColor("#159C77"));
    ui->colorButton5->setBorderColor(QColor("#1D9E74"));
    ui->colorButton5->setShowSuperText(true);
    ui->colorButton5->setSuperText("5");

    ui->colorButton6->setText("Palete\n10");
    ui->colorButton7->setText("Group\n17");
    ui->colorButton8->setText("201");
    ui->colorButton8->setTextAlign(ColorButton::TextAlign_Top_Center);
    ui->colorButton9->setText("202");
    ui->colorButton9->setTextAlign(ColorButton::TextAlign_Bottom_Center);
    ui->colorButton10->setText("1/500");

    QFont textFont;
    textFont.setPixelSize(25);
    textFont.setBold(true);
    ui->colorButton10->setTextFont(textFont);
    ui->colorButton10->setTextAlign(ColorButton::TextAlign_Center_Center);

    //判断图形字体是否存在,不存在则加入
    QFontDatabase fontDb;
    if (!fontDb.families().contains("FontAwesome")) {
        int fontId = fontDb.addApplicationFont(":/image/fontawesome-webfont.ttf");
        QStringList fontName = fontDb.applicationFontFamilies(fontId);
        if (fontName.count() == 0) {
            qDebug() << "load fontawesome-webfont.ttf error";
        }
    }

    if (fontDb.families().contains("FontAwesome")) {
        iconFont = QFont("FontAwesome");
#if (QT_VERSION >= QT_VERSION_CHECK(4,8,0))
        iconFont.setHintingPreference(QFont::PreferNoHinting);
#endif
    }

    iconFont.setPixelSize(45);

    ui->colorButton11->setTextFont(iconFont);
    ui->colorButton11->setText(QChar(0xf100));
    ui->colorButton11->setTextColor(QColor("#F4B634"));

    ui->colorButton12->setTextFont(iconFont);
    ui->colorButton12->setText(QChar(0xf101));
    ui->colorButton12->setTextColor(QColor("#F4B634"));

    ui->colorButton13->setTextFont(iconFont);
    ui->colorButton13->setText(QChar(0xf102));
    ui->colorButton13->setTextColor(QColor("#F4B634"));

    ui->colorButton14->setTextFont(iconFont);
    ui->colorButton14->setText(QChar(0xf103));
    ui->colorButton14->setTextColor(QColor("#F4B634"));

    ui->colorButton15->setTextFont(iconFont);
    ui->colorButton15->setText(QChar(0xf085));
    ui->colorButton15->setTextColor(QColor("#F4B634"));

#if 0
    //设置为图片
    QPixmap pix = IconHelper::Instance()->getPixmap("#FF0000", 0xf205, 20, 40, 30);
    QImage bgImage = pix.toImage();
    ui->colorButton15->setBgImage(bgImage);
#endif

    QFont font1;
    font1.setPointSize(8);
    QFont font2;
    font2.setPointSize(11);
    font2.setBold(true);

    ui->colorButton16->setSuperTextAlign(ColorButton::TextAlign_Top_Left);
    ui->colorButton16->setShowSuperText(true);
    ui->colorButton16->setSuperTextFont(font1);
    ui->colorButton16->setSuperText("1");
    ui->colorButton16->setTextFont(font2);
    ui->colorButton16->setText("演出秀1");

    ui->colorButton17->setSuperTextAlign(ColorButton::TextAlign_Top_Center);
    ui->colorButton17->setShowSuperText(true);
    ui->colorButton17->setSuperTextFont(font1);
    ui->colorButton17->setSuperText("2");
    ui->colorButton17->setTextFont(font2);
    ui->colorButton17->setText("演出秀2");

    ui->colorButton18->setSuperTextAlign(ColorButton::TextAlign_Top_Right);
    ui->colorButton18->setShowSuperText(true);
    ui->colorButton18->setSuperTextFont(font1);
    ui->colorButton18->setSuperText("3");
    ui->colorButton18->setTextFont(font2);
    ui->colorButton18->setText("演出秀3");

    ui->colorButton19->setSuperTextAlign(ColorButton::TextAlign_Bottom_Left);
    ui->colorButton19->setShowSuperText(true);
    ui->colorButton19->setSuperTextFont(font1);
    ui->colorButton19->setSuperText("4");
    ui->colorButton19->setTextFont(font2);
    ui->colorButton19->setText("演出秀4");

    ui->colorButton20->setSuperTextAlign(ColorButton::TextAlign_Bottom_Right);
    ui->colorButton20->setShowSuperText(true);
    ui->colorButton20->setSuperTextFont(font1);
    ui->colorButton20->setSuperText("5");
    ui->colorButton20->setTextFont(font2);
    ui->colorButton20->setText("演出秀5");

    ui->colorButton21->setNormalColor(QColor("#16A085"));
    ui->colorButton21->setBorderColor(ui->colorButton21->getNormalColor().light(90));
    ui->colorButton22->setNormalColor(QColor("#2980B9"));
    ui->colorButton22->setBorderColor(ui->colorButton22->getNormalColor().light(90));
    ui->colorButton23->setNormalColor(QColor("#8E44AD"));
    ui->colorButton23->setBorderColor(ui->colorButton23->getNormalColor().light(90));
    ui->colorButton24->setNormalColor(QColor("#2C3E50"));
    ui->colorButton24->setBorderColor(ui->colorButton24->getNormalColor().light(90));
    ui->colorButton25->setNormalColor(QColor("#D35400"));
    ui->colorButton25->setBorderColor(ui->colorButton25->getNormalColor().light(90));
}
