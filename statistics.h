
#ifndef STATISTICS_H
#define STATISTICS_H

#include <QVector>
#include "qmath.h"


class Statistics
{
public:
    Statistics();
    GetKurtosisAndAsymmetry(QVector <qint16> &v1, double &asymmetry_, double &kurtosis_);
};

#endif // STATISTICS_H
