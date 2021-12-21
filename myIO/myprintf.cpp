#define __MYPRINTF
#include <cstdarg>
#include <cmath>
#include "mystdio.hpp"

extern char out_buf[];
extern int out_idx;
int myprintf(const char *format, ...) {
    printf("%d",421);
    _Tp *data;
    char *buf;
    data = new _Tp[102];
    buf = new char[2000];
    va_list vl;
    int count = 0;
    va_start(vl, format);
    int dataL = split(format, data);
    for(int i = 0; i<dataL; ++i) {
        int TYPE, len = 0;
        if(data[i].type() == _Tp::str) {
            data[i].content(out_buf+out_idx);
            while(out_buf[out_idx] != '\0')
                out_idx++;
        }else if (data[i].type() == _Tp::fmt) {
            TYPE = data[i].name();
            if (TYPE == _Tp::SHORT){
                short t = va_arg(vl, int);
                len = write(buf, t, data[i].number_system());
            }
            else if (TYPE == _Tp::INT){
                int t = va_arg(vl, int);
                len = write(buf, t, data[i].number_system());
            }
            else if (TYPE == _Tp::LONG){
                long t = va_arg(vl, long);
                len = write(buf, t, data[i].number_system());
            }
            else if (TYPE == _Tp::LONGLONG){
                long long t = va_arg(vl, long long);
                len = write(buf, t, data[i].number_system());
            }
            else if (TYPE == -_Tp::SHORT){
                unsigned short t = va_arg(vl, int);
                len = write(buf, t, data[i].number_system(), data[i].upperCase());
            }
            else if (TYPE == -_Tp::INT){
                unsigned int t = va_arg(vl, int);
                len = write(buf, t, data[i].number_system(), data[i].upperCase());
            }
            else if (TYPE == -_Tp::LONG){
                unsigned long t = va_arg(vl, long);
                len = write(buf, t, data[i].number_system(), data[i].upperCase());
            }
            else if (TYPE == -_Tp::LONGLONG){
                unsigned long long t = va_arg(vl, long long);
                len = write(buf, t, data[i].number_system(), data[i].upperCase());
            }
            
            if (TYPE == _Tp::CHAR) {
                buf[0] = va_arg(vl, int);
                len = 1;
            }
            if (TYPE == _Tp::STRING) {
                char *tar_str = va_arg(vl, char*);
                for (len = 0; tar_str[len] != '\0';++len) {buf[len] = tar_str[len];}
            }

            if(TYPE == _Tp::FLOAT || TYPE == _Tp::DOUBLE) {
                double tmp = va_arg(vl, double);
                if (tmp < 0) {
                    buf[len++] = '-';
                    tmp = -tmp;
                }

                auto writedec = [&len](double &ss, char* _tar) -> auto {
                    assert(ss < 1);
                    ss *= 10;
                    len += write(_tar, (int)floor(ss), 10);
                    ss -= floor(ss);
                };

                if (data[i].fopt() == splim::f){
                    len += write(buf + len, (int)floor(tmp), 10);
                    tmp -= floor(tmp);
                    buf[len++] = '.';
                    for (int k = 1; k<=data[i].decimals_kept(); ++k) {
                        // tmp *= 10;
                        // len += write(buf+len, (int)floor(tmp), 10);
                        // tmp -= floor(tmp);
                        writedec(tmp, buf+len);
                    }
                }else if (data[i].fopt() == splim::e) {
                    int t = floor(log10(tmp));
                    tmp /= pow(10, t);
                    buf[len++] = (int)floor(tmp) + '0';
                    tmp -= floor(tmp);
                    buf[len++] = '.';
                    for(int k = 1; k<=6; ++k)
                        writedec(tmp, buf+len);
                    //（最后指数）
                    buf[len++] = data[i].upperCase()?'E':'e';
                    if(t < 0) buf[len++] = '-';
                    else buf[len++] = '+';
                    if(t < 10) buf[len++] = '0';
                    len += write(buf+len, t, 10);
                }else if (data[i].fopt() == splim::g){

                }
            }
        //alignment coping
            if(data[i].align_limit() == splim::non_align) {
                for(int k = 0; k<len; ++k) {out_buf[out_idx++] = buf[k];}
            }else{
                int ali_len = data[i].align_width();
                int less_than_limits = ali_len - len;
                if (data[i].align_limit() == splim::right_align) {
                    for(int k = 0; k<less_than_limits; ++k)
                        out_buf[out_idx++] = data[i].align_fill();
                    for(int k = 0; k<len; ++k) {out_buf[out_idx++] = buf[k];}
                }else{
                    for(int k = 0; k<len; ++k) {out_buf[out_idx++] = buf[k];}
                    for(int k = 0; k<less_than_limits; ++k)
                        out_buf[out_idx++] = ' ';
                }
            }
            count++;
        }
        
    }

    delete []buf;
    delete []data;
    return count;
}