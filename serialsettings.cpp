#include "ui_serialsettings.h"
#include "serialsettings.h"
#include <QSerialPortInfo>

SerialSettings::SerialSettings(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::SerialSettings)
{
    ui->setupUi(this);

    //setup UI with default values
    ui->cbxParity->setCurrentIndex(0);
    ui->cbxBaudrate->setCurrentText(QString::number(parameters().baud));
    ui->cbxDatabits->setCurrentText(QString::number(parameters().databits));
    ui->cbxStopbits->setCurrentText(QString::number(parameters().stopbits));
    ui->spxTimeout->setValue(parameters().timeout);
    ui->spxRetry->setValue(parameters().retry);


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
        m_parameters.timeout = ui->spxTimeout->value();
        m_parameters.retry = ui->spxRetry->value();

        hide();
    });
}

SerialSettings::~SerialSettings()
{
    delete ui;
}

SerialSettings::Parameters SerialSettings::parameters() const
{
    return m_parameters;
}
