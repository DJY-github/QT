#include "mydatahelper.h"

#include <QHeaderView>

myDataHelper::myDataHelper(QObject *parent) :
    QObject(parent)
{
}

myDataHelper::myDataHelper(QString dataBaseName) :
    QObject()
{
    this->strConnection=dataBaseName;
}

void myDataHelper::InitDataBase()
{
    this->myDatabase=QSqlDatabase::addDatabase("QSQLITE","mydatasqlite");
    this->myDatabase.setDatabaseName(this->strConnection);
}

bool myDataHelper::OpenDataBase()
{
    //�����û��ʼ�����ʼ�����ݿ�
    if (this->myDatabase.databaseName()=="")
    {
        this->InitDataBase();
    }

    return this->myDatabase.open();
}

bool myDataHelper::CloseDataBase()
{
    if (this->myDatabase.isOpen())
    {
        this->myDatabase.close();        
    }
    return true;
}

bool myDataHelper::ExecuteSql(QString sql)
{
    if (this->myDatabase.isOpen())
    {
        QSqlQueryModel *model=new QSqlQueryModel;
        model->setQuery(sql,this->myDatabase);//ִ����䣬ע�������Ҫָ�����ݿ�
        return true;
    }
    return false;
    this->CloseDataBase();
}

bool myDataHelper::ExecuteSqls(QStringList sqlList)
{
    if (this->myDatabase.isOpen())
    {
        QSqlQueryModel *model=new QSqlQueryModel;
        for (int i=0;i<sqlList.length();++i)
        {
            model->setQuery(sqlList.at(i),this->myDatabase);//ִ����䣬ע�������Ҫָ�����ݿ�
        }
        this->myDatabase.commit();
        return true;
    }
    return false;
    this->CloseDataBase();
}

bool myDataHelper::BindData(QString sql, QTableView *view)
{
    if (this->myDatabase.isOpen())
    {
        QSqlQueryModel *model=new QSqlQueryModel;
        model->setQuery(sql,this->myDatabase);//ִ����䣬ע�������Ҫָ�����ݿ�
        view->setModel(model);
        return true;
    }
    return false;
    this->CloseDataBase();
}

bool myDataHelper::BindData(QString sql, QTableView *view, QStringList fieldList)
{
    if (this->myDatabase.isOpen())
    {
        QSqlQueryModel *model=new QSqlQueryModel;
        model->setQuery(sql,this->myDatabase);//ִ����䣬ע�������Ҫָ�����ݿ�
        for (int i=0;i<fieldList.length();++i)
        {
            model->setHeaderData(i,Qt::Horizontal,fieldList.at(i));
        }
        view->setModel(model);
        view->verticalHeader()->hide();//�����������
        return true;
    }
    return false;
    this->CloseDataBase();
}
