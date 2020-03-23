#include "costomerregisterinfodialog.h"
#include "ui_costomerregisterinfodialog.h"

#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>
#include "app/myhelper.h"

CostomerRegisterInfoDialog::CostomerRegisterInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CostomerRegisterInfoDialog)
{
    ui->setupUi(this);
    this->InitForm();
}

CostomerRegisterInfoDialog::~CostomerRegisterInfoDialog()
{
    delete ui;
}

void CostomerRegisterInfoDialog::InitForm()
{
    ColumnNames[0] = tr("�ͻ����");
    ColumnNames[1] = tr("����");
    ColumnNames[2] = tr("�Ա�");
    ColumnNames[3] = tr("����");
    ColumnNames[4] = tr("�绰");
    ColumnNames[5] = tr("��ַ");
    ColumnNames[6] = tr("ע��ʱ��");
    ColumnNames[7] = tr("��ע");

    ColumnWidths[0] = 70;
    ColumnWidths[1] = 100;
    ColumnWidths[2] = 80;
    ColumnWidths[3] = 100;
    ColumnWidths[4] = 100;
    ColumnWidths[5] = 200;
    ColumnWidths[6] = 160;
    ColumnWidths[7] = 200;

    BindCustomInfo("customer",ui->tableView,ColumnNames,ColumnWidths);

    ui->CustomerNo->setEnabled(false);  //�ͻ���Ų������޸�
    ui->pbnSave->setEnabled(false);
    ui->pbnCancel->setEnabled(false);

    SetLineEditNoEdit();
    this->connect(ui->tableView,SIGNAL(clicked(QModelIndex)),SLOT(showCustomerInfo()));

    //������ʽ������������ݽ������ƣ��绰����11λ
    QRegExp rxPhone("\\d{11}$");
    QRegExpValidator *regPhone = new QRegExpValidator(rxPhone,this);
    ui->CustomerPhone->setValidator(regPhone);
}

void CostomerRegisterInfoDialog::RefreshInfo()
{
     BindCustomInfo("customer",ui->tableView,ColumnNames,ColumnWidths);
}

void CostomerRegisterInfoDialog::BindCustomInfo(QString tableName, QTableView *tableView, QString columnNames[], int columnWidths[])
{
    QueryModel = new QSqlQueryModel(this);
    QString sql = "SELECT *FROM " + tableName+";";
    qDebug() <<sql;
    QueryModel->setQuery(sql);
    tableView->setModel(QueryModel);

    //���������б��⡢�п��
    for (int i = 0;i<tableView->model()->columnCount();i++)
    {
        QueryModel->setHeaderData(i,Qt::Horizontal,columnNames[i]);     //�����б���
        tableView->setColumnWidth(i,columnWidths[i]);                   //�����п�
    }

    tableView->horizontalHeader()->setHighlightSections(false);         //�����ͷʱ���Ա�ͷ����
    tableView->setSelectionMode(QAbstractItemView::ContiguousSelection);//ѡ��ģʽΪ����ѡ��
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);     //ѡ������
    tableView->setStyleSheet( "QTableView::item:hover{background-color:rgb(92,188,227,200)}"
                              "QTableView::item:selected{background-color:#1B89A1}");
}

void CostomerRegisterInfoDialog::ClearCustomerInfo()
{
    ui->CustomerNo->clear();
    ui->ledSex->clear();
    ui->CustomerName->clear();
    ui->CustomerRePwd->clear();
    ui->CustomerPhone->clear();
    ui->ledCustomDate->clear();
    ui->CustomerAddress->clear();
    ui->CustomerRemark->clear();
}

void CostomerRegisterInfoDialog::SetLineEditNoEdit()
{
    ui->CustomerNo->setEnabled(false);
    ui->ledSex->setEnabled(false);
    ui->CustomerName->setEnabled(false);
    ui->CustomerRePwd->setEnabled(false);
    ui->CustomerPhone->setEnabled(false);
    ui->ledCustomDate->setEnabled(false);
    ui->CustomerAddress->setEnabled(false);
    ui->CustomerRemark->setEnabled(false);
}

void CostomerRegisterInfoDialog::SetLineEditEdit()
{
    ui->CustomerNo->setEnabled(true);
    ui->ledSex->setEnabled(true);
    ui->CustomerName->setEnabled(true);
    ui->CustomerRePwd->setEnabled(true);
    ui->CustomerPhone->setEnabled(true);
    ui->ledCustomDate->setEnabled(true);
    ui->CustomerAddress->setEnabled(true);
    ui->CustomerRemark->setEnabled(true);
}

