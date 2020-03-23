#ifndef COMPLEX_HH
#define COMPLEX_HH
#include<QString>
const double DBL_EPS=1e-20,$pi=3.141592653589793238,$e=2.71828182845905;
class Complex
{
public:
      Complex( double r=0, double i =0 ) { Real=r ;Imag=i;}
      Complex(int a) { Real = a ;  Imag = 0 ;}
      Complex& operator =(Complex c);
      friend Complex operator+ ( const Complex & c1, const Complex & c2 );
      friend Complex operator- ( const Complex & c1, const Complex & c2 );
      friend Complex operator* ( const Complex & c1, const Complex & c2 );
      friend Complex operator/ ( const Complex & c1, const Complex & c2 );
      void operator +=(const Complex &c);
      void operator -=(const Complex &c);
      void operator *=(const Complex &c);
      void operator /=(const Complex &c);
      double cfabs();  //��ģ��,����ֵΪʵ��
      void cAbs();     //��ģ�����޷���ֵ
      bool isZero();
      void conj();     //���������
      void cPow(Complex Index,bool isDeg=false);
      QString toExponential(bool isDeg,int precision);
      QString toString(int precision,double eps=1e-5);
      void   setComplex(QString str);
      double getReal();
      double getImag();
private:
      double Real;
      double Imag;
};
#endif
