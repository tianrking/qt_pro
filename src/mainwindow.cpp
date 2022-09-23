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
//#include <QMediaPlaylist>

#include <QSerialPort>
#include <QtSerialPort/QSerialPortInfo>    //端口号索引（用在串口号接收上）
#include <QList>                     //链表（用在串口号接收上）
#include <QtWidgets/QLabel>          //标签
#include <QtCharts/QChartView>       //图表
#include <QtWidgets/QPushButton>     //按钮
#include <QtWidgets/QApplication>    //
#include <QtWidgets/QPlainTextEdit>  //留言板
#include <QtCharts>    //画图
#include <QtCharts/QScatterSeries>   //点
#include <QtCharts/QLineSeries>      //线
#include <QtCharts/QValueAxis>       //坐标系
#include <QResizeEvent>              //绘图区域大小变化事件
#include <QDebug>                    //打印参数头文件，最好加上，最好用上，很方便


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

// QT5 block
//    player->setMedia(QUrl::fromLocalFile("/home/w0x7ce/Downloads/videoplayback.mp4"));
//    videoWidget->show();
//    player->play();
// NOW is QT 6

    ui->verticalLayout->addWidget(videoWidget);

    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(startVideo()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(pauseVideo()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(setVideo()));

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

    //设置串口数据位
    switch(ui->comboBox_Data_Bits->currentIndex())
    {
        case 8: serialPort->setDataBits(QSerialPort::Data8); break;
        default: break;
    }


    //校验位
    switch(ui->comboBox_Parity->currentIndex())
    {
        case 0: serialPort->setParity(QSerialPort::NoParity); break;
        default: break;
    }

    //停止位
    switch(ui->comboBox_Stop_Bits->currentIndex())
    {
        case 1: serialPort->setStopBits(QSerialPort::OneStop); break;
        case 2: serialPort->setStopBits(QSerialPort::TwoStop); break;
        default: break;
    }

//    //设置流控制
//    serial.setFlowControl(QSerialPort::NoFlowControl);

//    //打开串口
//    if(!serial.open(QIODevice::ReadWrite))
//    {
//        QMessageBox::about(NULL, "提示", "无法打开串口！");
//        return;
//    }


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
    serialPort->write("Off\n");
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
//    player->setMedia(QUrl::fromLocalFile("/home/w0x7ce/Downloads/videoplayback.mp4"));
//    player->setVideoOutput(QUrl::fromEncoded("https://cdn2.jin10.com/dc/media/mp4/dc_video.mp4"));
    player->setSource(QUrl::fromEncoded("https://cdn2.jin10.com/dc/media/mp4/dc_video.mp4"));
//    videoWidget->show();
    player->play();
    qDebug()<< "start Video";
}

void MainWindow::pauseVideo()
{
    player->pause();
    qDebug()<< "pause Video";
}


void MainWindow::closeVideo()
{
    player->stop();
    qDebug()<< "close Video";
}

void MainWindow::setVideo()
{
    int kk = ui->horizontalSlider->value();
    player->setPosition(kk*1000);
    qDebug()<< "set Video" << kk ;
}

