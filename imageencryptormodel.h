#ifndef IMAGEENCRYPTORMODEL_H
#define IMAGEENCRYPTORMODEL_H

#include <QImage>

#include "imageencryptorpresenter.h"
#include "encryption/imageencryptor.h"
#include "encryption/evolutionencryptor.h"
#include "encryption/dnaencryptor.h"
#include "maps.h"

class ImageEncryptorModel
{
private:

    ImageEncryptorPresenter *presenter;

    QImage srcImage;
    QImage dstImage;

    ImageEncryptor *encryptor;

    ChaoticMap3D *getChaoticMap(int map);

public:
    enum EncryptionMethods{DNA, Yoon, EvolutionAlgorithm};

    ImageEncryptorModel(ImageEncryptorPresenter *presenter);

    bool loadSrcImage(const QString filename);
    bool saveDstImage(const QString filename);
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
};

#endif // IMAGEENCRYPTORMODEL_H
