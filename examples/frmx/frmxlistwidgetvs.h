#ifndef FRMXLISTWIDGETVS_H
#define FRMXLISTWIDGETVS_H

#include <QWidget>

namespace Ui {
class frmXListWidgetVS;
}

class frmXListWidgetVS : public QWidget
{
    Q_OBJECT

public:
    explicit frmXListWidgetVS(QWidget *parent = 0);
    ~frmXListWidgetVS();

private:
    Ui::frmXListWidgetVS *ui;
};

#endif // FRMXLISTWIDGETVS_H
