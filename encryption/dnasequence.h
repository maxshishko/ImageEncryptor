#ifndef DNASEQUENCE_H
#define DNASEQUENCE_H

#include <QVector>
#include "dna.h"

class DNASequence
{
    QVector<DNA> sequence;

protected:
    DNASequence(QVector<DNA> sequence):sequence(sequence){}

public:
    DNASequence();
    DNASequence(QByteArray ba, int encoding);

    void push_back(DNA el);
    void push_back(uchar byte, int encoding);
    void pop_back();
    void clear();
    int size();
    DNASequence mid(int pos, int len = -1);
    const DNASequence operator^(const DNASequence &l, const DNASequence &r);
    QByteArray toByteArray(int encoding);
    DNA &operator[](int index);
};

#endif // DNASEQUENCE_H
