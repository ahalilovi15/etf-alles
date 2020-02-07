//NA 2017/2018: Zadaća 5, Zadatak 3
#include <iostream>
#include <cmath>
#include <utility>
#include <vector>
#include <exception>
#include <limits>
template <typename FunTip>
double stepCalc(FunTip f, double x, double y, double h)
{
    double k1 = f(x,y);
    double k2 = f(x + h / 2, y + h * k1 / 2);
    double k3 = f(x + h / 2, y + h * k2 / 2);
    double k4 = f(x + h,y + h * k3);
    return y + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}
template <typename FunTip>
std::vector<std::pair<double, double>> RK4Integrator(FunTip f, double x0, double y0, double xmax, double h, double eps = 1e-8, bool adaptive = false)
{
    if((h>0 && xmax<x0) || (h<=0 && xmax>x0)) return {{x0,y0}};
    std::vector<std::pair<double,double>> k;
    if(!adaptive) {
        double x=x0,y=y0;
        if(h>0) {
            while(x<=xmax+eps) {
                k.push_back({x,y});
                double k1=f(x,y);
                double k2=f(x+h/2,y+h*k1/2);
                double k3=f(x+h/2,y+h*k2/2);
                double k4=f(x+h,y+h*k3);
                y=y+h*(k1+2*k2+2*k3+k4)/6;
                x=x+h;
            }
        } else {
            while(x>=xmax-eps) {
                k.push_back({x,y});
                double k1=f(x,y);
                double k2=f(x+h/2,y+h*k1/2);
                double k3=f(x+h/2,y+h*k2/2);
                double k4=f(x+h,y+h*k3);
                y=y+h*(k1+2*k2+2*k3+k4)/6;
                x=x+h;
            }
        }
    } else {
        if(h>0) {
            double x=x0,y=y0;
            k.push_back({x,y});
            while(x<=xmax+eps) {
                double u=stepCalc(f,x,y,h/2);
                double v=stepCalc(f,x+h/2,u,h/2);
                double w=stepCalc(f,x,y,h);
                double delta=std::abs(w-v)/h;
                if(delta<=eps) {
                    x=x+h;
                    y=v;
                    k.push_back({x,y});
                }
                h=h*std::min(5.0,0.9*std::pow(eps/delta,1/4.));
            }
            if(std::abs(k[k.size()-1].first-xmax)>std::numeric_limits<double>::epsilon()) {
                k.erase(k.begin());
                h=xmax-k[k.size()-1].first;
                double u=stepCalc(f,x,y,h/2);
                double v=stepCalc(f,x+h/2,u,h/2);
                double w=stepCalc(f,x,y,h);
                k[k.size()-1]= {xmax,v};
            }
        } else {
            double x=x0,y=y0;
            k.push_back({x,y});
            while(x>=xmax-eps) {
                double u=stepCalc(f,x,y,h/2);
                double v=stepCalc(f,x+h/2,u,h/2);
                double w=stepCalc(f,x,y,h);
                double delta=std::abs(w-v)/((-1)*h);
                if(delta<=eps) {
                    x=x+h;
                    y=v;
                    k.push_back({x,y});
                }
                h=h*std::min(5.0,0.9*std::pow(eps/delta,1/4.));
            }
            if(std::abs(k[k.size()-1].first-xmax)>std::numeric_limits<double>::epsilon()) {
                k.erase(k.begin());
                h=xmax-k[k.size()-1].first;
                double u=stepCalc(f,x,y,h/2);
                double v=stepCalc(f,x+h/2,u,h/2);
                double w=stepCalc(f,x,y,h);
                k[k.size()-1]= {xmax,v};
            }
        }
    }
    return k;

}
// kako sam debuggiro u CLionu zalijepio sam kod
int main ()
{
    auto res = RK4Integrator([](double x, double y) {
        return 2 * x + y + 1;
    },
    0, 1, 0.4, 0.1, 1e-8, true);
    auto exact = [](double x) {
        return -3 - 2 * x + 4 * std::exp(x);
    };
    for(int i = 0; i < res.size(); i++) {
        double x = res[i].first;
        std::cout << x << " " << res[i].second << " " << exact(x) << std::endl;
    }
    return 0;
}
