#pragma execution_character_set("utf-8")

#include "frmtelwidget.h"
#include "ui_frmtelwidget.h"
#include "qmessagebox.h"
#include "qdebug.h"



frmTelWidget::frmTelWidget(QWidget *parent) : QWidget(parent), ui(new Ui::frmTelWidget)
{
    ui->setupUi(this);
    this->initForm();
}

frmTelWidget::~frmTelWidget()
{
    delete ui;
}

void frmTelWidget::initForm()
{
    //绑定单击事件
    connect(ui->telWidget, SIGNAL(telClicked(QString, QString, QString)),
            this, SLOT(telClicked(QString, QString, QString)));

    ui->telWidget->setBgImage(QPixmap(":/image/bg.jpg"));
    //ui->telWidget->setBgColor(QColor(40, 45, 48));

    //设置类背景图片则优先取背景图片,否则样式为中间圆形
    //ui->telWidget->setTelHighBgImage(QPixmap(":/image/letter.png"));
    ui->telWidget->setTelHighBgColor(QColor(0, 0, 0, 130));

#if 1
    ui->telWidget->setTelHighBgColor(QColor(255, 255, 255, 100));
    ui->telWidget->setTelBannerBgColor(QColor(255, 255, 255, 50));
    ui->telWidget->setTelBannerTextColor(QColor(255, 255, 255));
    ui->telWidget->setTelLetterNormalColor(QColor(255, 255, 255));
    ui->telWidget->setTelLetterHighColor(QColor(27, 188, 155));
    ui->telWidget->setTelButtonNameColor(QColor(255, 255, 255));
    ui->telWidget->setTelButtonTypeColor(QColor(200, 200, 200));
    ui->telWidget->setTelPanelNormalColor(QColor(255, 255, 255, 100));
    ui->telWidget->setTelPanelHighColor(QColor(255, 255, 255, 200));
#endif

    //设置联系人信息集合
    QStringList listName, listType, listTel;
    QList<QPixmap> listPix;

    //123许    、许    *许    @++许    さぎす许    ~许    ???许    厤瀵硅
#if 0
    listName << "张三" << "李四" << "王二" << "123许" << "、许" << "张五";
    listType << "家里" << "公司" << "" << "住宅" << "住宅" << "住宅";
    listTel << "12866666666" << "02162569999" << "15622222222" << "13888888888" << "13888888888" << "13888888888";
    listPix << QPixmap(":/image/img1.jpg") << QPixmap(":/image/img2.jpg") << QPixmap(":/image/img3.jpg") << QPixmap(":/image/img4.jpg") << QPixmap(":/image/img4.jpg") << QPixmap(":/image/img4.jpg");
#else
    QStringList list;
    list << "住宅" << "家里" << "公司";
    for (int i = 0; i < 550; i++) {
        //设置字母属性
        QString letter;
        if (i < 10) {
            letter = "A";
        } else if (i < 23) {
            letter = "B";
        } else if (i < 45) {
            letter = "C";
        } else if (i < 80) {
            letter = "D";
        } else if (i < 100) {
            letter = "E";
        } else if (i < 130) {
            letter = "F";
        } else if (i < 160) {
            letter = "G";
        } else if (i < 180) {
            letter = "H";
        } else if (i < 200) {
            letter = "I";
        } else if (i < 230) {
            letter = "J";
        } else if (i < 250) {
            letter = "K";
        } else if (i < 260) {
            letter = "L";
        } else if (i < 270) {
            letter = "M";
        } else if (i < 280) {
            letter = "N";
        } else if (i < 290) {
            letter = "O";
        } else if (i < 300) {
            letter = "P";
        } else if (i < 310) {
            letter = "Q";
        } else if (i < 330) {
            letter = "R";
        } else if (i < 350) {
            letter = "S";
        } else if (i < 380) {
            letter = "T";
        } else if (i < 400) {
            letter = "U";
        } else if (i < 430) {
            letter = "V";
        } else if (i < 450) {
            letter = "W";
        } else if (i < 470) {
            letter = "X";
        } else if (i < 500) {
            letter = "Y";
        } else {
            letter = "Z";
        }

        //统计下当前该字母的有多少
        int count = 1;
        foreach (QString name, listName) {
            if (QString(name.at(0)) == letter) {
                count++;
            }
        }

        listName << QString("%1 %2").arg(letter).arg(count, 2, 10, QChar('0'));
        listType << list.at(qrand() % 3);
        listTel << QString("1381234%1").arg(qrand() % 10000, 3, 10, QChar('0'));
        listPix << QPixmap(QString(":/image/img%1.jpg").arg(qrand() % 10));
    }
#endif

    ui->telWidget->setInfo(listName, listType, listTel, listPix);
}

void frmTelWidget::telClicked(const QString &name, const QString &type, const QString &tel)
{
    QString info = QString("姓名: %1  类型: %2  电话: %3").arg(name).arg(type).arg(tel);
    QMessageBox::information(this, "单击", info);
}

void frmTelWidget::on_btnAdd_clicked()
{
    QString name = ui->txtName->text().trimmed();
    QString type = ui->txtType->text().trimmed();
    QString tel = ui->txtTel->text().trimmed();
    ui->telWidget->addInfo(name, type, tel, QPixmap(":/image/tel.png"));
}
