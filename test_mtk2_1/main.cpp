#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "Com_PORT.h"
#include "mtk2.h"
#define __MINGW32__
using namespace std;
Com_PORT com_mtk2;


unsigned int Bytes_read =0;
unsigned int count_bytes=0;
unsigned int count_cycles=0;

//
//char mtk2::outout[4000] = {};
//unsigned int mtk2::current_position = 0;
//static
mtk2 l_mtk2;
//
int main()

{

     if (com_mtk2.open_com(1,100) == -1)
        {
            cout << " Error open port "<<endl;
        }
        else
        {
            cout << " Open port "<<endl;
        }

    for (count_bytes=0;count_bytes<20000;count_bytes++)
    {
        Bytes_read = com_mtk2.read_com(10);
        for(count_cycles=0;count_cycles<Bytes_read;count_cycles++)
        {
            //printf("%s = %d ","count_cycles",count_cycles);
         //   printf("%s = %x \n","com_mtk2._buffer[count_cycles]",com_mtk2._buffer[count_cycles]);

           if(l_mtk2.encode(com_mtk2._buffer[count_cycles]))
              {
              //   cout<<"decode "<<l_mtk2.get_encode_result()<<endl;
              //   cout<<endl<<"decode"<<endl;
              //   printf("%s \n",l_mtk2.get_encode_result());
                 cout<<l_mtk2.get_encode_result()<<endl;
              }

        }

    }



    cout << "Hello world!" << endl;
    com_mtk2.close_com();
    return 0;
}
