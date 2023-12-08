#include "mainwindow.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include <QApplication>
#include <QLockFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLockFile lockFile(QDir::temp().absoluteFilePath("dtest.lock"));

    if (!lockFile.tryLock(100))
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Приложение уже запущено.\n"
                       "Разрешено запускать только один экземпляр приложения.");
        msgBox.exec();
        return 1;
    }

    MainWindow w;
    w.show();
    qRegisterMetaType<QVector<int> >("QVector<int>");
    return a.exec();
}

