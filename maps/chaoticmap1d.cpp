#include "chaoticmap1d.h"

double ChaoticMap1D::getX() const
{
    return x;
}

void ChaoticMap1D::setX(double value)
{
    x = value;
}

ChaoticMap1D::ChaoticMap1D(double init):
    x(init)
{

}
