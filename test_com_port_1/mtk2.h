#ifndef MTK2_H
#define MTK2_H

#define  MT_LF (unsigned char)          2
#define  MT_CR (unsigned char)          8

#define  MT_SET_LATIN (unsigned char)   31 //0x1f
#define  MT_SET_NUMERIC (unsigned char) 27 //0x1b
#define  MT_SPACE (unsigned char)       4
#define  MT_SET_RUS (unsigned char)     0

class mtk2
{
public:
    mtk2();
    unsigned char buffer[4000];
    //static
    unsigned int current_position ;
    //static
    char outout[4000];
    char outout_r[4000];

    bool flag_SET_LATIN ;
    bool flag_SET_NUMERIC ;
    bool flag_SET_RUS ;

    bool encode(char b);
    bool code(char* buf,char num_bytes);
    char* get_encode_result(void);
    char* get_code_result(void);
    unsigned long count_decoded_package;
    //
    /*
    unsigned char b_char[32]={ 0x03,0x19,0x0E,0x09,0x01,0x0D,0x1A,0x14,0x06,0x0B,0x0F,
                      0x12,0x1C,0x0C,0x18,0x16,0x17,0x0A,0x05,0x10,0x07,0x1E,
                      0x13,0x1D,0x15,0x11,
                      0x08,0x02,0x1F,0x1B,0x04,0x00};
    */
    // decode
    char n_latin[0xff];
    char n_number[0xff];
    char n_rus[0xff];
    //code
    char r_latin[0xff];
    char r_number[0xff];
    char r_rus[0xff];
    //
protected:
private:
    void init_array_mtk2(void);
    void init_array_mtk2_r(void);
};

#endif // MTK2_H
