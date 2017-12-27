#ifndef __DATABASE_H__
#define __DATABASE_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <mysql.h>

//dbShow.c
void connectdb();
void showUserInfo();
void showListName();
void showListEmail(char *typeid,int choice);

//dbValidate.c
int validateLogin(char *name,char *password);

//dbInsert.c
void insertUserInfo(char *name,char *password,char *address,char *phone);

//dbSubmit.c
void submitString(char *str,int index);//截取字符串
void submitAddressFromName(char *name);

#endif
