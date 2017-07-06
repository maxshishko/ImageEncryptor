#include "imageencryptormodel.h"

QImage ImageEncryptorModel::getSrcImage() const
{
    return srcImage;
}

QImage ImageEncryptorModel::getDstImage() const
{
    return dstImage;
}

bool ImageEncryptorModel::encrypt()
{
    if(!srcImage.isNull()){
        dstImage = encryptor->encrypt(srcImage);
        presenter->updateImages();
        presenter->updateParameters();
    }
    return false;
}

bool ImageEncryptorModel::decrypt()
{
    if(!srcImage.isNull()){
        dstImage = encryptor->decrypt(srcImage);
        presenter->updateImages();
        return true;
    }
    return false;
}

void ImageEncryptorModel::setRandomParameters()
{
    encryptor->setRandomParameters();
    presenter->updateParameters();
}

void ImageEncryptorModel::changeEncryptor(int encryptor)
{
    switch (encryptor) {
    case EncryptionMethods::DNA:
        break;
    case EncryptionMethods::Yoon:
        break;
    case EncryptionMethods::EvolutionAlgorithm:
        if(!dynamic_cast<EvolutionEncryptor*>(this->encryptor)){
            delete this->encryptor;
            this->encryptor = new EvolutionEncryptor();
        }
    default:
        break;
    }
}

void ImageEncryptorModel::setEvolutionEncryptorParameters(int popSize, double mutationRate, double entropy)
{
    EvolutionEncryptor *evEncryptor = dynamic_cast<EvolutionEncryptor*>(encryptor);
    if(!evEncryptor)
        throw std::logic_error("Invalid encryptor selected.");
    evEncryptor->setPopulationSize(popSize);
    evEncryptor->setMutationRate(mutationRate);
    evEncryptor->setEntropy(entropy);
}

void ImageEncryptorModel::setEvolutionEncryptorParameters(QString decryptionKey)
{
    EvolutionEncryptor *evEncryptor = dynamic_cast<EvolutionEncryptor*>(encryptor);
    if(!evEncryptor)
        throw std::logic_error("Invalid encryptor selected.");
    evEncryptor->setDecryptionKey(decryptionKey);
}

bool ImageEncryptorModel::getEvolutionEncryptorParameters(int &popSize, double &mutationRate, double &entropy)
{
    EvolutionEncryptor *evEncryptor = dynamic_cast<EvolutionEncryptor*>(encryptor);
    if(!evEncryptor)
        throw std::logic_error("Invalid encryptor selected.");
    popSize = evEncryptor->getPopulationSize();
    mutationRate = evEncryptor->getMutationRate();
    entropy = evEncryptor->getEntropy();
}

bool ImageEncryptorModel::getEvolutionEncryptorParameters(QString &decryptionKey)
{
    EvolutionEncryptor *evEncryptor = dynamic_cast<EvolutionEncryptor*>(encryptor);
    if(!evEncryptor)
        throw std::logic_error("Invalid encryptor selected.");
    decryptionKey = evEncryptor->getDecryptionKey();
}

ImageEncryptorModel::ImageEncryptorModel(ImageEncryptorPresenter *presenter):
    presenter(presenter)
{
    encryptor = new EvolutionEncryptor;
}

bool ImageEncryptorModel::loadSrcImage(const QString filename)
{
    QImage img = QImage(filename);
    if(!img.isNull()){
        srcImage = img;
        dstImage = QImage();
        presenter->updateImages();
        return true;
    }
    return false;
}

bool ImageEncryptorModel::saveDstImage(const QString filename)
{
    if(!dstImage.isNull() && dstImage.save(filename))
        return true;
    return false;
}

void ImageEncryptorModel::swapPlainCipher()
{
    QImage tmp = srcImage;
    srcImage.swap(dstImage);
    dstImage.swap(tmp);
    presenter->updateImages();
}
