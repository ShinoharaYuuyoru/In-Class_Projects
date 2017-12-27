#ifndef INCLUDE_STRING_H
#define INCLUDE_STRING_H

#include "types.h"
// 一些库函数的声明
void * memcpy(void *dest,const void *src,uint32_t n);

void bzero(void *dest, uint32_t len);

void * memset (void *dest,uint8_t val,uint32_t len);

char * strcpy(char *dest,char *src);

char * strncpy(char *dest,const char *src,uint32_t count);

char * strcat(char *dest,const char *src);

char * strncat(char *dest,const char *src,uint32_t count);

int strcmp(const char *cs,const char *ct);

int strlen(const char* str);

#endif