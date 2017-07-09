#include "dnaencryptor.h"

#include <QBuffer>
#include <QCryptographicHash>
#include <QRegularExpression>
#include <QFile>
#include <QTextStream>

QByteArray DNAEncryptor::calculateHash(QImage image)
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

double DNAEncryptor::getModification(QByteArray ba)
{
    char result;
    foreach (char value, ba)
        result = result^value;
    uchar ucresult = *reinterpret_cast<uchar*>(&result);
    double res = ((double)ucresult)/256.;
    return res;
}

QVector<DNASequence*> DNAEncryptor::image2dna(QImage src)
{
    QVector<DNASequence*> result;
    result.push_back(new DNASequence);
    result.push_back(new DNASequence);
    result.push_back(new DNASequence);
    for(int i = 0; i < src.width(); i++){
        for(int j = 0; j < src.height(); j++){
            uchar   r = static_cast<uchar>(src.pixelColor(i,j).red()),
                    g = static_cast<uchar>(src.pixelColor(i,j).green()),
                    b = static_cast<uchar>(src.pixelColor(i,j).blue());
            result[0]->push_back(r, encoding);
            result[1]->push_back(g, encoding);
            result[2]->push_back(b, encoding);
        }
    }
    return result;
}

QImage DNAEncryptor::dna2image(QVector<DNASequence*> seq, int width, int height)
{
    QImage result(width, height, QImage::Format_RGB888);
    QByteArray  rArray  = seq[0]->toByteArray(encoding),
                gArray  = seq[1]->toByteArray(encoding),
                bArray  = seq[2]->toByteArray(encoding);
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

QVector<QMultiMap<double, int>* > DNAEncryptor::generateChaoticSequence(ChaoticMap3D *map, int size)
{
    QVector<QMultiMap<double, int>* > chSequence;
    chSequence.push_back(new QMultiMap<double, int>);
    chSequence.push_back(new QMultiMap<double, int>);
    chSequence.push_back(new QMultiMap<double, int>);

    for(int i = 0; i < size; i++){
        chSequence[0]->insert(map->getX(), i);
        chSequence[1]->insert(map->getY(), i);
        chSequence[2]->insert(map->getZ(), i);
        map->next();
    }
    return chSequence;
}

void DNAEncryptor::diffusion(QVector<DNASequence *> &image, DNASequence *mask)
{
    DNASequence* xoredColorPlane;
    for(int c = 0; c < image.size(); c++){
        xoredColorPlane = new DNASequence((*image[c])^(*mask));
        delete image[c];
        image[c] = xoredColorPlane;
    }
}

void DNAEncryptor::fpermutation(QVector<DNASequence *> &image, ChaoticMap3D *map)
{
    QVector<QMultiMap<double, int>*> chaoticSequence = generateChaoticSequence(map, image[0]->size());
    DNASequence* confusedColorPlane;
    for(int c = 0; c < image.size(); c++){
        confusedColorPlane = new DNASequence;
        for(QMultiMap<double, int>::iterator it = chaoticSequence[c]->begin();
            it != chaoticSequence[c]->end(); it++){
            confusedColorPlane->push_back((*image[c])[it.value()]);
        }
        delete image[c];
        image[c] = confusedColorPlane;
    }
}

void DNAEncryptor::ipermutation(QVector<DNASequence *> &image, ChaoticMap3D *map)
{
    QVector<QMultiMap<double, int>*> chaoticSequence = generateChaoticSequence(map, image[0]->size());
    DNASequence* confusedColorPlane;
    for(int c = 0; c < image.size(); c++){
        confusedColorPlane = new DNASequence(image[c]->size());
        QMultiMap<double, int>::iterator it = chaoticSequence[c]->begin();
        for(int i = 0; i < image[c]->size(); i++, it++)
            (*confusedColorPlane)[it.value()] = (*(image[c]))[i];
        delete image[c];
        image[c] = confusedColorPlane;
    }
}

DNAEncryptor::DNAEncryptor(ChaoticMap3D *map, int encoding, QString hash):
    map(map)
{
    setEncoding(encoding);
    setHash(hash);
}

DNAEncryptor::~DNAEncryptor()
{
    delete map;
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

ChaoticMap3D *DNAEncryptor::getMap() const
{
    return map;
}

void DNAEncryptor::setMap(ChaoticMap3D *value)
{
    map = value;
}

QImage DNAEncryptor::encrypt(QImage src)
{
    hash = calculateHash(src);
    modifyInit();
    DNASequence* dnaHash = new DNASequence(hash, encoding);
    QVector<DNASequence*> dnaImage = image2dna(src);
    fpermutation(dnaImage, map);
    diffusion(dnaImage, dnaHash);
    QImage result = dna2image(dnaImage, src.height(), src.width());
    for(int i = 0; i < dnaImage.size(); i++)
        delete dnaImage[i];
    delete dnaHash;
    return result;
}

QImage DNAEncryptor::decrypt(QImage src)
{
    modifyInit();
    DNASequence* dnaHash = new DNASequence(hash, encoding);
    QVector<DNASequence*> dnaImage = image2dna(src);
    diffusion(dnaImage, dnaHash);
    ipermutation(dnaImage, map);
    QImage result = dna2image(dnaImage, src.height(), src.width());
    for(int i = 0; i < dnaImage.size(); i++)
        delete dnaImage[i];
    delete dnaHash;
    return result;
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
    result += QString::fromLocal8Bit(hash).append(';');
    return result;
}
