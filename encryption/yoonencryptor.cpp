#include "yoonencryptor.h"

YoonEncryptor::YoonEncryptor(double init, double param, int K){
    setInit(init);
    setParam(param);
    setK(K);
}

QImage YoonEncryptor::encrypt(const QImage &src)
{
    auto result = src;
    if(result.height() > result.width())
        result = result.transformed(QTransform().rotate(90));

    QVector<int> seed = dividers(result.height());
    int **lookUpTable = createLUT(seed);
    QImage tempImage;
    int red,green,blue;
    QColor oldColor;
    for(int r = 0; r < K; r++){
        tempImage = result;
        int **mask = createMask(result.height());
        for(int i = 0; i < result.height(); i++){
            for(int j = 0; j < result.width(); j++){
                oldColor = tempImage.pixelColor(j, i);
                red   = oldColor.red()^mask[lookUpTable[i][j]][j];
                green = oldColor.green()^mask[lookUpTable[i][j]][j];
                blue  = oldColor.blue()^mask[lookUpTable[i][j]][j];
                result.setPixelColor(j, lookUpTable[i][j], QColor(red, green, blue));
            }
        }
        freeMemory(mask, result.height());
    }
    freeMemory(lookUpTable, result.height());

    if(result.height() > result.width())
        result = result.transformed(QTransform().rotate(-90));
    return result;
}

QImage YoonEncryptor::decrypt(const QImage &src)
{
    auto result = src;
    if(result.height() > result.width())
        result = result.transformed(QTransform().rotate(90));

    QVector<int> seed = dividers(result.height());
    int **lookUpTable = createLUT(seed);
    QImage tempImage;
    int red,green,blue;
    QColor oldColor;

    double modInit = map.getX();
    for(int r = 0; r < K; r++){
        tempImage = result;
        map.setX(modInit);
        for(int i = 0; i < K - 1 - r; i++ )
            for(int j = 0; j < result.height()*result.height(); j++)
                map.next();
        int **mask = createMask(result.height());
        for(int i = 0; i < result.height(); i++){
            for(int j = 0; j < result.width(); j++){
                oldColor = tempImage.pixelColor(j, lookUpTable[i][j]);
                red   = oldColor.red()^mask[lookUpTable[i][j]][j];
                green = oldColor.green()^mask[lookUpTable[i][j]][j];
                blue  = oldColor.blue()^mask[lookUpTable[i][j]][j];
                result.setPixelColor(j, i, QColor(red, green, blue));
            }
        }
        freeMemory(mask, result.height());
    }
    freeMemory(lookUpTable, result.height());

    if(result.height() > result.width())
        result = result.transformed(QTransform().rotate(-90));
    return result;
}

void YoonEncryptor::setRandomParameters()
{
    K = rand()%20;
    map.setRandomInit();
    map.setParam((double)rand()/(double)RAND_MAX);
    init = map.getX();
    param = map.getParam();
}

QString YoonEncryptor::parametersToString()
{
    QString result;
    result += QString::number(init).append(';');
    result += QString::number(param).append(';');
    result += QString::number(K).append(';');
    return result;
}

int YoonEncryptor::getK() const
{
    return K;
}

void YoonEncryptor::setK(int value)
{
    if(value<=0)
        value = 1;
    K = value;
}

double YoonEncryptor::getInit() const
{
    return init;
}

void YoonEncryptor::setInit(double value)
{
    map.setX(value);
    init = map.getX();
}

double YoonEncryptor::getParam() const
{
    return param;
}

void YoonEncryptor::setParam(double value)
{
    map.setParam(value);
    param = map.getParam();
}

int **YoonEncryptor::createLUT(const QVector<int> &seed)
{
    int **lut = createSmallMatrix(seed[0]);
    shuffleMatrix(lut, seed[0]);
    int size = seed[0];
    for(int i = 1; i < seed.size(); i++){
        int **matrix = createSmallMatrix(seed[i]);
        shuffleMatrix(matrix, seed[i]);
        int** product = productMatrix(lut, size, matrix, seed[i]);
        freeMemory(lut, size);
        freeMemory(matrix, seed[i]);
        lut = product;
        size *= seed[i];
    }
    return lut;
}

int **YoonEncryptor::createSmallMatrix(int size)
{
    int **matrix = new int*[size];
    for(int i = 0; i < size; i++){
        matrix[i] = new int[size];
        for(int j = 0; j < size; j++)
            matrix[i][j] = i;
    }
    return matrix;
}

int **YoonEncryptor::createMask(int size)
{
    int** matrix = new int*[size];
    for(int i = 0; i < size; i++){
        matrix[i] = new int[size];
        for(int j = 0; j < size; j++){
            matrix[i][j] = static_cast<int>(map.next()*1e8)%256;
        }
    }
    return matrix;
}

int **YoonEncryptor::productMatrix(int **lmatrix, int lsize, int **rmatrix, int rsize)
{
    int productSize = lsize*rsize;
    int **product = new int*[productSize];
    for(int i = 0; i < productSize; i++)
        product[i] = new int[productSize];

    for(int i = 0; i < productSize; i++)
        for(int j = 0; j < productSize; j++){
            product[i][j] = rsize*lmatrix[i/rsize][j/rsize]+rmatrix[i%rsize][j%rsize];
        }
    return product;
}

QVector<int> YoonEncryptor::dividers(int value)
{
    QVector<int> div;
    int tmp = value;
    for(int i = 2; i <= 7; i++){
        if(tmp%i==0){
            div.push_back(1);
            div[div.size()-1]*= i;
            tmp /=i;
            i--;
        }
    }

    if(tmp!=1)
        div.push_back(tmp);
    return div;
}

void YoonEncryptor::shuffleMatrix(int **matrix, int size)
{
    for(int j = 0; j < size; j++){
        for(int i = 0; i < size; i++){
            map.next();
            int index = (static_cast<int>(map.getX()*1000))%size;
            if(j!=0){
                bool cont = false;
                for(int k = 0; k < j; k++){
                    if(matrix[i][k]==matrix[index][j]||matrix[index][k]==matrix[i][j]){
                        cont = true;
                        if(index > i)
                            swap(matrix, i, j, index, j);
                        break;
                    }
                }
                if(cont){
                    i--;
                    continue;
                }
            }
            swap(matrix, i, j, index, j);
        }
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            bool cont = false;
            for(int k = 0; k < size-1; k++){
                if(matrix[j][size-1] == matrix[i][k]){
                    cont = true;
                    break;
                }
            }
            if(cont)
                continue;
            swap(matrix, i, size-1, j, size-1);
            break;
        }
    }
    return;
}

void YoonEncryptor::swap(int **matrix, int i, int j, int k, int l)
{
    int tmp = matrix[i][j];
    matrix[i][j] = matrix[k][l];
    matrix[k][l] = tmp;
}

void YoonEncryptor::freeMemory(int **matrix, int size)
{
    for(int i = 0; i < size; i++)
        delete [] matrix[i];
    delete [] matrix;
}

YoonEncryptor::YoonEncryptor()
{

}

