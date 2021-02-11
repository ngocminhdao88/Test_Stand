#ifndef SERIALSETTINGS_H
#define SERIALSETTINGS_H

#include <QObject>
#include <QDialog>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui {
class ModbusRtuSettingsDialog;
}
QT_END_NAMESPACE

class ModbusRtuSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    ModbusRtuSettingsDialog(QWidget *parent = 0);
    ~ModbusRtuSettingsDialog();

    struct Parameters {
        QString portName;
        int parity;
        int baud;
        int databits;
        int stopbits;
        int id;
        int timeout;
        int retry;
    };

    Parameters parameters() const;

private:
    Parameters m_parameters;
    Ui::ModbusRtuSettingsDialog *ui;
};

#endif // SERIALSETTINGS_H
