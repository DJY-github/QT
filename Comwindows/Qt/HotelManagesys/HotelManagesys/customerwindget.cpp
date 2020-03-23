#include "customerwindget.h"
#include "ui_customerwindget.h"
#include "app/iconhelper.h"
#include "app/myhelper.h"
#include "app/myapp.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDate>

CustomerWindget::CustomerWindget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomerWindget)
{
    ui->setupUi(this);
    this->InitForm();
}

CustomerWindget::~CustomerWindget()
{
    delete ui;
}

void CustomerWindget::InitForm()
{
    //ui->letNo->setEnabled(false);//�û���Ų������޸�

    //���ô������������
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    this->setMinimumSize(1000,600);
    location = this->geometry();
    max = false;
    mousePressed = false;
    //��װ�¼�������,�ñ�����ʶ�����˫��
    ui->lab_Title->installEventFilter(this);

    IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d), 10);
    IconHelper::Instance()->SetIcon(ui->btnMenu_Max, QChar(0xf096), 10);
    IconHelper::Instance()->SetIcon(ui->btnMenu_Min, QChar(0xf068), 10);
    IconHelper::Instance()->SetIcon(ui->btnMenu, QChar(0xf0c9), 10);
    IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0xf015), 12);

    //��ʼ������������п�
    ColumnNames[0] = tr("������");
    ColumnNames[1] = tr("��������");
    ColumnNames[2] = tr("����۸�");
    ColumnNames[3] = tr("����״̬");

    ColumnWidths[0] = 80;
    ColumnWidths[1] = 120;
    ColumnWidths[2] = 120;
    ColumnWidths[3] = 120;

    //�˿���Ϣ��ʾ�ֶγ�ʼ��
    CustomeColumnNames[0] = "���";
    CustomeColumnNames[1] = "����";
    CustomeColumnNames[2] = "�Ա�";
    CustomeColumnNames[3] = "����";
    CustomeColumnNames[4] = "�绰";
    CustomeColumnNames[5] = "��ַ";
    CustomeColumnNames[6] = "ע������";
    CustomeColumnNames[7] = "��ע";


    CustomeColumnWidths[0] = 50;
    CustomeColumnWidths[1] = 90;
    CustomeColumnWidths[2] = 100;
    CustomeColumnWidths[3] = 80;
    CustomeColumnWidths[4] = 150;
    CustomeColumnWidths[5] = 200;
    CustomeColumnWidths[6] = 200;
    CustomeColumnWidths[7] = 200;


    BindRoomInfo("Room",ui->tableViewRoomInfo,ColumnNames,ColumnWidths);

    ui->dateRfrom->setDate(QDate::currentDate());
    ui->dateRto->setDate(QDate::currentDate());
    ui->dateCustomeIn->setDate(QDate::currentDate());

    roompicture = new RoomPicDialog();      //�Ƶ����ͽ���

    ui->stackedWidget->addWidget(roompicture);

    this->connect(ui->tableViewCustomeInfo,SIGNAL(clicked(QModelIndex)),SLOT(showCustomInfo()));
}

/*
 *�������ܣ���������Ϣ�󶨵�tableview��
*/
void CustomerWindget::BindRoomInfo(QString tableName, QTableView *tableView, QString columnNames[], int columnWidths[])
{
    QueryModel = new QSqlQueryModel(this);
    TableView = tableView;
    QString sql = "SELECT RoomNo,Typename,TypePrice,RoomState FROM " + tableName+
            ",RoomType where room.RoomTypeId = roomtype.RoomTypeId and Roomstate ='��';";
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

/*
 *�������ܣ����˿���Ϣ�󶨵�tableview��
*/
void CustomerWindget::BindCustomeInfo(QString tableName, QTableView *tableView, QString columnNames[], int columnWidths[])
{
    customModel = new QSqlQueryModel(this);

    //QString customename = GetCutrrentUserName("Customelogblog");
    QString customename = Myapp::CurrentUserName;
    qDebug() <<"��ǰ�û���:"<<customename;
    QString sql = "SELECT * FROM " + tableName+
            " where CustomerName ='"+customename+"';";
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

/*
 *�������ܣ���ȡ��ǰ��¼�û���
*/
QString CustomerWindget::GetCutrrentUserName(QString tablename)
{
    QString sql ="select CustomeName from "+tablename+";";
    QSqlQuery query;
    query.exec(sql);
    query.next();
    return query.value(0).toString();
}

bool CustomerWindget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        this->on_btnMenu_Max_clicked();
        return true;
    }
    return QObject::eventFilter(obj, event);
}

