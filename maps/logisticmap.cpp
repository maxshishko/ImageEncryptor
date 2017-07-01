#include "logisticmap.h"

double LogisticMap::getParam() const
{
    return param;
}

void LogisticMap::setParam(double value)
{
    if(value<0)
        value = abs(value);
    param = value;
}

void LogisticMap::setX(double value)
{
    if(value > 1 || value < 0)
        value = modf(abs(value), nullptr);
    x = value;
}

LogisticMap::LogisticMap(double init)
{
    setX(init);
}

LogisticMap::LogisticMap(double init, double param)
{
    setParam(param);
    setX(init);
}

double LogisticMap::next()
{
    x = param*x*(1-x);
    return x;
}
