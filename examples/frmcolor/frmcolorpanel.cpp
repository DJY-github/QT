#pragma execution_character_set("utf-8")

#include "frmcolorpanel.h"
#include "ui_frmcolorpanel.h"

frmColorPanel::frmColorPanel(QWidget *parent) : QWidget(parent), ui(new Ui::frmColorPanel)
{
    ui->setupUi(this);
    this->initForm();
}

frmColorPanel::~frmColorPanel()
{
    delete ui;
}

void frmColorPanel::initForm()
{
    ui->btnHue->setBorderColor(Qt::darkGray);
    ui->btnSat->setBorderColor(Qt::darkGray);
    ui->btnBright->setBorderColor(Qt::darkGray);
    ui->btnHue->setNormalColor(QColor(Qt::darkGray).light(20));
    ui->btnSat->setNormalColor(QColor(Qt::darkGray).light(20));
    ui->btnBright->setNormalColor(QColor(Qt::darkGray).light(20));

    ui->btnCyan->setBorderColor(Qt::cyan);
    ui->btnMagenta->setBorderColor(Qt::magenta);
    ui->btnYellow->setBorderColor(Qt::yellow);
    ui->btnCyan->setNormalColor(QColor(Qt::cyan).light(50));
    ui->btnMagenta->setNormalColor(QColor(Qt::magenta).light(50));
    ui->btnYellow->setNormalColor(QColor(Qt::yellow).light(50));

    ui->btnRed->setBorderColor(Qt::red);
    ui->btnGreen->setBorderColor(Qt::green);
    ui->btnBlue->setBorderColor(Qt::blue);
    ui->btnRed->setNormalColor(QColor(Qt::red).light(50));
    ui->btnGreen->setNormalColor(QColor(Qt::green).light(50));
    ui->btnBlue->setNormalColor(QColor(Qt::blue).light(50));

    ui->btnPanelFader->setText("颜色滑块面板");
    ui->btnPanelHSB->setText("颜色选取面板");
    ui->btnPanelBtn->setText("颜色按钮面板");

    ui->btnPanelFader->setNormalColor("#16A085");
    ui->btnPanelHSB->setNormalColor("#C0392B");
    ui->btnPanelBtn->setNormalColor("#27AE60");

    QFont font;
    font.setPixelSize(15);
    font.setBold(true);
    ui->btnPanelFader->setTextFont(font);
    ui->btnPanelHSB->setTextFont(font);
    ui->btnPanelBtn->setTextFont(font);

    connect(ui->colorPanelFader, SIGNAL(colorChanged(QColor, double, double, double)),
            this, SLOT(colorChangedFader(QColor, double, double, double)));
    connect(ui->colorPanelHSB, SIGNAL(colorChanged(QColor, double, double)),
            this, SLOT(colorChangedHSB(QColor, double, double)));
    connect(ui->colorPanelBar, SIGNAL(colorChanged(QColor, double, double)),
            this, SLOT(colorChangedBar(QColor, double, double)));
    connect(ui->colorPanelBtn, SIGNAL(colorChanged(QColor)),
            this, SLOT(colorChangedBtn(QColor)));

    ui->widgetColor->setEnabled(false);
    ui->stackedWidget->setCurrentIndex(1);
    ui->colorPanelBar->setStaticMode(false);
    colorChangedBar(Qt::red, 0, 100);

    connect(ui->btnPanelFader, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->btnPanelHSB, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    connect(ui->btnPanelBtn, SIGNAL(clicked()), this, SLOT(buttonClicked()));
}

void frmColorPanel::colorChangedFader(const QColor &color, double hue, double sat, double bright)
{
    ui->btnHue->setText(QString("Hue\n%1").arg(QString::number(hue, 'f', 1)));
    ui->btnSat->setText(QString("Sat\n%1%").arg(QString::number(sat, 'f', 1)));
    ui->btnBright->setText(QString("Bright\n%1%").arg(QString::number(bright, 'f', 1)));

    setColor(color);
}

void frmColorPanel::colorChangedHSB(const QColor &color, double hue, double sat)
{
    ui->colorPanelBar->setTopColor(color);
    ui->colorPanelBar->setBorderColor(color);

    ui->btnHue->setText(QString("Hue\n%1").arg(QString::number(hue, 'f', 1)));
    ui->btnSat->setText(QString("Sat\n%1%").arg(QString::number(sat, 'f', 1)));
    ui->btnBright->setText(QString("Bright\n%1%").arg(QString::number(ui->colorPanelBar->getPercent(), 'f', 1)));

    QColor c = QColor::fromHsvF(hue / 360, sat / 100, ui->colorPanelBar->getPercent() / 100);
    setColor(c);
}

void frmColorPanel::colorChangedBar(const QColor &color, double value, double percent)
{
    if (ui->colorPanelHSB->isVisible()) {
        ui->colorPanelHSB->setPercent(percent);
    }

    double hue = color.hue();
    hue = hue < 0 ? 360 : hue;
    double sat = color.saturationF() * 100;

    if (!ui->colorPanelBar->isVisible()) {
        ui->btnHue->setText(QString("Hue\n%1").arg(QString::number(hue, 'f', 1)));
        ui->btnSat->setText(QString("Sat\n%1%").arg(QString::number(sat, 'f', 1)));
    }

    ui->btnBright->setText(QString("Bright\n%1%").arg(QString::number(percent, 'f', 1)));

    setColor(color);
}

void frmColorPanel::colorChangedBtn(const QColor &color)
{
    colorChangedBar(color, 0, 100);
}

void frmColorPanel::setColor(const QColor &color)
{
    int temp = (color.red() + color.green() + color.blue()) / 3;
    ui->labColor->setText(color.name().toUpper());
    ui->labColor->setStyleSheet(QString("QLabel{font:25px;color:%1;background:%2;}")
                                .arg(temp < 200 ? "#FEFEFE" : "#000000").arg(color.name()));

    double percentRed = color.redF() * 100;
    double percentGreen = color.greenF() * 100;
    double percentBlue = color.blueF() * 100;

    ui->btnCyan->setText(QString("Cyan\n%1%").arg(QString::number(100 - percentRed, 'f', 1)));
    ui->btnMagenta->setText(QString("Magenta\n%1%").arg(QString::number(100 - percentGreen, 'f', 1)));
    ui->btnYellow->setText(QString("Yellow\n%1%").arg(QString::number(100 - percentBlue, 'f', 1)));

    ui->btnRed->setText(QString("Red\n%1%").arg(QString::number(percentRed, 'f', 1)));
    ui->btnGreen->setText(QString("Green\n%1%").arg(QString::number(percentGreen, 'f', 1)));
    ui->btnBlue->setText(QString("Blue\n%1%").arg(QString::number(percentBlue, 'f', 1)));
}

void frmColorPanel::buttonClicked()
{
    ColorButton *btn = (ColorButton *)sender();
    if (btn == ui->btnPanelFader) {
        ui->stackedWidget->setCurrentIndex(0);
    } else if (btn == ui->btnPanelHSB) {
        ui->stackedWidget->setCurrentIndex(1);
    } else if (btn == ui->btnPanelBtn) {
        ui->stackedWidget->setCurrentIndex(2);
    }
}