/*
 *��������:ʵʱ��ʾ��ǰ����пͻ�����Ϣ���ؼ���
*/
void CostomerRegisterInfoDialog::showCustomerInfo()
{
    QSqlQueryModel userMode(ui->tableView);
    QString sql = "SELECT *FROM customer;";
    qDebug() <<sql;
    userMode.setQuery(QString(sql));
    int Row = ui->tableView->currentIndex().row();
    QSqlRecord record = userMode.record(Row);
    ui->CustomerNo->setText(record.value(0).toString());
    ui->CustomerName->setText(record.value(1).toString());
    ui->ledSex->setText(record.value(2).toString());
    ui->CustomerRePwd->setText(record.value(3).toString());
    ui->CustomerPhone->setText(record.value(4).toString());
    ui->CustomerAddress->setText(record.value(5).toString());
    ui->ledCustomDate->setText(record.value(6).toString());
    ui->CustomerRemark->setText(record.value(7).toString());
}

void CostomerRegisterInfoDialog::on_checkBoxPwd_clicked(bool checked)
{
    if(checked)
    {
        ui->CustomerRePwd->setEchoMode(QLineEdit::Normal);
        ui->checkBoxPwd->setText(tr("����"));
    }
    else
    {
        ui->CustomerRePwd->setEchoMode(QLineEdit::Password);
        ui->checkBoxPwd->setText(tr("��ʾ"));
    }
}

/*
 *�������ܣ���ӿͻ���Ϣ
*/
void CostomerRegisterInfoDialog::on_pbnAddUser_clicked()
{
    ClearCustomerInfo();
    SetLineEditEdit();

    ui->pbnAddUser->setEnabled(false);
    ui->pbnModify->setEnabled(false);

    ui->pbnSave->setEnabled(true);
    ui->pbnCancel->setEnabled(true);
}

void CostomerRegisterInfoDialog::on_pbnModify_clicked()
{
    SetLineEditEdit();
    ui->CustomerNo->setEnabled(false);      //��Ų������޸�

    ui->pbnAddUser->setEnabled(false);
    ui->pbnModify->setEnabled(false);

    ui->pbnSave->setEnabled(true);
    ui->pbnCancel->setEnabled(true);
}

void CostomerRegisterInfoDialog::on_pbnCancel_clicked()
{
    SetLineEditEdit();
    ui->pbnAddUser->setEnabled(true);
    ui->pbnModify->setEnabled(true);

    ui->pbnAddUser->setEnabled(false);
    ui->pbnModify->setEnabled(false);
}

void CostomerRegisterInfoDialog::on_pbnSave_clicked()
{
    QString customerNo = ui->CustomerNo->text();
    QString customerSex = ui->ledSex->text();
    QString customerName = ui->CustomerName->text();
    QString customerPwd = ui->CustomerRePwd->text();
    QString customerPhone = ui->CustomerPhone->text();
    QString customerAddress = ui->CustomerAddress->text();
    QString customeDate = ui->ledCustomDate->text();
    QString customeRemark = ui->CustomerRemark->text();

    if(customerNo.isEmpty() && customerName.isEmpty()&& customerPwd.isEmpty()&&customerPhone.isEmpty())
    {
        myHelper::ShowMessageBoxInfo(tr("���������� * ������!"));
    }
    else
    {
        QSqlQuery query;
        bool ok = query.prepare("INSERT INTO Customer (Id, CustomerName,CustomerSex,CustomerPassword,"
                                "CustomerPhone,CustomerAddress,CustomerData,CustomerRemark)"
                                "VALUES (:Id,:CustomerName,:CustomerSex,:CustomerPassword,:CustomerPhone,:CustomerAddress,:CustomerData,:CustomerRemark)");
        query.bindValue(":Id",customerNo);
        query.bindValue(":CustomerName",customerName);
        query.bindValue(":CustomerSex",customerSex);
        query.bindValue(":CustomerPassword",customerPwd);
        query.bindValue(":CustomerPhone",customerPhone);
        query.bindValue(":CustomerAddress",customerAddress);
        query.bindValue(":CustomerData",customeDate);
        query.bindValue(":CustomerRemark",customeRemark);
        query.setForwardOnly(true);
        query.exec();

        if(ok)
        {
            myHelper::ShowMessageBoxInfo(tr("ע��ɹ�!"));
        }
        RefreshInfo();

        ui->pbnAddUser->setEnabled(true);
        ui->pbnModify->setEnabled(true);
    }

}
