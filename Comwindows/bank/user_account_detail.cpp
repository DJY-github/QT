#include "user_account_detail.h"
#include "ui_user_account_detail.h"
#include "widget.h"
#include "connect.h"
#include "deal_user.h"
#include <QMessageBox>
#include <QProgressDialog>
#include "bankbook.h"

extern const QString IP;
QString Name;

user_account_detail::user_account_detail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_account_detail)
{
    blocksize = 0;
    ui->setupUi(this);
    this->ui->yesorno->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    this->ui->yesorno->button(QDialogButtonBox::Ok)->setText(tr("ȷ��"));          //��buttonbox�е�ok ��ɺ���
    this->ui->yesorno->button(QDialogButtonBox::Cancel)->setText(tr("ȡ��"));
    this->ui->user_passward1->setEchoMode(QLineEdit::Password);                   //���뷽ʽ��ʾ�ı�
    this->ui->user_passward2->setEchoMode(QLineEdit::Password);
}

user_account_detail::~user_account_detail()
{
    delete ui;
}

void user_account_detail::on_close_music_clicked()
{
    Widget w;
    //w.sound->stop();
}

void user_account_detail::on_yesorno_clicked(QAbstractButton *button)
{
    str.cmd = USER_ACCOUNT_DETAIL;
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

        QProgressDialog dialog(tr("���ڲ�ѯ"),tr("ȡ��"), 0, 30000, this);
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
        switch(message.cmd)
        {
            case ACCOUNT_SUCCESS:
            {
                Name = message.user_name;
                this->close();
                bankbook B;
                B.show();
                B.exec();
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

void user_account_detail::read_server()
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
