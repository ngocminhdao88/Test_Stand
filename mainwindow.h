#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModbusClient>
#include "serialsettingsdialog.h"

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

    SerialSettingsDialog *serialSettingsDialog() const;

private:
    /*!
     * \brief Open a connection to ModbusRTU device
     */
    void onConnectVFDClicked();

    /*!
     * \brief Setup parameters for the ModbusRTU connection
     */
    void onConfigVFDClicked();

    /*!
     * \brief Change VFD speed
     */
    void onSpeedChanged(double speed);

    /*!
     * \brief Change VFD direction
     */
    void onDirectionChanged(int direction);



private:
    Ui::MainWindow *ui;
    QModbusClient *m_modbusClient;
    SerialSettingsDialog *m_serialSettingsDialog;
};
#endif // MAINWINDOW_H
