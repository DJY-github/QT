#ifndef FRMCUSTOMGRAPHICS_H
#define FRMCUSTOMGRAPHICS_H

#include <QWidget>

namespace Ui {
class frmCustomGraphics;
}

class frmCustomGraphics : public QWidget
{
    Q_OBJECT

public:
    explicit frmCustomGraphics(QWidget *parent = 0);
    ~frmCustomGraphics();

private:
    Ui::frmCustomGraphics *ui;
};

#endif // FRMCUSTOMGRAPHICS_H
