#ifndef MYSTATICCLASS_H
#define MYSTATICCLASS_H

#endif // MYSTATICCLASS_H

#include "myinclude.h"

class MyHelper : public QObject
{
public:
    MyHelper();~MyHelper();

    //��ȡ��ǰ·��
    static QString GetCurrentPath()
    {
        return QString(QCoreApplication::applicationDirPath()+"/");
    }

    //��������
    static void PlaySound(QString soundName)
    {
        QSound::play(soundName);
    }

    //��ʱ����
    static void DelayTime(int msc)
    {
        QTime t=QTime::currentTime().addMSecs(msc);
        while(QTime::currentTime()<t)
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents,100);
        }
    }

    //��ȡ��ǰ����ʱ������
    static QString GetLongDateTime()
    {
        QDateTime time=QDateTime::currentDateTime();
        return time.toString("yyyy��MM��dd�� hhʱmm��ss�� dddd");
    }

    //��ȡѡ���ļ�
    static QString GetFileName(QString filter)
    {
        return QFileDialog::getOpenFileName(NULL,tr("ѡ���ļ�"),QCoreApplication::applicationDirPath(),filter);
    }

    //��ȡѡ���ļ�����
    static QStringList GetFileNames(QString filter)
    {
        return QFileDialog::getOpenFileNames(NULL,tr("ѡ���ļ�"),QCoreApplication::applicationDirPath(),filter);
    }

    //��ȡѡ���ļ����е��ļ�
    static QStringList GetFolderFileNames(QStringList filter)
    {
        QStringList fileList;
        QString strFolder = QFileDialog::getExistingDirectory();
        if (!strFolder.length()==0)
        {
            QDir myFolder(strFolder);

            if (myFolder.exists())
            {
                fileList= myFolder.entryList(filter);
            }
        }
        return fileList;
    }

    //����ַ
    static void OpenUrlOrExe(QString url)
    {
        QDesktopServices::openUrl(QUrl(url));
    }

    //�ж��Ƿ�����
    static bool IsLeapYear(QString strDate)
    {
        int year=strDate.left(4).toInt();
        if(((year % 4 ==0) && (year % 100 !=0 ))|| (year % 400 ==0))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    //    //�����Լ�����,��Ҫ#include "windows.h",����ע�͵���Ϊ�˿�ƽ̨
    //    static void KillMe()
    //    {
    //        DWORD dwProcessID=::GetCurrentProcessId();
    //        HANDLE hProcess=::OpenProcess(PROCESS_TERMINATE,FALSE,dwProcessID);
    //        ::TerminateProcess(hProcess,0);
    //        ::CloseHandle(hProcess);
    //    }
};

class FileHelper : public QObject
{
public:
    FileHelper();~FileHelper();

    //�ļ��Ƿ����
    static bool FileExists(QString strFile)
    {
        QFile tempFile(strFile);
        if (tempFile.exists())
        {
            return true;
        }
        return false;
    }

    //�ļ����Ƿ����
    static bool FolderExists(QString strFolder)
    {
        QDir tempFolder(strFolder);
        if(tempFolder.exists())
        {
            return true;
        }
        return false;
    }

    //�Ƴ��ļ�
    static bool RemoveFile(QString strFile)
    {
        return QFile::remove(strFile);
    }

    //�������ļ�
    static bool RenameFile(QString oldName,QString newName)
    {
        return QFile::rename(oldName,newName);
    }

    //��ȡ�ļ�Ŀ¼
    static QString GetBasePath(QString strFullPath)
    {
        QFileInfo fileInfo(strFullPath);
        return fileInfo.path();
    }

    //��ȡ��չ��
    static QString GetExtension(QString strFile)
    {
        QFileInfo fileInfo(strFile);
        return fileInfo.suffix();
    }

    //��ȡ�ļ�������
    static QString GetFolderName(QString strFullPath)
    {
        QString strPath(strFullPath);
        strPath.replace('\\','/');
        int pos=strPath.lastIndexOf('/');
        return strPath.mid(pos+1);
    }

