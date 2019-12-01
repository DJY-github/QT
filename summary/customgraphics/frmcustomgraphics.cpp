#include "frmcustomgraphics.h"
#include "ui_frmcustomgraphics.h"

frmCustomGraphics::frmCustomGraphics(QWidget *parent) : QWidget(parent), ui(new Ui::frmCustomGraphics)
{
    ui->setupUi(this);    
}

frmCustomGraphics::~frmCustomGraphics()
{
    delete ui;
}
