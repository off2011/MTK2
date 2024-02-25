#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QThread>
#include <QMainWindow>
#include <qstring.h>
  #include "mtk2.h"
#include "addons.h"

#include <QLogValueAxis>
#include <QLineSeries>
#include <QValueAxis>
#include <QChart>
#include <QChartView>

#include <qcustomplot.h>

#define MAX_INDEX (qint32) 400


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    mtk2 l_mtk2;


private slots:

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    //void append_to_textEdit(char b);
    void append_to_textEdit(QByteArray b);
    void saveToFile();
    //void send_request();
    //void send_auto_exchange();

    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

    void connect_ok();   // соединение успешно
    void connect_error(QString err_str);// ошибка соединения с портом


private:
    Ui::MainWindow *ui;
    QThread thread_1;       //  поток чтения из ком порта
    SerialPort serial;      // компорт

    QCustomPlot *customPlot;    // Объявляем графическое полотно
        QCPGraph *graphic;          // Объявляем график

};

#endif // MAINWINDOW_H
