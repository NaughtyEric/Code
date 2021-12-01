#define __MYPRINTF
#include "myprintf.hpp"
#ifndef _LIBCPP_CSTDARG
#include <cstdarg>
#endif
int myprintf(char *format, ...) {
    _Tp a[100];
    int l = split(format, a);
}