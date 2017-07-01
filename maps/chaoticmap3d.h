#ifndef CHAOTICMAP3D_H
#define CHAOTICMAP3D_H


class ChaoticMap3D
{
protected:
    double x;
    double y;
    double z;
public:
    ChaoticMap3D();

    virtual void next() = 0;

    double getX() const;
    void setX(double value);
    double getY() const;
    void setY(double value);
    double getZ() const;
    void setZ(double value);
};

#endif // CHAOTICMAP3D_H
