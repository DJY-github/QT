#ifndef FRMWAVECHART_H
#define FRMWAVECHART_H

#include <QWidget>

namespace Ui
{
class frmWaveChart;
}

class frmWaveChart : public QWidget
{
	Q_OBJECT

public:
    explicit frmWaveChart(QWidget *parent = 0);
    ~frmWaveChart();

private:
    Ui::frmWaveChart *ui;
	QTimer *timer;

private slots:
	void initForm();
	void addData();
    void on_ckSmooth_stateChanged(int arg1);
	void on_ckShowHLine_stateChanged(int arg1);
	void on_ckShowPoint_stateChanged(int arg1);
	void on_ckShowPointBg_stateChanged(int arg1);
	void on_btnSetData_clicked();
	void on_btnAddData_clicked();
	void on_btnClearData_clicked();
};

#endif // FRMWAVECHART_H
