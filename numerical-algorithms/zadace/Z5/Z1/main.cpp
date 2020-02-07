//NA 2017/2018: Zadaća 5, Zadatak 1
#include <iostream>
#include <cmath>
#include <exception>
#include <functional>
#include <limits>
#include <complex>
#include <vector>
#include <algorithm>
template<typename FunTip>

bool BracketRoot(FunTip f, double x0, double &a, double &b, double hinit = 1e-5, double hmax = 1e10, double lambda = 1.4)
{
    if(hinit <= 0 || hmax <= 0 || lambda <= 0) throw std::domain_error("Invalid parameters");
    double a1 = x0;
    double f1 = f(a1);
    double h = hinit;
    double b1, f2;
    while (std::fabs(h) < hmax) {
        b1 = a1 + h;
        f2 = f(b1);
        if(f1 * f2 < 0) {
            if(a1 > b1) std::swap(a1, b1);
            a = a1;
            b = b1;
            return true;
        }
        h = h * lambda;
        a1 = b1;
        f1 = f2;
    }
    h = hinit;
    a1 = x0;
    f1 = f(a1);
    while (std::fabs(h) < hmax) {
        b1 = a1 - h;
        f2 = f(b1);
        if(f1 * f2 <= 0) {
            if(a1 > b1) std::swap(a1, b1);
            a = a1;
            b = b1;
            return true;
        }
        h = h * lambda;
        b1 = a1;
        f2 = f1;
    }
    return false;
}

// RegulaFalsi
enum RegulaFalsiMode {Unmodified, Illinois, Slavic, IllinoisSlavic};

template <typename FunTip>
double RegulaFalsiSolve(FunTip f, double a, double b, RegulaFalsiMode mode = Slavic, double eps = 1e-10, int maxiter = 100)
{
    if(f(a) * f(b) > 0) throw std::range_error("Root must be bracketed");
    if(maxiter <= 0 || eps <= 0) throw std::domain_error("Invalid parameters");
    std::function<double(double)> fi;
    int brojac = 0;
    double f1, f2, c, cold;
    if(mode == Unmodified) {
        f1 = f(a);
        f2 = f(b);
        c = a;
        cold = b;
        while(std::fabs(c - cold) > std::numeric_limits<double>::epsilon()) {
            if(brojac == maxiter) throw std::logic_error("Given accuracy has not achieved");
            cold = c;
            c = (a * f2 - b * f1) / (f2 - f1);
            double f3 = f(c);
            if(std::fabs(f3) < std::numeric_limits<double>::epsilon()) return c;
            if(f1 * f3 < 0) {
                b = a;
                f2 = f1;
            }
            a = c;
            f1 = f3;
            brojac++;
        }
        return c;
    } else if(mode == Illinois) {
        f1 = f(a);
        f2 = f(b);
        c = a;
        cold = b;
        while(std::fabs(c - cold) > std::numeric_limits<double>::epsilon()) {
            if(brojac == maxiter) throw std::logic_error("Given accuracy has not achieved");
            cold = c;
            c = (a * f2 - b * f1) / (f2 - f1);
            double f3 = f(c);
            if(std::fabs(f3) < std::numeric_limits<double>::epsilon()) return c;
            if(f1 * f3 < 0) {
                b = a;
                f2 = f1;
            } else {
                f2 /= 2;
            }
            a = c;
            f1 = f3;
            brojac++;
        }
        return c;
    } else if(mode == Slavic) {
        fi = [](double x) {
            return x / (1 + std::fabs(x));
        };
        f1 = fi(f(a));
        f2 = fi(f(b));
        c = a;
        cold = b;
        while(std::fabs(c - cold) > std::numeric_limits<double>::epsilon()) {
            if(brojac == maxiter) throw std::logic_error("Given accuracy has not achieved");
            cold = c;
            c = (a * f2 - b * f1) / (f2 - f1);
            double f3 = fi(f(c));
            if(std::fabs(f3) < std::numeric_limits<double>::epsilon()) return c;
            if(f1 * f3 < 0) {
                b = c;
                f2 = f3;
            } else {
                a = c;
                f1 = f3;
            }
            brojac++;
        }
        return c;
    } else if(mode == IllinoisSlavic) {
        fi = [](double x) {
            return x / (1 + std::fabs(x));
        };
        f1 = fi(f(a));
        f2 = fi(f(b));
        c = a;
        cold = b;
        while(std::fabs(c - cold) > std::numeric_limits<double>::epsilon()) {
            if(brojac == maxiter) throw std::logic_error("Given accuracy has not achieved");
            cold = c;
            c = (a * f2 - b * f1) / (f2 - f1);
            double f3 = fi(f(c));
            if(std::fabs(f3) < std::numeric_limits<double>::epsilon()) return c;
            if(f1 * f3 < 0) {
                b = a;
                f2 = f1;
            } else {
                f2 /= 2;
            }
            a = c;
            f1 = f3;
            brojac++;
        }
        return c;
    }

    throw std::domain_error("Invalid Regula Falsi mode");
}
// Riddler hehe
template <typename FunTip>
double RiddersSolve(FunTip f, double a, double b, double eps = 1e-10, int maxiter = 100)
{
    if(f(a) * f(b) > 0) throw std::range_error("Root must be bracketed");
    if(eps <= 0 || maxiter <= 0) throw std::domain_error("Invalid parameters");
    double f1 = f(a);
    double f2 = f(b);
    int brojac = 0;
    double c, f3, d, f4;
    while(std::fabs( b - a) >= eps) {
        if(brojac == maxiter) throw std::logic_error("Given accuracy has not achieved");
        c = (a + b) / 2;
        f3 = f(c);
        if(std::fabs(f3) < std::numeric_limits<double>::epsilon()) return c;
        int sign;
        if((f1 - f2) > 0) sign = 1;
        else if((f1 - f2) < 0) sign = -1;
        else sign = 0;
        d = c + (f3 * (c - a) * sign) / std::sqrt(f3 * f3 - f1 * f2);
        f4 = f(d);
        if(std::fabs(f4) < std::numeric_limits<double>::epsilon()) return d;
        if(f3 * f4 <= 0) {
            a = c;
            b = d;
            f1 = f3;
            f2 = f4;
        } else if(f1 * f4 <= 0) {
            b = d;
            f2 = f4;
        } else {
            a = d;
            f1 = f4;
        }
        brojac++;
    }
    return (a + b) / 2;
}

