#ifndef MYSQLAPI_H
#define MYSQLAPI_H

#include <QObject>
#include <QtSql>
#include <QTableView>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>

/* ˵��:mysql���ݿ����ͷ�ļ�
 * ����:���������ݿ���в�ѯ�ȴ���
 */
class MysqlApi : public QObject
{
    Q_OBJECT
public:
    explicit MysqlApi(QObject *parent = 0);

    //������Ҫ��ʾ���ݵı��,���ݷ�ҳ��Ӧ�İ�ť
    void SetControl(QTableView *tableView,QLabel *labInfo,
                    QPushButton *btnFirst,QPushButton *btnPre,
                    QPushButton *btnNext,QPushButton *btnLast);
    //�����ݵ�������
    void BindData(QString columnName,QString tableName,QComboBox *cbox);
    //����ĳ���ֶε����ֵ
    int SearchMaxValue(QString columnName,QString tableName);
    //������,������������������
    void BindData(QString tableName,QString orderColumn,QString orderType,int rowsCount,
                  QString columnNames[], int columnWidths[]);
    //��ĳ�����е����ݰ󶨵�ָ����TableView��
    void MyBindTable(QString tableName, QTableView *tableView,
                     QString columnNames[], int columnWidths[]);
    
    void BindSql(QString sql);
    void BindDataSelect(QString tableName,QString orderColumn,
                        QString orderType,QString where,int rowsCount,
                        QString columnNames[], int columnWidths[]);
signals:
    
private slots:
private slots:
    void First();       //��һҳ
    void Previous();    //��һҳ
    void Next();        //��һҳ
    void Last();        //ĩһҳ
private:
    
};

#endif // MYSQLAPI_H
