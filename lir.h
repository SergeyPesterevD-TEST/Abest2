#ifndef LIR_H
#define LIR_H

#include <QObject>
#include <QDebug>
#include "inc/ulp_lib.h"
#include "inc/module_system_types.h"

class Lir : public QObject
{
    Q_OBJECT
public:
    explicit Lir(QObject *parent = nullptr);

    int LirMain();
signals:

};

#endif // LIR_H
