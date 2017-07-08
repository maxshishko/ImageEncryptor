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
    DNASequence(const DNASequence &seq);
    DNASequence(int size);

    void push_back(DNA el);
    void push_back(uchar byte, int encoding);
    void pop_back();
    void clear();
    int size() const;
    void append(DNASequence seq);
    DNASequence mid(int pos, int len = -1);
    DNASequence operator^(DNASequence &r);
    DNASequence *fSerialXOR(DNASequence *mask);
    DNASequence *iSerialXOR(DNASequence *mask);
    QByteArray toByteArray(int encoding);
    DNA &operator[](int index);
    void crossover(DNASequence* second, int point);
    bool swap(int i, int j);
};

#endif // DNASEQUENCE_H
