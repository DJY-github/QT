//�˿���ס
#ifndef CHECKCUTOMDIALOG_H
#define CHECKCUTOMDIALOG_H

#include <QDialog>

namespace Ui {
class CheckCutomDialog;
}

class CheckCutomDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CheckCutomDialog(QWidget *parent = 0);
    ~CheckCutomDialog();

    void InitForm();

    void writetable();

    //������סʱ�������ݿ��еķ���״̬��
    void UpdateRoomeTableInfo(QString tablename,QString updatename,QString roomNo);
    
private slots:
    void on_pbnCheckOk_clicked();

private:
    Ui::CheckCutomDialog *ui;
};

#endif // CHECKCUTOMDIALOG_H
