#include "tentmap.h"

TentMap::TentMap(double init)
{
    setX(init);
}

void TentMap::setX(double value)
{
    if(value > 1 || value < 0)
        value = modf(abs(value), nullptr);
    x = value;
}

double TentMap::next()
{
    if(x < 0.5)
        x = 2.*x;
    else
        x = 2.*(1.-x);
    return x;
}
