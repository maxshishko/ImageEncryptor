#include "pwlcm.h"

double PWLCM::getParam() const
{
    return param;
}

void PWLCM::setParam(double value)
{
    if(value > 1 || value < 0)
        value = modf(abs(value), nullptr);
    if(value > 0.5)
        value *= 0.5;
    param = value;
}

void PWLCM::setX(double value)
{
    if(value > 1 || value < 0)
        value = modf(abs(value), nullptr);
    x = value;
}

PWLCM::PWLCM(double init)
{
    setX(init);
}

PWLCM::PWLCM(double init, double param)
{
    setX(init);
    setParam(param);
}

double PWLCM::next()
{
    x = pwlcm(x);
    return x;
}

double PWLCM::pwlcm(double value)
{
    if(value>=0 && value < param)
        return value/param;
    if(value>=param && value < 0.5)
        return (value-param)/(0.5-param);
    if(value >=0.5 && value < 1)
        return pwlcm(1-value);
}
