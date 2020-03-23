#ifndef COSTOMERREGISTERINFODIALOG_H
#define COSTOMERREGISTERINFODIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QTableView>

namespace Ui {
class CostomerRegisterInfoDialog;
}

class CostomerRegisterInfoDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CostomerRegisterInfoDialog(QWidget *parent = 0);
    ~CostomerRegisterInfoDialog();

    void InitForm();

    void RefreshInfo();                  //ˢ�²���
    //�󶨿ͻ���Ϣ
    void BindCustomInfo(QString tableName, QTableView *tableView,
                       QString columnNames[], int columnWidths[]);

    void ClearCustomerInfo();               //����ؼ�����ʾ�Ŀͻ���Ϣ

    void SetLineEditNoEdit();              //����lineEdit��������

    void SetLineEditEdit();                //����lineEdit������

public slots:
    void showCustomerInfo();
    
private slots:

    void on_checkBoxPwd_clicked(bool checked);

    void on_pbnAddUser_clicked();

    void on_pbnModify_clicked();

    void on_pbnCancel_clicked();

    void on_pbnSave_clicked();

private:
    Ui::CostomerRegisterInfoDialog *ui;

    QSqlQueryModel *QueryModel;     //��ѯģ��
    QTableView *TableView;          //��ʾ���ݵı�����

    QString ColumnNames[8];         //������������
    int ColumnWidths[8];            //�п���������
};

#endif // COSTOMERREGISTERINFODIALOG_H
