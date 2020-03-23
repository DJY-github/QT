#include <QtWidgets>
#include "frmmain.h"

#include <QTextCodec>
//#include <QDesktopWidget>
//#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //֧�����ı���


    //���������ʾ
    QDesktopWidget *desktop=QApplication::desktop();
    int width=desktop->width();
    int height=desktop->height();

    frmMain w;
    //���ô���û����󻯰�ť
    w.setWindowFlags(Qt::WindowMinimizeButtonHint);
    w.move((width-w.width())/2,(height-w.height())/2);
    w.setFixedSize(w.width(),w.height());
    w.show();
    //Ӧ����ʽ
    QApplication::setStyle(QStyleFactory::create("Plastique"));
    QApplication::setPalette(QApplication::style()->standardPalette());

    return a.exec();
}
