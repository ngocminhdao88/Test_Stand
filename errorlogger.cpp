#include "errorlogger.h"
#include <QFile>
#include <QTextStream>

ErrorLogger::ErrorLogger(QObject *parent) : QObject(parent)
{
}

void ErrorLogger::write(QString message)
{
    QFile logfile("error.log");
    if(logfile.open(QIODevice::Append)) {
        QTextStream stream(&logfile);
        stream << QString("%1: %2\n").arg(QTime::currentTime().toString(), message);
    }
    logfile.close();
}
