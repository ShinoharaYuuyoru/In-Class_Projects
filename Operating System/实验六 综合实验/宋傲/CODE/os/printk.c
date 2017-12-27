#include "console.h"
#include "os/kernel.h"
#include "string.h"
#include "vargs.h"

// vsprintf 定义在vsprintf.c中
extern int vsprintf(char * buf, const char * fmt, va_list args);

void printk(const char *format, ...)
{
	// 避免频繁创建临时变量，内核的栈很宝贵
	static char buff[1024];
	va_list args;
	int i;

	va_start(args, format);
	i = vsprintf(buff, format, args);
	va_end(args);

	buff[i] = '\0';

	console_puts(buff,dc_black,dc_white);
}

void printk_color(disp_color_t back, disp_color_t fore, const char *format, ...)
{
	// 避免频繁创建临时变量，内核的栈很宝贵
	static char buff[1024];
	va_list args;
	int i;

	va_start(args, format);
	i = vsprintf(buff, format, args);
	va_end(args);

	buff[i] = '\0';

	console_puts(buff, back, fore);
}