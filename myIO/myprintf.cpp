#define __MYPRINTF
#include <cstdarg>
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
    int l = split(format, data);
    for(int i = 0; i<l; ++i) {
        int l, t, len;
        if(data[i].type() == _Tp::str) {
            data[i].content(out_buf+out_idx);
            while(out_buf[out_idx] != '\0')
                out_idx++;
        }else if (data[i].type() == _Tp::fmt) {
            l = data[i].name();
            if (l == _Tp::INT){
                t = va_arg(vl, int);
                len = write(buf, t, data[i].number_system());
            }
            if(data[i].align_limit() == splim::non_align) {
                for(int k = 0; k<len; ++k) {out_buf[out_idx++] = buf[k];}
            }else{
                int ali_len = data[i].align_width();
                int longer_than_limits = len - ali_len;
                if (data[i].align_limit() == splim::left_align) {
                    for(int k = 0; k<longer_than_limits; ++k)
                        out_buf[out_idx++] = ' ';
                    for(int k = 0; k<len; ++k) {out_buf[out_idx++] = buf[k];}
                }else{
                    for(int k = 0; k<len; ++k) {out_buf[out_idx++] = buf[k];}
                    for(int k = 0; k<longer_than_limits; ++k)
                        out_buf[out_idx++] = ' ';
                }
            }
        }
        count++;
    }
    perror("awa");
    delete buf;
    delete data;
    perror("qwq");
    return count;
}