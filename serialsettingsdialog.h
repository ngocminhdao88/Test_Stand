#ifndef SERIALSETTINGS_H
#define SERIALSETTINGS_H

#include <QObject>
#include <QDialog>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui {
class SerialSettingsDialog;
}
QT_END_NAMESPACE

class SerialSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    SerialSettingsDialog(QWidget *parent = 0);
    ~SerialSettingsDialog();

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
    Ui::SerialSettingsDialog *ui;
};

#endif // SERIALSETTINGS_H
