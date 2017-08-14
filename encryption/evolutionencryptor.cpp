#include "evolutionencryptor.h"

#include <iostream>
#include <algorithm>

int EvolutionEncryptor::getPopulationSize() const
{
    return populationSize;
}

void EvolutionEncryptor::setPopulationSize(int value)
{
    if(value < 2)
        throw std::invalid_argument("Population size must be not less, than 2.");
    populationSize = value;
}

double EvolutionEncryptor::getMutationRate() const
{
    return mutationRate;
}

void EvolutionEncryptor::setMutationRate(double value)
{
    if(value < 0 || value > 1)
        throw std::invalid_argument("Mutation rate must be in range from 0 to 1.");
    mutationRate = value;
}

double EvolutionEncryptor::getEntropy() const
{
    return entropy;
}

void EvolutionEncryptor::setEntropy(double value)
{
    if(value < 0 || value > 8)
        throw std::invalid_argument("Entropy must be in range from 0 to 8.");
    entropy = value;
}

QString EvolutionEncryptor::getDecryptionKey() const
{
    return decryptionKey;
}

void EvolutionEncryptor::setDecryptionKey(const QString &value)
{
    if(value.size() != 32)
        std::invalid_argument("Decryption key must be 32 character in length.");

    QRegularExpression hexMatcher("^[0-9A-F]{32}$", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match = hexMatcher.match(value);
    if(!match.hasMatch())
        std::invalid_argument("Decryption key must be in hex.");

    decryptionKey = value;
}

void EvolutionEncryptor::setMap(ChaoticMap1DUptr &&value)
{
    map = std::move(value);
}

QByteArray EvolutionEncryptor::calculateHash(const QImage &image)
{
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "BMP");
    buffer.close();
    return QCryptographicHash::hash(ba, QCryptographicHash::Sha256);
}

double EvolutionEncryptor::getMapInit(const QByteArray &hash)
{
    double init = 0;
    char ch = hash[0];
    uint numerator = *reinterpret_cast<uchar*>(&ch);
    for(int i = 1; i < hash.size()/2; i++){
        ch = hash[i];
        ch = *reinterpret_cast<uchar*>(&ch);
        numerator = numerator^ch;
    }
    for(int i = 0; i < hash.size(); i++){
        ch = hash[i];
        ch = *reinterpret_cast<uchar*>(&ch);
        numerator += ch;
    }
    init = numerator;
    init = init / pow(2., 13);
    return init;
}

QVector<DNASequence> EvolutionEncryptor::getInitialPopulation(int length)
{
    QVector<DNASequence> population;
    for(int i = 0; i < populationSize; ++i){
        auto chaoticSequence = getChaoticSequence(length);
        population.push_back(getDnaMask(chaoticSequence));
    }
    return population;
}

QVector<double> EvolutionEncryptor::getChaoticSequence(int length, int index)
{
    QVector<double> seq;
    QVector<double> key;
    key.push_back(map->getX());

    for(int i = 0; i < length/2; ++i)
        seq.push_back(map->next());
    key.push_back(map->getX());
    if(index < 0)
        keys.push_back(key);
    else
        keys[index].swap(key);
    for(int i = length/2; i < length; ++i)
        seq.push_back(map->next());
    return seq;
}

QVector<double> EvolutionEncryptor::getChaoticSequence(int length, double keyL, double keyH)
{
    map->setX(keyL);
    QVector<double> seq;
    for(int i = 0; i < length/2; i++)
        seq.push_back(map->next());
    map->setX(keyH);
    for(int i = length/2; i< length; i++)
        seq.push_back(map->next());
    return seq;
}

DNASequence EvolutionEncryptor::getDnaMask(const QVector<double> &chaoticSequence)
{
    DNASequence result;

    for (auto chaoticVal: chaoticSequence) {
        uchar val = static_cast<uchar>(floor(chaoticVal*256));
        result.push_back(val, encoding);
    }
    return result;
}

int EvolutionEncryptor::getRule(double val)
{
    return floor(val*8);
}

