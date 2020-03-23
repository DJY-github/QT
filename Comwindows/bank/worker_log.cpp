#include "worker_log.h"
#include "widget.h"
#include "connect.h"
#include "deal_user.h"
#include "worker_init.h"
#include "ui_logging.h"
#include <QDebug>
#include <QPushButton>
#include <QProgressDialog>
#include <QMessageBox>
#include <QtNetwork>

QString xxx;
int yyy;
extern const QString IP;

void work_log::on_Yesorno_clicked(QAbstractButton *button)
{
    Send_MSG str;
    QString n = this->work_ui.num->text();
    str.work_num = n.toInt();
    qDebug()<<str.work_num;
    str.work_passward = this->work_ui.passward->text();
    qDebug()<<str.work_passward;
    str.cmd = WORKER_LOG;

    if(this->work_ui.Yesorno->button(QDialogButtonBox::Ok) == button)           //�жϰ��µ��Ƿ�Ϊ"ȷ������ť
    {
        if(this->work_ui.num->text() == "" | this->work_ui.passward->text() == "")
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

        switch (message.cmd)
        {
            case LOG_SUCCESS:
            {
                xxx = message.work_name;
                yyy = message.work_num;
                QMessageBox::information(this, tr("��Ϣ"), tr("��¼�ɹ���"), QMessageBox::Ok);
                this->close();
                deal_user D(this);
                D.show();
                D.exec();
                break;
            }
            case LOG_EXIST:
            {
                QMessageBox::information(this, tr("��Ϣ"), tr("��¼ʧ�ܣ���Ա���ѵ�¼!"), QMessageBox::Ok);
                this->close();
                Widget w;
                w.show();
                w.exec();
                break;
            }
            case ERROR:
            {
                QMessageBox::information(this, tr("��Ϣ"), tr("��¼ʧ�ܣ���Ա��δע��!"), QMessageBox::Ok);
                this->close();
                Widget w;
                w.show();
                w.exec();
                break;
            }
        }
    }
    else if(button == this->work_ui.Yesorno->button((QDialogButtonBox::Cancel)))
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

void work_log::read_server()
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
    qDebug()<<message.cmd;
    qDebug()<<"���ţ�"<<message.work_num;
    qDebug()<<"������"<<message.work_name;
}

void work_log::on_close_music_clicked()
{
    Widget w;
    //w.sound->stop();
}
