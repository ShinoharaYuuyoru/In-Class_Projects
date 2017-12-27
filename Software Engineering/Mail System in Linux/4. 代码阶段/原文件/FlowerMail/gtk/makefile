#Makefile for FMail
makeit:main.o login.o register.o  mainWin.o  theme.o
	gcc  ./obj/main.o ./obj/login.o ./obj/register.o ./obj/mainWin.o ./obj/theme.o -o ./bin/FMail `pkg-config --cflags --libs gtk+-2.0`
main.o:
	gcc -I./include -c ./src/main.c -o ./obj/main.o `pkg-config --cflags --libs gtk+-2.0`
login.o:
	gcc -I./include -c ./src/login.c -o ./obj/login.o `pkg-config --cflags --libs gtk+-2.0`
register.o:
	gcc -I./include -c ./src/register.c -o ./obj/register.o `pkg-config --cflags --libs gtk+-2.0`
mainWin.o:
	gcc -I./include -c ./src/mainWin.c -o ./obj/mainWin.o `pkg-config --cflags --libs gtk+-2.0`
write.o:
	gcc -I./include -c ./src/write.c -o ./obj/write.o `pkg-config --cflags --libs gtk+-2.0`
theme.o:
	gcc -I./include -c ./src/theme.c -o ./obj/theme.o `pkg-config --cflags --libs gtk+-2.0`
