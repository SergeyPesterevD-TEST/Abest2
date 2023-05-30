#include "statistics.h"

// Abs data of vector
void absVector (QVector <qint16> v, quint32 n)
{
    qint16* data = v.data();
    for (quint32 i = 0; i < n; i++)
        data[i] = qAbs(data[i]);
}

// Sum of vector elements
qint32 sumVector (QVector <qint16> v, quint32 n)
{
    qint16* data = v.data();
    qint32 s = 0;
    for (quint32 i = 0; i < n; i++)
        s += data[i];
    return s;
}

// Arithemit mean of vector elements
double arithmeticMean (qint32 s, quint32 n)
{
    double res = s / n;
    return res;
}

// Central moment random variables
QVector <qint16> centralMoment (QVector <qint16> v, quint32 n, double mx)
{
    QVector <qint16> temp(n);
    qint16* data = v.data();
    for (quint32 i = 0; i < n; i++)
        temp[i] = data[i] - mx;
    return temp;
}

// Exponentiation of vector elements
QVector <qint16> exponentiation (QVector <qint16> v, quint32 n, quint32 y)
{
    QVector <qint16> temp(n);
    qint16* data = v.data();
    for (quint32 i = 0; i < n; i++)
        temp[i] = qPow(data[i], y);
    return temp;
}

// Standart deviation
double deviation (qint32 s, quint32 n)
{
    double res = qSqrt( (double) s / (n - 1));
    return res;
}

// Asymmetry of vector elements
double asymmetry (qint32 s, quint32 n, double sig)
{
    double res = s / (n * qPow(sig,3));
    return res;
}

// Kurtosis of vector elements
double kurtosis(qint32 s, quint32 n, double sig)
{
    double res = s / (n * qPow(sig,4)) - 3;
    return res;
}


Statistics::GetKurtosisAndAsymmetry(QVector <qint16> &v1, double &asymmetry_, double &kurtosis_)
{
    int size;
    size=v1.count();

    //absVector(v1, size); // ???

    qint32 s1 = sumVector(v1, size);
    double Mx = arithmeticMean(s1, size);

    QVector <qint16> v2 = centralMoment(v1, size, Mx);
    QVector <qint16> v3 = exponentiation(v2, size, 2);

    qint32 s2 = sumVector(v3, size);
    double sig = deviation(s2, size);

    v3 = exponentiation(v2, size, 3);
    qint32 s3 = sumVector(v3, size);

    asymmetry_=asymmetry(s3, size, sig);
    v3 = exponentiation(v2, size, 4);
    qint32 s4 = sumVector(v3, size);
    kurtosis_ = kurtosis(s4, size, sig);
}

Statistics::Statistics()
{

}

