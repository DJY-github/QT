#include "usermanger.h"
#include "ui_usermanger.h"
#include <QTextCodec>
#include <QMessageBox>
#include <QDebug>

userManger::userManger(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userManger)
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    ui->setupUi(this);

}

userManger::~userManger()
{
    delete ui;
}

void userManger::on_pushButtonConfirm_clicked()
{
    //1.判断用户名是否为空
    //2.对比两次密码是否一致
    //3.两次密码一致后把用户名和密码存入数据库中

    if(ui->lineEditNewPassword->text().isEmpty()){
        QMessageBox msgBox(this);
        msgBox.setText("密码不能为空！");
        msgBox.exec();
    }else{
        if(ui->lineEditConfirm->text() == ui->lineEditNewPassword->text()){//如果两次密码一致，将用户信息存入数据库中

        }else{//如果两次密码不一致
            QMessageBox msgBox(this);
            msgBox.setText("两次输入密码不一致，请重新输入！");
            msgBox.exec();
        }
    }

}
