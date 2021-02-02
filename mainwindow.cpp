#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QModbusRtuSerialMaster>
#include "unicovfd.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) ,
      ui(new Ui::MainWindow),
      m_serialSettingsDialog(new SerialSettingsDialog(this))
{
    ui->setupUi(this);

    setModbusClient(new QModbusRtuSerialMaster(this));
    setVfdDevice(new UnicoVFD(this));
    //TODO: how to set modbus device to this Unico VFD???
    //can i do it using the constructor???

    if(modbusClient()) {
        //change the state of modbus device
    } else {
        //error when creating a modbus device
        //disable the connection button
        //show error message
    }

    //SIGNALS->SLOTS on UI
    connect(ui->btnConnectVFD, &QPushButton::clicked, this, &MainWindow::onConnectVFDClicked);
    connect(ui->btnConfigVFD, &QPushButton::clicked, this, &MainWindow::onConfigVFDClicked);
    connect(ui->sbxSpeed, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onSpeedChanged);
    connect(ui->sbxDirection, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onDirectionChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
    //delete m_modbusClient;
}

QModbusClient *MainWindow::modbusClient() const
{
    return m_modbusClient;
}

void MainWindow::setModbusClient(QModbusClient *modbusClient)
{
    m_modbusClient = modbusClient;
}

void MainWindow::onConnectVFDClicked()
{
    if(!modbusClient()) return;
    if(!serialSettingsDialog()) return;

    //device is not connected yet
    if(modbusClient()->state() != QModbusDevice::ConnectedState) {
        //setup connection parameter
        modbusClient()->setConnectionParameter(
                    QModbusDevice::SerialPortNameParameter,
                    serialSettingsDialog()->parameters().portName);
        modbusClient()->setConnectionParameter(
                    QModbusDevice::SerialParityParameter,
                    serialSettingsDialog()->parameters().parity);
        modbusClient()->setConnectionParameter(
                    QModbusDevice::SerialBaudRateParameter,
                    serialSettingsDialog()->parameters().baud);
        modbusClient()->setConnectionParameter(
                    QModbusDevice::SerialDataBitsParameter,
                    SerialSettingsDialog().parameters().databits);
        modbusClient()->setConnectionParameter(
                    QModbusDevice::SerialStopBitsParameter,
                    serialSettingsDialog()->parameters().stopbits);
        modbusClient()->setTimeout(serialSettingsDialog()->parameters().timeout);
        modbusClient()->setNumberOfRetries(serialSettingsDialog()->parameters().retry);

        //try to connect to the modbus device
        if(modbusClient()->connectDevice()) {
            statusBar()->showMessage(QString("Connected to device on: %1").arg(serialSettingsDialog()->parameters().portName));
        } else {
            statusBar()->showMessage(
                        QString("Connection failed: %1, %2").arg(QString::number(modbusClient()->error()), modbusClient()->errorString()));
        }
    } else { //device is already connected
        //stop the VFD first

        modbusClient()->disconnectDevice();
        statusBar()->showMessage(QString("Disconnected to device on: %1").arg(serialSettingsDialog()->parameters().portName));
    }

    //change the button description depends on modbus state
    if(modbusClient()->state() == QModbusDevice::ConnectedState) {
        ui->btnConnectVFD->setText("Disconnect");
    } else {
        ui->btnConnectVFD->setText("Connect");
    }
}

void MainWindow::onConfigVFDClicked()
{
    if(!serialSettingsDialog()) return;
    serialSettingsDialog()->show();
}

void MainWindow::onSpeedChanged(double speed)
{
    if(!vfdDevice()) return;
    vfdDevice()->setSpeed(speed);
}

void MainWindow::onDirectionChanged(int direction)
{
    if(!vfdDevice()) return;
    vfdDevice()->setSpeed(direction);
}

void MainWindow::setVfdDevice(iVFD *vfdDevice)
{
    m_vfdDevice = vfdDevice;
}

iVFD *MainWindow::vfdDevice() const
{
    return m_vfdDevice;
}

SerialSettingsDialog *MainWindow::serialSettingsDialog() const
{
    return m_serialSettingsDialog;
}
