#ifndef FRMBARVUMETER_H
#define FRMBARVUMETER_H

#include <QWidget>

namespace Ui {
class frmBarVUMeter;
}

class frmBarVUMeter : public QWidget
{
    Q_OBJECT

public:
    explicit frmBarVUMeter(QWidget *parent = 0);
    ~frmBarVUMeter();

private:
    Ui::frmBarVUMeter *ui;

private slots:
    void initForm();
    void updateValue();
};

#endif // FRMBARVUMETER_H
