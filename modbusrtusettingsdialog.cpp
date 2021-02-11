#include "ui_modbusrtusettingsdialog.h"
#include "modbusrtusettingsdialog.h"
#include <QSerialPortInfo>

ModbusRtuSettingsDialog::ModbusRtuSettingsDialog(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::ModbusRtuSettingsDialog)
{
    ui->setupUi(this);

    //initiate the default settings
    m_parameters = {
        "", //portname
        0, //parity
        9600, //baud
        8, //databits
        1, //stopbits
        1, //id
        100, //timeout
        3, //retry
    };

    //setup UI with default values
    ui->cbxParity->setCurrentIndex(QSerialPort::NoParity);
    //ui->cbxParity->setCurrentText(QString::number(QSerialPort::NoParity));
    ui->cbxBaudrate->setCurrentText(QString::number(QSerialPort::Baud9600));
    ui->cbxDatabits->setCurrentText(QString::number(QSerialPort::Data8));
    ui->cbxStopbits->setCurrentText(QString::number(QSerialPort::OneStop));
    ui->spxDeviceID->setValue(1);
    ui->spxTimeout->setValue(100);
    ui->spxRetry->setValue(3);


    //refresh serial port
    connect(ui->btnPort, &QPushButton::clicked, [this] {
        ui->cbxPort->clear();
        QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
        for(auto port: ports) {
            ui->cbxPort->addItem(port.portName());
        }
    });

    //save the settings
    connect(ui->btnApply, &QPushButton::clicked, [this] {
        m_parameters.portName = ui->cbxPort->currentText();
        m_parameters.parity = ui->cbxParity->currentIndex();
        if(m_parameters.parity > 0) m_parameters.parity++;
        m_parameters.baud = ui->cbxBaudrate->currentText().toInt();
        m_parameters.databits = ui->cbxDatabits->currentText().toInt();
        m_parameters.stopbits = ui->cbxStopbits->currentText().toInt();
        m_parameters.id = ui->spxDeviceID->value();
        m_parameters.timeout = ui->spxTimeout->value();
        m_parameters.retry = ui->spxRetry->value();

        hide();
    });
}

ModbusRtuSettingsDialog::~ModbusRtuSettingsDialog()
{
    delete ui;
}

ModbusRtuSettingsDialog::Parameters ModbusRtuSettingsDialog::parameters() const
{
    return m_parameters;
}
