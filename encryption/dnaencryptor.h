#ifndef DNAENCRYPTOR_H
#define DNAENCRYPTOR_H

#include <stdexcept>
#include <QMultiMap>

#include "imageencryptor.h"
#include "dnasequence.h"
#include "chaoticmap3d.h"

class DNAEncryptor : public ImageEncryptor
{
private:
    QByteArray hash;
    int encoding;
    double x, y, z;
    ChaoticMap3D *map;

    QByteArray imagePrefix;

    QByteArray calculateHash(QImage image);
    void modifyInit();
    double getModification(QByteArray ba);
    QVector<DNASequence *> image2dna(QImage src);
    QImage dna2image(QVector<DNASequence *> seq, int width, int height);
    QVector<QMultiMap<double, int> *> generateChaoticSequence(ChaoticMap3D *map, int size);
    void diffusion(QVector<DNASequence *> &image, DNASequence* mask);
    void fpermutation(QVector<DNASequence *> &image, ChaoticMap3D* map);
    void ipermutation(QVector<DNASequence *> &image, ChaoticMap3D* map);
public:
    DNAEncryptor(){}
    DNAEncryptor(ChaoticMap3D *map,
                 int encoding,
                 QString hash = QString('0', 64));
    ~DNAEncryptor();

    QString getHash() const;
    void setHash(const QString &value);
    int getEncoding() const;
    void setEncoding(int value);
    double getX() const;
    void setX(double value);
    double getY() const;
    void setY(double value);
    double getZ() const;
    void setZ(double value);
    ChaoticMap3D *getMap() const;
    void setMap(ChaoticMap3D *value);

    QImage encrypt(QImage src);
    QImage decrypt(QImage src);
    void setRandomParameters();
    QString parametersToString();
};

#endif // DNAENCRYPTOR_H
