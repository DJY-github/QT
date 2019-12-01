#include "frmcolor.h"
#include "ui_frmcolor.h"

#include "frmcolorpanel.h"
#include "frmcolorpanelbtn.h"
#include "frmcolorpanelfader.h"
#include "frmcolorpanelhsb.h"
#include "frmcolorbutton.h"
#include "frmcombobox.h"
#include "frmcolorstyle.h"

frmColor::frmColor(QWidget *parent) : QWidget(parent), ui(new Ui::frmColor)
{
    ui->setupUi(this);
    this->initForm();
}

frmColor::~frmColor()
{
    delete ui;
}

void frmColor::initForm()
{
    ui->stackedWidget->addWidget(new frmColorPanel);
    ui->stackedWidget->addWidget(new frmColorPanelBtn);
    ui->stackedWidget->addWidget(new frmColorPanelFader);
    ui->stackedWidget->addWidget(new frmColorPanelHSB);
    ui->stackedWidget->addWidget(new frmColorButton);    
    ui->stackedWidget->addWidget(new frmComboBox);
    ui->stackedWidget->addWidget(new frmColorStyle);
}

void frmColor::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
