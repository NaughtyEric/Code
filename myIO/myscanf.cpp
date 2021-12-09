#define __MYSCANF
#ifndef _LIBCPP_CSTDARG
#include <cstdarg>
#endif
#ifndef MYSTDIO_H
#include "mystdio.hpp"
#endif
#ifndef __UTILITIES_
#include "utilities.hpp"
#endif 

_Tp data[200];
int myscanf(char* format, ...) {
    va_list vl;
    va_start(vl, format);
    int __len = split(format, data);
    for (int i = 0; i<__len; ++i) {
        if(data[i].type() == _Tp::fmt) {
            if(data[i].name() == _Tp::INT) {
                if(data[i].align_limit() != splim::non_align) {
                    int l = data[i].align_width();
                    int ans;
                    for (int i = l-1; i >= 0; --i) {
                        ans = ans*10+in_buf[i+in_idx] - '0';
                    }
                    
                }
            }
        }
    }
    return 1;
}
