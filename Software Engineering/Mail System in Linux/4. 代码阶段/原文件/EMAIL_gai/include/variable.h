#ifndef __VARIABLE_H__
#define __VARIABLE_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <mysql.h>

//length
#define idLength 6
#define titleLength 26
#define perLength 29
#define addLength 31
#define dateLength 21
#define contentLength 1000

//database
char dbusername[100];
char *username;
char dbuserpwd[100];
char *userpwd;
char dbdataname[100];
char *dataname;

//socket
char ipadd[20];
char *ip;

//loginer
char loginerName[100];
char loginerAddress[100];
char sorr[30];

//frmLogin.c
GtkWidget *L_window;//窗体
GtkWidget *L_table0;//表格0
GtkWidget *L_table1;//表格1
GtkWidget *L_lbl1;//标签1
GtkWidget *L_lbl2;//标签2
GtkWidget *L_lbln;//空标签
GtkWidget *L_lbld;//对话框标签
GtkWidget *L_txt1;//文本框1
GtkWidget *L_txt2;//文本框2
GtkWidget *L_btn1;//按钮1
GtkWidget *L_btn2;//按钮2
GtkWidget *L_frame;//分组框
GtkWidget *L_dialog;//对话框

//frmRegister.c
GtkWidget *R_window;//窗体
GtkWidget *R_table;//表格
GtkWidget *R_lbl0;//标签1
GtkWidget *R_lbl1;//标签1
GtkWidget *R_lbl2;//标签2
GtkWidget *R_lbl3;//标签3
GtkWidget *R_lbl4;//标签4
GtkWidget *R_lbl5;//标签5
GtkWidget *R_lbl11;//标签11
GtkWidget *R_lbl22;//标签22
GtkWidget *R_lbl33;//标签33
GtkWidget *R_lbl44;//标签44
GtkWidget *R_lbl55;//标签55
GtkWidget *R_lbld;//对话框标签
GtkWidget *R_txt1;//文本框1
GtkWidget *R_txt2;//文本框2
GtkWidget *R_txt3;//文本框3
GtkWidget *R_txt4;//文本框4
GtkWidget *R_txt5;//文本框5
GtkWidget *R_btn1;//按钮1
GtkWidget *R_btn2;//按钮2
GtkWidget *R_btn3;//按钮3
GtkWidget *R_frame;//分组框
GtkWidget *R_dialog;//对话框

//frmMail.c
GtkWidget *M_window;//窗体
GtkWidget *M_table0;//表格
GtkWidget *M_table1;//表格
GtkWidget *M_txt;//文本框
GtkWidget *M_scrolled_txt;//滚动文本框
GtkWidget *M_lbld;//对话框标签
GtkWidget *M_menubar;//创建菜单栏
GtkAccelGroup *M_accel_group;//快捷菜单
GtkWidget *M_menuitem1;//菜单构件1
GtkWidget *M_menuitem2;//菜单构件2
GtkWidget *M_menuitem3;//菜单构件3
GtkWidget *M_menuitem10;//菜单构件10
GtkWidget *M_menuitem20;//菜单构件20
GtkWidget *M_menuitem30;//菜单构件30
GtkWidget *M_menuitem11;//菜单构件11
GtkWidget *M_menuitem18;//菜单构件18
GtkWidget *M_menuitem19;//菜单构件19
GtkWidget *M_menuitem22;//菜单构件22
GtkWidget *M_menuitem23;//菜单构件23
GtkWidget *M_menuitem24;//菜单构件24
GtkWidget *M_menuitem25;//菜单构件25
GtkWidget *M_menuitem26;//菜单构件26
GtkWidget *M_menuitem31;//菜单构件31
GtkWidget *M_toolbar;//创建工具栏
GtkWidget *M_toolbtn1;//按钮1
GtkWidget *M_toolbtn2;//按钮2
GtkWidget *M_toolbtn3;//按钮3
GtkWidget *M_toolbtn4;//按钮4
GtkWidget *M_toolbtn5;//按钮5
GtkWidget *M_toolbtn6;//按钮6
GtkWidget *M_separatortoolitem1;//工具栏分割符1
GtkWidget *M_separatortoolitem2;//工具栏分割符2
GtkWidget *M_separatormenuitem1;//菜单栏分割符1
GtkWidget *M_separatormenuitem2;//菜单栏分割符2
GtkWidget *M_list;//列表
GtkWidget *M_list1;//列表1
GtkWidget *M_list2;//列表2
GtkWidget *M_scrolled_list2;//滚动列表2
GtkCellRenderer *M_renderer;//单元格格式
GtkTreeViewColumn *M_column;//列表列
GtkListStore *M_store;//列表存储项
GtkTreeIter M_iter;//列表行指针
GtkTreeSelection *M_selection1;//列表选项1
GtkTreeSelection *M_selection2;//列表选项2
GtkWidget *M_dialog;//对话框
char ME_peradd[perLength+addLength+1];//传人和地址
char ME_rper[perLength+1];//收件人
char ME_radd[addLength+1];//收件人地址
char ME_title[titleLength+5];//传地址 Re:
char *ME_content;//内容
int ME_flag;//打开的方式：3种(撰写,转发,回复)
int M_flag;//选项的标志1-4

