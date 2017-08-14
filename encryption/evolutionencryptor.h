#ifndef EVOLUTIONENCRYPTOR_H
#define EVOLUTIONENCRYPTOR_H

#include <stdexcept>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QCryptographicHash>
#include <QBuffer>
#include <QSet>
#include <QVector>
#include <QPixmap>
#include <memory>

#include "imageencryptor.h"
#include "chaoticmap1d.h"
#include "logisticmap.h"
#include "dnasequence.h"

class EvolutionEncryptor : public ImageEncryptor
{
private:
    using ChaoticMap1DUptr = std::unique_ptr<ChaoticMap1D>;

    int populationSize;
    double mutationRate;
    double entropy;
    QString decryptionKey;
    int encoding = 0;
    ChaoticMap1DUptr map = std::make_unique<LogisticMap>();

    QVector<QVector<double>> keys;
    enum DNA{A, T, C, G};
    QVector<QVector<int>> rules;
    QByteArray imagePrefix;

    QByteArray calculateHash(const QImage &image);
    double getMapInit(const QByteArray &hash);
    QVector<DNASequence> getInitialPopulation(int length);
    QVector<double> getChaoticSequence(int length, int index = -1);
    QVector<double> getChaoticSequence(int length, double keyL, double keyH);
    DNASequence getDnaMask(const QVector<double> &chaoticSequence);
    inline int getRule(double val);
    DNASequence image2dna(const QImage &image, int encoding);
    QImage dna2image(const DNASequence &seq, int encoding);
    QVector<double> calcEntropies(const QVector<DNASequence> &population);
    double calcEntropy(const DNASequence &member);
    QVector<double> calcProbabilities(const QVector<double> &entropies);
    QVector<QVector<int> > getCrossoverPairs(const QVector<double> &probabilities);
    int doRouletteWheel(const QSet<int> &indices, const QVector<double> &probabilities);
    inline void singlepointCrossover(DNASequence &first, DNASequence &second);
    inline void singleMutation(QVector<DNASequence> &population, int index, const DNASequence &image);
    void swapKeys(int i, int j);
    QPair<double, int> findMaxEntropy(const QVector<DNASequence> &population);
    void doCrossover(QVector<DNASequence> &population);
    void doMutation(QVector<DNASequence> &population, const DNASequence &image);

public:
    EvolutionEncryptor() = default;
    EvolutionEncryptor(int populationSize, double mutationRate, double entropy);
    explicit EvolutionEncryptor(QString decryptionKey);
    ~EvolutionEncryptor() = default;

    QImage encrypt(const QImage &src) override;
    QImage decrypt(const QImage &src) override;

    void setRandomParameters() override;
    QString parametersToString() override;

    int getPopulationSize() const;
    void setPopulationSize(int value);
    double getMutationRate() const;
    void setMutationRate(double value);
    double getEntropy() const;
    void setEntropy(double value);
    QString getDecryptionKey() const;
    void setDecryptionKey(const QString &value);
    void setMap(ChaoticMap1DUptr &&value);
};

#endif // EVOLUTIONENCRYPTOR_H