    //�����ļ�
    static bool CopyFile(QString sourceFile, QString targetFile)
    {
        if (FileExists(targetFile))
        {
            int ret=QMessageBox::information(NULL,tr("��ʾ"),tr("�ļ��Ѿ����ڣ��Ƿ��滻��"),QMessageBox::Yes | QMessageBox::No);
            if (ret!=QMessageBox::Yes)
            {
                return false;
            }
        }
        return QFile::copy(sourceFile,targetFile);
    }

    //�ж��Ƿ����ļ�
    static bool IsFile(QString strFile)
    {
        QFileInfo fileInfo(strFile);
        return fileInfo.isFile();
    }

    //�ж��Ƿ����ļ���
    static bool IsFolder(QString strFolder)
    {
        QFileInfo fileInfo(strFolder);
        return fileInfo.isDir();
    }

    //׷���ı�
    static bool AppendText(QString strFile, QString strContent )
    {
        QFile inFile(strFile);
        if (!inFile.open(QIODevice::Append | QIODevice::Text))
        {
            QMessageBox::information(NULL,tr("��ʾ"),tr("���ļ�����"));
            return false;
        }
        QTextStream inStream(&inFile);
        inStream<<strContent;
        inFile.close();
        return true;
    }

    //�����ļ���
    static bool CreateFolder(QString strFolder)
    {
        QDir dir;
        return dir.mkdir(strFolder);
    }

    //�����ļ�
    static bool CreateFile(QString strFile)
    {
        QFile file(strFile);
        if (!file.open(QIODevice::WriteOnly))
        {
            return false;
        }
        file.close();
        return true;
    }

    //��ȡ�ļ�����
    static QString GetFileContent(QString strFile)
    {
        QFile file(strFile);
        QString txt;
        if (!file.open(QIODevice::WriteOnly))
        {
            txt= "";
        }
        else
        {
            txt=file.readAll();
        }
        file.close();
        return txt;
    }

};


class FormHelper : public QObject
{
public:
    FormHelper();~FormHelper();

    static void FormQQ(QWidget *frm,int frmHeight)
    {
        if (frm->windowState()!=Qt::WindowMinimized)
        {
            int DeskX=QCursor::pos().x();
            int DeskY=QCursor::pos().y();

            int FrmLeft=frm->geometry().left();
            int FrmRight=frm->geometry().right();
            int FrmTop=frm->geometry().top();
            int FrmBottom=frm->geometry().bottom();

            int FrmWidth=frm->geometry().width();
            int FrmHeight=frm->geometry().height();

            QDesktopWidget desktop;
            int DeskWidth=desktop.availableGeometry().width();
            //int DeskHeight=desktop.availableGeometry().height();

            if (DeskX>FrmLeft-1 && DeskX<FrmRight && DeskY>FrmTop-1 && DeskY<FrmBottom)
            {
                if (FrmTop<=0 && FrmLeft>5 && FrmLeft<DeskWidth-FrmWidth)
                {
                    frm->rect().setTop(0);
                }
                else if (FrmLeft<=0)
                {
                    frm->rect().setLeft(0);
                }
                else if (FrmLeft+FrmWidth>DeskWidth)
                {
                    frm->rect().setLeft(DeskWidth-FrmWidth);
                }
                else
                {
                    if (frmHeight>0)
                    {
                        frm->rect().setHeight(frmHeight);
                        frmHeight=0;
                    }
                }
            }
            else
            {
                if (frmHeight<1)
                {
                    frmHeight=FrmHeight;
                }

                if (FrmTop<=4 && FrmLeft>5 && FrmLeft<DeskWidth-FrmWidth)
                {
                    frm->rect().setTop(3-FrmHeight);

                    if (FrmLeft<=4)
                    {
                        frm->rect().setLeft(-5);
                    }
                    else if (FrmLeft+FrmWidth>=DeskWidth-4)
                    {
                        frm->rect().setLeft(DeskWidth-FrmWidth+5);
                    }
                }
                else if (FrmLeft<=4)
                {
                    frm->rect().setLeft(3-FrmWidth);
                }
                else if (FrmLeft+FrmWidth>=DeskWidth-4)
                {
                    frm->rect().setLeft(DeskWidth-3);
                }
            }
        }
    }


