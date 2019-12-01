#pragma execution_character_set("utf-8")

#include "frmgaugepanel.h"
#include "ui_frmgaugepanel.h"
#include "qdebug.h"

frmGaugePanel::frmGaugePanel(QWidget *parent) : QWidget(parent), ui(new Ui::frmGaugePanel)
{
    ui->setupUi(this);
    this->initForm();
}

frmGaugePanel::~frmGaugePanel()
{
    delete ui;
}

void frmGaugePanel::initForm()
{
#if 0
    ui->horizontalSlider1->setVisible(false);
    ui->horizontalSlider2->setVisible(false);
    ui->horizontalSlider3->setVisible(false);
    ui->horizontalSlider4->setVisible(false);
    ui->horizontalSlider5->setVisible(false);
    ui->horizontalSlider6->setVisible(false);
#endif

    //设置样式
    QStringList list;
    list.append("#widget{background:#222939;}");
    list.append("GaugePanel{qproperty-ringColor:#393F4D;qproperty-scaleColor:#03B7C9;"
                "qproperty-pointerColor:#03B7C9;qproperty-textColor:#EEEEEE;}");
    ui->widget->setStyleSheet(list.join(""));

    //设置单位
    ui->gaugePanel1->setUnit("V");
    ui->gaugePanel2->setUnit("A");
    ui->gaugePanel3->setUnit("m");
    ui->gaugePanel4->setUnit("kW");
    ui->gaugePanel5->setUnit("kWh");
    ui->gaugePanel6->setUnit("Hz");

    //设置名称
    ui->gaugePanel1->setText("电压");
    ui->gaugePanel2->setText("电流");
    ui->gaugePanel3->setText("水位");
    ui->gaugePanel4->setText("有功功率");
    ui->gaugePanel5->setText("有功电能");
    ui->gaugePanel6->setText("电网频率");

    //设置小数点
    ui->gaugePanel3->setPrecision(1);
    ui->gaugePanel4->setPrecision(2);
    ui->gaugePanel5->setPrecision(1);
    ui->gaugePanel3->setScalePrecision(1);

    //设置启用动画
    ui->gaugePanel4->setAnimation(true);
    ui->gaugePanel5->setAnimation(true);
    ui->gaugePanel5->setAnimationStep(0.2);

    //设置范围值
    ui->gaugePanel1->setRange(0, 500);
    ui->gaugePanel2->setRange(0, 60);
    ui->gaugePanel3->setRange(0, 2);
    ui->gaugePanel4->setRange(0, 50);
    ui->gaugePanel5->setRange(0, 70);
    ui->gaugePanel6->setRange(0, 100);

    ui->horizontalSlider1->setRange(0, 500);
    ui->horizontalSlider2->setRange(0, 60);
    ui->horizontalSlider3->setRange(0, 200);
    ui->horizontalSlider4->setRange(0, 50);
    ui->horizontalSlider5->setRange(0, 70);
    ui->horizontalSlider6->setRange(0, 100);

    //绑定滑块
    connect(ui->horizontalSlider1, SIGNAL(valueChanged(int)), ui->gaugePanel1, SLOT(setValue(int)));
    connect(ui->horizontalSlider2, SIGNAL(valueChanged(int)), ui->gaugePanel2, SLOT(setValue(int)));
    //connect(ui->horizontalSlider3, SIGNAL(valueChanged(int)), ui->gaugePanel3, SLOT(setValue(int)));
    connect(ui->horizontalSlider4, SIGNAL(valueChanged(int)), ui->gaugePanel4, SLOT(setValue(int)));
    connect(ui->horizontalSlider5, SIGNAL(valueChanged(int)), ui->gaugePanel5, SLOT(setValue(int)));
    connect(ui->horizontalSlider6, SIGNAL(valueChanged(int)), ui->gaugePanel6, SLOT(setValue(int)));

    //设置初始值
    ui->horizontalSlider1->setValue(220);
    ui->horizontalSlider2->setValue(32);
    ui->horizontalSlider3->setValue(150);
    ui->horizontalSlider4->setValue(6.34);
    ui->horizontalSlider5->setValue(6.28);
    ui->horizontalSlider6->setValue(50);
}

void frmGaugePanel::on_horizontalSlider3_valueChanged(int value)
{
    double v = (double)value / 100;
    ui->gaugePanel3->setValue(v);
}
