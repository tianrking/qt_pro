#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QStringList serialNamePort;
    ui->setupUi(this);

    this->setWindowTitle("w0x7ce_title");

    serialPort = new QSerialPort(this);

    foreach (const QSerialPortInfo &inf0, QSerialPortInfo::availablePorts()) {

        serialNamePort<<inf0.portName();

    }

    ui->serial_comboBox->addItems(serialNamePort);
}

MainWindow::~MainWindow()
{
    delete ui;

}


//void MainWindow::on_pushButton_clicked()


void MainWindow::on_pushButton_clicked()
{
    serialPort->setPortName(ui->serial_comboBox->currentText());
    serialPort->setBaudRate(ui->band_rate_comboBox->currentIndex());
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setParity(QSerialPort::NoParity);

    if(true ==  serialPort ->open(QIODevice::ReadWrite)){
        QMessageBox::information(this,"Warning","Success");
    }
    else{
        QMessageBox::information(this,"Warning","Fail");
    }
    qDebug()<< "A";
}

