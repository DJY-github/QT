#include "mysqlapi.h"
#include <QSqlQueryModel>
#include <QHeaderView>

int StartIndex;             //��ҳ��ʼ����,ÿ�η�ҳ���䶯
QString TempSql;            //��ʱSQL���
QString Sql;

int RowsCount;              //ÿҳ��ʾ����
int RowsCountAll;           //������
int PageCount;              //��ҳ��
int PageCurrent;            //��ǰ�ڼ�ҳ

QTableView *TableView;      //��ʾ���ݵı�����
QLabel *LabInfo;            //��ʾ��ҳ��Ϣ
QPushButton *BtnFirst;      //��һҳ��ť����
QPushButton *BtnPre;        //��һҳ��ť����
QPushButton *BtnNext;       //��һҳ��ť����
QPushButton *BtnLast;       //ĩһҳ��ť����

QSqlQueryModel *QueryModel; //��ѯģ��

MysqlApi::MysqlApi(QObject *parent) :
    QObject(parent)
{
    StartIndex=0;
    TempSql="";
    Sql="";
    RowsCount=0;
    RowsCountAll=0;
    PageCount=0;
    PageCurrent=1;
}


/*
 *�������ܣ����ð󶨵�Ҳ,��ť
*/
void MysqlApi::SetControl(QTableView *tableView, QLabel *labInfo, QPushButton *btnFirst, QPushButton *btnPre, QPushButton *btnNext, QPushButton *btnLast)
{
    TableView = tableView;
    LabInfo = labInfo;
    BtnFirst = btnFirst;
    BtnPre = btnPre;
    BtnNext = btnNext;
    BtnLast = btnLast;
    QueryModel = new QSqlQueryModel(TableView);

    //���ط�ҳ��ť�¼�
    connect(BtnFirst,SIGNAL(clicked()),this,SLOT(First()));
    connect(BtnPre,SIGNAL(clicked()),this,SLOT(Previous()));
    connect(BtnNext,SIGNAL(clicked()),this,SLOT(Next()));
    connect(BtnLast,SIGNAL(clicked()),this,SLOT(Last()));
}
/*
 *�������ܣ������ݵ�������
 *����������󶨵��ֶ���������������������
 *�����������
 *����ֵ����
 *˵�����ú������԰������ֶε������������
*/
void MysqlApi::BindData(QString columnName, QString tableName, QComboBox *cbox)
{
    QSqlQuery query;
    query.exec("select "+columnName+" from "+tableName+" order by "+columnName+" asc");
    while(query.next())
    {
        cbox->addItem(query.value(0).toString());
    }
}

/*
 *�������ܣ������������ĳ���ֶ��������ֵ
 *����������ֶ���������
 *�����������
 *����ֵ�����ݱ��в�ѯ�����ֶ�ֵ
 *˵����
*/
int MysqlApi::SearchMaxValue(QString columnName, QString tableName)
{
    QSqlQuery query;
    int maxvalue = 0;
    QString sql = "select MAX("+columnName+") from "+tableName+";";
    qDebug() <<sql;
    query.exec(sql);
    if(query.next())
    {

        maxvalue = query.value(0).toInt();
    }
    return maxvalue;
}

void MysqlApi::BindData(QString tableName, QString orderColumn, QString orderType, int rowsCount, QString columnNames[], int columnWidths[])
{
    StartIndex = 0;//���ÿ�ʼ����
    PageCurrent = 1;
    RowsCount = rowsCount;

    //��ʼ��ҳ������ǰ,��������������Լ�����
    TempSql = "select count(*) from "+tableName;
    QSqlQuery query;
    query.prepare(TempSql);
    query.exec();
    query.first();
    RowsCountAll = query.value(0).toInt();

    int yushu = RowsCountAll % RowsCount;
    //����������,˵��������,����300%5==0
    if (yushu == 0)
    {
        if (RowsCountAll > 0 && RowsCountAll < RowsCount)
        {
            PageCount = 1;
        }
        else
        {
            PageCount=RowsCountAll/RowsCount;
        }
    }
    else
    {
        PageCount=RowsCountAll/RowsCount+1;
    }

    TempSql = "select RoomNo,Typename,Typrice,RoomState,RoomRemark from "+tableName+" where room.RoomTypeId=roomtype.RoomTypeId order by "+orderColumn+" "+orderType;
    Sql = QString("%1 limit %2,%3;").arg(TempSql).arg(StartIndex).arg(RowsCount);//��֯��ҳSQL���
    BindSql(Sql);

    //���������б��⡢�п��
    for (int i = 0;i<TableView->model()->columnCount();i++)
    {
        QueryModel->setHeaderData(i,Qt::Horizontal,columnNames[i]);//�����б���
        TableView->setColumnWidth(i,columnWidths[i]);//�����п�
    }


    TableView->horizontalHeader()->setHighlightSections(false);//�����ͷʱ���Ա�ͷ����
    TableView->setSelectionMode(QAbstractItemView::ContiguousSelection);//ѡ��ģʽΪ����ѡ��
    TableView->setSelectionBehavior(QAbstractItemView::SelectRows);//ѡ������
    TableView->setStyleSheet( "QTableView::item:hover{background-color:rgb(92,188,227,200)}"
                              "QTableView::item:selected{background-color:#1B89A1}");
}

