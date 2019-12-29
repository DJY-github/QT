#pragma execution_character_set("utf-8")

#include "frmanimationbutton.h"
#include "ui_frmanimationbutton.h"

frmAnimationButton::frmAnimationButton(QWidget *parent) : QWidget(parent), ui(new Ui::frmAnimationButton)
{
    ui->setupUi(this);
    this->initForm();
}

frmAnimationButton::~frmAnimationButton()
{
    delete ui;
}

void frmAnimationButton::initForm()
{
    ui->animationButton1->setImageName(":/image/v-home-ico-contact.png");
    ui->animationButton2->setImageName(":/image/v-home-ico-home.png");
    ui->animationButton3->setImageName(":/image/v-home-ico-img.png");

    ui->animationButton4->setNormalImage(":/image/clean.png");
    ui->animationButton4->setEnterImage(":/image/clean_enter.png");
    ui->animationButton4->setLeaveImage(":/image/clean_leave.png");

    ui->animationButton5->setNormalImage(":/image/safe.png");
    ui->animationButton5->setEnterImage(":/image/safe_enter.png");
    ui->animationButton5->setLeaveImage(":/image/safe_leave.png");

    ui->animationButton6->setNormalImage(":/image/youhua.png");
    ui->animationButton6->setEnterImage(":/image/youhua_enter.png");
    ui->animationButton6->setLeaveImage(":/image/youhua_leave.png");
}
