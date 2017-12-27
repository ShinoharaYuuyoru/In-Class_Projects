#include "variable.h"
#include "database.h"
#include "formwindow.h"

void R_destroy(GtkWidget *widget,gpointer data)
{
	gtk_main_quit();//关闭窗体
	gtk_widget_show(L_window);//显示窗体
}

void R_show(GtkWidget *widget,gpointer data)
{
	//gtk_main_quit();
	//printf("fdsfds\n");
//	connectdb();
	showUserInfo();
}

void R_Clear(GtkWidget *widget,gpointer data)
{
	gtk_entry_set_text(GTK_ENTRY(R_txt1),"");
	gtk_entry_set_text(GTK_ENTRY(R_txt2),"");
	gtk_entry_set_text(GTK_ENTRY(R_txt3),"");
	gtk_entry_set_text(GTK_ENTRY(R_txt4),"");
	gtk_entry_set_text(GTK_ENTRY(R_txt5),"");	
}

void R_Insert(GtkWidget *widget,gpointer data)
{
	char name[100];
	char password[100];
	char address[100];
	char phone[100];
	strcpy(name,gtk_entry_get_text(GTK_ENTRY(R_txt1)));
	strcpy(password,gtk_entry_get_text(GTK_ENTRY(R_txt3)));
	strcpy(address,gtk_entry_get_text(GTK_ENTRY(R_txt2)));
	strcpy(phone,gtk_entry_get_text(GTK_ENTRY(R_txt5)));
	if(!strcmp(name,"")||!strcmp(password,"")||!strcmp(address,"")||!strcmp(phone,""))//空处理
	{
		R_dialog=gtk_dialog_new_with_buttons("提示",GTK_WINDOW(R_window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
		R_lbld=gtk_label_new("信息不完整,请检查!");
		gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(R_dialog)->vbox),R_lbld);//标签加入到对话框里
		gtk_widget_show_all(R_dialog);//显示对话框里的信息
		if(gtk_dialog_run(GTK_DIALOG(R_dialog))==GTK_RESPONSE_OK)
		{
       			gtk_widget_destroy(R_dialog);//ro不是or
			return;
		}
	}
	if(strcmp(password,gtk_entry_get_text(GTK_ENTRY(R_txt4))))//判断密码是否匹配相等
	{
		R_dialog=gtk_dialog_new_with_buttons("提示",GTK_WINDOW(R_window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
                R_lbld=gtk_label_new("密码不一致,请检查!");
                gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(R_dialog)->vbox),R_lbld);//标签加入到对话框里
                gtk_widget_show_all(R_dialog);//显示对话框里的信息
                if(gtk_dialog_run(GTK_DIALOG(R_dialog))==GTK_RESPONSE_OK)
                {
                        gtk_widget_destroy(R_dialog);//ro不是or
                        return;
                }	
	}
	//insertUserInfo(name,password,address,phone);
}

void registerInit()
{
	char title[]="用户注册";
	gtk_init(NULL,NULL);
	R_window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(R_window),title);
	gtk_widget_set_usize(R_window,700,250);
	gtk_window_set_position(GTK_WINDOW(R_window),GTK_WIN_POS_CENTER);
	//创建表格
	R_table=gtk_table_new(6,3,FALSE);
	//创建标签
	R_lbl1=gtk_label_new("*昵称:    ");
	R_lbl2=gtk_label_new("*邮件地址:");
	R_lbl3=gtk_label_new("*密码:    ");
	R_lbl4=gtk_label_new("*确认密码:");
	R_lbl5=gtk_label_new("*手机号码: ");
	R_lbl11=gtk_label_new("  最大12个字符(1个汉字占3个字符),不可以含有非法字符");
	R_lbl22=gtk_label_new("  6~16个字符,包括字母、数字、下划线、以字母开头");
	R_lbl33=gtk_label_new("    6~16个字符,包括字母、数字、特殊符号、区分大小写");
	R_lbl44=gtk_label_new("请再次输入密码");
	R_lbl55=gtk_label_new("密码遗忘或被选时可通过手机短信取回密码");
	//创建文本框
	R_txt1=gtk_entry_new_with_max_length(80);
	R_txt2=gtk_entry_new_with_max_length(80);
	R_txt3=gtk_entry_new_with_max_length(80);
	gtk_entry_set_visibility(GTK_ENTRY(R_txt3),FALSE);//设置密码框
        gtk_entry_set_invisible_char(GTK_ENTRY(R_txt3),'*');
	R_txt4=gtk_entry_new_with_max_length(80);
	gtk_entry_set_visibility(GTK_ENTRY(R_txt4),FALSE);
        gtk_entry_set_invisible_char(GTK_ENTRY(R_txt4),'*');
	R_txt5=gtk_entry_new_with_max_length(80);
	//创建分组框
	R_frame=gtk_frame_new("欢迎注册免费邮箱");
	gtk_frame_set_shadow_type(GTK_FRAME(R_frame),GTK_SHADOW_ETCHED_IN);
	//创建按钮
	R_btn1=gtk_button_new_with_label("提交");
	R_btn2=gtk_button_new_with_label("重置");
	R_btn3=gtk_button_new_with_label("显示");
	gtk_widget_set_size_request(R_btn1,150,30);
	gtk_widget_set_size_request(R_btn2,150,30);
	gtk_widget_set_size_request(R_btn3,100,30);
	//把表格加入到窗体中
	gtk_container_add(GTK_CONTAINER(R_window),R_frame);
	gtk_container_add(GTK_CONTAINER(R_frame),R_table);
	gtk_table_attach(GTK_TABLE(R_table),R_lbl1,0,1,0,1,(GtkAttachOptions)(GTK_FILL|GTK_EXPAND),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(R_table),R_lbl11,2,3,0,1,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(R_table),R_lbl2,0,1,1,2,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(R_table),R_lbl22,2,3,1,2,(GtkAttachOptions)(GTK_FILL|GTK_EXPAND),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(R_table),R_lbl3,0,1,2,3,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(R_table),R_lbl33,2,3,2,3,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(R_table),R_lbl4,0,1,3,4,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(R_table),R_lbl44,2,3,3,4,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(R_table),R_lbl5,0,1,4,5,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(R_table),R_lbl55,2,3,4,5,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(R_table),R_txt1,1,2,0,1,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(R_table),R_txt2,1,2,1,2,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(R_table),R_txt3,1,2,2,3,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(R_table),R_txt4,1,2,3,4,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(R_table),R_txt5,1,2,4,5,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(R_table),R_btn1,1,2,5,6,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(R_table),R_btn2,2,3,5,6,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	//gtk_table_attach(GTK_TABLE(R_table),R_btn3,0,1,5,6,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	g_signal_connect(G_OBJECT(R_window),"destroy",G_CALLBACK(R_destroy),NULL);
	g_signal_connect(G_OBJECT(R_btn3),"clicked",G_CALLBACK(R_show),R_table);
	g_signal_connect(G_OBJECT(R_btn1),"clicked",G_CALLBACK(R_Insert),R_table);
	g_signal_connect(G_OBJECT(R_btn2),"clicked",G_CALLBACK(R_Clear),R_table);
	gtk_widget_show_all(R_window);
	gtk_main();
}
