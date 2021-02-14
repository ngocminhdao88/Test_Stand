#include "errorlogger.h"
#include <QFile>
#include <QTextStream>

ErrorLogger::ErrorLogger(QObject *parent) : QObject(parent)
{
}

void ErrorLogger::write(QString message)
{
    QFile logfile("error.log");
    if(!logfile.open(QIODevice::Append)) {
	    //show the error message
	    return;
    }
	QTextStream stream(&logfile);
    stream << QString("%1: %2\r\n").arg(QDateTime::currentDateTime().toString(), message);

    logfile.close();
}
