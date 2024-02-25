#ifndef ADDONS_H
#define ADDONS_H
#include <QSerialPort>
#include <QtCore/QThread>
#include <QObject>


class SerialPort :public QSerialPort
{Q_OBJECT
    // Свойство, управляющее работой потока
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    //bool m_running=false;

public:
    SerialPort(QObject *parent = 0);
//    mtk2 l_mtk2;
    bool running() const; // +
    char data;
    qint64 NumRead;
    QString message() const;
    QByteArray bb ;
    char* cbb ;
    bool m_running=true;
    bool is_send_auto;
    bool is_send_reg;

signals:
    void runningChanged(bool running); // +
    void finished(); // +
    void connected(); // +
    void dataReceived(const QByteArray &data);
    void error(const QString &errorString); // +
public slots:
    void run();// +
    void setRunning(bool running); // +
    void send_req();     // послать в прибор команду обмена по запросу
    void send_auto();    // послать в прибор команду автообмена

};

#endif // ADDONS_H
