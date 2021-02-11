#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModbusClient>
#include <QDesktopServices>
#include <QUrl>
#include <QFile>
#include "modbusrtusettingsdialog.h"
#include "interfaces/ivfd.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ModbusRtuSettingsDialog *serialSettingsDialog() const;

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

    /*!
     * \brief Open error log
     */
    void viewErrorLog();


private:
    Ui::MainWindow *ui = 0;
    QModbusClient *m_modbusClient = 0;
    ModbusRtuSettingsDialog *m_modbusRtuSettingsDialog = 0;
    iVFD *m_vfdDevice = 0;
};
#endif // MAINWINDOW_H
