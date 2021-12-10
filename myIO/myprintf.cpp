#define __MYPRINTF
#include <cstdarg>
#include "mystdio.hpp"

int myprintf(const char *format, ...) {
    _Tp *data;
    char *buf;
    data = new _Tp[102];
    buf = new char[2000];

    va_list vl;
    int count;
    va_start(vl, format);
    int l = split(format, data);
    for(int i = 0; i<l; ++i) {
        if(data[i].type() == _Tp::str) {
            data[i].content(out_buf+out_idx);
            while(out_buf[out_idx] != '\0') out_idx++;
        }else if (data[i].type() == _Tp::fmt) {
            int l = data[i].name();
            if (l == _Tp::INT){
                int t = va_arg(vl, int);
                int len = write(buf, t, data[i].number_system());
            }else if(l == -_Tp::INT) {
                int t = va_arg(vl, unsigned int);
            }
        }
    }

    delete buf;
    delete data;
    return count;
}