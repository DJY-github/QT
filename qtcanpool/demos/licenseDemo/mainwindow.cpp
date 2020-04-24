#include "mainwindow.h"

#include <QDebug>
#include <QApplication>

#include "licensedialog.h"

#include "license/nrlicense.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(300, 200);
}

MainWindow::~MainWindow()
{
}

void MainWindow::checkLicense()
{
    QString softname = QApplication::applicationName();
    NR_STATUS status = CheckLicense(softname.toLocal8Bit().data());

    if (status > 0) {
        return;
    }

    LicenseDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        ;
    } else {
        exit(1);
    }
}