DNASequence EvolutionEncryptor::image2dna(const QImage &image, int encoding)
{
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "BMP");
    buffer.close();
    imagePrefix = ba.mid(0, 54);
    return DNASequence(ba.mid(54), encoding);
}

QImage EvolutionEncryptor::dna2image(const DNASequence &seq, int encoding)
{
    QByteArray ba = imagePrefix;
    ba.append(seq.toByteArray(encoding));
    return QImage::fromData(ba);
}

QVector<double> EvolutionEncryptor::calcEntropies(const QVector<DNASequence> &population)
{
    QVector<double> entropies;
    for (auto member: population)
        entropies.push_back(calcEntropy(member));
    return entropies;
}

double EvolutionEncryptor::calcEntropy(const DNASequence &member)
{
    QVector<double> colors(256, 0);

    QImage img = dna2image(member, encoding);

    for(int i = 0; i < img.height(); i++){
        for(int j = 0; j < img.width(); j++){
            colors[img.pixelColor(j, i).red()]++;
            colors[img.pixelColor(j, i).green()]++;
            colors[img.pixelColor(j, i).blue()]++;
        }
    }

    int dim = img.height()*img.width()*3;
    double entropy = 0;
    for(int i = 0; i < 256; i++){
        double p = colors[i]/dim;
        if(p < 1e-6)
            continue;
        else
            entropy += (p)*log(1/p)/log(2);
    }

    return entropy;
}

QVector<double> EvolutionEncryptor::calcProbabilities(const QVector<double> &entropies)
{
    QVector<double> probabilities;
    double probabilitySum = 0;
    for(int i = 0; i < entropies.size(); i++){
        probabilitySum += 1./(8.-entropies[i]);
        probabilities.push_back(1./(8.-entropies[i]));
    }
    for(int i = 0; i < probabilities.size(); i++)
        probabilities[i] /= probabilitySum;
    return probabilities;
}

QVector<QVector<int>> EvolutionEncryptor::getCrossoverPairs(const QVector<double> &probabilities)
{
    QVector<QVector<int>> crossoverPairs;
    QSet<int> indices;
    for(int i = 0; i < probabilities.size(); i++)
        indices.insert(i);

    while (!indices.empty()) {
        QVector<int> pair;
        pair.push_back(*indices.begin());
        indices.erase(indices.begin());
        int index = doRouletteWheel(indices, probabilities);
        indices.erase(indices.find(index));
        pair.push_back(index);
        crossoverPairs.push_back(pair);
    }
    return crossoverPairs;
}

int EvolutionEncryptor::doRouletteWheel(const QSet<int> &indices, const QVector<double> &probabilities)
{
    QVector<double> localProbabileties;
    double sum = 0;
    for(auto index: indices){
        localProbabileties.push_back(probabilities[index]);
        sum += probabilities[index];
    }
    std::for_each(localProbabileties.begin(), localProbabileties.end(), [sum](double &el){el/=sum;});
    double randomNumber = static_cast<double>(rand())/static_cast<double>(RAND_MAX);
    auto it = indices.begin();
    sum = 0;
    for(int i = 0; i < localProbabileties.size(); i++, it++){
        sum += localProbabileties[i];
        if(sum > randomNumber)
            return *it;
    }
    return *indices.end();
}

void EvolutionEncryptor::singlepointCrossover(DNASequence &first, DNASequence &second)
{
    first.crossover(second, first.size()/2);
}

void EvolutionEncryptor::singleMutation(QVector<DNASequence> &population, int index, const DNASequence &image)
{
    int size = population[index].size();
    population[index] = std::move(image^getDnaMask(getChaoticSequence(size/4, index)));
}

void EvolutionEncryptor::swapKeys(int i, int j){
    std::swap(keys[i][1], keys[j][1]);
}

QPair<double, int> EvolutionEncryptor::findMaxEntropy(const QVector<DNASequence> &population)
{
    auto entropies = calcEntropies(population);
    QMultiMap<double, int> sortedEntropies;
    for(int i = 0; i < entropies.size(); i++)
        sortedEntropies.insert(entropies[i], i);
    QPair<double, int> result;
    result.first = (--(sortedEntropies.end())).key();
    result.second = (--(sortedEntropies.end())).value();
    return result;
}

