#ifndef CALC_HH
#define CALC_HH

#include<Complex.h>
#include<QQueue>
#include<QString>
#include<QStack>
const char STR_OPERATORS[][4]=
         {"#","%","!","^","nad","div", "mod", "*", "/","+", "-","(",")" ","}; // '#'��ջ�ױ�־
const char STR_FUNCTIONS[][8]=
         {"abs","arccos","arccosh","arccot","arccoth","arcsin","arcsinh","arctan","arctanh",
          "conj","cos","cosh","cot","coth","csc","cur","exp","gcd","lcm","lg","ln",
          "log","pow","sec","sin","sinh","sqr","sqrt","tan","tanh"};
const char STR_CONST[][6]=
        {"$c","$e","$en","$eps0","$g","$h","$k","$me","$mi0","$mn","$mp","$mu","$pi"};
/*
$pi#Բ����#3.141592653589793238#
$e#ŷ��ָ��#2.71828182845905#
$g#�������ٶ�#9.80665#m / s^2
$c#����й���#299792458#m / s
$eps0#��ս�糣��#8.854187817E-12#F / m
$mi0#��մŵ���#1.2566370614E-6#H / m
$en#�������#1.60217733E-19#C
$mu#ԭ������#1.6605402E-27#kg
$me#��������#9.1093897E-31#kg
$mp#��������#1.6726231E-27#kg
$mn#��������#1.6749286E-27#kg
$k#������������#1.380658E-23#J / K
$h#���ʿ˳���#6.6260693E-34#J.s
*/
//���ȼ���ջ�ں�ջ���˳��
const int PRI_IN[] = {0, 15, 13, 10, 9, 7, 7, 5, 5, 3, 3, 1, -1, 1};   //�����-1��û�õ�
const int PRI_OUT[] ={0, 14, 12, 11, 8, 6, 6, 4, 4, 2, 2};
enum RETURN
{
    RET_CORRECT = 1,       //���ʽ�﷨��ȷ
    RET_WRONG  = 0,        //���ʽ�д����쳣�ַ�
    RET_WRONGSTR =-1,      //δ�������ַ���
    RET_END = -2,          //���ʽ����
    RET_BACK = -3,         //���Ų�ƥ��
    RET_POINT =-4,         //����С����
    RET_OPER =-5,          //����ʹ�����������
    RET_START=-6,          //���ʽ��ͷ���Ϸ�
    RET_LAST =-7,          //���ʽ��β���Ϸ�
    RET_BACKEMPTY=-8,      //������ɶ��û��
    RET_OPERNUMBER=-9,     //�����ȱ�ٲ�����
    RET_FUNNUMBER=-10,     //����ȱ�ٲ�����
    RET_ZERO=-11,          //����Ϊ��
    RET_INT=-12,           //�����ֻ����������
    RET_NONGINT=-13,       //NADֻ�����ڷǸ�����
    RET_NEGSQRT=-14,       //�������ܿ���
    RET_ARGUMENT=-15,      //���������Ƿ�
    RET_INF=-16,           //�������
    RET_COMMA=-17,         //����ʹ�ò��Ϸ�
    RET_COMPLEX=-18,       //�������²��ܼ���ĺ���
    RET_UPPERLETTER=-19,   //�Ƿ�ʹ�ô�д��ĸ
    RET_GCDLCM=-20,        //gcd��lcmd�Ĳ������Ϸ�
    RET_NUMBER=-21,        //ʹ�����ֲ��Ϸ�
    RET_VARIABLE=-22,      //������
    RET_USEINCOMP=-23,     //�ú���ֻ���ڸ�������ʹ��
    RET_SCIENTIFIC=-24     //��ѧ������ʹ������
};

const double INF=1.7e308;
const double CONST[]={299792458,2.71828182845905,1.60217733e-19,8.854187817e-12,9.80665,
                      6.6260693e-34,1.380658e-23,9.1093897e-31,1.2566370614e-6,
                      1.6749286e-27,1.6726231e-27,1.6605402e-27,3.141592653589793238};
