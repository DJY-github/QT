#include "frmxlistwidgetvs.h"
#include "ui_frmxlistwidgetvs.h"

frmXListWidgetVS::frmXListWidgetVS(QWidget *parent) : QWidget(parent), ui(new Ui::frmXListWidgetVS)
{
    ui->setupUi(this);
    ui->xlistWidgetVS->setItemCount(100);
}

frmXListWidgetVS::~frmXListWidgetVS()
{
    delete ui;
}