template <typename FunTip1, typename FunTip2>
double NewtonRaphsonSolve(FunTip1 f, FunTip2 fprim, double x0, double eps = 1e-10, double damping = 0, int maxiter = 100)
{
    if(eps <= 0 || maxiter <= 0 || damping < 0 || damping >= 1) throw std::domain_error("Invalid parameters");
    double dx = std::numeric_limits<double>::infinity();
    int brojac = 0;
    double v;
    if(damping == 0) {
        while(std::fabs(dx) > std::numeric_limits<double>::epsilon()) {
            if(brojac == maxiter || std::fabs(fprim(x0)) < std::numeric_limits<double>::epsilon() ) throw std::logic_error("Convergence has not achieved");
            v = f(x0);
            if(std::fabs(v) <std::numeric_limits<double>::epsilon() ) return x0;
            dx = v / fprim(x0);
            x0 -= dx;
            brojac++;
        }
        return x0;
    }
    v = f(x0);
    double d = fprim(x0), w;
    while(std::fabs(dx) > std::numeric_limits<double>::epsilon()) {
        if(brojac == maxiter ) throw std::logic_error("Convergence has not achieved");
        if(std::fabs(v) <std::numeric_limits<double>::epsilon() ) return x0;
        dx = v / d;
        w = v;
        v = f(x0 - dx);
        d = fprim(x0 - dx);
        while((std::fabs(v) > std::fabs(w)) || !std::isfinite(v) || d == 0) {
            dx = damping * dx;
            v = f(x0 - dx);
            d = fprim(x0 - dx);
        }
        x0 -= dx;
        brojac++;
    }
    return x0;
}