inline bool isZero( double db )
{
    if(db<DBL_EPS&&db>-DBL_EPS)
        return 1;
    else
        return 0;
}
inline bool isHexNumber(QChar ch)
{
    if((ch>='0'&&ch<='9')||ch=='.'||ch==' '||(ch>='A'&&ch<='F'))
       return true;
    else
       return false;
}
inline int toNumber(QChar ch)
{
    if(ch>='0'&&ch<='9')
       return ch.toLatin1()-48;
    else
        return ch.toLatin1()-55;
}
class CCalculator
{
public:
    unsigned short ERRORBEGIN,ERRORLENGTH;                  //��¼�����λ��
public:
     struct Symbol
     {
        enum SYMTYPE                                        //ö�����ͣ���������������������
        {NUMBER,OPERATOR,FUNCTION}type;
        enum OPTYPE
        {
            //����%��!�ǵ�Ŀ�����
            //�������������˳�򣬲��ܽ���λ��
            STACKEND,                                        // #������
            PERCENT,FACTORIAL,POWER,NAD,DIV,MOD,             // % ! ^ nad div,mod
            MULTIPLY,DIVIDE,ADD,SUBSTRACT,                   // * / + -
            LEFTBRACE,RIGHTBRACE,                            // ( )
            COMMA                                            // ,����
        };
        enum FUNTYPE
        {
            ABS,ACOS,ACOSH,ACOT,ACOTH,ASIN,ASINH,ATAN,ATANH,
            CONJ,COS,COSH,COT,COTH,CSC,CUR,                  //CONJΪ���������,CURΪ������
            EXP,GCD,LCM,LG,LN,LOG,POW,                       //����������gcd(a,b),lcm(a,b),log(a,b),pow(a,b)
            SEC,SIN,SINH,SQR,SQRT,TAN,TANH                   //SQRΪƽ��
        };
        struct
        {
            OPTYPE opType;
            FUNTYPE funType;
            double number;
            Complex CompNumber;
        } content;
     };
public:
      CCalculator();
      int Calc(QString &result, QString &express,int precision,bool isDeg,bool isFraction,
               bool isComplex,bool isChangeSystem,int oldSystem,int newSystem);
private:
     QString m_strExp,errorStr;
     int m_curIndex;
     int isComma;                                               //��¼������ʹ�á�,���ĸ���
     QQueue<Symbol> QueSymbol;									//���ݺͲ���������
     int TransExp(QString &express );						    //���ʽ��׺ʽת��Ϊ��׺ʽ���﷨���
     int GetNextSymbol(QQueue<Symbol> &que,Symbol &sym);	    //�����һ���������������
     int Check_Start();											//�����ʽ��ͷ�Ƿ�Ϸ�
     int Check_Last();											//�����ʽ��β�Ƿ�Ϸ�
     int Check_Next();											//����Ƿ��������������
     bool IsValid(QString str);                                 //����ַ��Ƿ�Ϸ�
     bool IsOpt();                                              //�ж��Ƿ��������
     bool CompPri(Symbol &symIN,Symbol &symOUT);				//���ȼ��Ƚϣ�ǰ�ߴ󷵻�1�����ߴ󷵻�0

     int DoCalcOpt(QStack<Symbol> &stk,Symbol &sym );				//���������
     int DoCalcFun(QStack<Symbol>&stk,Symbol &sym);     //��������
     void Fraction(double dl,QString &result);
private:
     bool isComplex;
     bool isDeg;
     bool isChangeSystem;
     int newSystem;
     int oldSystem;

};

double factorial(int n);
double combinate(int k,int n);
qlonglong gcd(qlonglong a,qlonglong b);
qlonglong lcm(qlonglong a,qlonglong b);
QString changeSystem(QString num,int new_System, int old_System=10);
bool isErrorNumber(QString str,int system);
Complex getComplex(QString str);

#endif // EXPRESSION_H
