#include "frmcommon.h"
#include "ui_frmcommon.h"

#include "frmflatui.h"
#include "frmzhtopy.h"
#include "frmpinyin.h"
#include "frmntpclient.h"
#include "frmsavelog.h"
#include "frmsaveruntime.h"

//下面为没有类库的demo
#include "frmiptool.h"
#include "frmpngtool.h"
#include "frmtextwrite.h"
#include "frmcountcode.h"

frmCommon::frmCommon(QWidget *parent) : QWidget(parent), ui(new Ui::frmCommon)
{
    ui->setupUi(this);
    this->initForm();
}

frmCommon::~frmCommon()
{
    delete ui;
}

void frmCommon::initForm()
{
    ui->stackedWidget->addWidget(new frmFlatUI);
    ui->stackedWidget->addWidget(new frmZhToPY);
    ui->stackedWidget->addWidget(new frmPinYin);
    ui->stackedWidget->addWidget(new frmNtpClient);
    ui->stackedWidget->addWidget(new frmSaveLog);
    ui->stackedWidget->addWidget(new frmSaveRunTime);

    ui->stackedWidget->addWidget(new frmIPTool);
    ui->stackedWidget->addWidget(new frmPngTool);
    ui->stackedWidget->addWidget(new frmTextWrite);
    ui->stackedWidget->addWidget(new frmCountCode);
}

void frmCommon::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
