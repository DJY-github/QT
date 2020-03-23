#ifndef CUSTOMERWINDGET_H
#define CUSTOMERWINDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QSqlQueryModel>
#include <QTableView>

#include "roompicdialog.h"

namespace Ui {
class CustomerWindget;
}

class CustomerWindget : public QWidget
{
    Q_OBJECT
    
public:
    explicit CustomerWindget(QWidget *parent = 0);
    ~CustomerWindget();

    void InitForm();

    //��������Ϣ��ʾ��tableview��
    void BindRoomInfo(QString tableName, QTableView *tableView,
                       QString columnNames[], int columnWidths[]);
    //��������Ϣ��ʾ��tableview��
    void BindCustomeInfo(QString tableName, QTableView *tableView,
                       QString columnNames[], int columnWidths[]);

    //��ȡ��ǰ�û���
    QString GetCutrrentUserName(QString tablename);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
    
private slots:
    void on_btnMenu_Max_clicked();

    void on_btnMenu_Min_clicked();

    void on_btnMenu_Close_clicked();

    void on_punroom_clicked();

    void on_pbnGuest_clicked();

    void on_pbnROK_clicked();

    void on_comboBoxRoomType_activated(const QString &arg1);

    void on_pbnroomPicture_clicked();

    void on_pbnmodify_clicked();

    void on_pbuModifyOk_clicked();

    void on_pbnCancle_clicked();

public slots:
    void showCustomInfo();

private:
    Ui::CustomerWindget *ui;

    QPoint mousePoint;
    bool mousePressed;
    bool max;
    QRect location;

    QSqlQueryModel *QueryModel;             //��ѯģ��
    QSqlQueryModel *customModel;            //
    QTableView *TableView;                  //��ʾ���ݵı�����

    QString ColumnNames[4];                 //������������
    int ColumnWidths[4];                    //�п���������

    QString CustomeColumnNames[8];         //������������
    int CustomeColumnWidths[8];            //�п���������

    RoomPicDialog *roompicture;             //������Ϣ�鿴����
};

#endif // CUSTOMERWINDGET_H
