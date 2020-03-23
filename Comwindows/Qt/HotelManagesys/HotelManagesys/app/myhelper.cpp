/***************************************************************
 *Copyright(c) 2014-2015 Company By LH Unigress
 *All rights reserved.
 *�ļ����ƣ����������������ļ�
 *��Ҫ����������һЩ��ʾ��ϵͳ�����ʽ��Ƥ�����ַ���ʽ
 *
 *��ǰ�汾��V2.0
 *���ߣ�Kelvin Li
 *�������ڣ�2014/10
 *˵����
*****************************************************************/
#include "myhelper.h"
#include <QApplication>
#include "frmmessagebox.h"

#include <QTime>
#include <QProcess>
#include <QSqlQuery>
#include <QDebug>

myHelper::myHelper(QObject *parent) :
    QObject(parent)
{
}
/*���ñ����ʽΪGB2312*/
void myHelper::SetGBK2312Code()
{
    QTextCodec *codec=QTextCodec::codecForName("GB2312");
    QTextCodec::setCodecForLocale(codec);
}

/*���ñ����ʽΪUTF8*/
void myHelper::SetUTF8Code()
{
#if(QT_VERSION <= QT_VERSION_CHECK(5,0,0))
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);

#endif
}

/*����Ƥ����ʽ*/
void myHelper::SetStyle(const QString &StyleName)
{
    QFile file(QString(":/image/%1.css").arg(StyleName));
    file.open(QFile::ReadOnly);
    QString qss = QLatin1String(file.readAll());
    qApp->setStyleSheet(qss);
    qApp->setPalette(QPalette(QColor("#F0F0F0")));
}

/*���������ַ�*/
void myHelper::SetChinese()
{
    QTranslator *translator = new QTranslator(qApp);
    translator->load(":/image/qt_zh_CN.qm");
    qApp->installTranslator(translator);
}


/*��ʾ��Ϣ��   ��ȷ�ϰ�ť*/
void myHelper::ShowMessageBoxInfo(QString info)
{
    frmMessageBox *msg = new frmMessageBox;
    msg->SetMessage(info,1);
    msg->exec();
}

/*
 *�������ܣ���ʾ�����,��ȷ����ť
 *�����������ʾ����Ϣ����
 *�����������
 *����ֵ����
*/
void myHelper::ShowMessageBoxError(QString info)
{
    frmMessageBox *msg = new frmMessageBox;
    msg->SetMessage(info,2);
    msg->exec();
}

//��ʾѯ�ʿ�,ȷ����ȡ����ť
int myHelper::ShowMessageBoxQuesion(QString info)
{
    frmMessageBox *msg = new frmMessageBox;
    msg->SetMessage(info,0);
    return msg->exec();
}

QString myHelper::ShowInputBox(QWidget *frm, QString info)
{
    bool ok;
    return QInputDialog::getText(frm,"��ʾ",info,QLineEdit::Password,"",&ok);
}

/*
 *��ʾ�û�������Ϣ��ȷ��������Ϣ�Ƿ���ȷ
*/
int myHelper::ShowMessageBoxPayInfo(QString info)
{
    frmMessageBox *msg = new frmMessageBox;
    msg->SetMessage(info,3);
    msg->exec();
}

/*
 *�����ļ��Ƿ����
*/
bool myHelper::FileIsExist(QString strFile)
{
    QFile tempFile(strFile);
    return tempFile.exists();
}

/*
 *�����ļ�
*/
bool myHelper::CopyFile(QString sourceFile,QString targetFile)
{
    if(FileIsExist(targetFile))
    {
        int ret = QMessageBox::information(0,"��ʾ","�ļ��Ѿ�����,�Ƿ��滻?",QMessageBox::Yes | QMessageBox::No);
        if(ret != QMessageBox::Yes)
        {
            return false;
        }
    }
    return QFile::copy(sourceFile,targetFile);
}

/*
 *�������ܣ���ʱ����
 *�����������Ҫ��ʱ��ʱ��
 *�����������
 *����ֵ����
*/
void myHelper::Sleep(int sec)
{
    QTime dieTime = QTime::currentTime().addMSecs(sec);
    while (QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

/*
 *�������ܣ�������ʾʱ��
 *��������������꣬�£��գ�ʱ������
 *�����������ϵͳʱ����ʾ�ڶ�Ӧ�ؼ���
*/
void myHelper::SetSystemDateTime(int year, int month, int day, int hour, int min, int sec)
{
    QProcess p(0);

    p.start("cmd");
    p.waitForStarted();
    p.write(QString("date %1-%2-%3\n").arg(year).arg(month).arg(day).toLatin1());
    p.closeWriteChannel();
    p.waitForFinished(1000);
    p.close();

    p.start("cmd");
    p.waitForStarted();
    p.write(QString("time %1:%2:%3.00\n").arg(hour).arg(min).arg(sec).toLatin1());
    p.closeWriteChannel();
    p.waitForFinished(1000);
    p.close();
}

/*
 *�������ܣ���¼���ݼ�¼
 *������������ݱ��������������ݣ�������
*/
void myHelper::MyLoginBlog(QString tablename, QString Trigger, QString BlogContent, QString UserName)
{
    QSqlQuery query;
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    qDebug() <<currentDateTime;

    QString sql = "insert into "+tablename+" values(:TriggerTimer,:Trigger,:TriggretContent,:TriggetUser)";
    qDebug() <<sql;
    query.prepare(sql);
    query.bindValue(":TriggerTimer",currentDateTime);
    query.bindValue(":Trigger",Trigger);
    query.bindValue(":TriggerContent",BlogContent);
    query.bindValue(":TriggerUser",UserName);
    query.setForwardOnly(true);
    query.exec();
}
