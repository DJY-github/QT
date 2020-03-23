#include "mythread.h"
#include <QDateTime>

Mythread::Mythread(QObject *parent) :
    QThread(parent)
{
    /***************����һ����ʱ����������ʾϵͳ��ǰ��ʱ��*************/
    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(showTimesslot));
    timer->start(1000);
}

void Mythread::run()
{
    showTimesslot();
}

void Mythread::SetCurrentTime(QLabel *label)
{
    curlabel = label;
}

void Mythread::showTimesslot()
{
    curlabel->setText(QDateTime::currentDateTime().toString(tr("yyyy-MM-dd\ndddd HH:mm")));
    sleep(1);
}
