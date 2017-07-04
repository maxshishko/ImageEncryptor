#include "dna.h"

DNA::Nucleotide DNA::getValue() const
{
    return value;
}

void DNA::setValue(const Nucleotide &value)
{
    this->value = value;
}

void DNA::setValue(const int &value, int rule = 0)
{
    if(rule < 0 || rule > 7 )
        rule = 0;
    if(value < 0 || value > 7)
        value = 0;
    this->value = rules[rule][value];
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

DNA::DNA(int value, int rule = 0)
{
    setValue(value, rule);
}
