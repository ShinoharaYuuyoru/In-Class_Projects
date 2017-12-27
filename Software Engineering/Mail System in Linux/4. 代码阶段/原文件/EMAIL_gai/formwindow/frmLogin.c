#include "variable.h"
#include "database.h"
#include "formwindow.h"

void L_destroy(GtkWidget *widget,gpointer data)
{
	gtk_main_quit();
}

void L_btn1_on_clicked(GtkWidget *widget,gpointer data)
{
	char name[20];
	char password[20];
	strcpy(name,gtk_entry_get_text(GTK_ENTRY(L_txt1)));
	strcpy(password,gtk_entry_get_text(GTK_ENTRY(L_txt2)));
	if(!strcmp("",name))
	{
		L_dialog=gtk_dialog_new_with_buttons("提示",GTK_WINDOW(L_window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
		L_lbld=gtk_label_new("用户名不能为空!");
		gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(L_dialog)->vbox),L_lbld);//标签加入到对话框里
		gtk_widget_show_all(L_dialog);//显示对话框里的信息
		if(gtk_dialog_run(GTK_DIALOG(L_dialog))==GTK_RESPONSE_OK)
		{
			gtk_widget_destroy(L_dialog);//ro不是or
		}
		return;
	}
	int ret=validateLogin(name,password);
	ret = 1;
	if(ret==0)
	{
		L_dialog=gtk_dialog_new_with_buttons("提示",GTK_WINDOW(L_window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
		L_lbld=gtk_label_new("用户名不存在,请注册!");
		gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(L_dialog)->vbox),L_lbld);//标签加入到对话框里
		gtk_widget_show_all(L_dialog);//显示对话框里的信息
		if(gtk_dialog_run(GTK_DIALOG(L_dialog))==GTK_RESPONSE_OK)
		{
			gtk_widget_destroy(L_dialog);//ro不是or
		}
		gtk_entry_set_text(GTK_ENTRY(L_txt1),"");
		gtk_entry_set_text(GTK_ENTRY(L_txt2),"");
		registerInit();
	}
	else if(ret==1)
	{		
		if(!strcmp("",password))
		{
			L_dialog=gtk_dialog_new_with_buttons("提示",GTK_WINDOW(L_window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
			L_lbld=gtk_label_new("密码不能为空!");
			gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(L_dialog)->vbox),L_lbld);//标签加入到对话框里
			gtk_widget_show_all(L_dialog);//显示对话框里的信息
			if(gtk_dialog_run(GTK_DIALOG(L_dialog))==GTK_RESPONSE_OK)
			{
				gtk_widget_destroy(L_dialog);//ro不是or
			}
			return ;
		}
		//printf("登录成功!\n");
		strcpy(loginerName,gtk_entry_get_text(GTK_ENTRY(L_txt1)));
		char address[100];
		strcpy(address,loginerName);
		//submitAddressFromName(address);
		strcpy(loginerAddress,address);
		gtk_entry_set_text(GTK_ENTRY(L_txt1),"");
                gtk_entry_set_text(GTK_ENTRY(L_txt2),"");
		gtk_widget_hide(L_window);//隐藏窗体
		mailInit();
	}
	else
	{
		if(!strcmp("",password))
		{
			L_dialog=gtk_dialog_new_with_buttons("提示",GTK_WINDOW(L_window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
			L_lbld=gtk_label_new("密码不能为空!");
			gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(L_dialog)->vbox),L_lbld);//标签加入到对话框里
			gtk_widget_show_all(L_dialog);//显示对话框里的信息
			if(gtk_dialog_run(GTK_DIALOG(L_dialog))==GTK_RESPONSE_OK)
			{
				gtk_widget_destroy(L_dialog);//ro不是or
			}
			return ;
		}
		L_dialog=gtk_dialog_new_with_buttons("提示",GTK_WINDOW(L_window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
		L_lbld=gtk_label_new("密码不正确!");
		gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(L_dialog)->vbox),L_lbld);//标签加入到对话框里
		gtk_widget_show_all(L_dialog);//显示对话框里的信息
		if(gtk_dialog_run(GTK_DIALOG(L_dialog))==GTK_RESPONSE_OK)
		{
			gtk_widget_destroy(L_dialog);//ro不是or
		}
		//gtk_entry_set_text(GTK_ENTRY(L_txt1),"");
                gtk_entry_set_text(GTK_ENTRY(L_txt2),"");
	}
}

void L_btn2_on_clicked(GtkWidget *widget,gpointer data)
{	
	gtk_widget_hide(L_window);//隐藏窗体
	registerInit();
}

void loginInit()
{
	char title[]="登录";
	gtk_init(NULL,NULL);
	L_window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(L_window),title);
	gtk_widget_set_usize(L_window,300,180);
	//gtk_widget_set_uposition(L_window,400,200);
	gtk_window_set_position(GTK_WINDOW(L_window),GTK_WIN_POS_CENTER);
	//创建表格
	L_table0=gtk_table_new(3,1,FALSE);
	L_table1=gtk_table_new(2,2,FALSE);
	//创建标签
	L_lbl1=gtk_label_new("   用户名");
	L_lbl2=gtk_label_new("   密  码");
	L_lbln=gtk_label_new("  ");
	//创建文本框
	L_txt1=gtk_entry_new_with_max_length(50);
	L_txt2=gtk_entry_new_with_max_length(50);
	gtk_entry_set_visibility(GTK_ENTRY(L_txt2),FALSE);
	gtk_entry_set_invisible_char(GTK_ENTRY(L_txt2),'*');
	//创建按钮
	L_btn1=gtk_button_new_with_label("登录");
	L_btn2=gtk_button_new_with_label("注册");
	gtk_widget_set_size_request(L_btn1,150,30);
	gtk_widget_set_size_request(L_btn2,150,30);
	//创建分组框
	L_frame=gtk_frame_new(NULL);
	gtk_frame_set_shadow_type(GTK_FRAME(L_frame),GTK_SHADOW_ETCHED_IN);
	gtk_widget_set_size_request(L_frame,270,80);
	//把表格加入到窗体中
	gtk_container_add(GTK_CONTAINER(L_window),L_table0);
	gtk_container_add(GTK_CONTAINER(L_frame),L_table1);
	gtk_table_attach(GTK_TABLE(L_table1),L_lbl1,0,1,0,1,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(L_table1),L_lbl2,0,1,1,2,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(L_table1),L_txt1,1,2,0,1,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(L_table1),L_txt2,1,2,1,2,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(L_table0),L_frame,0,1,0,1,(GtkAttachOptions)(GTK_FILL|GTK_EXPAND),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(L_table0),L_btn1,0,1,1,2,(GtkAttachOptions)(GTK_FILL|GTK_EXPAND),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(L_table0),L_btn2,0,1,2,3,(GtkAttachOptions)(GTK_FILL|GTK_EXPAND),(GtkAttachOptions)(0),5,5);
	g_signal_connect(G_OBJECT(L_window),"destroy",G_CALLBACK(L_destroy),NULL);
	g_signal_connect(G_OBJECT(L_btn1),"clicked",G_CALLBACK(L_btn1_on_clicked),NULL);
	g_signal_connect(G_OBJECT(L_btn2),"clicked",G_CALLBACK(L_btn2_on_clicked),NULL);
	gtk_widget_show_all(L_window);
	gtk_main();
}
