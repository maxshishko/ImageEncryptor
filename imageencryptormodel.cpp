#include "imageencryptormodel.h"

QImage ImageEncryptorModel::getSrcImage() const
{
    return srcImage;
}

QImage ImageEncryptorModel::getDstImage() const
{
    return dstImage;
}

ImageEncryptorModel::ImageEncryptorModel(ImageEncryptorPresenter *presenter):
    presenter(presenter)
{

}

bool ImageEncryptorModel::loadSrcImage(const QString filename)
{
    QImage img = QImage(filename);
    if(!img.isNull()){
        srcImage = img;
        dstImage = QImage();
        presenter->updateImages();
        return true;
    }
    return false;
}

bool ImageEncryptorModel::saveDstImage(const QString filename)
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
    presenter->updateImages();
}
