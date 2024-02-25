//
#define __MINGW32__  // ====================================================== дл€ WINDOWS
//#define __linux    // ====================================================== дл€ LINUX
//#define __QNX      // ====================================================== дл€ QNX
//

#ifndef COM_PORT_H
#define COM_PORT_H
#endif // COM_PORT_H
#ifdef __MINGW32__
#include <windows.h>
#include <winnt.h>
#endif

#ifdef __linux
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>     // UNIX standard function definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions
#endif


#ifdef __QNX
#include <time.h>
#include <termios.h>    // POSIX terminal control definitions
#include <sys/neutrino.h>
#include <errno.h>
#include <ioctl.h>
#include <fcntl.h>
#endif


// с топоприв€зчика расстановка портов
/*
ttyS0 - asn0
ttyS1 - ups
ttyS2 - bs
ttyS3 - kks
ttyS4 - apd
ttyS5 - bins
ttyS6 - sov
ttys7 - asn1
*/

//определени€ имен дл€ ¬индоус
#ifdef __MINGW32__
#define port_1 "\\\\.\\COM1"
#define port_2 "\\\\.\\COM2"
#define port_3 "\\\\.\\COM3"
#define port_4 "\\\\.\\COM4"
#define port_5 "\\\\.\\COM5"
#define port_6 "\\\\.\\COM6"
#define port_7 "\\\\.\\COM7"
#define port_8 "\\\\.\\COM8"
#define port_9 "\\\\.\\COM9"
#define port_10 "\\\\.\\COM10"
#define port_11 "\\\\.\\COM11"
#define port_12 "\\\\.\\COM12"
#define port_13 "\\\\.\\COM13"
#define port_14 "\\\\.\\COM14"
#define port_15 "\\\\.\\COM15"
#define port_16 "\\\\.\\COM16"
#endif // __MINGW32__
//определени€ имен дл€ Ћинукс
#ifdef __linux
#define port_1 "/dev/ttyUSB0"
#define port_2 "/dev/ttyUSB1"
#define port_3 "/dev/ttyUSB2"
#define port_4 "/dev/ttyUSB3"
#define port_5 "/dev/ttyUSB4"
#define port_6 "/dev/ttyUSB5"
#define port_7 "/dev/ttyUSB6"
#define port_8 "/dev/ttyUSB7"
#define port_9 "/dev/ttyUSB8"
#define port_10 "/dev/ttyUSB9"
#define port_11 "/dev/ttyUSB10"
#define port_12 "/dev/ttyUSB11"
#define port_13 "/dev/ttyUSB12"
#define port_14 "/dev/ttyUSB13"
#define port_15 "/dev/ttyUSB14"
#define port_16 "/dev/ttyUSB15"
#endif
//определени€ имен дл€ QNX
#ifdef __QNX
#define port_1 "/dev/ttyS0"
//#define port_2 "/dev/ttyS1"
#define port_2 "/dev/serusb1"
#define port_3 "/dev/ttyS2"
#define port_4 "/dev/ttyS3"
#define port_5 "/dev/ttyS4"
#define port_6 "/dev/ttyS5"
#define port_7 "/dev/ttyS6"
#define port_8 "/dev/ttyS7"
#define port_9 "/dev/ttyS8"
#define port_10 "/dev/ttyS9"
#define port_11 "/dev/ttyS10"
#define port_12 "/dev/ttyS11"
#define port_13 "/dev/ttyS12"
#define port_14 "/dev/ttyS13"
#define port_15 "/dev/ttyS14"
#define port_16 "/dev/ttyS15"
#endif

#define SIZE_BUFFER (unsigned int) 4096

class Com_PORT
{
public:
    Com_PORT();
    ~Com_PORT();
    // ошибки будут отрицательные
    int open_com(unsigned char number, int BoundRate);
    int close_com();
    unsigned long read_com(unsigned int size_buffer);
    int write_com(char *buffer,unsigned char size_buffer);
    char _buffer [SIZE_BUFFER];

protected:

private:
    char port_str[100]; // строка с именем порта
    unsigned int speed; // скорость
    unsigned char PORT_NUMBER;
#ifdef __MINGW32__      // переменные дл€ порта
    HANDLE hSerial;
    DCB dcb;
    COMMTIMEOUTS commtime;
    COMSTAT ComState;
    OVERLAPPED Overlap;
    unsigned long temp;
#endif
#ifdef __linux         // переменные дл€ порта
    int fd;
    struct termios tty;
#endif
#ifdef __QNX           // переменные дл€ порта
    int fd ;
    termios tty;
#endif

};


