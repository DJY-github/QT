#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H
#include"Polynomial.h"
const int u=100,v=200,nga=200;
struct unit
{
    unsigned short x[20];
    double fitness;
};
class GeneticAlgorithm
{
public:
    GeneticAlgorithm(const Polynomial &p);
protected:
    unit encode(double real, double imag);//����
    Complex decode(const unit &u1);       //����
    unit crossover(unit &u1,unit &u2);    //��������
    unit variation01(const unit &u1,double pm1,double pm2);//ͻ������1
    unit variation02(const unit &u1); //ͻ������2
    void initialize();                    //��ʼ������
public:
    bool searchRoot(Complex *roots);
private:
    Polynomial poly,originalPoly;
    double e;
    unit group[u];
};
#endif // GENETICALGORITHM_H