//frmEdit.c
GtkWidget *E_window;//窗体
GtkWidget *E_table0;//表格
GtkWidget *E_table1;//表格
GtkWidget *E_table2;//表格
GtkWidget *E_lbl1;//标签1
GtkWidget *E_lbl2;//标签2
GtkWidget *E_lbln;//空标签
GtkWidget *E_lbld;//对话框标签
GtkWidget *E_txt1;//文本框1
GtkWidget *E_txt2;//文本框2
GtkWidget *E_txt3;//文本框3
GtkWidget *E_scrolled_txt3;//滚动文本框3
GtkWidget *E_txt4;//文本框4
GtkWidget *E_menubar;//创建菜单栏
GtkAccelGroup *E_accel_group;//快捷菜单
GtkWidget *E_menuitem1;//菜单构件1
GtkWidget *E_menuitem2;//菜单构件2
GtkWidget *E_menuitem3;//菜单构件3
GtkWidget *E_menuitem10;//菜单构件10
GtkWidget *E_menuitem20;//菜单构件20
GtkWidget *E_menuitem30;//菜单构件30
GtkWidget *E_menuitem11;//菜单构件11
GtkWidget *E_menuitem12;//菜单构件12
GtkWidget *E_menuitem13;//菜单构件13
GtkWidget *E_menuitem19;//菜单构件19
GtkWidget *E_menuitem21;//菜单构件21
GtkWidget *E_menuitem22;//菜单构件22
GtkWidget *E_menuitem23;//菜单构件23
GtkWidget *E_menuitem31;//菜单构件31
GtkWidget *E_toolbar;//创建工具栏
GtkWidget *E_toolbtn1;//按钮1
GtkWidget *E_toolbtn2;//按钮2
GtkWidget *E_toolbtn3;//按钮3
GtkWidget *E_toolbtn4;//按钮4
GtkWidget *E_toolbtn5;//按钮5
GtkWidget *E_toolbtn6;//按钮6
GtkWidget *E_toolbtn7;//按钮7
GtkWidget *E_list;//列表
GtkWidget *E_scrolled_list;//滚动列表
GtkWidget *E_separatortoolitem1;//工具栏分割符1
GtkWidget *E_separatortoolitem2;//工具栏分割符2
GtkWidget *E_separatortoolitem3;//工具栏分割符3
GtkWidget *E_separatormenuitem1;//菜单栏分割符1
GtkWidget *E_separatormenuitem2;//菜单栏分割符2
GtkWidget *E_separatormenuitem3;//菜单栏分割符3
GtkCellRenderer *E_renderer;//单元格格式
GtkTreeViewColumn *E_column;//列表列
GtkListStore *E_store;//列表存储项
GtkTreeIter E_iter;//列表行指针
GtkTreeSelection *E_selection;//列表选项
GtkWidget *E_dialog;//对话框
int E_flag;//打开的方式：3种(撰写,转发,回复)

#endif
