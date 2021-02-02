#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModbusClient>
#include <QModbusRtuSerialMaster>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QModbusClient *modbusClient() const;
    void setModbusClient(QModbusClient *modbusClient);

private:
    /*!
     * \brief Setup the Modbus connection
     */
    void onConnectVFDClicked();

private:
    Ui::MainWindow *ui;
    QModbusClient *m_modbusClient;
};
#endif // MAINWINDOW_H
