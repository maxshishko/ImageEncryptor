#ifndef DNASEQUENCE_H
#define DNASEQUENCE_H

#include <QVector>
#include "dna.h"

class DNASequence
{
    QVector<DNA> sequence;

public:
    DNASequence();
    DNASequence(QByteArray ba, int encoding);

    void push_back(DNA el);
    void push_back(char byte, int encoding);
    void pop_back();
    void clear();
    int size();
    const DNASequence operator^(const DNASequence &l, const DNASequence &r);
    QByteArray toByteArray(int encoding);
    DNA &operator[](int index);
};

#endif // DNASEQUENCE_H
