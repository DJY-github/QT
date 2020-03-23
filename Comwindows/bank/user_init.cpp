#include "user_init.h"
#include "ui_user_init.h"
#include "widget.h"
#include "connect.h"
#include "deal_user.h"
#include <QMessageBox>
#include <QFile>
#include <QProgressDialog>

extern const QString IP;

user_init::user_init(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_init)
{
    blocksize = 0;
    ui->setupUi(this);
    this->ui->yesorno->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    this->ui->yesorno->button(QDialogButtonBox::Ok)->setText(tr("ȷ��"));          //��buttonbox�е�ok ��ɺ���
    this->ui->yesorno->button(QDialogButtonBox::Cancel)->setText(tr("ȡ��"));
    this->ui->user_passward1->setEchoMode(QLineEdit::Password);                   //���뷽ʽ��ʾ�ı�
    this->ui->user_passward2->setEchoMode(QLineEdit::Password);
}

user_init::~user_init()
{
    delete ui;
}

void user_init::on_close_music_clicked()
{
    Widget w;
    //w.sound->stop();
}

void user_init::on_yesorno_clicked(QAbstractButton *button)
{
    Send_MSG str;
    QString pass1, pass2;
    str.cmd = USER_INIT;
    str.user_name = this->ui->user_name->text();
    str.user_id = this->ui->user_id->text();
    pass1 = this->ui->user_passward1->text();
    pass2 = this->ui->user_passward2->text();
    str.first_money = this->ui->first_money->text();

    if(this->ui->yesorno->button(QDialogButtonBox::Ok) == button)           //�жϰ��µ��Ƿ�Ϊ"ȷ������ť
    {
        if(this->ui->user_name->text() == "" | this->ui->user_id->text() == "" | this->ui->user_passward1->text() == "" |
                this->ui->user_passward2->text() == "" | this->ui->first_money->text() == "")
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

        QProgressDialog dialog(tr("����ע��"),tr("ȡ��"), 0, 30000, this);
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
            case INIT_SUCCESS:                                                      //ע��ɹ�
            {
                QString str1 = QString("ע��ɹ�\n�˺�Ϊ%1").arg(message.user_num);
                QMessageBox::information(this, tr("��Ϣ"), str1, QMessageBox::Ok);
                SaveUserInit();                                                     //�˻����汾��
                this->close();
                deal_user D(this);
                D.show();
                D.exec();
                break;
            }
            case ERROR:                                                             //ע��ʧ��
            {
                QMessageBox::information(this, tr("��Ϣ"), tr("ע��ʧ�ܣ����û��ѱ�ע��!"), QMessageBox::Ok);
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

void user_init::read_server()
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

void user_init::SaveUserInit()                          //������Ϣ���汾���Դ�ӡ
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    QString save = QString("����\t�˺�\t��������\t�������\t\t����\n%1\t%2\t�й�����\t%3\t\t%4\n\n\n\t����\t\t�ִ�\t֧��\t��Ϣ\t ת�� \t\t���\t\tְ����").arg(message.user_name).arg(message.user_num).arg(message.money).arg(current_date);
    qDebug()<<save;

    QString filename = QString("%1�Ĵ���.txt").arg(message.user_name);
    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug()<<file.errorString();
    }
    file.write(save.toLatin1());
    file.close();
}
