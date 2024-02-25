
//
#define __MINGW32__  // ====================================================== дл€ WINDOWS
//#define __linux    // ====================================================== дл€ LINUX
//#define __QNX      // ====================================================== дл€ QNX
//

using namespace std;


#include "Com_PORT.h"
#include <stdio.h>
#include <iostream>

#ifdef __QNX
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <sys/neutrino.h>
#include <time.h>
#include <errno.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>   /* ќбъ€влени€ управлени€ файлами */
#endif

Com_PORT::Com_PORT()
{
    port_str[0] = 0;
#ifdef __QNX
    fd = -1;
#endif
}

Com_PORT::~Com_PORT()
{
    //dtor
}

int Com_PORT::open_com(unsigned char number, int BoundRate)
{
    PORT_NUMBER = number;
    speed = BoundRate;

    switch(number)
    {
    case  1:
        memcpy(&port_str,port_1,sizeof(port_1));
        break;
    case  2:
        memcpy(&port_str,port_2,sizeof(port_2));
        break;
    case  3:
        memcpy(&port_str,port_3,sizeof(port_3));
        break;
    case  4:
        memcpy(&port_str,port_4,sizeof(port_4));
        break;
    case  5:
        memcpy(&port_str,port_5,sizeof(port_5));
        break;
    case  6:
        memcpy(&port_str,port_6,sizeof(port_6));
        break;
    case  7:
        memcpy(&port_str,port_7,sizeof(port_7));
        break;
    case  8:
        memcpy(&port_str,port_8,sizeof(port_8));
        break;
    case  9:
        memcpy(&port_str,port_9,sizeof(port_9));
        break;
    case  10:
        memcpy(&port_str,port_10,sizeof(port_10));
        break;
    case  11:
        memcpy(&port_str,port_11,sizeof(port_11));
        break;
    case  12:
        memcpy(&port_str,port_12,sizeof(port_12));
        break;
    case  13:
        memcpy(&port_str,port_13,sizeof(port_13));
        break;
    case  14:
        memcpy(&port_str,port_14,sizeof(port_14));
        break;
    case  15:
        memcpy(&port_str,port_15,sizeof(port_15));
        break;
    case  16:
        memcpy(&port_str,port_16,sizeof(port_16));
        break;
    default:
        break;
    }
#ifdef __MINGW32__
    hSerial = CreateFileA(port_str,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,1,NULL);
    if (hSerial == INVALID_HANDLE_VALUE)
    {
        // printf("Error opening port\r\n");
        return -1;//ошибка открыти€ порта
    }
    PurgeComm(hSerial,PURGE_TXABORT||PURGE_RXABORT||PURGE_TXCLEAR||PURGE_RXCLEAR);
    GetCommState(hSerial,&dcb);
    //  dcb.BaudRate = CBR_9600;
    //  dcb.BaudRate = CBR_115200;
    dcb.BaudRate = speed;
    dcb.fBinary = TRUE;
    dcb.fOutxCtsFlow = FALSE;
    dcb.fOutxDsrFlow = FALSE;
    dcb.fDtrControl = DTR_CONTROL_HANDSHAKE;
    dcb.fDsrSensitivity = FALSE;
    dcb.fNull = FALSE;
    dcb.fRtsControl = RTS_CONTROL_DISABLE;
    dcb.fAbortOnError = FALSE;
    dcb.ByteSize = 5;
    dcb.Parity = NOPARITY;
    dcb.StopBits = 2;
    if (!SetCommState(hSerial, &dcb))
    {
        cout << "error setting serial port state\n";
    };
    commtime.ReadIntervalTimeout= 10;
    commtime.ReadTotalTimeoutMultiplier = 1;
// значений этих тайм Ц аутов вполне хватает дл€ уверенного приема
// даже на скорости 110 бод
    commtime.ReadTotalTimeoutConstant = 100;
// используетс€ в данном случае как врем€ ожидани€ посылки
    commtime.WriteTotalTimeoutMultiplier = 0;
    commtime.WriteTotalTimeoutConstant = 0;
    SetCommTimeouts(hSerial, &commtime);
#endif // __MINGW32__
#ifdef __linux
    fd = open(port_str,O_RDWR);
    if (fd == -1)
    {
        //printf("Error opening port - ");
        return -1;
    }
    //memset (&tty, 0, sizeof tty);
    /* Flush Port, then applies attributes */
    tcflush( fd, TCIFLUSH );
    if ( tcgetattr ( fd, &tty ) != 0 )
    {
        printf("Error from tcgetattr: ");
//        return -2;
    }
    cfmakeraw(&tty);
    // Set Baud Rate
    //cfsetospeed (&tty, (speed_t)B9600);
    cfsetospeed (&tty, (speed_t)speed);
    cfsetispeed (&tty, (speed_t)speed);
    // Setting other Port Stuff
    tty.c_cflag     &=  ~PARENB;            // Make 8n1
    tty.c_cflag     &=  ~CSTOPB;
    tty.c_cflag     &=  ~CSIZE;
    tty.c_cflag     |=  CS8;
    tty.c_cflag     &=  ~CRTSCTS;           // no flow control
    tty.c_cc[VMIN]   =  1;                  // read doesn't block
    tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout в марсе =1
    tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines
    if ( tcsetattr ( fd, TCSANOW, &tty ) != 0)
    {
        //printf("Error from tcsetattr :\n");
        return -1;
    }
#endif // __linux

#ifdef __QNX
    //std::cout << "open port" << std::endl;
    fd = open(port_str,O_RDWR);
    if (fd == -1)
    {
        std::cout << strerror(errno)<< std::endl ;
        return -1;
    }
//    memset (&tty, 0, sizeof tty);
    tcflush( fd, TCIFLUSH );
    if ( tcgetattr ( fd, &tty ) != 0 )
    {
        printf("Error from tcgetattr: ");
        return -2;
    }
    cfmakeraw(&tty);
    cfsetospeed (&tty, (speed_t)speed);
    cfsetispeed (&tty, (speed_t)speed);

    tcflush (fd, TCIFLUSH);
    tty.c_cc[VMIN]   =  0;                  // read doesn't block
    tty.c_cc[VTIME]  =  1;                  // 0.5 seconds read timeout в марсе =1
    tty.c_iflag &= ~(BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON | IXOFF);
    tty.c_iflag |= IGNBRK;
    tty.c_oflag &= ~OPOST;
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_cflag     |= (CREAD | CS8 | CLOCAL);    // no flow control

    if ( tcsetattr ( fd, TCSANOW, &tty ) != 0)
    {
        printf("Error from tcsetattr :\n");
        return -1;
    }

#endif // __QNX
    //std::cout << "OPEN-OK" << std::endl;
    return 0;
}

