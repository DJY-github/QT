#include "frmprogress.h"
#include "ui_frmprogress.h"

#include "frmprogresswater.h"
#include "frmprogresscolor.h"
#include "frmprogresspercent.h"
#include "frmprogressround.h"
#include "frmprogresswait.h"
#include "frmprogressbutton.h"
#include "frmprogressthree.h"
#include "frmprogressplay.h"
#include "frmprogressring.h"

frmProgress::frmProgress(QWidget *parent) : QWidget(parent), ui(new Ui::frmProgress)
{
    ui->setupUi(this);
    this->initForm();
}

frmProgress::~frmProgress()
{
    delete ui;
}

void frmProgress::initForm()
{
    ui->stackedWidget->addWidget(new frmProgressWater);
    ui->stackedWidget->addWidget(new frmProgressPercent);
    ui->stackedWidget->addWidget(new frmProgressRound);
    ui->stackedWidget->addWidget(new frmProgressWait);
    ui->stackedWidget->addWidget(new frmProgressColor);
    ui->stackedWidget->addWidget(new frmProgressButton);
    ui->stackedWidget->addWidget(new frmProgressThree);
    ui->stackedWidget->addWidget(new frmProgressPlay);
    ui->stackedWidget->addWidget(new frmProgressRing);
}

void frmProgress::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
