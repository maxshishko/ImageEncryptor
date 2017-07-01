#ifndef CHAOTICMAP_H
#define CHAOTICMAP_H


class ChaoticMap1D
{
protected:
    double x;
public:
    ChaoticMap1D(){}
    ChaoticMap1D(double init);
    virtual double next() = 0;

    double getX() const;
    void setX(double value);
};

#endif // CHAOTICMAP_H
