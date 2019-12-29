#ifndef FRMCOLORSTYLE_H
#define FRMCOLORSTYLE_H

#include <QWidget>

class ColorStyle;

namespace Ui {
class frmColorStyle;
}

class frmColorStyle : public QWidget
{
    Q_OBJECT

public:
    explicit frmColorStyle(QWidget *parent = 0);
    ~frmColorStyle();

private:
    Ui::frmColorStyle *ui;
    QList<ColorStyle *> widgets;

private slots:
    void initForm();
    void selected(const QColor &color);
    void sliderReleased();

signals:
    void changeStyle(const QString &color);

};

#endif // FRMCOLORSTYLE_H
