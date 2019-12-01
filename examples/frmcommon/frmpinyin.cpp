#pragma execution_character_set("utf-8")

#include "frmpinyin.h"
#include "ui_frmpinyin.h"
#include "pinyin.h"

frmPinYin::frmPinYin(QWidget *parent) : QWidget(parent), ui(new Ui::frmPinYin)
{
    ui->setupUi(this);

    ui->txtChinese->setText("飞扬青云 QQ:517216493");
    PinYin::Instance()->initPath(":/image");
    on_btn3_clicked();
}

frmPinYin::~frmPinYin()
{
    delete ui;
}

void frmPinYin::on_btn1_clicked()
{
    QString result = PinYin::Instance()->getFanTi(ui->txtChinese->toPlainText());
    ui->txtResult->setPlainText(result);
}

void frmPinYin::on_btn2_clicked()
{
    QString result = PinYin::Instance()->getJianTi(ui->txtChinese->toPlainText());
    ui->txtResult->setPlainText(result);
}

void frmPinYin::on_btn3_clicked()
{
    PinYin::Format format;
    if (ui->rbtn1->isChecked()) {
        format = PinYin::Format_None;
    } else if (ui->rbtn2->isChecked()) {
        format = PinYin::Format_Tone;
    } else if (ui->rbtn3->isChecked()) {
        format = PinYin::Format_Number;
    }

    QStringList results;
    QStringList txts = ui->txtChinese->toPlainText().split("\n");
    foreach (QString str, txts) {
        str = str.trimmed();
        results << PinYin::Instance()->getPinYin(str, " ", format);
    }

    ui->txtResult->setPlainText(results.join(""));
}
