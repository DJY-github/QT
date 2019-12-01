#pragma execution_character_set("utf-8")

#include "frmtumbler.h"
#pragma execution_character_set("utf-8")

#include "frmtumblerdatetime.h"
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

    QTabWidget w;
    w.addTab(new frmTumbler, "滑动选择器");
    w.addTab(new frmTumblerDateTime, "日期时间选择器");
    w.setWindowTitle("滑动选择器示例");
    w.resize(500, 300);
    w.setCurrentIndex(1);
    w.show();

    return a.exec();
}
