#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include <QWebSocket>

#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaPlaylist>

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

    player = new QMediaPlayer;
    videoWidget = new QVideoWidget;
    player->setVideoOutput(videoWidget);
    player->setMedia(QUrl::fromLocalFile("/home/w0x7ce/Downloads/videoplayback.mp4"));
//    videoWidget->show();

//    player->play();
    ui->verticalLayout->addWidget(videoWidget);
    player->setVideoOutput(videoWidget);

    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(startVideo()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(pauseVideo()));

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
    qDebug()<< serialPort->baudRate() << " " << serialPort->portName() ;
}


void MainWindow::on_pushButton_2_clicked()
{
    serialPort->close();
    qDebug()<< "Close";
}


void MainWindow::on_pushButton_3_clicked()  //on
{
    serialPort->write("On\n");
    qDebug()<< "On";
}


void MainWindow::on_pushButton_4_clicked()  //off
{
    serialPort->write("On\n");
    qDebug()<< "Off";
}

// POST

void MainWindow::requestFinished(QNetworkReply* reply) {
    // 获取http状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid())
        qDebug() << "status code=" << statusCode.toInt();

    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    if(reason.isValid())
        qDebug() << "reason=" << reason.toString();

    QNetworkReply::NetworkError err = reply->error();
    if(err != QNetworkReply::NoError) {
        qDebug() << "Failed: " << reply->errorString();
        QMessageBox::information(this,"",reply->errorString());
    }
    else {
        // 获取返回内容
        qDebug() << reply->readAll();
        QMessageBox::information(this,"",reply->readAll());
    }


}

void MainWindow::on_pushButton_5_clicked()
{
    QNetworkRequest request;
    QNetworkAccessManager* naManager = new QNetworkAccessManager(this);
    QMetaObject::Connection connRet = QObject::connect(naManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    Q_ASSERT(connRet);


    request.setUrl(QUrl("http://www.baidu.com"));


    //get
    QNetworkReply* reply_get = naManager->get(request);

    //post
//    QString testData = "test";
//    request.setHeader(request.ContentTypeHeader, "some/type" );
//    request.setRawHeader("a","a");
//    QNetworkReply* reply_post = naManager->post(request, testData.toUtf8());

}



void MainWindow::startVideo()
{
    player->setMedia(QUrl::fromLocalFile("/home/w0x7ce/Downloads/videoplayback.mp4"));
    videoWidget->show();
    player->play();
}

void MainWindow::pauseVideo()
{
    player->pause();
}

void MainWindow::closeVideo()
{
    player->stop();
}


