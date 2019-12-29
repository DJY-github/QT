#ifndef FRMCOMMON_H
#define FRMCOMMON_H

#include <QWidget>

namespace Ui {
class frmCommon;
}

class frmCommon : public QWidget
{
    Q_OBJECT

public:
    explicit frmCommon(QWidget *parent = 0);
    ~frmCommon();

private:
    Ui::frmCommon *ui;

private slots:
    void initForm();

public slots:
    void setIndex(int index);
};

#endif // FRMCOMMON_H
