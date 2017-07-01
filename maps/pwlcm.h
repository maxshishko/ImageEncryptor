#ifndef PWLCM_H
#define PWLCM_H

#include "chaoticmap1d.h"
#include <cmath>

class PWLCM : public ChaoticMap1D
{
    double param;
public:
    PWLCM(double init, double param);

    double next();
    double pwlcm(double x);

    double getParam() const;
    void setParam(double value);
    void setX(double value);
};

#endif // PWLCM_H
