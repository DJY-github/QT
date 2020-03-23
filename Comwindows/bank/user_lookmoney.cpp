#include "user_lookmoney.h"
#include "ui_user_lookmoney.h"
#include "widget.h"
#include <QMessageBox>
#include "deal_user.h"
#include <QProgressDialog>
#include "worker_log.h"

extern int yyy;
extern const QString IP;

user_lookmoney::user_lookmoney(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_lookmoney)
{
    blocksize = 0;
    ui->setupUi(this);
    this->ui->yesorno->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    this->ui->yesorno->button(QDialogButtonBox::Ok)->setText(tr("ȷ��"));          //��buttonbox�е�ok ��ɺ���
    this->ui->yesorno->button(QDialogButtonBox::Cancel)->setText(tr("ȡ��"));
    this->ui->user_passward1->setEchoMode(QLineEdit::Password);                   //���뷽ʽ��ʾ�ı�
    this->ui->user_passward2->setEchoMode(QLineEdit::Password);
}

user_lookmoney::~user_lookmoney()
{
    delete ui;
}

void user_lookmoney::on_close_music_clicked()
{
    Widget w;
    //w.sound->stop();
}

void user_lookmoney::on_yesorno_clicked(QAbstractButton *button)
{
    str.cmd = USER_LOOKMONEY;
    str.user_num = this->ui->user_num->text().toInt();
    str.user_id = this->ui->user_id->text();
    QString pass1, pass2;
    pass1 = this->ui->user_passward1->text();
    pass2 = this->ui->user_passward2->text();

    if(this->ui->yesorno->button(QDialogButtonBox::Ok) == button)           //�жϰ��µ��Ƿ�Ϊ"ȷ������ť
    {
        if(this->ui->user_num->text() == "" | this->ui->user_id->text() == "" | this->ui->user_passward1->text() == "" |
                this->ui->user_passward2->text() == "")
        {
            QMessageBox::warning(this, tr("����"), tr("���벻��Ϊ�գ�"), QMessageBox::Ok);
            return;
        }
        if(pass1 != pass2)
        {
            QMessageBox::warning(this, tr("����"), tr("��������������ٴ����룡"), QMessageBox::Ok);
            return;
        }
        str.user_passward = pass1;

        tcpsocket = new QTcpSocket(this);
        tcpsocket->abort();
        tcpsocket->connectToHost(IP, SERV_PORT);

        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_0);
        out<<(quint16)0;
        out<<str;
        out.device()->seek(0);
        out<<(quint16)(block.size()-sizeof(quint16));
        tcpsocket->write(block, block.length());

        connect(tcpsocket, SIGNAL(readyRead()), this, SLOT(read_server()));

        QProgressDialog dialog(tr("���ڲ�ѯ���"),tr("ȡ��"), 0, 30000, this);
        dialog.setWindowTitle(tr("����"));
        dialog.setWindowModality(Qt::WindowModal);
        dialog.show();
        for(int k = 0; k < 30000; k++)
        {
            dialog.setValue(k);
            QCoreApplication::processEvents();
            if(dialog.wasCanceled())
            {
                break;
            }
        }
        dialog.setValue(30000);

        switch (message.cmd)
        {
            case LOOKMONEY_SUCCESS:
            {
                QString str0 = QString("�����������Ϊ%1Ԫ").arg(message.money);
                QMessageBox::information(this, tr("��Ϣ"), str0, QMessageBox::Ok);
                this->close();
                deal_user D(this);
                D.show();
                D.exec();
                break;
            }
            case ERROR:
            {
                QMessageBox::information(this, tr("��Ϣ"), tr("�˺����벻ƥ��!"), QMessageBox::Ok);
                this->close();
                deal_user D(this);
                D.show();
                D.exec();
                break;
            }
        }
    }
    else if(button == this->ui->yesorno->button((QDialogButtonBox::Cancel)))
    {
        this->close();

        QProgressDialog dialog(tr("���ڷ���������"),tr("ȡ��"), 0, 30000, this);
        dialog.setWindowTitle(tr("����"));
        dialog.setWindowModality(Qt::WindowModal);
        dialog.show();
        for(int k = 0; k < 30000; k++)
        {
            dialog.setValue(k);
            QCoreApplication::processEvents();
            if(dialog.wasCanceled())
            {
                break;
            }
        }
        dialog.setValue(30000);

        deal_user D(this);
        D.show();
        D.exec();
    }
}
void user_lookmoney::read_server()
{
    QDataStream in(tcpsocket);

    in.setVersion(QDataStream::Qt_4_6);                 //���ܴ���
    if(blocksize == 0)
    {
        if(tcpsocket->bytesAvailable() < (int)sizeof(quint16))
        {
            return;
        }
        in>>blocksize;
    }
    if(tcpsocket->bytesAvailable() < blocksize)
    {
        return;
    }
    in>>message;                                        //�������Ĵ���message
}
