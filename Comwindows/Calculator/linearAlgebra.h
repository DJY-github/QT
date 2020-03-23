#ifndef LINEARALGEBRA_H
#define LINEARALGEBRA_H
#include"ui_linearAlgebra.h"
class LinearAlgebra:public QWidget, public Ui_linearAlgebra
{
    Q_OBJECT
public:
    LinearAlgebra(QWidget* parent=0);
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void changeRow(int row);
    void changeCol(int col);
    void changeColWidth(int colWidth);

    void on_inputPushButton_clicked();
    void on_outputPushButton_clicked();
    void on_inputComboBox_activated(int Index);
    void on_outputComboBox_activated(int Index);
    void on_Calc_pushButton_clicked();
    void on_clearPushButton_clicked();
protected:
    bool eventFilter(QObject *target, QEvent *event);
protected:
      void dragEnterEvent(QDragEnterEvent *event);
      void dropEvent(QDropEvent *event);
private:
      bool readFile(const QString &fileName);
private:
    double **matrix[4];
    bool isAssiged[4];
    int matrixRow[4],matrixCol[4];

    unsigned ladderSwapCount[4];            //���ݻ������н�������
    int *pivcol[4],*augPivcol;              //��¼���ݻ������н���������
    double **ladderMatrix[4];               //���ݾ���
    bool isLadder[4];                       //�Ƿ��Ѿ����ݻ�
    int Rank[4];                            //�������
    double Det[4];                          //���������ʽֵ
    double *eigen_Value_Real[4];            //���������ֵ��ʵ��
    double *eigen_Value_Comp[4];            //���������ֵ���鲿
protected:
    void assign(int Index1,int Index2);     //��ֵ
    void assign(int Index,double **a,int row,int col);
    bool add(int Index,int Index1,int Index2);//matrix[Index]=matrix[Index1]+matrix[Index2]
    bool subtract(int Index,int Index1,int Index2);//����
    bool multiply(int Index,int Index1,int Index2);//�˷�
    void multiply(int Index1,double n,int Index2); //����
    bool power(int Index1,int Index2,int n);       //����
    bool transpose(int Index);              //��ת��
    bool adjoint(int Index);                //��������
    bool ladder(int Index);                 //����ݾ���
    int augLadder();                        //���������Ľ��ݾ���,��������������
    void rank(int Index);                   //��������
    void det(int Index, bool val=0);        //������ʽ��ֵ
    bool inver(int Index);                  //�������
    bool generInver(int Index);             //����������
    bool matrixQR(int Index);               //��QR�ֽ�
    void homogen(int Index);                //��������Է�����ͨ��
    bool inhomogen(int Index);              //���������Է�����ͨ��
    void eigenValue(int Index, bool val=0); //������ֵ
    void maxEigenValue(int Index);          //�����ֵ��������ֵ
    void eigenVector(int Index);            //����������
    void eigenPolyomial(int Index);         //����������ʽ
    void isOrthogonal(int Index);           //�жϷ�Ϊ��������
    double trace(int Index);                //�����ļ�
    double trace(double **a,int n);         //���������ļ�
};
void sss(double fg[],double cs[]);           //�������������Ҫ�õ�
#endif // LINEARALGEBRA_H
