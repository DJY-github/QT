﻿#pragma execution_character_set("utf-8")

#include "frmnavlistview.h"
#include "frmnavlistviewform.h"
#include "qtabwidget.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setFont(QFont("Microsoft Yahei", 9));

#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("gbk");
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
#endif
#if 0
    QTabWidget w;
    w.addTab(new frmNavListView, "树状导航控件");
    w.addTab(new frmNavListViewForm, "树状导航界面");
    w.setWindowTitle("树状导航示例");
    w.resize(800, 600);
    w.show();
#else
    frmNavListViewForm w;
    w.show();
#endif
    return a.exec();
}
