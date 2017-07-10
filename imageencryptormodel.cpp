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
        if(!dynamic_cast<DNAEncryptor*>(this->encryptor)){
            delete this->encryptor;
            this->encryptor = new DNAEncryptor();
        }
        break;
    case EncryptionMethods::Yoon:
        if(!dynamic_cast<YoonEncryptor*>(this->encryptor)){
            delete this->encryptor;
            this->encryptor = new YoonEncryptor();
        }
        break;
    case EncryptionMethods::EvolutionAlgorithm:
        if(!dynamic_cast<EvolutionEncryptor*>(this->encryptor)){
            delete this->encryptor;
            this->encryptor = new EvolutionEncryptor();
        }
        break;
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

void ImageEncryptorModel::setDNAEncryptorParameters(double x, double y, double z, int map, int encoding, QString hash)
{
    DNAEncryptor *dnaEncryptor = dynamic_cast<DNAEncryptor*>(encryptor);
    if(!dnaEncryptor)
        throw std::logic_error("Invalid encryptor selected.");
    dnaEncryptor->setMap(getChaoticMap(map));
    dnaEncryptor->setX(x);
    dnaEncryptor->setY(y);
    dnaEncryptor->setZ(z);
    dnaEncryptor->setEncoding(encoding);
    if(hash.size() == 0)
        hash = QString(64, '0');
    dnaEncryptor->setHash(hash);
}

bool ImageEncryptorModel::getDNAEncryptorParameters(double &x, double &y, double &z, int &encoding, QString &hash)
{
    DNAEncryptor *dnaEncryptor = dynamic_cast<DNAEncryptor*>(encryptor);
    if(!dnaEncryptor)
        throw std::logic_error("Invalid encryptor selected.");
    x = dnaEncryptor->getX();
    y = dnaEncryptor->getY();
    z = dnaEncryptor->getZ();
    encoding = dnaEncryptor->getEncoding();
    hash = dnaEncryptor->getHash();
}

void ImageEncryptorModel::setYoonEncryptorParameters(double init, double param, double K)
{
    YoonEncryptor *yoonEncryptor = dynamic_cast<YoonEncryptor*>(encryptor);
    if(!yoonEncryptor)
        throw std::logic_error("Invalid encryptor selected.");
    yoonEncryptor->setInit(init);
    yoonEncryptor->setParam(param);
    yoonEncryptor->setK(K);
}

bool ImageEncryptorModel::getYoonEncryptorParameters(double &init, double &param, int &K)
{
    YoonEncryptor *yoonEncryptor = dynamic_cast<YoonEncryptor*>(encryptor);
    if(!yoonEncryptor)
        throw std::logic_error("Invalid encryptor selected.");
    init = yoonEncryptor->getInit();
    param = yoonEncryptor->getParam();
    K = yoonEncryptor->getK();
}

QVector<QVector<int> > ImageEncryptorModel::getSrcHistogram()
{
    if(!srcImage.isNull())
        return Analysis::histogram(srcImage);
    return QVector<QVector<int> >();
}

QVector<QVector<int> > ImageEncryptorModel::getDstHistogram()
{
    if(!dstImage.isNull())
        return Analysis::histogram(dstImage);
    return QVector<QVector<int> >();
}

QVector<QVector<QVector<double> > > ImageEncryptorModel::getSrcCorrelationData(int type)
{
    if(srcImage.isNull())
        return QVector<QVector<QVector<double> > >();
    return Analysis::getCorrelationData(srcImage, (Analysis::CorrelationType)type);
}

QVector<QVector<QVector<double> > > ImageEncryptorModel::getDstCorrelationData(int type)
{
    if(dstImage.isNull())
        return QVector<QVector<QVector<double> > >();
    return Analysis::getCorrelationData(dstImage, (Analysis::CorrelationType)type);
}

QVector<double> ImageEncryptorModel::getSrcCorrelation(int type)
{
    if(srcImage.isNull())
        return QVector<double>();
    return Analysis::correlation(srcImage, (Analysis::CorrelationType)type);
}

QVector<double> ImageEncryptorModel::getDstCorrelation(int type)
{
    if(dstImage.isNull())
        return QVector<double>();
    return Analysis::correlation(dstImage, (Analysis::CorrelationType)type);
}

ChaoticMap3D *ImageEncryptorModel::getChaoticMap(int map)
{
    switch (map) {
    case 0:
        return new LorenzMap;
    case 1:
        return new Combined3DMap(new PWLCM, new PWLCM, new PWLCM);
    case 2:
        return new Combined3DMap(new LogisticMap, new LogisticMap, new LogisticMap);
    case 3:
        return new Combined3DMap(new TentMap, new TentMap, new TentMap);
    case 4:
        return new Baker3DMap;
    }
    return new LorenzMap;
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
