#include "mtk2.h"
//#include "QDebug"
#include "stdio.h"
#include "string.h"

mtk2::mtk2()
{
    memset(buffer,0,sizeof(buffer));
    memset(mtk2::outout,0,sizeof(outout));
    memset(mtk2::outout_r,0,sizeof(outout_r));

    memset(n_latin,0,sizeof(n_latin));
    memset(n_rus,0,sizeof(n_rus));
    memset(n_number,0,sizeof(n_number));

    memset(r_latin,0,sizeof(n_latin));
    memset(r_rus,0,sizeof(n_rus));
    memset(r_number,0,sizeof(n_number));


    init_array_mtk2();
    init_array_mtk2_r();// call after init_array_mtk2

    current_position=0;
    count_decoded_package = 0;

    flag_SET_LATIN   = false;
    flag_SET_NUMERIC = false;
    flag_SET_RUS     = false;
}
void mtk2::init_array_mtk2_r(void)
{
    int i=0;
    for (i=0;i<0xff;i++)
    {
        if(n_latin[i]!=0)
        {
            r_latin[n_latin[i]]=i;
        }
        if(n_number[i]!=0)
        {
            r_number[n_number[i]]=i;
        }
    }
}


void mtk2::init_array_mtk2(void)
{
    n_latin[0x03] = 'A';
    n_latin[0x19] = 'B';
    n_latin[0x0E] = 'C';
    n_latin[0x09] = 'D';
    n_latin[0x01] = 'E';
    n_latin[0x0D] = 'F';
    n_latin[0x1A] = 'G';
    n_latin[0x14] = 'H';
    n_latin[0x06] = 'I';
    n_latin[0x0B] = 'J';
    n_latin[0x0F] = 'K';
    n_latin[0x12] = 'L';
    n_latin[0x1C] = 'M';
    n_latin[0x0C] = 'N';
    n_latin[0x18] = 'O';
    n_latin[0x16] = 'P';
    n_latin[0x17] = 'Q';
    n_latin[0x0A] = 'R';
    n_latin[0x05] = 'S';
    n_latin[0x10] = 'T';
    n_latin[0x07] = 'U';
    n_latin[0x1E] = 'V';
    n_latin[0x13] = 'W';
    n_latin[0x1D] = 'X';
    n_latin[0x15] = 'Y';
    n_latin[0x11] = 'Z';
    //
    /*
    n_rus[0x03] = 'А';
    n_rus[0x19] = 'Б';
    n_rus[0x0E] = 'Ц';
    n_rus[0x09] = 'Д';
    n_rus[0x01] = 'Е';
    n_rus[0x0D] = 'Ф';
    n_rus[0x1A] = 'Г';
    n_rus[0x14] = 'Х';
    n_rus[0x06] = 'И';
    n_rus[0x0B] = 'Й';
    n_rus[0x0F] = 'К';
    n_rus[0x12] = 'Л';
    n_rus[0x1C] = 'М';
    n_rus[0x0C] = 'Н';
    n_rus[0x18] = 'О';
    n_rus[0x16] = 'П';
    n_rus[0x17] = 'Я';
    n_rus[0x0A] = 'Р';
    n_rus[0x05] = 'С';
    n_rus[0x10] = 'Т';
    n_rus[0x07] = 'У';
    n_rus[0x1E] = 'Ж';
    n_rus[0x13] = 'В';
    n_rus[0x1D] = 'Ь';
    n_rus[0x15] = 'Ы';
    n_rus[0x11] = 'З';
    */
    //
    n_number[0x03] = '-';
    n_number[0x19] = '?';
    n_number[0x0E] = ':';
    n_number[0x09] = ' '; //who are you?
    n_number[0x01] = '3';
    n_number[0x0D] = '&'; //russian simbol ???????????????????????????????????
    n_number[0x1A] = ' '; //russian simbol ?
    n_number[0x14] = ' '; //russian simbol ?
    n_number[0x06] = '8';
    n_number[0x0B] = ' '; //russian simbol ?
    n_number[0x0F] = '(';
    n_number[0x12] = ')';
    n_number[0x1C] = '.';
    n_number[0x0C] = ',';
    n_number[0x18] = '9';
    n_number[0x16] = '0';
    n_number[0x17] = '1';
    n_number[0x0A] = '4';
    n_number[0x05] = 0x27; //'''
    n_number[0x10] = '5';
    n_number[0x07] = '7';
    n_number[0x1E] = '=';
    n_number[0x13] = '2';
    n_number[0x1D] = '/';
    n_number[0x15] = '6';
    n_number[0x11] = '+';
}
bool mtk2::encode(char b)
{
   if((b == MT_SET_LATIN) && (flag_SET_LATIN != true ))
   {
       flag_SET_LATIN   = true;
       return false;
   }
   else
   {
     if (flag_SET_LATIN != true )
     {
         return false;
     }
   }
   if((b == MT_SET_NUMERIC) && (flag_SET_NUMERIC != true ))
   {
       flag_SET_NUMERIC = true;
       return false;
   }
   else
   {
      if (flag_SET_NUMERIC != true )
     {
         return false;
     }
     else
     {
     }
   }

   if ((flag_SET_LATIN & flag_SET_NUMERIC))
   {
       if (b==MT_LF)
       {
           flag_SET_LATIN = false;
           flag_SET_NUMERIC = false;
           current_position = 0;
           return true;
       }
       else
       {
           mtk2::outout[mtk2::current_position] = n_number[b];
           mtk2::current_position = mtk2::current_position + 1;
           return false;
       }
   }
   else
   {
       return false;
   }
exit_from:
   return false;
}

bool mtk2::code(char* buf,char num_bytes)
{
    memset(outout_r,0,sizeof(outout_r));
    outout_r[0] = 0x1f;
    outout_r[1] = 0x1b;
    int c = 0;
    for(c = 0; c < num_bytes; c++)
    {
        outout_r[c+2] = r_number[buf[c]];
    }
    outout_r[c+2] = 0x2;
    outout_r[c+3] = 0x8;
    return  true;
}

char* mtk2::get_encode_result(void)
{
  return (char *) outout;
}

char* mtk2::get_code_result(void)
{
  return (char *) outout_r;
}