std::complex<double> operator+(std::complex<double> c1, std::complex<double> c2)
{
    return {c1.real()+c2.real(),c1.imag()+c2.imag()};
}

std::complex<double> operator-(std::complex<double> c1, std::complex<double> c2)
{
    return {c1.real()-c2.real(),c1.imag()-c2.imag()};
}

std::complex<double> operator*(std::complex<double> c1, std::complex<double> c2)
{
    return {c1.real()*c2.real()-c1.imag()*c2.imag(),c1.real()*c2.imag()+c1.imag()*c2.real()};
}


std::complex<double> operator/(std::complex<double> c1, std::complex<double> c2)
{
    std::complex<double> brojnik=c1*std::conj(c2), nazivnik=c2*std::conj(c2);
    return {brojnik.real()/nazivnik.real(), brojnik.imag()/nazivnik.real()};
}

std::complex<double> operator*(double c1, std::complex<double> c2)
{
    std::complex<double> temp(c1,0);
    return temp*c2;
}

std::complex<double> operator*(std::complex<double> c1, double c2)
{
    return c2*c1;
}

bool operator==(std::complex<double> c1, std::complex<double> c2)
{
    return (std::abs(c1.real()-c2.real())<std::numeric_limits<double>::epsilon() && std::abs(c1.imag()-c2.imag())<std::numeric_limits<double>::epsilon());
}

bool operator!=(std::complex<double> c1, std::complex<double> c2)
{
    return !(c1==c2);
}

std::pair<std::complex<double>,bool> Laguerre(std::vector<double> p, int n, std::complex<double> x, double eps, int maxiter)
{
    std::complex<double> deltax = std::numeric_limits<double>::infinity();
    int k=1;
    while(std::abs(deltax)>eps && k<maxiter) {
        std::complex<double> f=p[n];
        std::complex<double> d=0;
        std::complex<double> s=0;
        for(int i(n-1); i>=0; i--) {
            s=s*x+2*d;
            d=d*x+f;
            f=f*x+p[i];
        }
        if(f==0) return {x,true};
        std::complex<double> r=std::sqrt((n-1)*((n-1)*d*d-n*f*s));
        if(std::abs(d+r)>std::abs(d-r)) deltax=n*f/(d+r);
        else deltax=n*f/(d-r);
        x=x-deltax;
        k++;
    }
    if(std::abs(deltax)<=eps) return {x,true};
    return {x,false};
}

std::pair<std::complex<double>,bool> Laguerre(std::vector<std::complex<double>> p, int n, std::complex<double> x, double eps, int maxiter)
{
    std::complex<double> deltax= std::numeric_limits<double>::infinity();
    int k=1;
    while(std::abs(deltax)>eps && k<maxiter) {
        std::complex<double> f=p[n];
        std::complex<double> d=0;
        std::complex<double> s=0;
        for(int i(n-1); i>=0; i--) {
            s=s*x+2*d;
            d=d*x+f;
            f=f*x+p[i];
        }
        if(f==0) return {x,true};
        std::complex<double> r=std::sqrt((n-1)*((n-1)*d*d-n*f*s));
        if(std::abs(d+r)>std::abs(d-r)) deltax=n*f/(d+r);
        else deltax=n*f/(d-r);
        x=x-deltax;
        k++;
    }
    if(std::abs(deltax)<=eps) return {x,true};
    return {x,false};
}

