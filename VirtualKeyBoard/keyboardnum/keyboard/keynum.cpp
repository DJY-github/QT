#include "keynum.h"
#include "ui_keynum.h"

Keynum::Keynum(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Keynum)
{
    ui->setupUi(this);
}

Keynum::~Keynum()
{
    delete ui;
}
