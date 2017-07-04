#include "dna.h"

DNA::Nucleotide DNA::getValue() const
{
    return value;
}

int DNA::getValue(int encoding) const
{
    if(encoding < 0 || encoding > 7)
        encoding = 0;
    return rules[encoding][static_cast<int>(value)];
}

void DNA::setValue(const Nucleotide &value)
{
    this->value = value;
}

void DNA::setValue(const int &value, int encoding = 0)
{
    if(encoding < 0 || encoding > 7 )
        encoding = 0;
    if(value < 0 || value > 7)
        value = 0;
    this->value = rules[encoding][value];
}

const DNA DNA::operator^(const DNA &l, const DNA &r)
{
    return DNA(static_cast<int>(l.getValue())^static_cast<int>(r.getValue()));
}

DNA::DNA()
{

}

DNA::DNA(DNA::Nucleotide value):value(value)
{

}

DNA::DNA(int value, int encoding = 0)
{
    setValue(value, encoding);
}
