#include "baker3dmap.h"

Baker3DMap::Baker3DMap(double x, double y, double z)
{
    setX(x);
    setY(y);
    setZ(z);
}

void Baker3DMap::next()
{
    if(0. <= x && x < 0.5){
        x = 2.*x;
        if(0.<= y && y < 0.5){
            y = 2.*y;
            z = z/4.;
        }
        else{
            y = 2.*y-1.;
            z = z/4.+0.5;
        }
    }
    else{
        x = 2.*x-1.;
        if(0. <= y && y < 0.5){
            y = 2.*y;
            z = z/4.+0.25;
        }
        else{
            y = 2.*y-1.;
            z = z/4.+0.75;
        }
    }
}

void Baker3DMap::setX(double value)
{
    x = toRange(value);
}

void Baker3DMap::setY(double value)
{
    y = toRange(value);
}

void Baker3DMap::setZ(double value)
{
    z = toRange(value);
}

double Baker3DMap::toRange(double value)
{
    if(value > 1 || value < 0)
        value = modf(abs(value), nullptr);
    return value;
}
