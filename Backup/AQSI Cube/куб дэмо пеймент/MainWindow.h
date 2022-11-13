#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QTcpSocket>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    void on_pushButtonSend_clicked();
    
    void on_lineEditAddress_textChanged(const QString &arg1);
    
    void on_pushButtonConnect_clicked();
    
    void on_spinBoxPort_valueChanged(int arg1);
    
    void on_pushButtonTestConnection_clicked();
    
    void on_pushButtonGetParameters_clicked();
    
    void on_pushButtonTransaction_clicked();
    
    void on_pushButtonCancelTransaction_clicked();
    
    void on_pushButtonReport_clicked();
    
    void on_pushButtonUpdateconfiguration_clicked();

    void on_pushButtonLoadworkkeys_clicked();

    void on_pushButtonLoadmasterkeys_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButtonReportFull_clicked();

    void on_pushButtonSettlement_clicked();

    void on_pushButtonClear_clicked();

    void on_pushButtonRunreset_clicked();

    void on_pushButtonClearOutput_clicked();

    void on_pushButtonJpayLogin_clicked();

    void on_pushButtonJpayLogout_clicked();

    void on_pushButtonJpayChangepassword_clicked();

    void on_pushButtonJpayUpdateconfiguration_clicked();

    void on_pushButtonJpayLoadmasterkeys_clicked();

    void on_pushButtonJpayLoadworkkeys_clicked();

    void on_pushButtonJpayTestConnection_clicked();

    void on_pushButtonJpayGetParameters_clicked();

    void on_pushButtonJpayTransaction_clicked();

    void on_pushButtonJpayReport_clicked();

    void on_pushButtonJpaySettlement_clicked();

    void on_pushButtonJpayClear_clicked();

    void on_pushButtonJpayResetpassword_clicked();

    void on_pushButtonJpayDirectpayment_clicked();

    void on_pushJpayButtonRunreset_clicked();

    void on_pushButtonJpayKeepalive_clicked();

    void on_pushButtonJpayDisplay_clicked();

private:
    QTimer timer;
    QTcpSocket socket;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
