#ifndef RFTHREAD_H
#define RFTHREAD_H

#include <QObject>
#include <QDebug>
#include <QRandomGenerator>
#include "windows.h"
#include "inisettings.h"
#include "RFHeaders/RF603Device.h"
#include "RFHeaders/RFEthernetDetector.h"


class RFThread : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    bool m_running;
    int count;  // Счётчик, для понимания живой ли поток
public:
    RFThread();
    bool running() const;
signals:
    void finished();
    void runningChanged(bool running);
    void EmitMeasures(QVector<int> OutputMeasures);
public slots:
    void run();
    void setRunning(bool running);
};

#endif // RFTHREAD_H
