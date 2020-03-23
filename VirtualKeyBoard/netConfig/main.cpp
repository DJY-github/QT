#include "def.h"
#include "mainwindow.h"
#include "frminput.h"
#include "QSettings"
#include "QTextCodec"
#include <QApplication>


void iniFileInit()
{
    QString path;
    path= QDir::currentPath()+ "/"+CONFIG_NAME;

    QFileInfo fileInfo(path);
    if(!fileInfo.isFile())
    {
        //Qt中使用QSettings类读写ini文件
        //QSettings构造函数的第一个参数是ini文件的路径,第二个参数表示针对ini文件,第三个参数可以缺省
        QSettings *configIniWrite = new QSettings(CONFIG_NAME, QSettings::IniFormat);
        //向ini文件中写入内容,setValue函数的两个参数是键值对
        //向ini文件的第一个节写入内容,ip节下的第一个参数
        configIniWrite->setValue("ip/ip", "192.168.0.1");
        //向ini文件的第二个节写入内容,port节下的第一个参数
        configIniWrite->setValue("port/open", "333");
        //写入完成后删除指针
        configIniWrite->setValue(CONFIG_PASSWD_KEY,"123");
        delete configIniWrite;
    }

}



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    iniFileInit();
    MainWindow w;

    //    frmInput *input = new frmInput(&w);

    w.show();


    return a.exec();
}
