#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "def.h"
#include "ui_mainwindow.h"
#include "usermanger.h"
#include "frminput.h"
#include "QTextCodec"
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    ui->setupUi(this);
    ui->tabWidget->hide();

    ui->tabWidget->setCurrentIndex(0);


    QRegExp rx1("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");
    QRegExpValidator *pReg1 = new QRegExpValidator(rx1, this);
    ui->lineEdit_ip->setValidator(pReg1);

    QRegExp rx2("^([0-9a-fA-F]{2})(([:-][0-9a-fA-F]{2}){5})$");
    QRegExpValidator *pReg2 = new QRegExpValidator(rx2, this);
    ui->lineEdit_mac->setValidator(pReg2);

    ui->buttonBox->button(QDialogButtonBox::Reset)->setText(tr("复位"));
    ui->buttonBox->button(QDialogButtonBox::SaveAll)->setText(tr("保存全部"));

    QPushButton *resetButton = ui->buttonBox->button(QDialogButtonBox::Reset);
    QPushButton *saveAllButton = ui->buttonBox->button(QDialogButtonBox::SaveAll);

    connect(resetButton, SIGNAL(clicked()), this, SLOT(resetButtonClicked()));
    connect(saveAllButton, SIGNAL(clicked()), this, SLOT(saveAllButtonClicked()));

    uiUserMangerInit();

    mLogin = new Login(this);
    mLogin->show();

    QObject::connect(mLogin, SIGNAL(passWordIsRight()), this, SLOT(showSetPage()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::uiUserMangerInit()
{
    QRegExp rx("^[a-zA-Z0-9]+$");
    QRegExpValidator *pReg = new QRegExpValidator(rx, this);
    ui->lineEditConfirm->setValidator(pReg);
    ui->lineEditNewPassword->setValidator(pReg);
    ui->lineEditOldPassword->setValidator(pReg);

}

void MainWindow::resetButtonClicked()
{
    ui->lineEdit_ip->setText("");
    ui->lineEdit_mac->setText("");
    ui->lineEdit_netmask->setText("");
}

void MainWindow::saveAllButtonClicked()
{
    QMessageBox msgBox(this);
    msgBox.setText(tr("保存成功"));
    msgBox.exec();
}

void MainWindow::showSetPage()
{
    ui->tabWidget->show();
    frmInput *input =  new frmInput(this);
    input->show();
}

void MainWindow::on_pushButton_user_clicked()
{
    userManger *user = new userManger();
    user->show();

}

void MainWindow::on_pushButtonConfirm_clicked()
{
    QMessageBox msgBox(this);
    QSettings *configIniRead = new QSettings(CONFIG_NAME, QSettings::IniFormat);
    //将读取到的ini文件保存在QString中，先取值，然后通过toString()函数转换成QString类型
    QString passWord = configIniRead->value(CONFIG_PASSWD_KEY).toString();


    if(ui->lineEditOldPassword->text() != passWord)
    {
        msgBox.setText(tr("原密码错误，请重新输入"));
        msgBox.exec();
    }
    else if(ui->lineEditNewPassword->text().isEmpty()&&  ui->lineEditConfirm->text().isEmpty())
    {
        msgBox.setText(tr("请输入新密码"));
        msgBox.exec();
    }else if(ui->lineEditNewPassword->text() != ui->lineEditConfirm->text())
    {
        msgBox.setText(tr("两次密码不一致，请重新输入"));
        msgBox.exec();
        ui->lineEditNewPassword->setText("");
        ui->lineEditConfirm->setText("");
    }else
    {
        //Qt中使用QSettings类读写ini文件
        //QSettings构造函数的第一个参数是ini文件的路径,第二个参数表示针对ini文件,第三个参数可以缺省
        QSettings *configIniWrite = new QSettings(CONFIG_NAME, QSettings::IniFormat);
        //向ini文件中写入内容,setValue函数的两个参数是键值对
        configIniWrite->setValue(CONFIG_PASSWD_KEY,ui->lineEditConfirm->text());
        delete configIniWrite;

        msgBox.setText(tr("密码修改成功"));
        msgBox.exec();
    }






}