int Com_PORT::close_com()
{
#ifdef __MINGW32__
    CloseHandle(hSerial);
#endif
#ifdef __linux
    close(fd);
    fd = -1;
#endif
#ifdef  __QNX
    close(fd);
    fd = -1;
#endif

    return 0;
}

unsigned long Com_PORT::read_com(unsigned int size_buffer)
{
#ifdef __MINGW32__
    static unsigned long iOut = 0; // кол-во прочитанных байтов
    if(!ReadFile(hSerial, _buffer,size_buffer, &iOut, NULL))
        //if(!ReadFile(hSerial, _buffer,(DWORD) 4096, &iOut, NULL))
    {
        ClearCommError(hSerial, &temp, &ComState);
        PurgeComm(hSerial,PURGE_TXABORT||PURGE_RXABORT||PURGE_TXCLEAR||PURGE_RXCLEAR);
        open_com(PORT_NUMBER,speed);
        if (open_com(PORT_NUMBER,speed) == -1)
        {
            std::cout << "Not found port" << std::endl;
            exit(1);
        }
    }
    // std::cout << _buffer << endl;
#endif
#ifdef __linux
    int iOut;
    iOut = read(fd_1, &buff, 1);
    {
        //printf("write error\r\n");
        if (iOut < 0)
        {
            buff = errno; //?????
            buff = -1;
        }
#endif // __linux

#ifdef __QNX
        static int iOut;
        iOut = read(fd, &_buffer, size_buffer);
        // std::cout << "Read" << std::endl;
        if (iOut == -1)
        {
            // вставить сброс порта
            std::cout << strerror(errno) << std::endl;

        }
        //  std::cout << "Read" << std::endl;
#endif // __QNX
        return iOut;
    }

    int Com_PORT::write_com(char *buffer,unsigned char size_buffer)
    {
#ifdef __MINGW32__
        unsigned long dwBytesWrite;
        unsigned char wr_count;
        if(!WriteFile(hSerial, buffer, size_buffer, &dwBytesWrite, NULL))
        {


            PurgeComm(hSerial,PURGE_TXABORT||PURGE_RXABORT||PURGE_TXCLEAR||PURGE_RXCLEAR);
            ClearCommError(hSerial, &temp, &ComState);
            //break;
            return -1;
        }
        buffer = buffer+1;

#endif

#ifdef __linux

#endif // __linux

#ifdef __QNX

#endif //__QNX


        return 0;
    }
