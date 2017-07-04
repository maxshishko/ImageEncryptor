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
    for(int i = 0; i < ba.size(); i++)
        push_back(*reinterpret_cast<uchar*>(&ba[i]), encoding);
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

int DNASequence::size()
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

const DNASequence DNASequence::operator^(const DNASequence &l, const DNASequence &r)
{
    DNASequence result;
    for(int i = 0, j = 0; i < l.size(); i++, j++, j = j%r.size())
        result.push_back(l[i]^r[j]);
    return result;
}

QByteArray DNASequence::toByteArray(int encoding)
{
    QByteArray ba;
    char c = 0;
    for(int i = 0, j = 0; i < sequence.size(); i++, j++){
        c+=sequence[i].getValue(encoding);
        c = c<<2;
        if(j==3){
            ba.push_back(c);
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
