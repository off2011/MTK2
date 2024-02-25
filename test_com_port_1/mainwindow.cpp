#include "mainwindow.h"
#include "ui_mainwindow.h"
//
//#include <QLogValueAxis>
//#include <QLineSeries>
//#include <QValueAxis>
//#include <QChart>
//#include <QChartView>
//


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(640,480,800,600);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);

    // Инициализируем объект полотна для графика ...
       customPlot = new QCustomPlot();
       customPlot->setGeometry(320,200,640,480);
       customPlot->xAxis->setRange(0, MAX_INDEX);
       customPlot->yAxis->setRange(80, 110);
       customPlot->axisRect()->setupFullAxesBox();
       customPlot->axisRect()->setMinimumSize(300, 200);
       //ui->gridLayout->addWidget(wGraphic,1,0,1,1); // ... и устанавливаем
       //ui->verticalLayout_2->addWidget(customPlot,0,0);
       //ui->gridLayout->addWidget(customPlot,0,0); // ... и устанавливаем
       ui->verticalLayout_2->addWidget(customPlot); // ... и устанавливаем
       graphic = customPlot->addGraph();
     //  customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
       //customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
       customPlot->graph(0)->setBrush(QBrush(QColor(0, 255, 0, 50))); // first graph will be filled with translucent blue
       //customPlot->graph(0)->setBrush(QBrush(QColor(R, G, B, яркость до 255)));
    //  customPlot->graph(0)->setLineStyle(QCPGraph::lsImpulse); // График в виде импульсных тиков

    //
       // Инициализируем график и привязываем его к Осям
       //  graphic = new QCPGraph(customPlot->xAxis, customPlot->yAxis);
       //  customPlot->addPlottable(graphic);  // Устанавливаем график на полотно
       //  graphic->setName("Доход, Р");       // Устанавливаем
         graphic->setPen(QPen(QColor(Qt::green))); // Устанавливаем цвет графика
         graphic->setAntialiased(true);         // Отключаем сглаживание, по умолчанию включено
         graphic->setLineStyle(QCPGraph::lsImpulse); // График в виде импульсных тиков
       //

    // Запуск выполнения метода run будет осуществляться по сигналу запуска от соответствующего потока
    connect(&thread_1, &QThread::started, &serial, &SerialPort::run);
    // Остановка потока же будет выполняться по сигналу finished от соответствующего объекта в потоке
    connect(&serial, &SerialPort::finished, &thread_1, &QThread::terminate);
    connect(&serial, &SerialPort::dataReceived, this,&MainWindow::append_to_textEdit);
    connect(&serial, &SerialPort::connected, this, &MainWindow::connect_ok);
    connect(&serial, &SerialPort::error, this, &MainWindow::connect_error);

    // запись в файл по кнопке
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::saveToFile);

    serial.moveToThread(&thread_1);    // Передаём объекты в соответствующие потоки

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
  MainWindow::close();
}


void MainWindow::on_pushButton_2_clicked()
{
    if (ui->pushButton_2->isChecked())
    {
        ui->pushButton_2->setText("СТОП");
  //      ui->textEdit->append("Process started");
        serial.setRunning(true);
        thread_1.start();
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
    }
    else
    {
        ui->pushButton_2->setText("СТАРТ");
   //     ui->textEdit->append("Process stoped");
        serial.setRunning(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);

    }
}

void MainWindow::append_to_textEdit(QByteArray b)
{
         char *cbb;
         QString data_s;
         cbb = b.data();
         qint64 x;
         double y;
         //
         qint32 n = MAX_INDEX; // number of points in graph
         QVector<double> x_(n), y_(n);
         //

         for (unsigned int mcount=0;mcount<b.size();mcount++ )
         {
           if(l_mtk2.encode((unsigned char) cbb[mcount]))
             {
                 ui->textEdit->append(l_mtk2.get_encode_result());
                 x_[l_mtk2.count_decoded_package] =l_mtk2.count_decoded_package;
                 y_[l_mtk2.count_decoded_package] = (double) (atoi(l_mtk2.get_encode_result()) / 1000);
                 if (y_[l_mtk2.count_decoded_package]<80)
                 {
                     y_[l_mtk2.count_decoded_package]=80;
                    // graphic->setPen(QPen(QColor(Qt::red))); // Устанавливаем цвет графика
                 }
                     else
                   //  graphic->setPen(QPen(QColor(Qt::green))); // Устанавливаем цвет графика
                 {

                 }
                 qDebug()<<x_[l_mtk2.count_decoded_package];
                 qDebug()<<y_[l_mtk2.count_decoded_package];
                 b.clear();
                 //

                 //
   //              customPlot->graph(0)->setData(x_, y_);
                 //customPlot->graph(0)->addData(x_, y_);
                 graphic->addData(x_, y_);

                 customPlot->replot();
                 l_mtk2.count_decoded_package++;
             }
          }
}

void MainWindow::saveToFile()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save File", "", "Text Files (*.txt)");

           if (!filePath.isEmpty()) {
               QFile file(filePath);
               if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                   QTextStream stream(&file);
                   stream <<ui-> textEdit->toPlainText();
                   file.close();
               }
           }

}

void MainWindow::on_pushButton_4_clicked() //обмен по запросу
{
  serial.send_req();
}

void MainWindow::on_pushButton_5_clicked() // автообмен
{
    serial.send_auto();
}

//
void MainWindow::connect_ok() // коннект с портом успешный
{
   ui->textEdit->append("Порт открыт");
}

void MainWindow::connect_error(QString err_str) // ошибка порта
{
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->textEdit->append(err_str);
    ui->pushButton_2->setChecked(false);
    ui->pushButton_2->setText("СТАРТ");
    serial.setRunning(false);

}


