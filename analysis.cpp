#include "analysis.h"

constexpr int Analysis::corrMask[3][2];

QVector<QPoint> Analysis::getRandomPixelset(int sizex, int sizey, int setSize)
{
    QVector<QPoint> set;
    for(int c = 0; c < 3; c++)
        for(int i = 0; i < setSize; i++)
            set.push_back(QPoint(rand()%sizex, rand()%sizey));
    return set;
}

double Analysis::calcCorrelation(const QVector<double> &samplesX, const QVector<double> &samplesY)
{
    auto mean = [](auto seq){
        double sum;
        for(auto el:seq)
            sum+=el;
        return sum/seq.size();
    };

    double r = 0, divX = 0, divY = 0, meanX = 0, meanY = 0;
    meanX = mean(samplesX);
    meanY = mean(samplesY);
    for(int i = 0; i < samplesX.size(); i++){
        r += (samplesX[i]-meanX)*(samplesY[i]-meanY);
        divX += (samplesX[i]-meanX)*(samplesX[i]-meanX);
        divY += (samplesY[i]-meanY)*(samplesY[i]-meanY);
    }
    return r/sqrt(divX*divY);
}

void Analysis::writeVector(QTextStream &stream, const QVector<double> &vector)
{
    for(int i = 0; i < vector.size(); i++)
        stream << vector[i] << ';';
}

QVector<QVector<int>> Analysis::histogram(const QImage &image)
{
    QVector<QVector<int>> hist(3, QVector<int>(256, 0));

    QColor color;
    for(int i = 0; i < image.width(); i++){
        for(int j = 0; j < image.height(); j++){
            color = image.pixelColor(i, j);
            hist[0][color.red()]++;
            hist[1][color.green()]++;
            hist[2][color.blue()]++;
        }
    }
    return hist;
}

QVector<double> Analysis::correlation(const QImage &image, Analysis::CorrelationType type, int pixelSetSize)
{

    auto dataSet = getCorrelationData(image, type, pixelSetSize);
    QVector<double> result;
    result.push_back(calcCorrelation(dataSet[0][0], dataSet[0][1]));
    result.push_back(calcCorrelation(dataSet[1][0], dataSet[1][1]));
    result.push_back(calcCorrelation(dataSet[2][0], dataSet[2][1]));

    return result;
}

QVector<QVector<QVector<double>>> Analysis::getCorrelationData(const QImage &image, Analysis::CorrelationType type, int pixelSetSize)
{
    int dx = corrMask[static_cast<int>(type)][0], dy = corrMask[static_cast<int>(type)][1];

    if(pixelSetSize>image.width()*image.height())
        pixelSetSize = image.width()*image.height()/2;

    auto pixelSet = getRandomPixelset(image.width()-dx, image.height()-dy, pixelSetSize);
    QVector<QVector<QVector<double>>> dataSet(3, QVector<QVector<double>>(2, QVector<double>()));
    for (auto point: pixelSet) {
        dataSet[0][0].push_back(image.pixelColor(point).redF());
        dataSet[0][1].push_back(image.pixelColor(point+QPoint(dx, dy)).redF());
        dataSet[1][0].push_back(image.pixelColor(point).greenF());
        dataSet[1][1].push_back(image.pixelColor(point+QPoint(dx, dy)).greenF());
        dataSet[2][0].push_back(image.pixelColor(point).blueF());
        dataSet[2][1].push_back(image.pixelColor(point+QPoint(dx, dy)).blueF());
    }
    return dataSet;
}

QVector<double> Analysis::entropy(const QImage &image)
{
    QVector<QVector<double>> colors(3, QVector<double>(256, 0));

    for(int i = 0; i < image.width(); i++)
        for(int j = 0; j < image.height(); j++){
            QColor color = image.pixelColor(i,j);
            colors[0][color.red()]++;
            colors[1][color.green()]++;
            colors[2][color.blue()]++;
        }

    int size = image.width()*image.height();
    QVector<double> result;
    for(int c = 0; c < 3; c++){
        double ent = 0;
        for(auto el: colors[c]) {
            double p = el/size;
            if(p < 1e-6)
                continue;
            else
                ent += (p)*log(1/p)/log(2);
        }
        result.push_back(ent);
    }
    return result;
}

QVector<double> Analysis::NPCR(ImgEncryptorPtr encryptor, QImage image)
{
    QVector<double> result(3, 0);
    auto modifiedImage = image;
    modifiedImage.setPixelColor(rand()%image.width(),
                                rand()%image.height(),
                                QColor(rand()%256, rand()%256, rand()%256));

    image = encryptor->encrypt(image);
    modifiedImage = encryptor->encrypt(modifiedImage);

    for(int i = 0; i < image.width(); i++){
        for(int j = 0; j < image.height(); j++){
            QColor srcColor = image.pixelColor(i,j);
            QColor modColor = modifiedImage.pixelColor(i,j);
            if(srcColor.red()!=modColor.red())
                result[0]++;
            if(srcColor.green()!=modColor.green())
                result[1]++;
            if(srcColor.blue()!=modColor.blue())
                result[2]++;
        }
    }
    result[0] /= image.width()*image.height(); result[0] *= 100.;
    result[1] /= image.width()*image.height(); result[1] *= 100.;
    result[2] /= image.width()*image.height(); result[2] *= 100.;
    return result;
}

QVector<double> Analysis::UACI(ImgEncryptorPtr encryptor, QImage image)
{
    QVector<double> result(3, 0);
    QImage modifiedImage = image;
    modifiedImage.setPixelColor(rand()%image.width(),
                                rand()%image.height(),
                                QColor(rand()%256, rand()%256, rand()%256));

    image = encryptor->encrypt(image);
    modifiedImage = encryptor->encrypt(modifiedImage);

    for(int i = 0; i < image.width(); i++){
        for(int j = 0; j < image.height(); j++){
            QColor srcColor = image.pixelColor(i,j);
            QColor modColor = modifiedImage.pixelColor(i,j);
            result[0] += fabs((double)(srcColor.red()-modColor.red()))/255.;
            result[1] += fabs((double)(srcColor.green()-modColor.green()))/255.;
            result[2] += fabs((double)(srcColor.blue()-modColor.blue()))/255.;
        }
    }
    result[0] /= image.width()*image.height()/100;
    result[1] /= image.width()*image.height()/100;
    result[2] /= image.width()*image.height()/100;
    return result;
}

double Analysis::encryptionTime(ImgEncryptorPtr encryptor, const QImage &image)
{
    int begin = clock();
    encryptor->encrypt(image);
    return static_cast<double>(clock()-begin)/1000.;
}

bool Analysis::fullAnalysis(ImgEncryptorPtr encryptor, const QImage &image, const QString &filename, bool useRandomParams, int numSimulations)
{
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly)){
        QTextStream stream(&file);

        for(int i = 0; i < numSimulations; i++){
            stream << image.text().append(';');
            if(useRandomParams)
                encryptor->setRandomParameters();
            QImage encImage = encryptor->encrypt(image);
            stream << encryptor->parametersToString();
            writeVector(stream, correlation(encImage, CorrelationType::CORR_H));
            writeVector(stream, correlation(encImage, CorrelationType::CORR_V));
            writeVector(stream, correlation(encImage, CorrelationType::CORR_D));
            writeVector(stream, entropy(encImage));
            writeVector(stream, NPCR(encryptor, image));
            writeVector(stream, UACI(encryptor, image));
            stream << encryptionTime(encryptor, image) << "\n";
        }
        file.close();
        return true;
    }
    return false;
}
