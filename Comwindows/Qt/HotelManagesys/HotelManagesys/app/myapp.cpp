/***************************************************************
 *Copyright(c) 2014-2015 Company By LH Unigress
 *All rights reserved.
 *�ļ����ƣ���¼��־�ļ�
 *��Ҫ�����������¼ʱ��״̬��Ϣ
 *
 *��ǰ�汾��V2.0
 *���ߣ�Kelvin Li
 *�������ڣ�2014/10
 *˵����
*****************************************************************/

#include <QSettings>
#include "myapp.h"

QString Myapp::AppPath = "";

//�洢��ǰ��¼�û���Ϣ,�����û������޸ĺ��û��˳�����
QString Myapp::CurrentUserName = "";
QString Myapp::CurrentUserPwd = "";
QString Myapp::CurrentUserType = "";
QString Myapp::CurrentUserId ="";

QString Myapp::LastLoginter = "";

Myapp::Myapp()
{
}

/*
 *�������ܣ���ȡ�����ļ�����
 *�����������
 *�����������
 *����ֵ:  ��
*/
void Myapp::ReadConfig()
{
    QString fileName = Myapp::AppPath+"config.txt";
    //��������ļ�������,���Գ�ʼֵ��������
    //û������жϵĻ�,���ø�ֵ��Ϊ��
    if(!myHelper::FileIsExist(fileName))
    {
        Myapp::CurrentUserType = Myapp::CurrentUserType.toLatin1();
        return;
    }
    QSettings *set = new QSettings(fileName,QSettings::IniFormat);
    set->beginGroup("AppConfig");

    set->endGroup();

}

void Myapp::WriteConfig()
{
    QString fileName = Myapp::AppPath+"config.txt";
    QSettings *set = new QSettings(fileName,QSettings::IniFormat);

    set->beginGroup("AppConfig");

    set->setValue("LastLoginer",Myapp::LastLoginter);
    set->setValue("CurrentUserPwd",Myapp::CurrentUserPwd);
    set->setValue("CurrentUserType",Myapp::CurrentUserType);
    set->value("urrentUserId",Myapp::CurrentUserId);


    set->endGroup();
}
