#pragma execution_character_set("utf-8")

#include "frmtiledbg.h"
#include "ui_frmtiledbg.h"

frmTiledBg::frmTiledBg(QWidget *parent) : QWidget(parent), ui(new Ui::frmTiledBg)
{
    ui->setupUi(this);
    this->initForm();
}

frmTiledBg::~frmTiledBg()
{
    delete ui;
}

void frmTiledBg::initForm()
{
    ui->tiledBg1->setColor2(QColor(166, 193, 215));
    ui->tiledBg2->setColor2(QColor(34, 163, 169, 150));
    ui->tiledBg3->setColor2(QColor(214, 77, 84, 150));
    ui->tiledBg4->setColor2(QColor(0, 177, 125, 150));
}
