#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setApplicationName("licenseDemo");
    QApplication::setOrganizationDomain("canpool@163.com");
    QApplication::setOrganizationName("canpool");
    QApplication::setApplicationVersion("V1.0.0");

    MainWindow w;
    w.checkLicense();
    w.show();

    return a.exec();
}