    //���������ʾ
    static void FormInCenter(QWidget *frm)
    {
        QDesktopWidget desktop;
        int screenX=desktop.availableGeometry().width();
        int screenY=desktop.availableGeometry().height();
        int wndX=frm->width();
        int wndY=frm->height();
        QPoint movePoint(screenX/2-wndX/2,screenY/2-wndY/2);
        frm->move(movePoint);
    }

    //����û����󻯰�ť
    static void FormNoMaxButton(QWidget *frm)
    {
        frm->setWindowFlags(Qt::WindowMinimizeButtonHint);
    }

    //����û����󻯺���С����ť
    static void FormOnlyCloseButton(QWidget *frm)
    {
        frm->setWindowFlags(Qt::WindowMinMaxButtonsHint);
        frm->setWindowFlags(Qt::WindowCloseButtonHint);
    }

    //���ô���͸����
    static void FormOpacity(QWidget *frm,double value)
    {
        frm->setWindowOpacity(value);
    }

    //���岻�ܸı��С
    static void FormNotResize(QWidget *frm)
    {
        frm->setFixedSize(frm->width(),frm->height());
    }

    //����ǰ����ʾ
    static void FormOnTop(QWidget *frm)
    {
        frm->setWindowFlags(Qt::WindowStaysOnTopHint);
    }

    //��������ʾ
    static void FormOnBottom(QWidget *frm)
    {
        frm->setWindowFlags(Qt::WindowStaysOnBottomHint);
    }

    //��ȡ�����С
    static QSize GetDesktopSize()
    {
        QDesktopWidget desktop;
        return QSize(desktop.availableGeometry().width(),desktop.availableGeometry().height());
    }

    //���ñ���ΪGB2312
    static void SetGB2312Code()
    {
       // QTextCodec *codec=QTextCodec::codecForName("GB2312");
        //QTextCodec::setCodecForLocale(codec);
        //QTextCodec::setCodecForCStrings(codec);
       // QTextCodec::setCodecForTr(codec);
    }

    //���ñ���ΪUTF8
    static void SetUTF8Code()
    {
       // QTextCodec *codec=QTextCodec::codecForName("UTF8");
       // QTextCodec::setCodecForLocale(codec);
      //  QTextCodec::setCodecForCStrings(codec);
       // QTextCodec::setCodecForTr(codec);
    }

    //����ȫ��Ϊplastique��ʽ
    static void SetPlastiqueStyle()
    {
        QApplication::setStyle(QStyleFactory::create("Plastique"));
        QApplication::setPalette(QApplication::style()->standardPalette());//�滻Ӧ�ó������ɫ���
    }

    static void SetPlastiqueStyle(QWidget *frm)
    {
        frm->setStyle(QStyleFactory::create("Plastique"));
    }

    static void SetMyStyle(QWidget *frm)
    {
        QString myStyle1="QPushButton {";
        myStyle1.append("border: 2px solid #8f8f91; ");
        myStyle1.append("border-radius: 6px;");
        myStyle1.append("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #f6f7fa, stop: 1 #dadbde); ");
        myStyle1.append("min-width: 80px;}");
        myStyle1.append("QPushButton:pressed {");
        myStyle1.append("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #dadbde, stop: 1 #f6f7fa); }");
        myStyle1.append("QPushButton:default  {");
        myStyle1.append("border-color: navy; /* ʹ�ð�ť��ʾ��ø���ͻ�� */}");

        QString myStyle2="QSlider::groove:horizontal {";
        myStyle2.append("border: 1px solid #999999;");
        myStyle2.append("height: 8px;");
        myStyle2.append("background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);");
        myStyle2.append("margin: 2px 0;}");
        myStyle2.append("QSlider::handle:horizontal {");
        myStyle2.append("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);");
        myStyle2.append("border: 1px solid #5c5c5c;");
        myStyle2.append("width: 18px; margin: -2px 0;");
        myStyle2.append("border-radius: 3px;}");

        QString myStyle3="QGroupBox {";
        myStyle3.append("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,  stop: 0 #E0E0E0, stop: 1 #FFFFFF);");
        myStyle3.append("border: 2px solid gray;");
        myStyle3.append("border-radius: 5px;");
        myStyle3.append("margin-top: 1ex;}");
        myStyle3.append("QGroupBox::title {");
        myStyle3.append("subcontrol-origin: margin; ");
        myStyle3.append("subcontrol-position: top center;");
        myStyle3.append("padding: 0 3px;}");

        frm->setStyleSheet(myStyle1+myStyle2+myStyle3);
    }

