#include <QDateTime>
#include <QtEndian>
#include <QLayout>

#include "MainWindow.h"
#include "ui_MainWindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(size());
    setWindowTitle("demo-cube-payment v1.1.0");
    ui->lineEditAddress->setText(QSettings().value("address", "127.0.0.1").toString());
    ui->spinBoxPort->setValue(QSettings().value("port", 4455).toInt());
    ui->tabWidget->setCurrentIndex(QSettings().value("tab_index", 0).toInt());
    statusBar()->showMessage("Ready");
    connect(&socket, &QTcpSocket::stateChanged, this, [this]() {
        QPalette palette = ui->labelConnected->palette();
        switch (socket.state()) {
        case QTcpSocket::ConnectedState:
            ui->labelConnected->setText("Connected");
            statusBar()->showMessage("Connected");
            palette.setColor(ui->labelConnected->foregroundRole(), Qt::darkGreen);
            break;
        case QTcpSocket::UnconnectedState:
            ui->labelConnected->setText("Disconnected");
            palette.setColor(ui->labelConnected->foregroundRole(), Qt::red);
            if (ui->checkBoxAutoReconnect->isChecked())
                on_pushButtonConnect_clicked();
            break;
        default:
            ui->labelConnected->setText(QVariant::fromValue(socket.state()).toString());
            palette.setColor(ui->labelConnected->foregroundRole(), Qt::darkYellow);
            break;
        }
        ui->labelConnected->setPalette(palette);
    });
#if QT_VERSION < QT_VERSION_CHECK(5, 15, 0)
    connect(&socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this,
        [this]() {
            statusBar()->showMessage("Error: " + socket.errorString());
        });
#else
    connect(&socket, &QTcpSocket::errorOccurred, this,
        [this]() {
            statusBar()->showMessage("Error: " + socket.errorString());
        });
