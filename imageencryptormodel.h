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

    bool loadSrcImage(const QString filename);
    bool saveDstImage(const QString filename);
    void swapPlainCipher();

    QImage getSrcImage() const;
    QImage getDstImage() const;
};

#endif // IMAGEENCRYPTORMODEL_H
