#include "mainwindow.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

