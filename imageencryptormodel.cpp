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
        if(auto presenterShared = presenter.lock()){
            presenterShared->updateImages();
            presenterShared->updateParameters();
        }
    }
    return false;
}

bool ImageEncryptorModel::decrypt()
{
    if(!srcImage.isNull()){
        dstImage = encryptor->decrypt(srcImage);
        if(auto presenterShared = presenter.lock())
            presenterShared->updateImages();
        return true;
    }
    return false;
}

void ImageEncryptorModel::setRandomParameters()
{
    encryptor->setRandomParameters();
    if(auto presenterShared = presenter.lock())
        presenterShared->updateParameters();
}

void ImageEncryptorModel::changeEncryptor(int encryptor)
{
    switch (encryptor) {
    case EncryptionMethods::DNA:
        if(!std::dynamic_pointer_cast<DNAEncryptor>(this->encryptor)){
            this->encryptor = std::make_shared<DNAEncryptor>();
        }
        break;
    case EncryptionMethods::Yoon:
        if(!std::dynamic_pointer_cast<YoonEncryptor>(this->encryptor)){
            this->encryptor = std::make_shared<YoonEncryptor>();
        }
        break;
    case EncryptionMethods::EvolutionAlgorithm:
        if(!std::dynamic_pointer_cast<EvolutionEncryptor>(this->encryptor)){
            this->encryptor = std::make_shared<EvolutionEncryptor>();
        }
        break;
    default:
        break;
    }
}

void ImageEncryptorModel::setEvolutionEncryptorParameters(int popSize, double mutationRate, double entropy)
{
    auto evEncryptor = std::dynamic_pointer_cast<EvolutionEncryptor>(encryptor);
    if(!evEncryptor)
        throw std::logic_error("Invalid encryptor selected.");
    evEncryptor->setPopulationSize(popSize);
    evEncryptor->setMutationRate(mutationRate);
    evEncryptor->setEntropy(entropy);
}

void ImageEncryptorModel::setEvolutionEncryptorParameters(QString decryptionKey)
{
    auto evEncryptor = std::dynamic_pointer_cast<EvolutionEncryptor>(encryptor);
    if(!evEncryptor)
        throw std::logic_error("Invalid encryptor selected.");
    evEncryptor->setDecryptionKey(decryptionKey);
}

bool ImageEncryptorModel::getEvolutionEncryptorParameters(int &popSize, double &mutationRate, double &entropy)
{
    auto evEncryptor = std::dynamic_pointer_cast<EvolutionEncryptor>(encryptor);
    if(!evEncryptor)
        throw std::logic_error("Invalid encryptor selected.");
    popSize = evEncryptor->getPopulationSize();
    mutationRate = evEncryptor->getMutationRate();
    entropy = evEncryptor->getEntropy();
}

bool ImageEncryptorModel::getEvolutionEncryptorParameters(QString &decryptionKey)
{
    auto evEncryptor = std::dynamic_pointer_cast<EvolutionEncryptor>(encryptor);
    if(!evEncryptor)
        throw std::logic_error("Invalid encryptor selected.");
    decryptionKey = evEncryptor->getDecryptionKey();
}

void ImageEncryptorModel::setDNAEncryptorParameters(double x, double y, double z, int map, int encoding, QString hash)
{
    auto dnaEncryptor = std::dynamic_pointer_cast<DNAEncryptor>(encryptor);
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
    auto dnaEncryptor = std::dynamic_pointer_cast<DNAEncryptor>(encryptor);
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
    auto yoonEncryptor = std::dynamic_pointer_cast<YoonEncryptor>(encryptor);
    if(!yoonEncryptor)
        throw std::logic_error("Invalid encryptor selected.");
    yoonEncryptor->setInit(init);
    yoonEncryptor->setParam(param);
    yoonEncryptor->setK(K);
}

bool ImageEncryptorModel::getYoonEncryptorParameters(double &init, double &param, int &K)
{
    auto yoonEncryptor = std::dynamic_pointer_cast<YoonEncryptor>(encryptor);
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

QVector<double> ImageEncryptorModel::getSrcEntropy()
{
    QVector<double> result;
    if(!srcImage.isNull())
        result =  Analysis::entropy(srcImage);
    return result;
}

QVector<double> ImageEncryptorModel::getDstEntropy()
{
    QVector<double> result;
    if(!srcImage.isNull())
        result = Analysis::entropy(srcImage);
    return result;
}

QVector<double> ImageEncryptorModel::getNPCR()
{
    QVector<double> result;
    if(!srcImage.isNull())
        result = Analysis::NPCR(encryptor, srcImage);
    return result;
}

QVector<double> ImageEncryptorModel::getUACI()
{
    QVector<double> result;
    if(!srcImage.isNull())
        result = Analysis::UACI(encryptor, srcImage);
    return result;
}

double ImageEncryptorModel::getEncryptionTime()
{
    if(srcImage.isNull())
        return -1;
    return Analysis::encryptionTime(encryptor, srcImage);
}

bool ImageEncryptorModel::fullAnalysis(QString filename, bool useRandomParams, int numSimulations)
{
    if(srcImage.isNull())
        return false;
    return Analysis::fullAnalysis(encryptor, srcImage, filename,useRandomParams, numSimulations);
}

std::unique_ptr<ChaoticMap3D> ImageEncryptorModel:: getChaoticMap(int map)
{
    switch (map) {
    case 0:
        return std::make_unique<LorenzMap>();
    case 1:
        return std::make_unique<Combined3DMap>(
                    std::make_unique<PWLCM>(),
                    std::make_unique<PWLCM>(),
                    std::make_unique<PWLCM>());
    case 2:
        return std::make_unique<Combined3DMap>(
                    std::make_unique<LogisticMap>(),
                    std::make_unique<LogisticMap>(),
                    std::make_unique<LogisticMap>());
    case 3:
        return std::make_unique<Combined3DMap>(
                    std::make_unique<TentMap>(),
                    std::make_unique<TentMap>(),
                    std::make_unique<TentMap>());
    case 4:
        return std::make_unique<Baker3DMap>();
    }
    return std::make_unique<LorenzMap>();
}

void ImageEncryptorModel::setPresenter(const std::shared_ptr<ImageEncryptorPresenter> &value)
{
    presenter = value;
}

bool ImageEncryptorModel::loadSrcImage(const QString &filename)
{
    QImage img = QImage(filename);
    if(!img.isNull()){
        srcImage = img;
        dstImage = QImage();
        if(auto presShared = presenter.lock())
            presShared->updateImages();
        return true;
    }
    return false;
}

bool ImageEncryptorModel::saveDstImage(const QString &filename)
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
    if(auto presShared = presenter.lock())
        presShared->updateImages();
}
