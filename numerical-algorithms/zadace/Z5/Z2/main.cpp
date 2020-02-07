//NA 2017/2018: Zadaća 5, Zadatak 2
#include <iostream>
#include <cmath>
#include <exception>
#include <limits>
template <typename FunTip>
double FindMinimum(FunTip f, double x0, double eps = 1e-8, double hinit = 1e-5, double hmax = 1e10, double lambda = 1.4){
 if(eps <= 0 || hinit <= 0 || hmax <= 0|| lambda <= 0) throw std::domain_error("Invalid parameters");
 bool flag = false;
 double h = hinit;
 double a = x0 - h;
 double b = x0 + h;
 double c = x0;
 while(std::fabs(h) < hmax){
     if(f(c + h) < f(c)) {
         b = c + h;
         a = c - h;
     }
     else if(f(c - h) < f(c)){
         b = c - h;
         a = b -h;
     }
     else{
         a = c - h;
         b = c + h;
         flag = true;
         break;
     }
     c = b;
     h = h * lambda;
 }
 if(!flag) throw std::logic_error("Minimum has not found");
 double k = (1 + std::sqrt(5)) / 2;
 double d;
 if(std::fabs(c - a) < std::fabs(b - c)){
     d = b - (b - c) / k;
 }
 else{
     d = c;
     c = a + (c - a) / k;
 }
 double u = f(c);
 double v = f(d);
 while(std::fabs(b - a) > eps){
     if(u < v){
         b = d;
         d = c;
         c = a + (c - a) / k;
         v = u;
         u = f(c);
     }
     else{
         a = c;
         c = d;
         d = b - (b - d) / k;
         u = v;
         v = f(d);
     }
 }
 return (a + b) / 2;
}

int main ()
{
    std::cout << FindMinimum([](double x){return x * x + 4 * x + 3;}, -4) << std::endl;
    std::cout << FindMinimum([](double x){return sqrt((x*x + 1));}, -6) << std::endl; // približno
    std::cout << FindMinimum([](double x){return std::sin(x);}, 2) << std::endl;
	return 0;
}