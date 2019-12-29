#ifndef FRMMAGICPOOL_H
#define FRMMAGICPOOL_H

#include <QWidget>

namespace Ui {
class frmMagicPool;
}

class frmMagicPool : public QWidget
{
    Q_OBJECT

public:
    explicit frmMagicPool(QWidget *parent = 0);
    ~frmMagicPool();

private:
    Ui::frmMagicPool *ui;
};

#endif // FRMMAGICPOOL_H
