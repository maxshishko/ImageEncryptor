#ifndef IMAGEENCRYPTORMODEL_H
#define IMAGEENCRYPTORMODEL_H

#include <QImage>

#include "imageencryptorpresenter.h"
#include "encryption/imageencryptor.h"
#include "encryption/evolutionencryptor.h"

class ImageEncryptorModel
{
private:

    ImageEncryptorPresenter *presenter;

    QImage srcImage;
    QImage dstImage;

    ImageEncryptor *encryptor;

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
};

#endif // IMAGEENCRYPTORMODEL_H
