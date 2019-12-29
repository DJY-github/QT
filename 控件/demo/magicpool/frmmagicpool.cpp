#include "frmmagicpool.h"
#include "ui_frmmagicpool.h"

frmMagicPool::frmMagicPool(QWidget *parent) : QWidget(parent), ui(new Ui::frmMagicPool)
{
    ui->setupUi(this);
}

frmMagicPool::~frmMagicPool()
{
    delete ui;
}
