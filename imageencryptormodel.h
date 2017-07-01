#ifndef IMAGEENCRYPTORMODEL_H
#define IMAGEENCRYPTORMODEL_H

#include <QImage>

#include "imageencryptorpresenter.h"

class ImageEncryptorModel
{
private:

    ImageEncryptorPresenter *presenter;

    QImage srcImage;
    QImage dstImage;

public:
    ImageEncryptorModel(ImageEncryptorPresenter *presenter);

    bool loadImage(const QString filename);

    QImage getSrcImage() const;
    void setSrcImage(const QImage &value);
    QImage getDstImage() const;
    void setDstImage(const QImage &value);
};

#endif // IMAGEENCRYPTORMODEL_H
