#ifndef FRMMAGICFISH_H
#define FRMMAGICFISH_H

#include <QWidget>

namespace Ui {
class frmMagicFish;
}

class frmMagicFish : public QWidget
{
    Q_OBJECT

public:
    explicit frmMagicFish(QWidget *parent = 0);
    ~frmMagicFish();

private:
    Ui::frmMagicFish *ui;

private slots:
    void initForm();
};

#endif // FRMMAGICFISH_H
