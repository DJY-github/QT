#pragma execution_character_set("utf-8")

#include "frmtextmovewidget.h"
#include "ui_frmtextmovewidget.h"

frmTextMoveWidget::frmTextMoveWidget(QWidget *parent) : QWidget(parent), ui(new Ui::frmTextMoveWidget)
{
    ui->setupUi(this);
    this->initForm();
}

frmTextMoveWidget::~frmTextMoveWidget()
{
    delete ui;
}

void frmTextMoveWidget::initForm()
{
    ui->textMoveWidget1->setTextSize(30);
    ui->textMoveWidget2->setTextSize(40);
    ui->textMoveWidget3->setTextSize(40);

    ui->textMoveWidget1->setText("今天天气真不错啊!中奖啦!");

    ui->textMoveWidget2->setInterval(15);
    ui->textMoveWidget2->setText("今天天气真不错啊!中奖啦!");
    ui->textMoveWidget2->setForeground(QColor(255, 107, 107));
    ui->textMoveWidget2->setMoveStyle(TextMoveWidget::MoveStyle_LeftToRight);

    ui->textMoveWidget3->setInterval(15);
    ui->textMoveWidget3->setMouseHoverStop(true);
    ui->textMoveWidget3->setText("中华人民共和国万岁!");
    ui->textMoveWidget3->setForeground(QColor(24, 189, 155));
    ui->textMoveWidget3->setMoveStyle(TextMoveWidget::MoveStyle_RightToLeft);
}
