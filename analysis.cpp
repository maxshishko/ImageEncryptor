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

double Analysis::mean(QVector<double> sequence)
{
    double sum = 0;
    foreach (double el, sequence)
        sum+=el;
    return sum / sequence.size();
}

QVector<double> Analysis::calcCorrelation(QVector<QVector<double> > samplesX, QVector<QVector<double> > samplesY)
{
    QVector<double> result;
    for(int c = 0; c < 3; c++){
        double r = 0, divX = 0, divY = 0, meanX = 0, meanY = 0;
        meanX = mean(samplesX[c]);
        meanY = mean(samplesY[c]);
        for(int i = 0; i < samplesX.size(); i++){
            r += (samplesX[c][i]-meanX)*(samplesY[c][i]-meanY);
            divX += (samplesX[c][i]-meanX)*(samplesX[c][i]-meanX);
            divY += (samplesY[c][i]-meanY)*(samplesY[c][i]-meanY);
        }
        result.push_back(r/sqrt(divX*divY));
    }
    return result;
}

void Analysis::writeVector(QTextStream *stream, QVector<double> vector)
{
    for(int i = 0; i < vector.size(); i++)
        (*stream) << vector[i] << ';';
}

QVector<QVector<int> > Analysis::histogram(QImage image)
{
    QVector<QVector<int> > hist(3, QVector<int>(256, 0));

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

QVector<double> Analysis::correlation(QImage image, Analysis::CorrelationType type, int pixelSetSize)
{
    int dx = corrMask[type][0], dy = corrMask[type][1];

    if(pixelSetSize>image.width()*image.height())
        pixelSetSize = image.width()*image.height()/2;

    QVector<QPoint> pixelSet = getRandomPixelset(image.width()-dx, image.height()-dy, pixelSetSize);
    QVector<QVector<double> > samplesX(3, QVector<double>());
    QVector<QVector<double> > samplesY(3, QVector<double>());
    foreach (QPoint point, pixelSet) {
        samplesX[0].push_back(image.pixelColor(point).red());
        samplesY[0].push_back(image.pixelColor(point+QPoint(dx, dy)).red());
        samplesX[1].push_back(image.pixelColor(point).green());
        samplesY[1].push_back(image.pixelColor(point+QPoint(dx, dy)).green());
        samplesX[2].push_back(image.pixelColor(point).blue());
        samplesY[2].push_back(image.pixelColor(point+QPoint(dx, dy)).blue());
    }

    return calcCorrelation(samplesX, samplesY);
}

QVector<double> Analysis::entropy(QImage image)
{
    QVector<QVector<double> > colors(3, QVector<double>(256, 0));

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
        foreach (double el, colors[c]) {
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

QVector<double> Analysis::NPCR(ImageEncryptor *encryptor, QImage image)
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
            if(srcColor.red()!=modColor.red())
                result[0]++;
            if(srcColor.green()!=modColor.green())
                result[1]++;
            if(srcColor.blue()!=modColor.blue())
                result[2]++;
        }
    }
    result[0] /= image.width()*image.height()/100;
    result[1] /= image.width()*image.height()/100;
    result[2] /= image.width()*image.height()/100;
    return result;
}

QVector<double> Analysis::UACI(ImageEncryptor *encryptor, QImage image)
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

double Analysis::encryptionTime(ImageEncryptor *encryptor, QImage image)
{
    int begin = clock();
    encryptor->encrypt(image);
    return static_cast<double>(clock()-begin)/1000.;
}

void Analysis::fullAnalysis(ImageEncryptor *encryptor, QImage image, QString filename, int numSimulations)
{
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly)){
        QTextStream stream(&file);

        for(int i = 0; i < numSimulations; i++){
            stream << image.text().append(';');
            stream << encryptor->parametersToString();
            QImage encImage = encryptor->encrypt(image);
            writeVector(&stream, correlation(encImage, CorrelationType::CORR_H));
            writeVector(&stream, correlation(encImage, CorrelationType::CORR_V));
            writeVector(&stream, correlation(encImage, CorrelationType::CORR_D));
            writeVector(&stream, entropy(encImage));
            writeVector(&stream, NPCR(encryptor, image));
            writeVector(&stream, UACI(encryptor, image));
            stream << encryptionTime(encryptor, image) << "\n";
        }
        file.close();
    }
}
