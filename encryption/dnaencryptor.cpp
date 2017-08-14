#include "dnaencryptor.h"

#include <QBuffer>
#include <QCryptographicHash>
#include <QRegularExpression>
#include <QFile>
#include <QTextStream>

QByteArray DNAEncryptor::calculateHash(const QImage &image)
{
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "BMP");
    buffer.close();
    return QCryptographicHash::hash(ba, QCryptographicHash::Sha256);
}

void DNAEncryptor::modifyInit()
{
    map->setX(x+getModification(hash.mid(0, 11)));
    map->setY(y+getModification(hash.mid(11, 11)));
    map->setZ(z+getModification(hash.mid(22)));
}

double DNAEncryptor::getModification(const QByteArray &ba)
{
    char result;
    for (char value: ba)
        result = result^value;
    uchar ucresult = *reinterpret_cast<uchar*>(&result);
    double res = ((double)ucresult)/256.;
    return res;
}

DNAEncryptor::VecDNASequence DNAEncryptor::image2dna(const QImage &src)
{
    VecDNASequence result;
    result.push_back(DNASequence());
    result.push_back(DNASequence());
    result.push_back(DNASequence());
    for(int i = 0; i < src.width(); i++){
        for(int j = 0; j < src.height(); j++){
            uchar   r = static_cast<uchar>(src.pixelColor(i,j).red()),
                    g = static_cast<uchar>(src.pixelColor(i,j).green()),
                    b = static_cast<uchar>(src.pixelColor(i,j).blue());
            result[0].push_back(r, encoding);
            result[1].push_back(g, encoding);
            result[2].push_back(b, encoding);
        }
    }
    return result;
}

QImage DNAEncryptor::dna2image(VecDNASequence seq, int width, int height)
{
    QImage result(width, height, QImage::Format_RGB888);
    QByteArray  rArray  = seq[0].toByteArray(encoding),
                gArray  = seq[1].toByteArray(encoding),
                bArray  = seq[2].toByteArray(encoding);
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            char    r = rArray[i*height+j],
                    g = gArray[i*height+j],
                    b = bArray[i*height+j];
            QColor c = QColor(*reinterpret_cast<uchar*>(&r),
                              *reinterpret_cast<uchar*>(&g),
                              *reinterpret_cast<uchar*>(&b));
            result.setPixelColor(i, j, c);
        }
    }
    return result;
}

DNAEncryptor::ChaoticSequences DNAEncryptor::generateChaoticSequence(int size)
{
    ChaoticSequences chSequences;
    chSequences.push_back(QMultiMap<double, int>());
    chSequences.push_back(QMultiMap<double, int>());
    chSequences.push_back(QMultiMap<double, int>());

    for(int i = 0; i < size; i++){
        chSequences[0].insert(map->getX(), i);
        chSequences[1].insert(map->getY(), i);
        chSequences[2].insert(map->getZ(), i);
        map->next();
    }
    return chSequences;
}

void DNAEncryptor::diffusion(VecDNASequence &image, const DNASequence &mask)
{
    DNASequence xoredColorPlane;
    for(int c = 0; c < image.size(); c++){
        xoredColorPlane = image[c]^mask;
        image[c] = std::move(xoredColorPlane);
    }
}

void DNAEncryptor::fpermutation(VecDNASequence &image)
{
    auto chaoticSequence = generateChaoticSequence(image[0].size());
    for(int c = 0; c < image.size(); c++){
        DNASequence confusedColorPlane;
        for(auto it = chaoticSequence[c].begin();
            it != chaoticSequence[c].end(); ++it){
            confusedColorPlane.push_back(image[c][it.value()]);
        }
        image[c] = std::move(confusedColorPlane);
    }
}

void DNAEncryptor::ipermutation(VecDNASequence &image)
{
    auto chaoticSequence = generateChaoticSequence(image[0].size());
    for(int c = 0; c < image.size(); c++){
        DNASequence confusedColorPlane(image[c].size());
        auto it = chaoticSequence[c].begin();
        for(int i = 0; i < image[c].size(); i++, it++)
            confusedColorPlane[it.value()] = image[c][i];
        image[c] = std::move(confusedColorPlane);
    }
}

DNAEncryptor::DNAEncryptor(ChaoticMap3DUptr &&map, int encoding, QString hash):
    map(std::move(map))
{
    setEncoding(encoding);
    setHash(hash);
}

DNAEncryptor::~DNAEncryptor()
{
}

QString DNAEncryptor::getHash() const
{
    return QString::fromLocal8Bit(hash.toHex());
}

void DNAEncryptor::setHash(const QString &value)
{
    if(value.size() != 64)
        throw std::invalid_argument("Hash size must be 64.");
    QRegularExpression hexMatcher("^[0-9A-F]{32}$", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match = hexMatcher.match(value);
    if(!match.hasMatch())
        std::invalid_argument("Decryption key must be in hex.");
    hash = QByteArray::fromHex(value.toLocal8Bit());
}

int DNAEncryptor::getEncoding() const
{
    return encoding;
}

void DNAEncryptor::setEncoding(int value)
{
    if(value < 0)
        value = 0;
    else if(value > 7)
        value = 7;
    encoding = value;
}

double DNAEncryptor::getX() const
{
    return x;
}

void DNAEncryptor::setX(double value)
{
    x = value;
}

double DNAEncryptor::getY() const
{
    return y;
}

void DNAEncryptor::setY(double value)
{
    y = value;
}

double DNAEncryptor::getZ() const
{
    return z;
}

void DNAEncryptor::setZ(double value)
{
    z = value;
}

void DNAEncryptor::setMap(ChaoticMap3DUptr &&value)
{
    map = std::move(value);
}

QImage DNAEncryptor::encrypt(const QImage &src)
{
    hash = calculateHash(src);
    modifyInit();
    DNASequence dnaHash(hash, encoding);
    VecDNASequence dnaImage = image2dna(src);
    fpermutation(dnaImage);
    diffusion(dnaImage, dnaHash);
    return dna2image(dnaImage, src.height(), src.width());
}

QImage DNAEncryptor::decrypt(const QImage &src)
{
    modifyInit();
    DNASequence dnaHash(hash, encoding);
    VecDNASequence dnaImage = image2dna(src);
    diffusion(dnaImage, dnaHash);
    ipermutation(dnaImage);
    return dna2image(dnaImage, src.height(), src.width());
}

void DNAEncryptor::setRandomParameters()
{
    encoding = rand()%8;
    map->setRandomInit();
    x = map->getX();
    y = map->getY();
    z = map->getZ();
}

QString DNAEncryptor::parametersToString()
{
    QString result;
    result += QString::number(x).append(';');
    result += QString::number(y).append(';');
    result += QString::number(z).append(';');
    result += QString::number(encoding).append(';');
    result += QString::fromLocal8Bit(hash.toHex()).append(';');
    return result;
}
