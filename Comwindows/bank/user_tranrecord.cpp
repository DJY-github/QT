#include "user_tranrecord.h"
#include "ui_user_tranrecord.h"
#include "widget.h"
#include <QMessageBox>
#include "deal_user.h"
#include <QProgressDialog>
#include "worker_log.h"
#include "record.h"

extern int yyy;
extern const QString IP;
QString ReCord;

user_tranRecord::user_tranRecord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_tranRecord)
{
    blocksize = 0;
    ui->setupUi(this);
    this->ui->Yesorno->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    this->ui->Yesorno->button(QDialogButtonBox::Ok)->setText(tr("ȷ��"));          //��buttonbox�е�ok ��ɺ���
    this->ui->Yesorno->button(QDialogButtonBox::Cancel)->setText(tr("ȡ��"));
    this->ui->passward->setEchoMode(QLineEdit::Password);                   //���뷽ʽ��ʾ�ı�
}

user_tranRecord::~user_tranRecord()
{
    delete ui;
}

void user_tranRecord::on_close_music_clicked()
{
    Widget w;
    //w.sound->stop();
}

void user_tranRecord::on_Yesorno_clicked(QAbstractButton *button)
{
    QString ecf = QString("%1").arg(yyy);
    this->ui->num->setText(ecf);
    str.work_num = this->ui->num->text().toInt();
    str.work_passward = this->ui->passward->text();
    str.cmd = LOOK_RECORD;

    if(this->ui->Yesorno->button(QDialogButtonBox::Ok) == button)           //�жϰ��µ��Ƿ�Ϊ"ȷ������ť
    {
        if(this->ui->num->text() == "" | this->ui->passward->text() == "")
        {
            QMessageBox::warning(this, tr("����"), tr("���벻��Ϊ�գ�"), QMessageBox::Ok);
            return;
        }

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

        QProgressDialog dialog(tr("���ڵ�¼"),tr("ȡ��"), 0, 30000, this);
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
        qDebug()<<message.record;
        switch (message.cmd)
        {
            case LOOKRECORD_SUCCESS:
            {
                this->close();
                ReCord = message.record;
                record R;
                R.show();
                R.exec();
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
    else if(button == this->ui->Yesorno->button((QDialogButtonBox::Cancel)))
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

        Widget w;
        w.show();
        w.exec();
    }
}

void user_tranRecord::read_server()
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
