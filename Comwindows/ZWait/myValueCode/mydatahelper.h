#ifndef MYDATAHELPER_H
#define MYDATAHELPER_H

#include <QObject>
#include <QTableView>
#include <QtSql>

class myDataHelper : public QObject
{
    Q_OBJECT
public:
    explicit myDataHelper(QObject *parent = 0);
    explicit myDataHelper(QString dataBaseName);

    QSqlDatabase myDatabase;
    QString strConnection;

public:
    void InitDataBase();//��ʼ�����ݿ�
    bool OpenDataBase();//�����ݿ�
    bool CloseDataBase();//�ر����ݿ�

    bool ExecuteSql(QString sql);//ִ��SQL���
    bool ExecuteSqls(QStringList sqlList);//ִ��һϵ��SQL���

    bool BindData(QString sql,QTableView *view);//�󶨲�ѯ������ݵ���Ӧ���
    bool BindData(QString sql,QTableView *view,QStringList fieldList);//�󶨲�ѯ������ݵ���Ӧ���,����fieldList˳������ֶ�����

signals:

public slots:

};

#endif // MYDATAHELPER_H
