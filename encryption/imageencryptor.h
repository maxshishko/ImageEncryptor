#ifndef IMAGEENCRYPTOR_H
#define IMAGEENCRYPTOR_H

#include <QImage>

class ImageEncryptor
{
public:
    ImageEncryptor();

    virtual QImage encrypt(QImage src) = 0;
    virtual QImage decrypt(QImage src) = 0;
    virtual void setRandomParameters() = 0;
    virtual QString parametersToString() = 0;
};

#endif // IMAGEENCRYPTOR_H
