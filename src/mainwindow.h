#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSerialPortInfo>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include <QMediaPlayer>
#include <QVideoWidget>
//#include <QMediaPlaylist>

#include <QMainWindow>                 //主文件头文件
#include <QSerialPort>                 //串口头文件
#include <QScatterSeries>              //画点状曲线头文件
#include <QtCharts/QLineSeries>        //画线曲线头文件
#include <QtCharts/QValueAxis>         //画坐标轴头文件
#include <QtCharts/QChartView>         //画绘图区域头文件
#include <QtCore/QTimer>               //时间定时器头文件
#include <QtWidgets/QGesture>          //手势头文件（鼠标动作）
#include <QtWidgets/QGraphicsScene>    //绘图屏幕参数头文件
#include <QtWidgets/QGraphicsView>     //绘图区域显示头文件
#include <QtGui/QMouseEvent>           //鼠标动作时间头文件（产生槽函数）

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
    void setVideo();

private:

    Ui::MainWindow *ui;

    QSerialPort *serialPort;

    QMediaPlayer *player;
    QVideoWidget *videoWidget;

    //绘图定义变量 Start
    QChartView *chartView_Vs;
    QChart *chart_Vs;
    QLineSeries *m_series_line_Vsua;
    QLineSeries *m_series_line_Vsub;
    QLineSeries *m_series_line_Vsuc;
    QScatterSeries *m_series_point_Vsua;
    QScatterSeries *m_series_point_Vsub;
    QScatterSeries *m_series_point_Vsuc;
    QValueAxis *m_axisX_Vs;
    QValueAxis *m_axisY_Vs;
    //绘图定义变量 End

};
#endif // MAINWINDOW_H