    //�ı���ʽ
    static bool InstallStyle(QWidget* window,QString styleFile)
    {
        QFile file(styleFile);
        QString strStyleSheet;
        if (!file.open(QIODevice::WriteOnly))
        {
            strStyleSheet= "";
        }
        else
        {
            strStyleSheet=file.readAll();
        }
        file.close();

        if(strStyleSheet.isEmpty())
        {
            return false;
        }
        window->setStyleSheet(strStyleSheet);
        return true;
    }

    //��ȡICOͼ��
    static QIcon GetLocalFileIcon(QString strFile)
    {
        QFileIconProvider fIconProvider;
        return fIconProvider.icon(QFileInfo(strFile));
    }
};


class ListWidget : public QObject
{
public :
        ListWidget();~ListWidget();

static bool HasTheData(QListWidget* root,int role,const QString& strData)
{
    bool has=false;
    for(int i=0;i<root->count();i++)
    {
        QListWidgetItem* theItem=root->item(i);
        QString tmpData=theItem->data(role).toString();
        if(tmpData==strData)
        {
            has=true;
            break;
        }
    }
    return has;
}

static bool HasTheText(QListWidget* root,const QString& strText)
{
    bool has=false;
    for(int i=0;i<root->count();i++)
    {
        QListWidgetItem* theItem=root->item(i);
        QString tmpData=theItem->text();
        if(tmpData==strText)
        {
            has=true;
            break;
        }
    }
    return has;
}

static int CheckedItemCount(QListWidget* root)
{
    int count=0;
    for(int i=0;i<root->count();i++)
    {
        QListWidgetItem* item=root->item(i);
        if(item->checkState()==Qt::Checked)
        {
            count++;
        }
    }
    return count;
}

static int UncheckedItemCount(QListWidget* root)
{
    int checkedCount=CheckedItemCount(root);
    int totalCount=root->count();
    return totalCount-checkedCount;
}

};


class SettingMgr : public QObject
{
public:
    SettingMgr();~SettingMgr();

    static QString ReadSetting(QString strFile,QString bootName,QString key)
    {
        QSettings settings(strFile,bootName);
        return settings.value(key).toString();
    }

    static void WriteSetting(QString strFile,QString bootName,QString key, QString value)
    {
        QSettings settings(strFile,bootName);
        settings.setValue(key,value);
    }

};


class MyMessageBox : public QObject
{
public:
    MyMessageBox();~MyMessageBox();

    static void ChMessageOnlyOk(QString info)
    {
        QMessageBox msg;
        msg.setWindowTitle(tr("��ʾ"));
        msg.setText(info);
        msg.setIcon(QMessageBox::Information);
        msg.addButton(tr("ȷ��"),QMessageBox::ActionRole);
        msg.exec();
    }

    static void ChMessageOkCancel(QString info)
    {
        QMessageBox msg;
        msg.setWindowTitle(tr("��ʾ"));
        msg.setText(info);
        msg.setIcon(QMessageBox::Information);
        msg.addButton(tr("ȷ��"),QMessageBox::ActionRole);
        msg.addButton(tr("ȡ��"),QMessageBox::ActionRole);
        msg.exec();
    }
};


