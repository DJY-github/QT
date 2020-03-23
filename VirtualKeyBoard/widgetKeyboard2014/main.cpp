#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include "mainwindow.h"
#include "tester.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication    app(argc, argv);
    QTranslator     qtTranslator;
    QString         lang = "virtualBoard_" + QLocale::system().name().mid(0, 2);
    Tester          w;

    //QGuiApplication::setApplicationName("widgetKeyboard");
    if (qtTranslator.load(lang))
        app.installTranslator(&qtTranslator);
	else
        qDebug("Failed to load a translation for QT in your local language");
	w.show();
	return app.exec();
}
