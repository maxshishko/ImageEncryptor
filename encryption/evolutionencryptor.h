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

#include "imageencryptor.h"
#include "chaoticmap1d.h"
#include "logisticmap.h"
#include "dnasequence.h"

class EvolutionEncryptor : public ImageEncryptor
{
private:
    int populationSize;
    double mutationRate;
    double entropy;
    QString decryptionKey;
    int encoding = 0;
    ChaoticMap1D *map = new LogisticMap();

    QVector<QVector<double> > keys;
    enum DNA{A, T, C, G};
    QVector<QVector<int> > rules;
    QByteArray imagePrefix;

    QByteArray calculateHash(QImage image);
    double getMapInit(QByteArray hash);
    QVector<DNASequence *> getInitialPopulation(int length);
    QVector<double> *getChaoticSequence(int length, int index = -1);
    QVector<double> *getChaoticSequence(int length, double keyL, double keyH);
    DNASequence *getDnaMask(QVector<double> *chaoticSequence);
    int getRule(double val);
    DNASequence *image2dna(QImage image, int encoding);
    QImage dna2image(DNASequence* seq, int encoding);
    QVector<double> calcEntropies(QVector<DNASequence*> population);
    double calcEntropy(DNASequence *member);
    QVector<double> calcProbabilities(QVector<double> entropies);
    QVector<QVector<int> > getCrossoverPairs(QVector<double> probabilities);
    int doRouletteWheel(QSet<int> indices, QVector<double> probabilities);
    void singlepointCrossover(DNASequence* first, DNASequence* second);
    void singleMutation(QVector<DNASequence *> &population, int index, DNASequence* image);
    void swapKeys(int i, int j);
    QPair<double, int> findMaxEntropy(QVector<DNASequence*> population);
    void doCrossover(QVector<DNASequence*> population);
    void doMutation(QVector<DNASequence*> population, DNASequence* image);

public:
    EvolutionEncryptor();
    EvolutionEncryptor(int populationSize, double mutationRate, double entropy);
    EvolutionEncryptor(QString decryptionKey);
    ~EvolutionEncryptor(){
        delete map;
    }

    QImage encrypt(QImage src);
    QImage decrypt(QImage src);

    void setRandomParameters();
    QString parametersToString();

    int getPopulationSize() const;
    void setPopulationSize(int value);
    double getMutationRate() const;
    void setMutationRate(double value);
    double getEntropy() const;
    void setEntropy(double value);
    QString getDecryptionKey() const;
    void setDecryptionKey(const QString &value);
    ChaoticMap1D *getMap() const;
    void setMap(ChaoticMap1D *value);
};

#endif // EVOLUTIONENCRYPTOR_H
