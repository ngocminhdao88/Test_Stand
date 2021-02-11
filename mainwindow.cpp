#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QModbusRtuSerialMaster>
#include "unicovfd.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) ,
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //TODO: how to set modbus device to this Unico VFD???
    //can i do it using the constructor???
    m_modbusRtuSettingsDialog = new ModbusRtuSettingsDialog(this);
    m_modbusClient = new QModbusRtuSerialMaster(this);
    m_vfdDevice = new UnicoVFD(this);

    //SIGNALS->SLOTS on UI
    connect(ui->btnConnectVFD, &QPushButton::clicked, this, &MainWindow::onConnectVFDClicked);
    connect(ui->btnConfigVFD, &QPushButton::clicked, this, &MainWindow::onConfigVFDClicked);
    connect(ui->sbxSpeed, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onSpeedChanged);
    connect(ui->sbxDirection, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onDirectionChanged);

    connect(ui->actionViewErrorLog, &QAction::triggered, this, &MainWindow::viewErrorLog);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_modbusClient;
    delete m_modbusRtuSettingsDialog;
    delete m_vfdDevice;
}

void MainWindow::onConnectVFDClicked()
{
    if(!m_modbusClient) return;
    if(!serialSettingsDialog()) return;

    //device is not connected yet
    if(m_modbusClient->state() != QModbusDevice::ConnectedState) {
        //setup connection parameter
        m_modbusClient->setConnectionParameter(
                    QModbusDevice::SerialPortNameParameter,
                    serialSettingsDialog()->parameters().portName);
        m_modbusClient->setConnectionParameter(
                    QModbusDevice::SerialParityParameter,
                    serialSettingsDialog()->parameters().parity);
        m_modbusClient->setConnectionParameter(
                    QModbusDevice::SerialBaudRateParameter,
                    serialSettingsDialog()->parameters().baud);
        m_modbusClient->setConnectionParameter(
                    QModbusDevice::SerialDataBitsParameter,
                    ModbusRtuSettingsDialog().parameters().databits);
        m_modbusClient->setConnectionParameter(
                    QModbusDevice::SerialStopBitsParameter,
                    serialSettingsDialog()->parameters().stopbits);
        m_modbusClient->setTimeout(serialSettingsDialog()->parameters().timeout);
        m_modbusClient->setNumberOfRetries(serialSettingsDialog()->parameters().retry);

        //try to connect to the modbus device
        if(m_modbusClient->connectDevice()) {
            statusBar()->showMessage(QString("Connected to device on: %1").arg(serialSettingsDialog()->parameters().portName));
        } else {
            statusBar()->showMessage(
                        QString("Connection failed: %1, %2").arg(QString::number(m_modbusClient->error()), m_modbusClient->errorString()));
        }
    } else { //device is already connected
        //stop the VFD first

        m_modbusClient->disconnectDevice();
        statusBar()->showMessage(QString("Disconnected to device on: %1").arg(serialSettingsDialog()->parameters().portName));
    }

    //change the button description depends on modbus state
    if(m_modbusClient->state() == QModbusDevice::ConnectedState) {
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
    //set the motor speed
}

void MainWindow::onDirectionChanged(int direction)
{
    //set the motor turn direction
}

void MainWindow::viewErrorLog()
{
    QFile errorLog("error.log");
    if(!errorLog.exists()) return;

    QDesktopServices::openUrl(QUrl("error.log"));
}

ModbusRtuSettingsDialog *MainWindow::serialSettingsDialog() const
{
    return m_modbusRtuSettingsDialog;
}
