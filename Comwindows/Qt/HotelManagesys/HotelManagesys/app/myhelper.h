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
#ifndef MYHELPER_H
#define MYHELPER_H

#include <QTextCodec>
#include <QMessageBox>
#include <QInputDialog>
#include <QFile>
#include <QTranslator>

#include <QObject>

class myHelper : public QObject
{
    Q_OBJECT
public:
    static void SetGBK2312Code();//���ñ���ΪGB2312
    static void SetUTF8Code();//���ñ���ΪUTF8
    static void SetStyle(const QString &StyleName);//����Ƥ����ʽ
    static void SetChinese();//���������ַ�

    static void Sleep(int sec);//��ʱ

    static void SetMessage(const QString &msg,int type);//������Ϣ��Ĳ�������ʽ����

    static void ShowMessageBoxInfo(QString info);//��ʾ��Ϣ��
    static void ShowMessageBoxError(QString info);//��ʾ�����
    static int ShowMessageBoxQuesion(QString info);//��ʾѯ�ʿ�
    static QString ShowInputBox(QWidget *frm,QString info);//��ʾ��׼�����
    static int ShowMessageBoxPayInfo(QString info);//��ʾ������Ϣ��

    static bool FileIsExist(QString strFile);
    static bool CopyFile(QString sourceFile,QString targetFile);//�����ļ�

    static void SetSystemDateTime(int year,int month,int day,int hour,int min,int sec);//����ϵͳʱ��

    //д������־
    static void MyLoginBlog(QString tablename,QString Trigger,
                            QString BlogContent,QString UserName);

public:
    explicit myHelper(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // MYHELPER_H
