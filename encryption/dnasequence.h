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
    DNASequence(const QByteArray &ba, int encoding);
    explicit DNASequence(int size);

    void push_back(const DNA &el);
    void push_back(uchar byte, int encoding);
    void pop_back();
    void clear();
    int size() const;
    void append(const DNASequence &seq);
    void append(DNASequence &&seq);
    void append(const DNA &el);
    DNASequence mid(int pos, int len = -1);
    DNASequence operator ^(const DNASequence &r) const;
    DNASequence fSerialXOR(const DNASequence &mask);
    DNASequence iSerialXOR(const DNASequence &mask);
    QByteArray toByteArray(int encoding) const;
    DNA &operator[](int index);
    const DNA &operator [](int index) const;
    void crossover(DNASequence &second, int point);
    bool swap(int i, int j);
};

#endif // DNASEQUENCE_H