void EvolutionEncryptor::doCrossover(QVector<DNASequence> &population)
{
    QVector<double> entropies = calcEntropies(population);
    QVector<double> probabilities = calcProbabilities(entropies);
    QVector<QVector<int> > crossoverPairs = getCrossoverPairs(probabilities);
    for(int i = 0; i < crossoverPairs.size(); i++){
        singlepointCrossover(population[crossoverPairs[i][0]], population[crossoverPairs[i][1]]);
        swapKeys(crossoverPairs[i][0], crossoverPairs[i][1]);
    }
}

void EvolutionEncryptor::doMutation(QVector<DNASequence> &population, const DNASequence &image)
{
    auto entropies = calcEntropies(population);
    QMultiMap<double, int> sortedEntropies;
    for(int i = 0; i < entropies.size(); i++)
        sortedEntropies.insert(entropies[i], i);

    auto it = sortedEntropies.begin();
    for(auto mutN = 0; mutN < static_cast<int>(populationSize*mutationRate); mutN++, it++)
        singleMutation(population, it.value(), image);
}

EvolutionEncryptor::EvolutionEncryptor(int populationSize, double mutationRate, double entropy)
{
    setPopulationSize(populationSize);
    setMutationRate(mutationRate);
    setEntropy(entropy);
}

EvolutionEncryptor::EvolutionEncryptor(QString decryptionKey)
{
    setDecryptionKey(decryptionKey);
}

QImage EvolutionEncryptor::encrypt(const QImage &src)
{
    auto hash = calculateHash(src);
    map->setX(getMapInit(hash));
    int length = src.height()*src.width()*3;

    auto masksPopulation = getInitialPopulation(length);
    auto dnaImage = image2dna(src, encoding);
    QVector<DNASequence> maskedPopulation;

    for(int i = 0; i < populationSize; i++)
        maskedPopulation.push_back(dnaImage.fSerialXOR(masksPopulation[i]));

    QPair<double, int> maxEntropy;
    do{
        doCrossover(maskedPopulation);
        doMutation(maskedPopulation, dnaImage);
        maxEntropy = findMaxEntropy(maskedPopulation);
    } while(maxEntropy.first < entropy);

    double keyL = keys[maxEntropy.second][0];
    double keyH = keys[maxEntropy.second][1];
    decryptionKey = QString::number(*reinterpret_cast<qlonglong*>(&keyL), 16).
             append(QString::number(*reinterpret_cast<qlonglong*>(&keyH), 16));

    return dna2image(maskedPopulation[maxEntropy.second],encoding);
}

QImage EvolutionEncryptor::decrypt(const QImage &src)
{
    auto dnaImage = image2dna(src, encoding);
    int length = src.height()*src.width()*3;
    qlonglong keyLll = decryptionKey.mid(0, decryptionKey.size()/2).toLongLong(nullptr, 16);
    qlonglong keyHll = decryptionKey.mid(decryptionKey.size()/2, decryptionKey.size()/2).toLongLong(nullptr, 16);
    double keyL = *reinterpret_cast<double*>(&keyLll);
    double keyH = *reinterpret_cast<double*>(&keyHll);

    auto seq = getChaoticSequence(length, keyL, keyH);
    auto dnaMask = getDnaMask(seq);
    auto rawImage = dnaImage.iSerialXOR(dnaMask);
    return dna2image(rawImage, encoding);
}

void EvolutionEncryptor::setRandomParameters()
{
    populationSize = rand()%100;
    mutationRate = (double)rand()/(double)RAND_MAX;
    entropy = (double)rand()/(double)RAND_MAX*8.;
}

QString EvolutionEncryptor::parametersToString()
{
    QString result;
    result += QString::number(populationSize).append(';');
    result += QString::number(mutationRate).append(';');
    result += QString::number(entropy).append(';');
    result += decryptionKey.append(';');
    return result;
}
