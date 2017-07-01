#ifndef BAKER3DMAP_H
#define BAKER3DMAP_H

#include <cmath>

#include "chaoticmap3d.h"

class Baker3DMap : public ChaoticMap3D
{
public:
    Baker3DMap(double x, double y, double z);

    void next();

    void setX(double value);
    void setY(double value);
    void setZ(double value);
private:
    double toRange(double value);
};

#endif // BAKER3DMAP_H