/*
 *�������ܣ���������е����ݵ�tableview��
*/
void MysqlApi::MyBindTable(QString tableName, QTableView *tableView, QString columnNames[], int columnWidths[])
{
    TableView = tableView;
    QString sql = "SELECT * FROM " + tableName;
    QueryModel->setQuery(sql);
    TableView->setModel(QueryModel);

    //���������б��⡢�п��
    for (int i = 0;i<TableView->model()->columnCount();i++)
    {
        QueryModel->setHeaderData(i,Qt::Horizontal,columnNames[i]);     //�����б���
        TableView->setColumnWidth(i,columnWidths[i]);                   //�����п�
    }

    TableView->horizontalHeader()->setHighlightSections(false);         //�����ͷʱ���Ա�ͷ����
    TableView->setSelectionMode(QAbstractItemView::ContiguousSelection);//ѡ��ģʽΪ����ѡ��
    TableView->setSelectionBehavior(QAbstractItemView::SelectRows);     //ѡ������
    TableView->setStyleSheet( "QTableView::item:hover{background-color:rgb(92,188,227,200)}"
                              "QTableView::item:selected{background-color:#1B89A1}");
}

void MysqlApi::BindSql(QString sql)
{
    QueryModel->setQuery(sql);
    TableView->setModel(QueryModel);
    LabInfo->setText(QString("����%1������  ��%2ҳ  ��ǰ��%3ҳ").arg(RowsCountAll).arg(PageCount).arg(PageCurrent));
}

void MysqlApi::BindDataSelect(QString tableName, QString orderColumn, QString orderType, QString where, int rowsCount, QString columnNames[], int columnWidths[])
{
    StartIndex=0;//���ÿ�ʼ����
    PageCurrent=1;
    RowsCount=rowsCount;

    //��ʼ��ҳ������ǰ,��������������Լ�����
    TempSql="select count(*) from "+tableName+" "+where;
    QSqlQuery query;
    query.prepare(TempSql);//����д��ʱ��ע��ո�����
    query.exec();
    query.first();
    RowsCountAll= query.value(0).toInt();

    int yushu=RowsCountAll % RowsCount;
    //����������,˵��������,����300%5==0
    if (yushu==0) {
        if (RowsCountAll>0 && RowsCountAll<RowsCount){
            PageCount=1;
        }else{
            PageCount=RowsCountAll/RowsCount;
        }
    }else{
        PageCount=RowsCountAll/RowsCount+1;
    }

    TempSql="select * from "+tableName+" "+where+" order by "+orderColumn+" "+orderType;
    Sql=QString("%1 limit %2,%3;").arg(TempSql).arg(StartIndex).arg(RowsCount);//��֯��ҳSQL���
    BindSql(Sql);

    //���������б��⡢�п��
    for (int i=0;i<TableView->model()->columnCount();i++){
        QueryModel->setHeaderData(i,Qt::Horizontal,columnNames[i]);//�����б���
        TableView->setColumnWidth(i,columnWidths[i]);//�����п�
    }


    TableView->horizontalHeader()->setHighlightSections(false);//�����ͷʱ���Ա�ͷ����
    TableView->setSelectionMode(QAbstractItemView::SingleSelection);//ѡ��ģʽΪ����ѡ��
    TableView->setSelectionBehavior(QAbstractItemView::SelectRows);//ѡ������
    TableView->setStyleSheet( "QTableView::item:hover{background-color:rgb(92,188,227,200)}"
                              "QTableView::item:selected{background-color:#1B89A1}");
}

void MysqlApi::First()
{
    if (PageCount>1)
    {
        StartIndex=0;
        PageCurrent=1;
        Sql=QString("%1 limit %2,%3;").arg(TempSql).arg(StartIndex).arg(RowsCount);//��֯��ҳSQL���
        BindSql(Sql);
    }
}

void MysqlApi::Previous()
{
    if (PageCurrent>1)
    {
        PageCurrent--;
        StartIndex-=RowsCount;
        Sql=QString("%1 limit %2,%3;").arg(TempSql).arg(StartIndex).arg(RowsCount);//��֯��ҳSQL���
        BindSql(Sql);
    }
}

void MysqlApi::Next()
{
    if (PageCurrent<PageCount)
    {
        PageCurrent++;
        StartIndex+=RowsCount;
        Sql=QString("%1 limit %2,%3;").arg(TempSql).arg(StartIndex).arg(RowsCount);//��֯��ҳSQL���
        BindSql(Sql);
    }
}

void MysqlApi::Last()
{
    if (PageCount>0)
    {
        StartIndex=(PageCount-1)*RowsCount;
        PageCurrent=PageCount;
        Sql=QString("%1 limit %2,%3;").arg(TempSql).arg(StartIndex).arg(RowsCount);//��֯��ҳSQL���
        BindSql(Sql);
    }
}
