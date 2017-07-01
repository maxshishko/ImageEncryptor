#ifndef LOGISTIC_H
#define LOGISTIC_H

#include <cmath>

#include "chaoticmap1d.h"

class LogisticMap : public ChaoticMap1D
{
    double param = 3.9999;
public:
    LogisticMap(double init, double param);

    double next();
    double getParam() const;
    void setParam(double value);
    void setX(double value);
};

#endif // LOGISTIC_H
