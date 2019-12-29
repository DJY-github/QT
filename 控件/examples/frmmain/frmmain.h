#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QWidget>

class frmGauge;
class frmProgress;
class frmNav;
class frmWave;
class frmRuler;
class frmSlider;
class frmBar;
class frmColor;
class frmImage;
class frmPainter;
class frmOther;
class frmDemo;
class frmVideo;
class frmX;
class frmCommon;

namespace Ui
{
    class frmMain;
}

class frmMain : public QWidget
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::frmMain *ui;
    bool needDraw;
    QStringList listDraw;
    QPixmap bgPix;

    QStringList listItem;
    QStringList listParent;
    QStringList listGauge;
    QStringList listProgress;
    QStringList listNav;
    QStringList listWave;
    QStringList listRuler;
    QStringList listSlider;
    QStringList listBar;
    QStringList listColor;
    QStringList listImage;
    QStringList listPainter;
    QStringList listOther;
    QStringList listDemo;
    QStringList listVideo;
    QStringList listX;
    QStringList listCommon;
    QStringList listHide;

    frmGauge *gauge;
    frmProgress *progress;
    frmNav *nav;
    frmWave *wave;
    frmRuler *ruler;
    frmSlider *slider;
    frmBar *bar;
    frmColor *color;
    frmImage *image;
    frmPainter *painter;
    frmOther *other;
    frmDemo *demo;
    frmVideo *video;
    frmX *x;
    frmCommon *common;

private slots:
    void initForm();
    void addItem();
    void addItem(const QString &parentName, const QStringList &childNames);

    void addGauge();
    void addProgress();
    void addNav();
    void addWave();
    void addRuler();
    void addSlider();
    void addBar();
    void addColor();
    void addImage();
    void addPainter();
    void addOther();
    void addDemo();
    void addVideo();
    void addX();
    void addCommon();
    void addHide();

private slots:
    void pressed(const QString &childText, const QString &parentText);
};

#endif // FRMMAIN_H
