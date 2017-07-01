#include "imageencryptormodel.h"

QImage ImageEncryptorModel::getSrcImage() const
{
    return srcImage;
}

void ImageEncryptorModel::setSrcImage(const QImage &value)
{
    srcImage = value;
}

QImage ImageEncryptorModel::getDstImage() const
{
    return dstImage;
}

void ImageEncryptorModel::setDstImage(const QImage &value)
{
    dstImage = value;
}

ImageEncryptorModel::ImageEncryptorModel(ImageEncryptorPresenter *presenter):
    presenter(presenter)
{

}

bool ImageEncryptorModel::loadImage(const QString filename)
{
    QImage img = QImage(filename);
    if(img.isNull())
        return false;

    srcImage = img;
    dstImage = QImage();
    presenter->updateImages();
    return true;
}
