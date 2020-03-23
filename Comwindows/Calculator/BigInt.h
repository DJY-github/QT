#ifndef BIGINT_H
#define BIGINT_H

#include<cmath>
#include<Qstring>
typedef qlonglong qllong;
#define MAXN 5000
#define BASE 100000000                  //����10^8����
#define BASELEN 8
class BigInt
{
    bool sign;                          //0��ʾ����1��ʾ��
    qllong  digital[MAXN];
    int len;                            //��ǰ�������ĳ���
public:
    //���캯��
    BigInt();
    BigInt(qllong );
    BigInt(const BigInt &);
    //��ֵ�����أ�
    BigInt& operator =(const BigInt &);
    BigInt& operator = (QString);

    //��Ŀ�������
    BigInt operator +(const BigInt &);
    BigInt operator -(const BigInt &);
    BigInt operator *(const BigInt &);
    BigInt operator /(const BigInt &);
    BigInt operator +(int n);
    BigInt operator -(int n);
    BigInt operator *(int n);
    BigInt operator /(int n);
    bool operator >(const BigInt &);
    bool operator <(const BigInt &);
    BigInt& operator +=(const BigInt &);
    BigInt& operator -=(const BigInt &);
    BigInt& operator *=(const BigInt &);
    BigInt operator ^(int n);               //�������˷�
    BigInt operator %(BigInt);              //��������ģ
    BigInt& operator >>=(int n);            //�������ڶ�����������nλ
    BigInt& operator <<=(int n);            //�������ڶ�����������nλ

    //һЩ������
    bool Zero()const;                       //�жϴ������Ƿ�Ϊ��
    qllong FirSecDigit();                    //����ǰ��λԪ��
    BigInt Sqrt();                          //���������ƽ����
    void Factorial(int n);                  //��׳�
    void Factorial(int n,char c);           //��˫�׳�
    BigInt Shift(int n);                    //ʮ������λ
    int Cmp(const BigInt &,bool Is_Abs=0);  //�ȽϺ���,�ڶ�������Ϊ1���ʾ����ֵ�Ƚϣ�Ĭ�ϱȽϱ����С
friend void Swap(BigInt *num1,BigInt *num2);//��������������
    QString toQString();                    //ת��Ϊ�ַ���

    bool isLegal;
};

#endif // BIGINT_H
