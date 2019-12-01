#ifndef FRMLUNARCALENDARINFO_H
#define FRMLUNARCALENDARINFO_H

#include <QWidget>
#include <QDate>

namespace Ui {
class frmLunarCalendarInfo;
}

class frmLunarCalendarInfo : public QWidget
{
    Q_OBJECT

public:
    explicit frmLunarCalendarInfo(QWidget *parent = 0);
    ~frmLunarCalendarInfo();

private:
    Ui::frmLunarCalendarInfo *ui;

private slots:
    void on_calendarWidget_clicked(const QDate &date);
};

#endif // FRMLUNARCALENDARINFO_H
