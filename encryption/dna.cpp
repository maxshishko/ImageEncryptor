#include "dna.h"

constexpr int DNA::rules[8][4];

DNA::Nucleotide DNA::getValue() const
{
    return value;
}

int DNA::getValue(int encoding) const
{
    if(encoding < 0 || encoding > 7)
        encoding = 0;
    int result = 0;
    for(int i = 0; i < 4; i++){
        if(static_cast<int>(value)==rules[encoding][i])
            result = i;

    }
    return result;
}

void DNA::setValue(const Nucleotide &value)
{
    this->value = value;
}

void DNA::setValue(int value, int encoding)
{
    if(encoding < 0 || encoding > 7 )
        encoding = 0;
    if(value < 0 || value > 4)
        value = 0;
    this->value = static_cast<Nucleotide>(DNA::rules[encoding][value]);
}

const DNA DNA::operator^(const DNA &r) const
{
    DNA result(static_cast<Nucleotide>(static_cast<int>(this->getValue())^static_cast<int>(r.getValue())));
    return result;
}

DNA::DNA(DNA::Nucleotide value):value(value)
{

}

DNA::DNA(int value, int encoding)
{
    setValue(value, encoding);
}
