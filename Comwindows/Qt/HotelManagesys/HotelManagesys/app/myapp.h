/***************************************************************
 *Copyright(c) 2014-2015 Company By LH Unigress
 *All rights reserved.
 *�ļ����ƣ���¼��־ͷ�ļ�
 *��Ҫ�����������¼ʱ��״̬��Ϣ
 *
 *��ǰ�汾��V2.0
 *���ߣ�Kelvin Li
 *�������ڣ�2014/10
 *˵����
*****************************************************************/
#ifndef MYAPP_H
#define MYAPP_H

#include "myhelper.h"

class Myapp
{
public:
    Myapp();
    static QString AppPath;                 //Ӧ�ó���·��
    static QString CurrentImage;            //���õ�ǰ�������ӦͼƬ

    static QString CurrentUserName;         //��ǰ�û���
    static QString CurrentUserPwd;          //��ǰ�û�����
    static QString CurrentUserType;         //��ǰ�û�����(����Ա���ۻ�Ա����)
    static QString CurrentUserId;           //��ǰ�û��ı��

    static QString LastLoginter;            //���һ�ε�¼�û����������Զ���¼ʱ���ص��û���Ϣ


    static void ReadConfig();           //��ȡ�����ļ�,��main�����ʼ���س�������
    static void WriteConfig();          //д�������ļ�,�ڸ��������ļ�������ر�ʱ����
};

#endif // MYAPP_H
