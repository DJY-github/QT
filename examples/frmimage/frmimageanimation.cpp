#pragma execution_character_set("utf-8")

#include "frmimageanimation.h"
#include "ui_frmimageanimation.h"
#include "imageanimation.h"

frmImageAnimation::frmImageAnimation(QWidget *parent) : QWidget(parent), ui(new Ui::frmImageAnimation)
{
    ui->setupUi(this);
    this->initForm();
}

frmImageAnimation::~frmImageAnimation()
{
    delete ui;
}

void frmImageAnimation::showEvent(QShowEvent *)
{
    on_cboxType_activated(ui->cboxType->currentIndex());
}

void frmImageAnimation::resizeEvent(QResizeEvent *)
{
    if (this->isVisible()) {
        on_cboxType_activated(ui->cboxType->currentIndex());
    }
}

void frmImageAnimation::initForm()
{
    QStringList types;
    types << "渐变" << "百叶窗" << "从右向左翻转" << "从外到内水平分割" << "从左到右"
          << "从右到左" << "从下到上" << "从上到下" << "从右下到左上";
    ui->cboxType->addItems(types);
}

void frmImageAnimation::on_cboxType_activated(int index)
{
    //以下两种方式二选一
    QString imageName1 = ":/image/liuyifei.jpg";
    QString imageName2 = ":/image/liuyifei2.jpg";
#if 1
    ui->imageAnimation->setImageName1(imageName1);
    ui->imageAnimation->setImageName2(imageName2);
#else
    ui->imageAnimation->setPixmap1(QPixmap(imageName1));
    ui->imageAnimation->setPixmap2(QPixmap(imageName2));
#endif

    ui->imageAnimation->setAnimationType((ImageAnimation::AnimationType)index);
    ui->imageAnimation->start();
}
