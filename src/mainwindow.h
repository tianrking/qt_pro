#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaPlaylist>

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void requestFinished(QNetworkReply* reply);

//    void on_pushButton_6_clicked();

    void startVideo();
    void pauseVideo();
    void closeVideo();

private:
    Ui::MainWindow *ui;

    QSerialPort *serialPort;

    QMediaPlayer *player;
    QVideoWidget *videoWidget;

};
#endif // MAINWINDOW_H
