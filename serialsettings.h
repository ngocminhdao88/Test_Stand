#ifndef SERIALSETTINGS_H
#define SERIALSETTINGS_H

#include <QObject>
#include <QDialog>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui {
class SerialSettings;
}
QT_END_NAMESPACE

class SerialSettings : public QDialog
{
    Q_OBJECT
public:
    SerialSettings(QWidget *parent = 0);
    ~SerialSettings();

    struct Parameters {
        QString portName = "";
        int parity = QSerialPort::NoParity;
        int baud = QSerialPort::Baud9600;
        int databits = QSerialPort::Data8;
        int stopbits = QSerialPort::OneStop;
        int timeout = 100;
        int retry = 3;
    };

    Parameters parameters() const;

private:
    Parameters m_parameters;
    Ui::SerialSettings *ui;
};

#endif // SERIALSETTINGS_H
