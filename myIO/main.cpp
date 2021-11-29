#include <stdio.h>
#include <stdarg.h>

#define MAX_LEN 4096

//各种数据类型的变量
char c = '\0';
short s = 0;
int i = 0;
long long ll = 0;
float f = 0.0;
double d = 0.0;
char str[MAX_LEN] = "";

//输入、输出缓存区
char in_buf[MAX_LEN], out_buf[MAX_LEN];

//输入、输出缓冲区当前位置
int in_idx, out_idx;

//输入、输出格式化字符串
char in_fmt[MAX_LEN], out_fmt[MAX_LEN];

int myscanf(char *fmt, ...)
{
}

int myprintf(char *fmt, ...)
{
}

int main()
{
    int ret1, ret2;
    gets(in_fmt);
    gets(out_fmt);
    gets(in_buf);

    ret1 = myscanf(in_fmt, &d, &c);
    ret2 = myprintf(out_fmt, d, c);
    puts(out_buf);
    myprintf("%d %d\n", ret1, ret2);
}