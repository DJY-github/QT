#pragma execution_character_set("utf-8")

#include "pinyin.h"
#include "qmutex.h"
#include "qfile.h"
#include "qtextstream.h"
#include "qdatetime.h"
#include "qapplication.h"
#include "qdebug.h"

QScopedPointer<PinYin> PinYin::self;
PinYin *PinYin::Instance()
{
    if (self.isNull()) {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if (self.isNull()) {
            self.reset(new PinYin);
        }
    }

    return self.data();
}

PinYin::PinYin(QObject *parent) : QObject(parent)
{
}

QMap<QString, QString> PinYin::getDict(const QString &fileName)
{
    QTime time;
    time.start();

    QMap<QString, QString> map;
    QFile file(fileName);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        //QTextStream方法读取速度至少快30%
#if 0
        while(!file.atEnd()) {
            QString line = file.readLine();
            line = line.trimmed();
            if (!line.isEmpty()) {
                QStringList list = line.split("=");
                map.insert(list.at(0), list.at(1));
            }
        }
#else
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            line = line.trimmed();
            if (!line.isEmpty()) {
                QStringList list = line.split("=");
                map.insert(list.at(0), list.at(1));
            }
        }
#endif
        file.close();
    }

    //qDebug() << QString("read %1 finsh,used %2 ms").arg(fileName).arg(time.elapsed());
    return map;
}

void PinYin::initPath(const QString &path)
{
    QString pinyin_one = path + "/pinyin_one.txt";
    QString pinyin_group = path + "/pinyin_group.txt";
    QString pinyin_fanti = path + "/pinyin_fanti.txt";
    this->initDict(pinyin_one, pinyin_group, pinyin_fanti);
}

void PinYin::initDict(const QString &pinyin_one, const QString &pinyin_group, const QString &pinyin_fanti)
{
    map_one = getDict(pinyin_one);
    map_group = getDict(pinyin_group);
    map_fanti = getDict(pinyin_fanti);
}

QChar PinYin::getFanTi(const QChar &letter)
{
    QString result = map_fanti.key(letter);
    return result.isEmpty() ? letter : result.at(0);
}

QString PinYin::getFanTi(const QString &str)
{
    QString result;
    int len = str.length();
    for (int i = 0; i < len; i++) {
        result += getFanTi(str.at(i));
    }

    return result;
}

QChar PinYin::getJianTi(const QChar &letter)
{
    QString result = map_fanti.value(letter);
    return result.isEmpty() ? letter : result.at(0);
}

QString PinYin::getJianTi(const QString &str)
{
    QString result;
    int len = str.length();
    for (int i = 0; i < len; i++) {
        result += getJianTi(str.at(i));
    }

    return result;
}

bool PinYin::isChinese(const QChar &letter)
{
    bool result = (letter == '〇') || (letter.unicode() >= 0x4e00 && letter.unicode() <= 0x9fa5);
    return result;
}

QStringList PinYin::formatPinyin(const QString &str, const PinYin::Format &format)
{
    //所有带声调的拼音字母
    QString toneStr = "aeiouv";
    QString toneList = "āáǎàēéěèīíǐìōóǒòūúǔùǖǘǚǜ";
    QString pinyin = str;
    QStringList listPinYin = pinyin.split(",");

    if (format == PinYin::Format_None) {
        //替换带音调的字符
        for (int i = toneList.length() - 1; i >= 0; i--) {
            QString originalChar = toneList.at(i);
            QString replaceChar = toneStr.at(((i - i % 4)) / 4);
            pinyin = pinyin.replace(originalChar, replaceChar);
        }

        //将拼音中的ü替换为v
        pinyin = pinyin.replace("ü", "v");
        listPinYin = pinyin.split(",");
    } else if (format == PinYin::Format_Number) {
        for (int i = listPinYin.length() - 1; i >= 0; i--) {
            //将拼音中的ü替换为v
            QString originalPinyin = listPinYin.at(i);
            originalPinyin = originalPinyin.replace("ü", "v");

            bool hasMarkedChar = false;
            for (int j = originalPinyin.length() - 1; j >= 0; j--) {
                //搜索带声调的拼音字母,如果存在则替换为对应不带声调的英文字母,后面带数字声调数
                QString originalChar = originalPinyin.at(j);
                if (originalChar < "a" || originalChar > "z") {
                    int indexInAllMarked = toneList.indexOf(originalChar);
                    int toneNumber = indexInAllMarked % 4 + 1;
                    QString replaceChar = toneStr.at(((indexInAllMarked - indexInAllMarked % 4)) / 4);
                    listPinYin[i] = originalPinyin.replace(originalChar, replaceChar) + QString::number(toneNumber);
                    hasMarkedChar = true;
                    break;
                }
            }

            //找不到带声调的拼音字母说明是轻声,用数字5表示
            if (!hasMarkedChar) {
                listPinYin[i] = originalPinyin + "5";
            }
        }
    }

    return listPinYin;
}

QStringList PinYin::getPinYin(const QChar &letter, const PinYin::Format &format)
{
    QStringList result;
    QString pinyin = map_one.value(letter);
    if (!pinyin.isEmpty()) {
        result = formatPinyin(pinyin, format);
    }

    return result;
}

QString PinYin::getPinYin(const QString &str, const QString &separator, const PinYin::Format &format)
{
    QString result;
    QString chinese = getJianTi(str);

    int len = chinese.length();
    for (int i = 0; i < len; i++) {
        //判断是否为汉字或者〇,不是汉字则添加原字符
        QChar letter = chinese.at(i);
        if (isChinese(letter)) {
            //多音字识别处理,将当前汉字依次与后面的3个 2个 1个汉字组合,判断下是否存在多音字词组
            bool isFoundFlag = false;
            int rightMove = 3;
            for (int rightIndex = (i + rightMove) < len ? (i + rightMove) : (len - 1); rightIndex > i; rightIndex--) {
                QString group = str.mid(i, rightIndex + 1);
                if (map_group.keys().indexOf(group) != -1) {
                    QStringList listPinYin = formatPinyin(map_group.value(group), format);
                    int len = listPinYin.length();
                    for (int j = 0; j < len; j++) {
                        result.append(listPinYin.at(j));
                        if (j < len - 1) {
                            result.append(separator);
                        }
                    }

                    i = rightIndex;
                    isFoundFlag = true;
                    break;
                }
            }

            if (!isFoundFlag) {
                QStringList listPinYin = getPinYin(str.at(i), format);
                if (!listPinYin.isEmpty()) {
                    result.append(listPinYin.at(0));
                } else {
                    result.append(str.at(i));
                }
            }

            if (i < len - 1) {
                result.append(separator);
            }
        } else {
            result.append(letter);
            if ((i + 1) < len && isChinese(str.at(i + 1))) {
                result.append(separator);
            }
        }
    }

    return result;
}
