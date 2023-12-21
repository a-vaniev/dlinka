#include <iostream>
#include <vector>

#include "dlinka.hpp"

// Supplementary
using namespace dlinka;

verylong fac(verylong i)
{
    verylong one(1);
    verylong zero(0);
    return ((i == zero) ? one : (i * fac(i - one)));
}

verylong nCk(verylong n, verylong k)
{
    return (fac(n) / (fac(k) * fac(n - k)));
}

long long nCk(long long n, long long k)
{
    verylong nvl(n);
    verylong kvl(k);

    auto result = nCk(nvl, kvl);
    return result.asLongLong();
}

using namespace dlinka;

int main()
{
    long long a = 9223372036854775806;
    long long b = 2;
    long long c = 7231940124821421422;
    long long d = 13194012482122;
    auto r = a/b;
   std::cout<<r<<"\n";

    verylong avl(a);
    verylong bvl(b);
    verylong cvl(c);
    verylong dvl(d);
    verylong rvl(r);
    
    std::cout << "avl=" << avl.asLongLong()<<"\n";
    std::cout << "bvl=" << bvl.asLongLong()<<"\n";
    std::cout << "rvl=" << rvl.asLongLong()<<"\n";
    std::cout << "Comparision"<<"\n";
    std::cout << "\nEq c and a:"<<(cvl==avl?"c==a":"a!=c");
    std::cout << "\nEq a and a:"<<(avl==avl?"a==a":"a!=a");
    

    std::cout << "\nCompare c and a:"<<(cvl<avl?"c<a":"a<c");
    std::cout << "\nCompare a and c:"<<(avl<cvl?"a<c":"c<a");
    std::cout << "\nCompare c and d:"<<(cvl<dvl?"c<d":"d<c");
    std::cout << "\nCompare d and c:"<<(dvl<cvl?"d<c":"c<d");
    
    auto division = avl/dvl;
    std::cout<<"Division:"<<division.asLongLong()<<"\n";

    std::cout << "Combinations:" << nCk(59,50)<<"\n";
    
   }