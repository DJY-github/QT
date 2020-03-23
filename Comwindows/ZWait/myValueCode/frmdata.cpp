#include "frmdata.h"
#include "ui_frmdata.h"
#include "myStaticClass.h"

frmData::frmData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmData)
{
    ui->setupUi(this);
    FormHelper::FormInCenter(this);
    FormHelper::FormNotResize(this);
    FormHelper::FormOnTop(this);
    FormHelper::FormOnlyCloseButton(this);
    FormHelper::SetMyStyle(this);

    myData=new myDataHelper(QCoreApplication::applicationDirPath()+"/alarm.db");
    this->ChangeEnable(false);

}

frmData::~frmData()
{
    delete ui;
}

void frmData::ChangeEnable(bool b)
{
    ui->tableView->setEnabled(b);
    ui->btn1->setEnabled(b);
    ui->btn2->setEnabled(b);
    ui->btn3->setEnabled(b);
    ui->btn4->setEnabled(b);
    ui->btn5->setEnabled(b);
}

void frmData::on_btn1_clicked()
{
    QString sql="select * from information";
    myData->BindData(sql,ui->tableView);
}

void frmData::on_btn2_clicked()
{
    QString sql="select * from information";
    QStringList mylist;
    mylist<<"���"<<"��ϵͳ"<<"������"<<"�¼�"<<"����"<<"ʱ��";
    myData->BindData(sql,ui->tableView,mylist);

    ui->tableView->verticalHeader()->hide();//�����������
    ui->tableView->setColumnWidth(0,50);//�����п�
    ui->tableView->setColumnWidth(1,50);
    ui->tableView->setColumnWidth(2,50);
    ui->tableView->setColumnWidth(3,90);
    ui->tableView->setColumnWidth(4,90);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//����ѡ��
}

void frmData::on_btn3_clicked()
{
    QStringList mysql;
    mysql.append("insert into information(subsystem,defenceid,incident,triggerdate,triggertime) values('1','010','������������1','2011-01-02','12:21:12')");
    mysql.append("insert into information(subsystem,defenceid,incident,triggerdate,triggertime) values('1','011','������������2','2011-01-02','12:21:12')");
    mysql.append("insert into information(subsystem,defenceid,incident,triggerdate,triggertime) values('1','012','������������3','2011-01-02','12:21:12')");
    mysql.append("insert into information(subsystem,defenceid,incident,triggerdate,triggertime) values('1','013','������������4','2011-01-02','12:21:12')");
    mysql.append("insert into information(subsystem,defenceid,incident,triggerdate,triggertime) values('1','014','������������5','2011-01-02','12:21:12')");
    if (myData->ExecuteSqls(mysql))
    {
        MyMessageBox::ChMessageOnlyOk(tr("�����������ݳɹ���"));
    }
    else
    {
        MyMessageBox::ChMessageOnlyOk(tr("������������ʧ�ܣ�"));
    }
}

void frmData::on_btnOpen_clicked()
{
    if (ui->btnOpen->text()=="�����ݿ�")
    {
        if (myData->OpenDataBase())
        {
            ui->btnOpen->setText("�ر����ݿ�");
            MyMessageBox::ChMessageOnlyOk(tr("�����ݿ�ɹ���"));
            this->ChangeEnable(true);
        }
        else
        {
            MyMessageBox::ChMessageOnlyOk(tr("�����ݿ�ʧ�ܣ�"));
        }
    }
    else
    {
        if (myData->CloseDataBase())
        {
            ui->btnOpen->setText("�����ݿ�");
            MyMessageBox::ChMessageOnlyOk(tr("�ر����ݿ�ɹ���"));
            this->ChangeEnable(false);
        }
        else
        {
            MyMessageBox::ChMessageOnlyOk(tr("�ر����ݿ�ʧ�ܣ�"));
        }
    }

}

void frmData::on_btn4_clicked()
{

}
