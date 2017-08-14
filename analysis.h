#ifndef ENCRYPTIONANALYZER_H
#define ENCRYPTIONANALYZER_H

#include <QVector>
#include <ctime>
#include <QFile>
#include <QTextStream>
#include <memory>

#include "encryption/imageencryptor.h"

class Analysis
{
    using ImgEncryptorPtr = std::shared_ptr<ImageEncryptor>;

    static constexpr int corrMask[3][2] = {{1, 0},
                                 {0, 1},
                                 {1, 1}};
    static QVector<QPoint> getRandomPixelset(int sizex, int sizey, int setSize);
    static double calcCorrelation(const QVector<double> &samplesX, const QVector<double> &samplesY);
    static void writeVector(QTextStream &stream, const QVector<double> &vector);
public:
    enum class CorrelationType{CORR_H, CORR_V, CORR_D};

    static QVector<QVector<int>> histogram(const QImage &image);
    static QVector<double> correlation(const QImage &image, CorrelationType type, int pixelSetSize = 2000);
    static QVector<QVector<QVector<double>>> getCorrelationData(const QImage &image, CorrelationType type, int pixelSetSize = 2000);
    static QVector<double> entropy(const QImage &image);
    static QVector<double> NPCR(ImgEncryptorPtr encryptor, QImage image);
    static QVector<double> UACI(ImgEncryptorPtr encryptor, QImage image);
    static double encryptionTime(ImgEncryptorPtr encryptor, const QImage &image);
    static bool fullAnalysis(ImgEncryptorPtr encryptor, const QImage &image, const QString &filename, bool useRandomParams = false, int numSimulations = 1);
};

#endif // ENCRYPTIONANALYZER_H
