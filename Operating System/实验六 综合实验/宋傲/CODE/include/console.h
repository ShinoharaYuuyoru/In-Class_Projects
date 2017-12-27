#ifndef INCLUDE_CONSOLE_H
#define INCLUDE_CONSOLE_H

#include "types.h"

//定义字符的颜色信息
typedef enum disp_color
{
	dc_black = 0,
    dc_blue = 1,
    dc_green = 2,
    dc_cyan = 3,
    dc_red = 4,
    dc_magenta = 5,
    dc_brown = 6,
    dc_light_grey = 7,
    dc_dark_grey = 8,
    dc_light_blue = 9,
    dc_light_green = 10,
    dc_light_cyan = 11,
    dc_light_red = 12,
    dc_light_magenta = 13,
    dc_light_brown  = 14,   // yellow
    dc_white = 15
} disp_color_t;

//清屏幕
void console_clear();

//输出字符，带颜色信息
void console_putc(char c,disp_color_t back,disp_color_t fore);

//输出字符串
void console_puts(char *str,disp_color_t back,disp_color_t fore);

//输出十进制整数
void console_puti(uint32_t num,disp_color_t back,disp_color_t fore);

#endif
