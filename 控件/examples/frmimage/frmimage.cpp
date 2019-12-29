#include "frmimage.h"
#include "ui_frmimage.h"

#include "frmadswidget.h"
#include "frmadswidget2.h"
#include "frmanimationbutton.h"
#include "frmbuttondefence.h"
#include "frmimageanimation.h"
#include "frmimageswitch.h"
#include "frmimageview.h"
#include "frmimagecalendar.h"
#include "frmimagepower.h"
#include "frmimageclock.h"
#include "frmimagepilot.h"

frmImage::frmImage(QWidget *parent) : QWidget(parent), ui(new Ui::frmImage)
{
    ui->setupUi(this);
    this->initForm();
}

frmImage::~frmImage()
{
    delete ui;
}

void frmImage::initForm()
{
    ui->stackedWidget->addWidget(new frmAdsWidget);
    ui->stackedWidget->addWidget(new frmAdsWidget2);
    ui->stackedWidget->addWidget(new frmAnimationButton );
    ui->stackedWidget->addWidget(new frmButtonDefence);
    ui->stackedWidget->addWidget(new frmImageAnimation);
    ui->stackedWidget->addWidget(new frmImageSwitch);
    ui->stackedWidget->addWidget(new frmImageView);
    ui->stackedWidget->addWidget(new frmImageCalendar);
    ui->stackedWidget->addWidget(new frmImagePower);
    ui->stackedWidget->addWidget(new frmImageClock);
    ui->stackedWidget->addWidget(new frmImagePilot);
}

void frmImage::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
