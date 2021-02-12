#ifndef ERRORLOGGER_H
#define ERRORLOGGER_H

/*
 * Write down error message with current time
 */

#include <QObject>
#include <QTime>
#include <QFile>
#include <QTextStream>

#include "interfaces/ilogger.h"

class ErrorLogger : public QObject, public iLogger
{
    Q_OBJECT
public:
    explicit ErrorLogger(QObject *parent = nullptr);

signals:


    // iLogger interface
public:
    void write(QString message) override;

};

#endif // ERRORLOGGER_H
