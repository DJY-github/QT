#ifndef CONNECT_H
#define CONNECT_H

#include <QDialog>
#include <QtNetwork>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QString>

#define SERV_PORT           6666        //�˿ں�
#define ERROR               99          //����
#define WORKER_INIT         100         //ע��
#define INIT_SUCCESS        101         //ע��ɹ�
#define WORKER_LOG          102         //��¼
#define LOG_SUCCESS         103         //��¼�ɹ�
#define LOG_EXIST           104         //�ѵ�¼
#define EXIT                105         //�˳�
#define USER_INIT           106         //����
#define USER_CLOSE          107         //����
#define CLOSER_SUCCESS      108         //�����ɹ�
#define USER_SAVEMONEY      109         //���
#define SAVEMONEY_SUCCESS   110         //���ɹ�
#define USER_GETMONEY       111         //ȡ��
#define GETMONEY_SUCCESS    112         //ȡ��ɹ�
#define OVER_MONEY          113         //����
#define USER_TRANMONEY      114         //ת��
#define TRANMONEY_SUCCESS   115         //ת�˳ɹ�
#define NO_TRANPEOPLE       116         //���շ�δע��
#define USER_LOOKMONEY      117         //�鿴���
#define LOOKMONEY_SUCCESS   118         //�鿴���ɹ�
#define USER_CHANGE         119         //�޸�����
#define CHANGE_SUCCESS      120         //�޸�����ɹ�
#define USER_ACCOUNT_DETAIL 121         //�˻���ϸ
#define ACCOUNT_SUCCESS     122         //�鿴�˻���ϸ�ɹ�
#define LOOK_RECORD         123         //�鿴���׼�¼
#define LOOKRECORD_SUCCESS  124         //�鿴���׼�¼�ɹ�

const QString IP = "127.0.0.1";

typedef struct Send
{
    int     cmd;                    //����
    int     work_num;               //ְ������
    QString work_id;                //ְ�����֤����
    QString work_name;              //ְ������
    QString work_passward;          //ְ����¼����
    QString user_name;              //�û�����
    int     user_num;               //�û��˺�
    QString user_id;                //�û����֤
    QString user_passward;          //�û�����
    QString first_money;            //��������ȡ�
    QString recv_people;            //ת�˽��շ�
    QString new_passward;           //�޸ĺ��������
    QString record;                 //���׼�¼
}Send_MSG;

typedef struct Recv
{
    int     cmd;                    //����
    int     work_num;               //ְ������
    QString work_id;                //ְ�����֤����
    QString work_name;              //ְ������
    QString work_passward;          //ְ����¼����
    QString user_name;              //�û�����
    int     user_num;               //�û��˺�
    QString money;                  //���
    QString recv_people;            //ת�˽��շ�
    QString record;                 //���׼�¼
}Recv_MSG;


inline QDataStream& operator<<(QDataStream& out, Send_MSG &send_msg)
{
    out<<send_msg.cmd;
    out<<send_msg.work_num;
    out<<send_msg.work_id;
    out<<send_msg.work_name;
    out<<send_msg.work_passward;
    out<<send_msg.first_money;
    out<<send_msg.user_id;
    out<<send_msg.user_name;
    out<<send_msg.user_num;
    out<<send_msg.user_passward;
    out<<send_msg.recv_people;
    out<<send_msg.new_passward;
    out<<send_msg.record;
    return out;
}

inline QDataStream& operator>>(QDataStream& in, Send_MSG &send_msg)
{
    in>>send_msg.cmd;
    in>>send_msg.work_num;
    in>>send_msg.work_id;
    in>>send_msg.work_name;
    in>>send_msg.work_passward;
    in>>send_msg.first_money;
    in>>send_msg.user_id;
    in>>send_msg.user_name;
    in>>send_msg.user_num;
    in>>send_msg.user_passward;
    in>>send_msg.recv_people;
    in>>send_msg.new_passward;
    in>>send_msg.record;
    return in;
}

inline QDataStream& operator <<(QDataStream& out, Recv_MSG &recv_msg)
{
    out<<recv_msg.cmd;
    out<<recv_msg.work_num;
    out<<recv_msg.work_id;
    out<<recv_msg.work_name;
    out<<recv_msg.work_passward;
    out<<recv_msg.money;
    out<<recv_msg.user_name;
    out<<recv_msg.user_num;
    out<<recv_msg.recv_people;
    out<<recv_msg.record;
    return out;
}

inline QDataStream& operator>>(QDataStream& in, Recv_MSG &recv_msg)
{
    in>>recv_msg.cmd;
    in>>recv_msg.work_num;
    in>>recv_msg.work_id;
    in>>recv_msg.work_name;
    in>>recv_msg.work_passward;
    in>>recv_msg.money;
    in>>recv_msg.user_name;
    in>>recv_msg.user_num;
    in>>recv_msg.recv_people;
    in>>recv_msg.record;
    return in;
}

#endif // CONNECT_H