std::vector<std::complex<double>> PolyRoots(std::vector<double> coefficients, double eps = 1e-10, int maxiters = 100, int maxtrials = 10)
{
    if(eps<=0 || maxiters<=0 || maxtrials<=0) throw std::domain_error("Invalid parameters");
    int n=coefficients.size()-1, i=n, it=0;
    std::vector<std::complex<double>> p(n+1);
    while(i>=1) {
        if(it==maxiters) throw std::logic_error("Convergence has not achieved");
        int t=1;
        bool c=false;
        std::complex<double> x;
        while(!c && (t<maxtrials)) {
            x= {1,1};
            std::pair<std::complex<double>,bool> pair=Laguerre(coefficients,i,x,eps,maxiters);
            c=pair.second;
            x=pair.first;
            t++;
        }
        if(!c) throw std::logic_error("Convergence has not achieved");
        if(std::abs(x.imag())<=eps) {
            x=x.real();
            p[i]=x;
            double v=coefficients[i];
            for(int j(i-1); j>=0; j--) {
                double w=coefficients[j];
                coefficients[j]=v;
                v=w+x.real()*v;
            }
            i--;
        } else {
            p[i]=x;
            p[i-1]=std::conj(x);
            double alfa=2*x.real(),beta=std::abs(x);
            beta*=beta;
            double u=coefficients[i],v=coefficients[i-1]+alfa*u;
            for(int j=i-2; j>=0; j--) {
                double w=coefficients[j];
                coefficients[j]=u;
                u=v;
                v=w+alfa*v-beta*coefficients[j];
            }
            i-=2;
        }
        it++;
    }
    p.erase(p.begin());
    std::sort(p.begin(),p.end(),[](std::complex<double> x1, std::complex<double> x2) {
        if(std::abs(x1.real()-x2.real())>std::numeric_limits<double>::epsilon()) return x1.real()<x2.real();
        return x1.imag()<x2.imag();
    });
    return p;
}

std::vector<std::complex<double>> PolyRoots(std::vector<std::complex<double>> coefficients, double eps = 1e-10, int maxiters = 100, int maxtrials = 10)
{
    if(eps<=0 || maxiters<=0 || maxtrials<=0) throw std::domain_error("Invalid parameters");
    int n=coefficients.size()-1, i=n, it=0;
    std::vector<std::complex<double>> p;
    while(i>=1) {
        if(it==maxiters) throw std::logic_error("Convergence has not achieved");
        int t=1;
        bool c=false;
        std::complex<double> x;
        while(!c && (t<maxtrials)) {
            x= {0,0};
            std::pair<std::complex<double>,bool> pair=Laguerre(coefficients,i,x,eps,maxiters);
            c=pair.second;
            x=pair.first;
            t++;
        }
        if(!c) throw std::logic_error("Convergence has not achieved");
        if(std::abs(x.imag())<=eps) x=x.real();
        p.push_back(x);
        std::complex<double> v=coefficients[i];
        for(int j(i-1); j>=0; j--) {
            std::complex<double> w=coefficients[j];
            coefficients[j]=v;
            v=w+x*v;
        }
        i--;
        it++;
    }
    std::sort(p.begin(),p.end(),[](std::complex<double> x1, std::complex<double> x2) {
        if(std::abs(x1.real()-x2.real())>std::numeric_limits<double>::epsilon()) return x1.real()<x2.real();
        return x1.imag()<x2.imag();
    });
    return p;
}
/* Testovi i nisu najdetaljniji, predispitna sedmica :'( */
int main ()
{
{
    double a = -2, b = 2;
    std::cout << BracketRoot([](double x){return x - 1;}, 0.5, a, b ) << std::endl;
    try{
        a = 2;
        b = 3;
    std::cout << BracketRoot([](double x){return std::sin(x);}, -7, a, b ) << std::endl;
    }
    catch(std::range_error r){
        std::cout << r.what() << std::endl;
    }
}
{
    auto f = [](double x){return x*x - 4;};
    std::cout << RegulaFalsiSolve(f,-5, 1) << std::endl;
    try{
     std::cout << RegulaFalsiSolve(f,-1, 1) << std::endl;
    }
    catch(std::range_error r){
        std::cout << r.what() << std::endl;
    }
    std::cout << RegulaFalsiSolve(f,-5, 1, Slavic) << std::endl;
    std::cout << RegulaFalsiSolve(f,-5, 1, Illinois) << std::endl;
    std::cout << RegulaFalsiSolve(f,-5, 1, IllinoisSlavic) << std::endl;
}
{
    auto f = [](double x){return x*x + 4*x + 3;};
    auto fprim = [](double x){return 2*x + 4;};
    std::cout << NewtonRaphsonSolve(f, fprim, -1) << std::endl;
}
    return 0;
}