void CustomerWindget::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton) && !max) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void CustomerWindget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void CustomerWindget::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void CustomerWindget::on_btnMenu_Max_clicked()
{
    if (max)
    {
        this->setGeometry(location);
        IconHelper::Instance()->SetIcon(ui->btnMenu_Max, QChar(0xf096), 10);
        ui->btnMenu_Max->setToolTip("���");
    }
    else
    {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
        IconHelper::Instance()->SetIcon(ui->btnMenu_Max, QChar(0xf079), 10);
        ui->btnMenu_Max->setToolTip("��ԭ");
    }
    max = !max;
}

void CustomerWindget::on_btnMenu_Min_clicked()
{
    this->showMinimized();
}

void CustomerWindget::on_btnMenu_Close_clicked()
{
    this->close();
}

void CustomerWindget::on_punroom_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    BindRoomInfo("Room",ui->tableViewRoomInfo,ColumnNames,ColumnWidths);
}

void CustomerWindget::on_pbnGuest_clicked()
{
    BindCustomeInfo("Customer",ui->tableViewCustomeInfo,CustomeColumnNames,CustomeColumnWidths);

    ui->stackedWidget->setCurrentIndex(1);
}


/*
 *�������ܣ�ȷ��Ԥ������
*/
void CustomerWindget::on_pbnROK_clicked()
{
    QString roomId = ui->letNo->text();
    QString roomType = ui->comboBoxRoomType->currentText();
    QString roomPrice = ui->letprice->text();
    //QString roomstate = ui->letstate->text();
    QString dateto = ui->dateRto->text();
    QString datefrom = ui->dateRfrom->text();

    QString currentdatetime = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");

    //��ˮ��
    QString serialNumber = "2014"+currentdatetime;

    if(ui->radioButtonNo->isChecked())
    {
        //����֧��
        if(roomId.isEmpty()||roomPrice.isEmpty())
        {
            myHelper::ShowMessageBoxError(tr("����������*���ֶ�"));
        }
        else
        {
            QString roomTypeId = "";
            if(roomType == "���˼�")
            {
                roomTypeId ="1";
            }
            else if(roomType == "˫�˼�")
            {
                roomTypeId == "2";
            }
            else if(roomType == "�����׼�")
            {
                roomTypeId == "3";
            }
            else
            {
                roomTypeId == "4";
            }
            qDebug() <<roomTypeId;
            QString customerName = GetCutrrentUserName("customelogblog");
            QSqlQuery query;
            bool ok = query.prepare("INSERT INTO book(Id,roomno,bookName,roomtypeId,"
                                    "booktimefrom,booktimeto,bookremark)"
                                    "VALUES (:Id,:roomno,:bookName,:roomtypeId,:booktimefrom,:booktimeto,:bookremark)");
            query.bindValue(":Id",serialNumber);
            query.bindValue(":roomno",roomId);
            query.bindValue(":bookName",customerName);
            query.bindValue(":roomtypeId",roomTypeId);
            query.bindValue(":booktimefrom",dateto);
            query.bindValue(":booktimeto",datefrom);
            query.bindValue(":bookremark"," ");
            query.setForwardOnly(true);
            query.exec();

            if(ok)
            {
                myHelper::ShowMessageBoxInfo(QString("Ԥ���ɹ�!������:"+serialNumber));
                qDebug() <<"�˿�Ԥ���ɹ�!";
            }
        }

    }
    else if(ui->radioButtonOk->isChecked())
    {
        //����֧��
    }
    else
    {
        //����
        myHelper::ShowMessageBoxInfo(tr("��ѡ��֧����ʽ"));
    }

}

