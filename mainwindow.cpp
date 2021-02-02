#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setModbusClient(new QModbusRtuSerialMaster(this));

    if(modbusClient()) {
        //change the state of modbus device
    } else {
        //error when creating a modbus device
        //disable the connection button
        //show error message
    }

    //SIGNALS->SLOTS on UI
    connect(ui->btnConnectVFD, &QPushButton::clicked, this, &MainWindow::onConnectVFDClicked);
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

    //device is not connected yet
    if(modbusClient()->state() != QModbusDevice::ConnectedState) {
        //setup connection parameter
        modbusClient()->setConnectionParameter(
                    QModbusDevice::SerialPortNameParameter,
                    "COM3");
        modbusClient()->setConnectionParameter(
                    QModbusDevice::SerialParityParameter,
                    0);
        modbusClient()->setConnectionParameter(
                    QModbusDevice::SerialBaudRateParameter,
                    9600);
        modbusClient()->setConnectionParameter(
                    QModbusDevice::SerialDataBitsParameter,
                    8);
        modbusClient()->setConnectionParameter(
                    QModbusDevice::SerialStopBitsParameter,
                    0);
        //modbusClient()->setTimeout(10);
        //modbusClient()->setNumberOfRetries(3);

        //try to connect to the modbus device
        if(modbusClient()->connectDevice()) {
            statusBar()->showMessage("Connected to device on: ");
        } else {
            statusBar()->showMessage(
                        QString("Connection failed: %1, %2").arg(QString::number(modbusClient()->error()), modbusClient()->errorString()));
        }
    } else { //device is already connected
        //stop the VFD first

        modbusClient()->disconnectDevice();
        statusBar()->showMessage("Disconnected to device on: ");
    }

    //change the button description depends on modbus state
    if(modbusClient()->state() == QModbusDevice::ConnectedState) {
        ui->btnConnectVFD->setText("Disconnect");
    } else {
        ui->btnConnectVFD->setText("Connect");
    }
}
