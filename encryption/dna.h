#ifndef DNA_H
#define DNA_H

class DNA
{
public:
    enum Nucleotide{A, T, C, G};
private:
    Nucleotide value;
    static constexpr int rules[8][4] = {{0,3,2,1},
                                    {0,3,1,2},
                                    {3,0,2,1},
                                    {3,0,1,2},
                                    {2,1,0,3},
                                    {1,2,0,3},
                                    {2,1,3,0},
                                    {1,2,3,0}};

public:
    DNA();
    explicit DNA(Nucleotide value);
    explicit DNA(int value, int encoding = 0);

    Nucleotide getValue() const;
    int getValue(int encoding) const;
    void setValue(const Nucleotide &value);
    void setValue(int value, int encoding = 0);
    const DNA operator^(const DNA &r) const;
};

#endif // DNA_H
