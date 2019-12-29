#include "frmxlistwidgetvt.h"
#include "ui_frmxlistwidgetvt.h"

frmXListWidgetVT::frmXListWidgetVT(QWidget *parent) : QWidget(parent), ui(new Ui::frmXListWidgetVT)
{
    ui->setupUi(this);
    ui->xlistWidgetVT->setItemCount(100);
}

frmXListWidgetVT::~frmXListWidgetVT()
{
    delete ui;
}
