#ifndef FRMTILEDBG_H
#define FRMTILEDBG_H

#include <QWidget>

namespace Ui {
class frmTiledBg;
}

class frmTiledBg : public QWidget
{
    Q_OBJECT

public:
    explicit frmTiledBg(QWidget *parent = 0);
    ~frmTiledBg();

private:
    Ui::frmTiledBg *ui;

private slots:
    void initForm();
};

#endif // FRMTILEDBG_H
