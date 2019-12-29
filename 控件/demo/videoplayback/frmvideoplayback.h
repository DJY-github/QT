#ifndef FRMVIDEOPLAYBACK_H
#define FRMVIDEOPLAYBACK_H

#include <QWidget>

namespace Ui
{
class frmVideoPlayback;
}

class frmVideoPlayback : public QWidget
{
	Q_OBJECT

public:
    explicit frmVideoPlayback(QWidget *parent = 0);
    ~frmVideoPlayback();

private:
    Ui::frmVideoPlayback *ui;

private slots:
    void initForm();

};

#endif // FRMVIDEOPLAYBACK_H