#endif
    connect(&socket, &QTcpSocket::readyRead, this, [this]() {
        if (socket.bytesAvailable() < 4)
            return ;
        quint32 length;
        socket.peek(reinterpret_cast<char *>(&length), 4);
        length = qFromBigEndian<quint32>(length);
        if (socket.bytesAvailable() < 4 + length)
            return ;
        socket.read(4);
        QByteArray data = socket.read(length);
        qDebug("received %d bytes", length);
        statusBar()->showMessage("Received " + QString::number(length) + " bytes");
        ui->textEditOutput->append(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.z"));
        ui->textEditOutput->append(data);
        emit socket.readyRead();
    }, Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    socket.disconnectFromHost();
    delete ui;
}

void MainWindow::on_pushButtonSend_clicked()
{
    if (socket.state() != QTcpSocket::ConnectedState) {
        statusBar()->showMessage("Need to connect first");
        return;
    }
    QString str = ui->textEditInput->toPlainText();
    if (str.isEmpty()) {
        statusBar()->showMessage("Message is empty");
        return;
    }
    QByteArray data = ui->textEditInput->toPlainText().toLocal8Bit();
    quint32 sz = qToBigEndian<quint32>(data.size());
    socket.write(reinterpret_cast<char *>(&sz), 4);
    socket.write(data);
    statusBar()->showMessage("Sended " + QString::number(data.size()) + " bytes");
    qDebug("sended %d bytes", data.size());
}

void MainWindow::on_lineEditAddress_textChanged(const QString &arg1)
{
    QSettings().setValue("address", arg1);
}

void MainWindow::on_pushButtonConnect_clicked()
{
    socket.disconnectFromHost();
    uint16_t port = static_cast<uint16_t>(ui->spinBoxPort->value());
    socket.connectToHost(ui->lineEditAddress->text(), port);
    statusBar()->showMessage("Connecting");
}

void MainWindow::on_spinBoxPort_valueChanged(int arg1)
{
    QSettings().setValue("port", arg1);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    int new_port = ui->spinBoxPort->value();

    switch (index) {
    case 0:
        new_port = 4455;
        break ;
    case 1:
        new_port = 4444;
        break ;
    case 2:
        new_port = 4433;
        break ;
    }
    ui->spinBoxPort->setValue(new_port);
    QSettings().setValue("port", new_port);
    QSettings().setValue("tab_index", index);
}

void MainWindow::on_pushButtonUpdateconfiguration_clicked()
{
    ui->textEditInput->setText(
        "{\n"
        "    \"command\": \"updateconfiguration\"\n"
        "}\n"
        );
}

void MainWindow::on_pushButtonTestConnection_clicked()
{
    ui->textEditInput->setText(
        "{\n"
        "    \"command\": \"testconnection\"\n"
        "}\n"
        );
}

void MainWindow::on_pushButtonGetParameters_clicked()
{
    ui->textEditInput->setText(
        "{\n"
        "    \"command\": \"getparameters\"\n"
        "}\n"
        );
    
}

void MainWindow::on_pushButtonTransaction_clicked()
{
    QString type = ui->comboBoxTransactionType->currentText();
    if (type == "purchase") {
        ui->textEditInput->setText(
            "{\n"
            "    \"command\": \"transaction\",\n"
            "    \"type\": \"purchase\",\n"
            "    \"currency\": 643,\n"
            "    \"amount\": 123.00\n"
            "}\n"
            );
    } else if (type == "refund") {
        ui->textEditInput->setText(
            "{\n"
            "    \"command\": \"transaction\",\n"
            "    \"type\": \"refund\",\n"
            "    \"amount\": 123.00,\n"
            "    \"rrn\": \"INSERT_RRN\"\n"
            "}\n"
            );
    } else if (type == "purchase-with-cashback") {
        ui->textEditInput->setText(
            "{\n"
            "    \"command\": \"transaction\",\n"
            "    \"type\": \"purchase-with-cashback\",\n"
            "    \"amount\": 123.00,\n"
            "    \"amount-other\": \"000000000100\"\n"
            "}\n"
            );
    } else if (type == "void") {
        ui->textEditInput->setText(
            "{\n"
            "    \"command\": \"transaction\",\n"
            "    \"type\": \"void\",\n"
            "    \"number\": \"000008\",\n"
            "    \"amount\": \"1.00\"\n"
            "}\n"
            );
    }
    
}

void MainWindow::on_pushButtonCancelTransaction_clicked()
{
    ui->textEditInput->setText(
        "{\n"
        "    \"keep-alive-status\": \"cancelled\"\n"
        "}\n"
        );
}

void MainWindow::on_pushButtonReport_clicked()
{
    ui->textEditInput->setText(
        "{\n"
        "    \"command\": \"report\",\n"
        "    \"report-type\": \"brief\"\n"
        "}\n"
        );
}

void MainWindow::on_pushButtonLoadworkkeys_clicked()
{
    ui->textEditInput->setText(
        "{\n"
        "    \"command\": \"loadworkkey\"\n"
        "}\n"
        );
}

void MainWindow::on_pushButtonLoadmasterkeys_clicked()
{
    ui->textEditInput->setText(
        "{\n"
        "    \"command\": \"loadmasterkey\"\n"
        "}\n"
        );
}


void MainWindow::on_pushButtonReportFull_clicked()
{
    ui->textEditInput->setText(
        "{\n"
        "    \"command\": \"report\",\n"
        "    \"report-type\": \"full\"\n"
        "}\n"
        );
}

void MainWindow::on_pushButtonSettlement_clicked()
{
    ui->textEditInput->setText(
        "{\n"
        "    \"command\": \"settlement\"\n"
        "}\n"
        );
}

void MainWindow::on_pushButtonClear_clicked()
{
    ui->textEditInput->setText(
        "{\n"
        "    \"command\": \"clear\"\n"
        "}\n"
        );
}

void MainWindow::on_pushButtonRunreset_clicked()
{
    ui->textEditInput->setText(
        "{\n"
        "    \"command\": \"runreset\"\n"
        "}\n"
        );
}

void MainWindow::on_pushButtonClearOutput_clicked()
{
    ui->textEditOutput->clear();
}

void MainWindow::on_pushButtonJpayLogin_clicked()
{
    ui->textEditInput->setText(
        "<login>\n"
        "    <password>" + ui->lineEditJpayPassword->text() + "</password>\n"
        "</login>\n"
        );
}

void MainWindow::on_pushButtonJpayLogout_clicked()
{
    ui->textEditInput->setText(
        "<logout>\n"
        "    <token>" + ui->lineEditJpayToken->text() + "</token>\n"
        "</logout>\n"
        );
}

void MainWindow::on_pushButtonJpayChangepassword_clicked()
{
    ui->textEditInput->setText(
        "<changepassword>\n"
        "    <token>" + ui->lineEditJpayToken->text() + "</token>\n"
        "    <password>" + ui->lineEditJpayPassword->text() + "</password>\n"
        "    <newpassword> </newpassword>\n"
        "</changepassword>\n"
        );
}

void MainWindow::on_pushButtonJpayUpdateconfiguration_clicked()
{
    ui->textEditInput->setText(
        "<updateconfiguration>\n"
        "    <token>" + ui->lineEditJpayToken->text() + "</token>\n"
        "</updateconfiguration>\n"
        );
}

void MainWindow::on_pushButtonJpayLoadmasterkeys_clicked()
{
    ui->textEditInput->setText(
        "<loadmasterkeys>\n"
        "    <token>" + ui->lineEditJpayToken->text() + "</token>\n"
        "</loadmasterkeys>\n"
        );
}

void MainWindow::on_pushButtonJpayLoadworkkeys_clicked()
{
    ui->textEditInput->setText(
        "<loadworkkeys>\n"
        "    <token>" + ui->lineEditJpayToken->text() + "</token>\n"
        "</loadworkkeys>\n"
        );
}

void MainWindow::on_pushButtonJpayTestConnection_clicked()
{
    ui->textEditInput->setText(
        "<testconnection>\n"
        "    <token>" + ui->lineEditJpayToken->text() + "</token>\n"
        "</testconnection>\n"
        );
}

void MainWindow::on_pushButtonJpayGetParameters_clicked()
{
    ui->textEditInput->setText(
        "<getparameters>\n"
        "    <token>" + ui->lineEditJpayToken->text() + "</token>\n"
        "</getparameters>\n"
        );
}

void MainWindow::on_pushButtonJpayTransaction_clicked()
{
    ui->textEditInput->setText(
        "<transaction>\n"
        "    <type>purchase</type>\n"
        "    <currency>643</currency>\n"
        "    <amount>000000012300</amount>\n"
        "</transaction>\n"
        );
}

void MainWindow::on_pushButtonJpayKeepalive_clicked()
{
    ui->textEditInput->setText(
        "<keepalive>\n"
        "    <status>ok</status>\n"
        "</keepalive>\n"
        );
}

void MainWindow::on_pushButtonJpayDisplay_clicked()
{
    ui->textEditInput->setText(
        "<display>\n"
        "    <status>ok</status>\n"
        "</display>\n"
        );

}

void MainWindow::on_pushButtonJpayReport_clicked()
{
    ui->textEditInput->setText(
        "<report>\n"
        "    <password>" + ui->lineEditJpayPassword->text() + "</password>\n"
        "    <report-type>brief</report-type>\n"
        "</report>\n"
        );
}

void MainWindow::on_pushButtonJpaySettlement_clicked()
{
    ui->textEditInput->setText(
        "<settlement>\n"
        "    <password>" + ui->lineEditJpayPassword->text() + "</password>\n"
        "</settlement>\n"
        );
}

void MainWindow::on_pushButtonJpayClear_clicked()
{
    ui->textEditInput->setText(
        "<clear>\n"
        "    <password>" + ui->lineEditJpayPassword->text() + "</password>\n"
        "</clear>\n"
        );
}

void MainWindow::on_pushButtonJpayResetpassword_clicked()
{
    ui->textEditInput->setText(
        "<resetpassword/>\n"
        );
}

void MainWindow::on_pushButtonJpayDirectpayment_clicked()
{
    ui->textEditInput->setText(
        "<directpayment>\n"
        "    <trd></trd>\n"
        "</directpayment>\n"
        );
}

void MainWindow::on_pushJpayButtonRunreset_clicked()
{
    ui->textEditInput->setText(
        "<runreset>\n"
        "    <token>" + ui->lineEditJpayToken->text() + "</token>\n"
        "</runreset>\n"
        );
}


