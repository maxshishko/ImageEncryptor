#ifndef DNA_H
#define DNA_H

class DNA
{
    static int rules[] =   {{0,3,2,1},
                            {0,3,1,2},
                            {3,0,2,1},
                            {3,0,1,2},
                            {2,1,0,3},
                            {1,2,0,3},
                            {2,1,3,0},
                            {1,2,3,0}};
    Nucleotide value;
public:
    enum Nucleotide{A, T, C, G};
    DNA();
    DNA(Nucleotide value);
    DNA(int value, int encoding = 0);

    Nucleotide getValue() const;
    int getValue(int encoding) const;
    void setValue(const Nucleotide &value);
    void setValue(const int &value, int encoding = 0);
    const DNA operator^(const DNA &l, const DNA &r);
};

#endif // DNA_H
