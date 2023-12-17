#include <iostream>
#include <vector>

#include "dlinka.hpp"
/*
verylong fac(verylong i)
{
    verylong one;
    one.setLL(1);
    return (i.isZero() ? one : (i * fac(i - one)));
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
    return result.getLL();
}
*/

using namespace dlinka;

int main()
{
    verylong a(12049101);
    verylong b(99);

    auto d = a/b;
    std::cout<<d.asLongLong()<<"\n";
   std::cout<<12049101/99<<"\n";
}