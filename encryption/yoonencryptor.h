#ifndef YOONENCRYPTOR_H
#define YOONENCRYPTOR_H

#include "imageencryptor.h"
#include "pwlcm.h"

class YoonEncryptor : public ImageEncryptor
{
private:
    int K;
    double init;
    double param;
    PWLCM map;

    int **createLUT(QVector<int> seed);
    int **createSmallMatrix(int size);
    int **createMask(int size);
    int **productMatrix(int **lmatrix, int lsize, int **rmatrix, int rsize);
    void outputMatrix(int **matrix, int size);
    QVector<int> dividers(int value);
    void shuffleMatrix(int **matrix, int size);
    void swap(int **matrix, int i, int j, int k, int l);
    void freeMemory(int **matrix, int size);
public:
    YoonEncryptor();
    YoonEncryptor(double init, double param, int K);

    QImage encrypt(QImage src);
    QImage decrypt(QImage src);

    void setRandomParameters();
    QString parametersToString();

    int getK() const;
    void setK(int value);
    double getInit() const;
    void setInit(double value);
    double getParam() const;
    void setParam(double value);
};

#endif // YOONENCRYPTOR_H
