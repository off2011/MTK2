#include "addons.h"

SerialPort::SerialPort(QObject *parent):
    QSerialPort(parent)
{
    m_running=false;
    is_send_auto = false;
    is_send_reg = false;
/*
    setPortName("\\\\.\\COM1");
    setBaudRate(100);
    setDataBits(QSerialPort::Data5);
    setParity(QSerialPort::NoParity);
    setStopBits(QSerialPort::TwoStop);
    setFlowControl(QSerialPort::NoFlowControl);
    if (open(QIODevice::ReadWrite)) {
      //  emit connected();
        qDebug("PORT OPEN");
    } else {
        qDebug("ERROR PORT OPEN");
        // Handle error opening the serial port
     //   emit error(errorString());
    }
*/
}

bool SerialPort::running() const
{
    return SerialPort::m_running;
}

void SerialPort::setRunning(bool running)
{
    if (m_running == running)
        return;

    m_running = running;
    emit runningChanged(running);
}

// Самый важный метод, в котором будет выполняться "полезная" работа объекта
void SerialPort::run()
{

    setPortName("\\\\.\\COM1");
    setBaudRate(100);
    setDataBits(QSerialPort::Data5);
    setParity(QSerialPort::NoParity);
    setStopBits(QSerialPort::TwoStop);
    setFlowControl(QSerialPort::NoFlowControl);
    if (open(QIODevice::ReadWrite)) {
        emit connected();
        qDebug("PORT OPEN");
    } else {
        qDebug("ERROR PORT OPEN");
        setRunning(false);
        // Handle error opening the serial port
        emit error(errorString());
    }

    while (m_running)
    {
       waitForReadyRead(10);
       bb = readAll();
       if(bb.size()>0)
       {
           emit dataReceived(bb);
           //qDebug("%s RUNNING");
           bb.clear();
       }
       else
       {

       }
       // посылка команд на прибор
       if(is_send_reg)
       {
           QByteArray data = "\x1F\x1B\x16\x17\x2\x8";
           write(data,6);
           qDebug("send_req()");
           is_send_reg = false;
       }
       if(is_send_auto)
       {
           QByteArray data = "\x1F\x1B\x16\x13\x2\x8";;
           write(data,6);
           qDebug("send_auto()");
           is_send_auto = false;
       }
       //
    }
    close(); // Закрытие порта
    emit finished();
}

void SerialPort::send_req()
{
    SerialPort::is_send_reg = true;
}
void SerialPort::send_auto()
{
    SerialPort::is_send_auto = true;
}

