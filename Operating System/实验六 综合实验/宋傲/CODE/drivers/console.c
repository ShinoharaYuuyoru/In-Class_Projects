#include "console.h"
#include "common.h"

//VGA缓冲区起始地址
static uint16_t *vga_buffer = (uint16_t*)0xB8000;

//屏幕光标XY
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

//更新光标位置
static void move_cursor()
{
	//屏幕尺寸80*24
	uint16_t cursor_location = cursor_y*80 + cursor_x;

	//http://web.stanford.edu/class/cs140/projects/pintos/specs/freevga/vga/crtcreg.htm#0A
	//读取内部寄存器索引3D4，写入下一步要操作的寄存器编号。之后读取3D5
	outb(0x3D4,14); //14号寄存器是光标位置高8位
	outb(0x3D5,cursor_location>>8);
	outb(0x3D4,15); //15号为低8位；
	outb(0x3D5,cursor_location&0x00FF);
}

//屏幕向上滚动一行
static void scroll()
{
	uint8_t console_color_attribute = (0<<4)|(15&0x0F); //黑底白字
	uint8_t whitespace = (0x20)|(console_color_attribute<<8);

	//下一行复制到上一行
	if(cursor_y>=25)
	{
		for(int i=0;i<80*24;i++)
		{
			vga_buffer[i] = vga_buffer[i+80];
		}
	}
	//最后一行填空格
	for(int i=24*80;i<25*80;i++)
	{
		vga_buffer[i] = whitespace;
	}
}

//清屏幕
void console_clear()
{
	uint8_t console_color_attribute = (0<<4) | (15&0x0F); //黑底白字
	uint8_t whitespace = (0x20) | (console_color_attribute<<8);

	//将这个屏幕的显示置成whitespace
	for(int i = 0;i<80*25;i++)
	{
		vga_buffer[i] = whitespace;
	}

	cursor_y = cursor_x = 0;
	move_cursor();
}

//输出字符，带颜色信息
void console_putc(char c,disp_color_t back,disp_color_t fore)
{
	uint8_t console_color_attribute = (((uint8_t)back)<<4) | (((uint8_t)fore)&0x0F);

	//0x08--退格
	if(c == 0x08 && cursor_x)
	{
		cursor_x--;
	}
	//回车
	else if(c == '\r')
	{
		cursor_x = 0;
		cursor_y++;
	}
	//换行
	else if(c =='\n')
	{
		cursor_x = 0;
		cursor_y++;
	}
	else if(c>=' ')
	{
		vga_buffer[cursor_y*80+cursor_x] = (console_color_attribute<<8) | c ;
		cursor_x++;
	}

	//一行满后跳至下一行
	if (cursor_x >= 80) {
        cursor_x = 0;
        cursor_y ++;
    }

	//如果屏幕满，向下滚动一行
	scroll();

	//更新光标位置
	move_cursor();
}

//输出字符串
void console_puts(char *str,disp_color_t back,disp_color_t fore)
{
	while(*str)
	{
		console_putc(*str,back,fore);
		str++;
	}
}

//输出十进制整数
void console_puti(uint32_t n,disp_color_t back,disp_color_t fore)
{
	if (n == 0) {
		console_putc('0', back, fore);
		return;
	}

	uint32_t acc = n;
	char c[32];
	int i = 0;
	while (acc > 0) {
		c[i] = '0' + acc % 10;
		acc /= 10;
		i++;
	}
	c[i] = 0;

	char c2[32];
	c2[i--] = 0;

	int j = 0;
	while(i >= 0) {
	      c2[i--] = c[j++];
	}

	console_puts(c2, back, fore);
}