void CustomerWindget::on_comboBoxRoomType_activated(const QString &arg1)
{
    if(arg1 == "���˼�")
    {
        ui->letprice->setText("120");
    }
    else if(arg1 == "˫�˼�")
    {
        ui->letprice->setText("200");
    }
    else if(arg1 == "�����׼�")
    {
        ui->letprice->setText("500");
    }
    else if(arg1 == "��ͳ�׼�")
    {
        ui->letprice->setText("1000");
    }
}

void CustomerWindget::on_pbnroomPicture_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

/*
 *�޸��Լ���Ϣ
*/
void CustomerWindget::on_pbnmodify_clicked()
{
    ui->letusename->clear();
    ui->letsex->clear();
    ui->letpossword->clear();
    ui->letphone->clear();
    ui->letaddress->clear();
    ui->letGnote->clear();

    ui->pbnmodify->setEnabled(false);
}

/*
 *�������ܣ�ȷ���޸ģ�����д��
*/
void CustomerWindget::on_pbuModifyOk_clicked()
{
    QString customeName = ui->letusename->text();
    QString customeSex = ui->letsex->text();
    QString customePwd = ui->letpossword->text();
    QString customePhone = ui->letphone->text();
    QString customedate = ui->dateCustomeIn->text();
    QString customeAddress = ui->letaddress->text();
    QString customeRemark = ui->letGnote->text();

    if(customeName.isEmpty() ||customePhone.isEmpty()
            ||customePwd.isEmpty()||customeAddress.isEmpty())
    {
        myHelper::ShowMessageBoxError(tr("����������*�ֶ�"));
    }
    else
    {
        QString currentUseName = Myapp::CurrentUserName;    //��ȡ��ǰ��¼��
        QSqlQuery query;
        QString sql ="update Customer set CustomerSex ='"+customeSex
                +"', CustomerPassword='"+customePwd+"',CustomerPhone='"+customePhone
                +"', CustomerData ='"+customedate+"', CustomerAddress='"+customeAddress
                +"', CustomerRemark ='"+customeRemark+"' where Id = '"+currentUseName+"';";
        qDebug() <<sql;
        query.exec(sql);
        myHelper::ShowMessageBoxInfo(tr("�޸ĳɹ�"));
        myHelper::MyLoginBlog("logblog","�޸���Ϣ","�ͻ�",currentUseName);
        qDebug() <<"update customer info success!";
    }
}

/*
 *�������ܣ�ȡ������
*/
void CustomerWindget::on_pbnCancle_clicked()
{
    ui->pbnCancle->setEnabled(false);
    ui->pbnmodify->setEnabled(true);
}

/*
 *���������ʾ�ͻ���Ϣ����Ӧ�ؼ���
*/
void CustomerWindget::showCustomInfo()
{
    QSqlQueryModel userMode(ui->tableViewCustomeInfo);
    QString sql = "SELECT *FROM customer;";
    qDebug() <<sql;
    userMode.setQuery(QString(sql));
    int Row = ui->tableViewCustomeInfo->currentIndex().row();
    QSqlRecord record = userMode.record(Row);

    ui->letusename->setText(record.value(1).toString());
    ui->letsex->setText(record.value(2).toString());
    ui->letpossword->setText(record.value(3).toString());
    ui->letphone->setText(record.value(4).toString());
    ui->letaddress->setText(record.value(5).toString());
    //ui->dateCustomeIn->setDate(QDate::addDays(record.value(6).toInt()));
    ui->letGnote->setText(record.value(7).toString());
}
