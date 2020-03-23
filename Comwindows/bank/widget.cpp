#include "widget.h"
#include "worker_log.h"
#include "worker_init.h"
#include "ui_widget.h"
#include "ui_logging.h"
#include <QDebug>

Widget::Widget(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //qDebug()<<QSound::isAvailable();
    //sound = new QSound("../client/tiankong.wav", this);
    //sound->setLoops(-1);
  //  sound->play();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_Exit_clicked()
{
    this->close();
    //sound->stop();
}

void Widget::on_log_worker_clicked()
{
    this->close();
    work_log m(this);
    m.work_ui.Yesorno->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    m.work_ui.Yesorno->button(QDialogButtonBox::Ok)->setText(tr("ȷ��"));                     //��buttonbox�е�ok ��ɺ���
    m.work_ui.Yesorno->button(QDialogButtonBox::Cancel)->setText(tr("ȡ��"));
    m.work_ui.passward->setEchoMode(QLineEdit::Password);                   //���뷽ʽ��ʾ�ı�
    m.show();
    m.exec();
}

void Widget::on_init_worker_clicked()
{
    this->close();
    work_init m(this);
    m.Init_ui.yesorno->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    m.Init_ui.yesorno->button(QDialogButtonBox::Ok)->setText(tr("ȷ��"));
    m.Init_ui.yesorno->button(QDialogButtonBox::Cancel)->setText(tr("ȡ��"));
    m.Init_ui.passward->setEchoMode(QLineEdit::Password);                   //���뷽ʽ��ʾ�ı�
    m.show();
    m.exec();
}
