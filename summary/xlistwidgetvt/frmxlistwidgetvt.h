#ifndef FRMXLISTWIDGETVT_H
#define FRMXLISTWIDGETVT_H

#include <QWidget>

namespace Ui {
class frmXListWidgetVT;
}

class frmXListWidgetVT : public QWidget
{
    Q_OBJECT

public:
    explicit frmXListWidgetVT(QWidget *parent = 0);
    ~frmXListWidgetVT();

private:
    Ui::frmXListWidgetVT *ui;
};

#endif // FRMXLISTWIDGETVT_H
