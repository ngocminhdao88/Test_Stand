#ifndef UNICOVFDCONFIGDIALOG_H
#define UNICOVFDCONFIGDIALOG_H

#include <QObject>
#include <QDialog>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui {
class UnicoVfdConfigDialog;
}
QT_END_NAMESPACE

class UnicoVfdConfigDialog : public QDialog
{
    Q_OBJECT
public:
     UnicoVfdConfigDialog(QWidget *parent = 0);
     ~UnicoVfdConfigDialog();


    struct Parameters {
        QString portName = "";
        int parity = QSerialPort::NoParity;
        int baud = QSerialPort::Baud9600;
        int databits = QSerialPort::Data8;
        int stopbits = QSerialPort::OneStop;
        int deviceid = 1;
        int timeout = 100;
        int retry = 3;
    };

    Parameters parameters() const;

private:
    Parameters m_parameters;
    Ui::UnicoVfdConfigDialog *ui;
};

#endif // UNICOVFDCONFIGDIALOG_H
