#define __MYSCANF
#include <cstdarg>
#include "mystdio.hpp"

extern char in_buf[];
extern int in_idx;
int is_delimiter(char ch) //判断是否是分隔符
{
    return (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t' || ch == '\v');
}

int myscanf(char* format, ...) {
    _Tp *data;
    data = new _Tp[200];
    va_list vl;
    va_start(vl, format);
    int __len = split(format, data);
    for (int i = 0; i<__len; ++i) {
        if(data[i].type() == _Tp::fmt) {
            if(data[i].name() == _Tp::INT) {
                int *_arg = va_arg(vl, int*);
                if(data[i].align_limit() == splim::non_align) {
                    int begin = i, end = i;
                    while(0) _arg++;
                    end -= begin;
                }
            }
        }
    }
    delete data;
    return 1;
}
