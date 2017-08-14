#ifndef IMAGEENCRYPTORMODEL_H
#define IMAGEENCRYPTORMODEL_H

#include <QImage>
#include <memory>

#include "imageencryptorpresenter.h"
#include "encryption/imageencryptor.h"
#include "encryption/evolutionencryptor.h"
#include "encryption/dnaencryptor.h"
#include "encryption/yoonencryptor.h"
#include "maps.h"
#include "analysis.h"

class ImageEncryptorModel
{
private:

    std::weak_ptr<ImageEncryptorPresenter> presenter;

    QImage srcImage;
    QImage dstImage;

    std::shared_ptr<ImageEncryptor> encryptor = std::make_shared<EvolutionEncryptor>();

    std::unique_ptr<ChaoticMap3D> getChaoticMap(int map);

public:
    enum EncryptionMethods{DNA, Yoon, EvolutionAlgorithm};

    bool loadSrcImage(const QString &filename);
    bool saveDstImage(const QString &filename);
    void swapPlainCipher();

    QImage getSrcImage() const;
    QImage getDstImage() const;

    bool encrypt();
    bool decrypt();

    void setRandomParameters();
    void changeEncryptor(int encryptor);

    void setEvolutionEncryptorParameters(int popSize, double mutationRate, double entropy);
    void setEvolutionEncryptorParameters(QString decryptionKey);
    bool getEvolutionEncryptorParameters(int &popSize, double &mutationRate, double &entropy);
    bool getEvolutionEncryptorParameters(QString &decryptionKey);

    void setDNAEncryptorParameters(double x, double y, double z, int map, int encoding, QString hash);
    bool getDNAEncryptorParameters(double &x, double &y, double &z, int &encoding, QString &hash);

    void setYoonEncryptorParameters(double init, double param, double K);
    bool getYoonEncryptorParameters(double &init, double &param, int &K);

    QVector<QVector<int> > getSrcHistogram();
    QVector<QVector<int> > getDstHistogram();
    QVector<QVector<QVector<double> > > getSrcCorrelationData(int type);
    QVector<QVector<QVector<double> > > getDstCorrelationData(int type);
    QVector<double> getSrcCorrelation(int type);
    QVector<double> getDstCorrelation(int type);
    QVector<double> getSrcEntropy();
    QVector<double> getDstEntropy();
    QVector<double> getNPCR();
    QVector<double> getUACI();
    double getEncryptionTime();
    bool fullAnalysis(QString filename, bool useRandomParams = false,  int numSimulations = 1);
    void setPresenter(const std::shared_ptr<ImageEncryptorPresenter> &value);
};

#endif // IMAGEENCRYPTORMODEL_H
