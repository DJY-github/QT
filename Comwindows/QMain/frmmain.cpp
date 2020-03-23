#include "frmmain.h"
#include "ui_frmmain.h"
#include <QtGui>

frmMain::frmMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);
    this->InitStyle();
    this->InitForm();
}

frmMain::~frmMain()
{
    delete ui;
}

void frmMain::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void frmMain::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void frmMain::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void frmMain::InitStyle()
{
    this->mousePressed = false;
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
}

void frmMain::InitForm()
{
    bg = "main2.jpg";
    QList<QToolButton *> btns = this->findChildren<QToolButton *>();
    foreach (QToolButton * btn, btns) {
        connect(btn, SIGNAL(clicked()), this, SLOT(buttonClick()));
    }
}

void frmMain::buttonClick()
{
    QToolButton *btn = (QToolButton *)sender();
    QString objName = btn->objectName();
    if (objName == "btnCOMTool") {
        if (bg == "main1.jpg") {
            bg = "main2.jpg";
        } else if (bg == "main2.jpg") {
            bg = "main3.jpg";
        } else if (bg == "main3.jpg") {
            bg = "main4.jpg";
        } else if (bg == "main4.jpg") {
            bg = "main5.jpg";
        } else if (bg == "main5.jpg") {
            bg = "main1.jpg";
        }
        QString qss = QString("QWidget#frm{background-image: url(:/image/%1);}").arg(bg);
        qss += "QToolButton{color:#E7ECF0;background-color:rgba(0,0,0,0);border-style:none;}";
        this->setStyleSheet(qss);
    } else if (objName == "btnAddressTool") {

    } else if (objName == "btnTCPTool") {
        this->close();
    } else if (objName == "btnCOMTCPTool") {

    } else if (objName == "btnDefence") {

    } else if (objName == "btnHostTool") {

    } else if (objName == "btnLinkTool") {

    } else if (objName == "btnMaiChongTool") {

    } else if (objName == "btnPlot") {

    } else if (objName == "btnZhangLi4Tool") {

    } else if (objName == "btnZhangLi5Tool") {

    } else if (objName == "btnZhangLiTool") {

    }
}
