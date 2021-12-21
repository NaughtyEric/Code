#define __MYPRINTF
#include <cstdarg>
#include <cmath>
#include "mystdio.hpp"

extern char out_buf[];
extern int out_idx;
int myprintf(const char *format, ...) {
    _Tp *data;
    char *buf;
    data = new _Tp[102];
    buf = new char[2000];
    va_list vl;
    int count = 0;
    va_start(vl, format);
    int dataL = split(format, data);
    for(int i = 0; i<dataL; ++i) {
        int l, len;
        if(data[i].type() == _Tp::str) {
            data[i].content(out_buf+out_idx);
            while(out_buf[out_idx] != '\0')
                out_idx++;
        }else if (data[i].type() == _Tp::fmt) {
            l = data[i].name();
            if (l == _Tp::SHORT){
                short t = va_arg(vl, int);
                len = write(buf, t, data[i].number_system());
            }
            if (l == _Tp::INT){
                int t = va_arg(vl, int);
                len = write(buf, t, data[i].number_system());
            }
            if (l == _Tp::LONG){
                long t = va_arg(vl, long);
                len = write(buf, t, data[i].number_system());
            }
            if (l == _Tp::LONGLONG){
                long long t = va_arg(vl, long long);
                len = write(buf, t, data[i].number_system());
            }
            
            if (l == _Tp::CHAR) {
                buf[0] = va_arg(vl, int);
                len = 1;
            }
            if (l == _Tp::STRING) {
                char *tar_str = va_arg(vl, char*);
                for (len = 0; tar_str[len] != '\0';++len) {buf[len] = tar_str[len];}
            }

            if(l == _Tp::FLOAT || l == _Tp::DOUBLE) {
                if (data[i].fopt() == splim::f){
                    double tmp = va_arg(vl, double);
                    len = write(buf, (int)floor(tmp), 10);
                    tmp -= floor(tmp);
                    buf[len++] = '.';
                    for (int k = 1; k<=data[i].decimals_kept(); ++k) {
                        tmp *= 10;
                        len += write(buf+len, (int)floor(tmp), 10);
                        tmp -= floor(tmp);
                    }
                }else if (data[i].fopt() == splim::e) {

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
                        out_buf[out_idx++] = ' ';
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