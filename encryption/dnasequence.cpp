#include "dnasequence.h"
#include <memory>

QVector<DNA> DNASequence::getSequence() const
{
    return sequence;
}

DNASequence::DNASequence()
{

}

DNASequence::DNASequence(const QByteArray &ba, int encoding)
{
    char tmp;
    for(int i = 0; i < ba.size(); i++){
        tmp = ba[i];
        push_back(*reinterpret_cast<uchar*>(&tmp), encoding);
    }
}


DNASequence::DNASequence(int size)
{
    sequence = QVector<DNA>(size);
}


void DNASequence::push_back(const DNA &el)
{
    sequence.push_back(el);
}

void DNASequence::push_back(uchar byte, int encoding)
{
    for(int i = 0; i < 4; i++)
        sequence.push_back(DNA((byte>>(2*(3-i)))&3, encoding));
}

void DNASequence::pop_back()
{
    sequence.pop_back();
}

void DNASequence::clear()
{
    sequence.clear();
}

int DNASequence::size() const
{
    return sequence.size();
}

void DNASequence::append(const DNASequence &seq)
{
    sequence.append(seq.getSequence());
}

void DNASequence::append(DNASequence &&seq)
{
    sequence.append(std::move(seq.sequence));
}

void DNASequence::append(const DNA &el)
{
    sequence.append(el);
}

DNASequence DNASequence::mid(int pos, int len)
{
    return DNASequence(sequence.mid(pos, len));
}

DNASequence DNASequence::operator ^(const DNASequence &r) const
{
    DNASequence result;
    for(int i = 0, j = 0; i < sequence.size(); i++, j++, j = j%r.size())
        result.push_back(sequence[i]^r[j]);
    return result;
}

DNASequence DNASequence::fSerialXOR(const DNASequence &mask)
{
    DNASequence result;
    if(mask.size() != sequence.size())
        return result;

    auto last = mask[0]^sequence[0];
    result.push_back(last);
    for(int i = 1; i < sequence.size(); i++){
        last = (mask[i]^sequence[i])^last;
        result.push_back(last);
    }
    return result;
}

DNASequence DNASequence::iSerialXOR(const DNASequence &mask)
{
    DNASequence result;
    if(mask.size()!=sequence.size())
        return result;
    result.push_back(mask[0]^sequence[0]);
    for(int i = 1; i < sequence.size(); i++)
        result.push_back(mask[i]^sequence[i]^sequence[i-1]);
    return result;
}

QByteArray DNASequence::toByteArray(int encoding) const
{
    QByteArray ba;
    uchar c = 0;
    for(int i = 0, j = 0; i < sequence.size(); i++, j++){
        c = c<<2;
        c+=sequence[i].getValue(encoding);
        if(j==3){
            ba.push_back(*reinterpret_cast<char*>(&c));
            c = 0;
            j = -1;
        }
    }
    return ba;
}

DNA &DNASequence::operator[](int index)
{
    return sequence[index];
}

const DNA &DNASequence::operator [](int index) const
{
    return sequence[index];
}

void DNASequence::crossover(DNASequence &second, int point)
{
    if(this->sequence.size() < point || second.size() < point)
        return;

    QVector<DNA> tmpseq = this->sequence.mid(point);
    this->sequence.remove(point, this->sequence.size()-point);
    this->sequence += second.sequence.mid(point);
    second.sequence.remove(point, second.size()-point);
    second.sequence += tmpseq;
}

bool DNASequence::swap(int i, int j)
{
    if(i < 0 || i >= sequence.size() || j < 0 || j >= sequence.size())
        return false;
    std::swap(sequence[i], sequence[j]);
    return true;
}
