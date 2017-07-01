#ifndef COMBINEDDMAP_H
#define COMBINEDDMAP_H

#include "chaoticmap3d.h"
#include "chaoticmap1d.h"

class Combined3DMap : public ChaoticMap3D
{
    ChaoticMap1D *xmap;
    ChaoticMap1D *ymap;
    ChaoticMap1D *zmap;
public:
    Combined3DMap(ChaoticMap1D* xmap, ChaoticMap1D* ymap, ChaoticMap1D* zmap);

    void next();

    void setX(double value);
    void setY(double value);
    void setZ(double value);
};

#endif // COMBINEDDMAP_H
