#include "demo.h"
#include "ui_demo.h"
#include "keyboard.h"

Demo::Demo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Demo)
{
    ui->setupUi(this);

    ui->lineEdit->installEventFilter(this);
}

Demo::~Demo()
{
    delete ui;
}

bool Demo::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->lineEdit && event->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard();
    }

    return QWidget::eventFilter(watched, event);
}

void Demo::callKeyBoard()
{
    KeyBoard *keyBoard = new KeyBoard(0, ui->lineEdit);
    keyBoard->show();
}
