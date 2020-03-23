#include "login.h"
#include "def.h"
#include "ui_login.h"
#include "frminput.h"
#include "QTextCodec"
#include <QCompleter>
#include <QDebug>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlTableModel>


Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    ui->setupUi(this);
    setWindowTitle(tr("登陆"));//窗口标题
    qDebug()<<__FUNCTION__<<"is running !";

    ui->lineEditUser->setFocus();
    QRegExp rx1("^\\w+$");
    QRegExpValidator *pReg1 = new QRegExpValidator(rx1, this);
    ui->lineEditUser->setValidator(pReg1);


    ui->lineEditNumber->setEchoMode(QLineEdit::Password);//密码方式显示文本
    QDialog::setModal( true );//设置模态，让该窗口一直在最前端
    setAttribute(Qt::WA_DeleteOnClose,true);//关闭后释放内存

    QRegExp rx2("^[a-zA-Z0-9]+$");
    QRegExpValidator *pReg2 = new QRegExpValidator(rx2, this);
    ui->lineEditNumber->setValidator(pReg2);

    new frmInput(this);

}

Login::~Login()
{
    qDebug()<<__FUNCTION__<<"is running !";
    delete ui;
}


void Login::on_pushButtonLogin_clicked()
{
    int userCnt=0;
    QString name = "root";

    QSettings *configIniRead = new QSettings(CONFIG_NAME, QSettings::IniFormat);
    //将读取到的ini文件保存在QString中，先取值，然后通过toString()函数转换成QString类型
    QString passWord = configIniRead->value(CONFIG_PASSWD_KEY).toString();

    qDebug()<<name<<passWord<<__FUNCTION__;
    if(ui->lineEditUser->text() == name){
        qDebug()<<"username right!";
        if(ui->lineEditNumber->text() == passWord){
            qDebug()<<"passwd right!";
            emit passWordIsRight();//密码正确传信号给Mainwindow,从而显示参数设置界面
            this->close();
        }
        else{
            qDebug()<<"密码错误!";
            QMessageBox msgBox(this);
            msgBox.setText(tr("密码错误，请重新输入"));
            msgBox.exec();
        }
        userCnt=1;
    }
    if(!userCnt)
    {
        QMessageBox msgBox(this);
        msgBox.setText(tr("该用户不存在！"));
        msgBox.exec();
    }
}
