#ifndef TENTMAP_H
#define TENTMAP_H

#include <cmath>

#include "chaoticmap1d.h"

class TentMap : public ChaoticMap1D
{
public:
    TentMap(double init);

    void setX(double value);
    double next();
};

#endif // TENTMAP_H
