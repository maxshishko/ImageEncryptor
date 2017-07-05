#ifndef DNASEQUENCE_H
#define DNASEQUENCE_H

#include <QVector>
#include "dna.h"

class DNASequence
{
private:
    QVector<DNA> sequence;

    DNASequence(QVector<DNA> sequence):sequence(sequence){}
    QVector<DNA> getSequence() const;

protected:

public:
    DNASequence();
    DNASequence(QByteArray ba, int encoding);

    void push_back(DNA el);
    void push_back(uchar byte, int encoding);
    void pop_back();
    void clear();
    int size();
    void append(DNASequence seq);
    DNASequence mid(int pos, int len = -1);
    const DNASequence operator^(const DNASequence &l, const DNASequence &r);
    const DNASequence fSerialXOR(const DNASequence &mask);
    const DNASequence iSerialXOR(const DNASequence &mask);
    QByteArray toByteArray(int encoding);
    DNA &operator[](int index);
    void crossover(DNASequence* second, int point);
};

#endif // DNASEQUENCE_H
