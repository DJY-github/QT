#ifndef FRMPROGRESS_H
#define FRMPROGRESS_H

#include <QWidget>

namespace Ui {
class frmProgress;
}

class frmProgress : public QWidget
{
    Q_OBJECT

public:
    explicit frmProgress(QWidget *parent = 0);
    ~frmProgress();

private:
    Ui::frmProgress *ui;

private slots:
    void initForm();

public slots:
    void setIndex(int index);
};

#endif // FRMPROGRESS_H
