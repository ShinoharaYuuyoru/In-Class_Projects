#include "string.h"

//库函数的实现
inline void * memcpy(void *dest,const void *src,uint32_t n)
{
	__asm__ ("cld\n\t"
             "rep\n\t"
             "movsb"
             ::"c" (n),"S" (src),"D" (dest)
            );
    return dest;
}

inline void * memset (void *dest,uint8_t val,uint32_t len)
{
	__asm__("cld\n\t"
            "rep\n\t"
            "stosb"
            ::"a" (val),"D" (dest),"c" (len)
            );
    return dest;
}
inline char * strcpy(char *dest,char *src)
{
	__asm__("cld\n"
            "1:\tlodsb\n\t"
            "stosb\n\t"
            "testb %%al,%%al\n\t"
            "jne 1b"
            ::"S" (src),"D" (dest));
    return dest;
}

inline char * strncpy(char *dest,const char *src,uint32_t count)
{
	__asm__("cld\n"
            "1:\tdecl %2\n\t"
            "js 2f\n\t"
            "lodsb\n\t"
            "stosb\n\t"
            "testb %%al,%%al\n\t"
            "jne 1b\n\t"
            "rep\n\t"
            "stosb\n"
            "2:"
            ::"S" (src),"D" (dest),"c" (count));
    return dest;
}

inline char * strcat(char *dest,const char *src)
{
	__asm__("cld\n\t"
            "repne\n\t"
            "scasb\n\t"
            "decl %1\n"
            "1:\tlodsb\n\t"
            "stosb\n\t"
            "testb %%al,%%al\n\t"
            "jne 1b"
            ::"S" (src),"D" (dest),"a" (0),"c" (0xffffffff));
    return dest;
}

inline char * strncat(char *dest,const char *src,uint32_t count)
{
	__asm__("cld\n\t"
            "repne\n\t"
            "scasb\n\t"
            "decl %1\n\t"
            "movl %4,%3\n"
            "1:\tdecl %3\n\t"
            "js 2f\n\t"
            "lodsb\n\t"
            "stosb\n\t"
            "testb %%al,%%al\n\t"
            "jne 1b\n"
            "2:\txorl %2,%2\n\t"
            "stosb"
            ::"S" (src),"D" (dest),"a" (0),"c" (0xffffffff),"g" (count)
            );
    return dest;
}

inline int strcmp(const char *cs,const char *ct)
{
	register int __res ;
    __asm__("cld\n"
            "1:\tlodsb\n\t"
            "scasb\n\t"
            "jne 2f\n\t"
            "testb %%al,%%al\n\t"
            "jne 1b\n\t"
            "xorl %%eax,%%eax\n\t"
            "jmp 3f\n"
            "2:\tmovl $1,%%eax\n\t"
            "jl 3f\n\t"
            "negl %%eax\n"
            "3:"
            :"=a" (__res):"D" (cs),"S" (ct));
    return __res;
}

inline int strlen(const char* str)
{
    register int __res ;
    __asm__("cld\n\t"
            "repne\n\t"
            "scasb\n\t"
            "notl %0\n\t"
            "decl %0"
            :"=c" (__res):"D" (str),"a" (0),"0" (0xffffffff));
    return __res;
}