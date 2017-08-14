#ifndef DNAENCRYPTOR_H
#define DNAENCRYPTOR_H

#include <stdexcept>
#include <QMultiMap>

#include "imageencryptor.h"
#include "dnasequence.h"
#include "chaoticmap3d.h"
#include <memory>

class DNAEncryptor : public ImageEncryptor
{
private:
    using ChaoticMap3DUptr = std::unique_ptr<ChaoticMap3D>;
    using VecDNASequence = QVector<DNASequence>;
    using ChaoticSequences = QVector<QMultiMap<double, int>>;

    QByteArray hash;
    int encoding;
    double x, y, z;
    ChaoticMap3DUptr map;

    QByteArray imagePrefix;

    QByteArray calculateHash(const QImage &image);
    void modifyInit();
    double getModification(const QByteArray &ba);
    VecDNASequence image2dna(const QImage &src);
    QImage dna2image(VecDNASequence seq, int width, int height);
    ChaoticSequences generateChaoticSequence(int size);
    void diffusion(VecDNASequence &image, const DNASequence &mask);
    void fpermutation(VecDNASequence &image);
    void ipermutation(VecDNASequence &image);
public:
    DNAEncryptor(){}
    DNAEncryptor(ChaoticMap3DUptr &&map,
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
    void setMap(ChaoticMap3DUptr &&value);

    QImage encrypt(const QImage &src) override;
    QImage decrypt(const QImage &src) override;
    void setRandomParameters() override;
    QString parametersToString() override;
};

#endif // DNAENCRYPTOR_H
