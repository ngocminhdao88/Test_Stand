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
    m_vfdDevice = new UnicoVFD(this);
    m_vfdDevice->initDevice();

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
    delete m_vfdDevice;
}

void MainWindow::onConnectVFDClicked()
{
    if(!m_vfdDevice) return;


    if(m_vfdDevice->state() != iVFD::ConnectedState) {
        if(m_vfdDevice->connectDevice()) {
            ui->btnConnectVFD->setText("Disconnect");
        } else {
            ui->btnConnectVFD->setText("Connect");
        }
    } else {
        ui->btnConnectVFD->setText("Connect");
        m_vfdDevice->disconnectDevice();
    }
}

void MainWindow::onConfigVFDClicked()
{
    if(!m_vfdDevice) return;
    m_vfdDevice->configDevice();
}

void MainWindow::onSpeedChanged(double speed)
{
    if(!m_vfdDevice) return;
    m_vfdDevice->setSpeed(speed);
}

void MainWindow::onDirectionChanged(int direction)
{
    if(!m_vfdDevice) return;
    m_vfdDevice->setDirection(direction);
}

void MainWindow::viewErrorLog()
{
    QFile errorLog("error.log");
    if(!errorLog.exists()) return;

    QDesktopServices::openUrl(QUrl("error.log"));
}
