#ifndef ENCRYPTIONANALYZER_H
#define ENCRYPTIONANALYZER_H

#include <QVector>
#include <ctime>
#include <QFile>
#include <QTextStream>

#include "encryption/imageencryptor.h"

class Analysis
{
    static constexpr int corrMask[3][2] = {{1, 0},
                                 {0, 1},
                                 {1, 1}};
    static QVector<QPoint> getRandomPixelset(int sizex, int sizey, int setSize);
    static double mean(QVector<double> sequence);
    static double calcCorrelation(QVector<double> samplesX, QVector<double> samplesY);
    static void writeVector(QTextStream *stream, QVector<double> vector);
public:
    enum CorrelationType{CORR_H, CORR_V, CORR_D};

    static QVector<QVector<int> > histogram(QImage image);
    static QVector<double> correlation(QImage image, CorrelationType type, int pixelSetSize = 2000);
    static QVector<QVector<QVector<double> > > getCorrelationData(QImage image, CorrelationType type, int pixelSetSize = 2000);
    static QVector<double> entropy(QImage image);
    static QVector<double> NPCR(ImageEncryptor *encryptor, QImage image);
    static QVector<double> UACI(ImageEncryptor *encryptor, QImage image);
    static double encryptionTime(ImageEncryptor *encryptor, QImage image);
    static bool fullAnalysis(ImageEncryptor *encryptor, QImage image, QString filename, bool useRandomParams = false, int numSimulations = 1);
};

#endif // ENCRYPTIONANALYZER_H
