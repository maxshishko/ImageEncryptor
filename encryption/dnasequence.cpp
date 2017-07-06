#include "dnasequence.h"

QVector<DNA> DNASequence::getSequence() const
{
    return sequence;
}

DNASequence::DNASequence()
{

}

DNASequence::DNASequence(QByteArray ba, int encoding)
{
    char tmp;
    for(int i = 0; i < ba.size(); i++){
        tmp = ba[i];
        push_back(*reinterpret_cast<uchar*>(&tmp), encoding);
    }
}

void DNASequence::push_back(DNA el)
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

void DNASequence::append(DNASequence seq)
{
    sequence.append(seq.getSequence());
}

DNASequence DNASequence::mid(int pos, int len)
{
    return DNASequence(sequence.mid(pos, len));
}

DNASequence DNASequence::operator^(DNASequence &r)
{
    DNASequence result;
    for(int i = 0, j = 0; i < r.size(); i++, j++, j = j%r.size())
        result.push_back(this->sequence[i]^r[j]);
    return result;
}

DNASequence *DNASequence::fSerialXOR(DNASequence *mask)
{
    DNASequence *result = new DNASequence;
    if(mask->size() != sequence.size())
        return result;

    DNA last = (*mask)[0]^sequence[0];
    result->push_back(last);
    for(int i = 1; i < sequence.size(); i++){
        last = ((*mask)[i]^sequence[i])^last;
        result->push_back(last);
    }
    return result;
}

DNASequence *DNASequence::iSerialXOR(DNASequence *mask)
{
    DNASequence *result = new DNASequence;
    if(mask->size()!=sequence.size())
        return result;
    result->push_back((*mask)[0]^sequence[0]);
    for(int i = 1; i < sequence.size(); i++)
        result->push_back((*mask)[i]^sequence[i]^sequence[i-1]);
    return result;
}

QByteArray DNASequence::toByteArray(int encoding)
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

void DNASequence::crossover(DNASequence *second, int point)
{
    if(this->sequence.size() < point || second->size() < point)
        return;

    QVector<DNA> tmpseq = this->sequence.mid(point);
    this->sequence.remove(point, this->sequence.size()-point);
    this->sequence += second->sequence.mid(point);
    second->sequence.remove(point, second->size()-point);
    second->sequence += tmpseq;
}
