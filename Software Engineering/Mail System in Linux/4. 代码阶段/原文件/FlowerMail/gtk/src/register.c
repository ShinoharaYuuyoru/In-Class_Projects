#include<gtk/gtk.h>
#include"include.h"
extern LoginCount;
//**********注册****************
/****************事件处理***********/
void btnConf_clicked(GtkWidget *widget, gpointer data)
{
	
}
void btnCancl_clicked(GtkWidget *widget, REG *reg)
{
	LoginCount-=1;
	gtk_widget_destroy(reg->window);
}
gint cancel(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	LoginCount=0;
	return FALSE;
}

/**********************************/


REG* register_creat()
{
	REG *reg=(REG*)malloc(sizeof(REG));
//==========window=============
	reg->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);//create a register window
	gtk_window_set_title(GTK_WINDOW(reg->window),"注册");//set title of the window
	gtk_window_set_default_size(GTK_WINDOW(reg->window),500,400);//set default size of the window
	gtk_window_set_position(GTK_WINDOW(reg->window),GTK_WIN_POS_CENTER);//set position of the window
//===========box===============
	reg->nameHBox=gtk_hbox_new(FALSE,0);
	reg->pswHBox=gtk_hbox_new(FALSE,0);
	reg->cfpswHBox=gtk_hbox_new(FALSE,0);
	reg->sfcdHBox=gtk_hbox_new(FALSE,0);
	reg->btnHBox=gtk_hbox_new(FALSE,0);
	reg->NPCSVBox=gtk_vbox_new(FALSE,0);
//===========widget============
 	reg->lblUsrname=gtk_label_new("用户名：");//create a username label
	reg->lblPasswd=gtk_label_new( " 密  码： ");//create a password label
	reg->lblCfpsw=gtk_label_new("确认密码：");//create a confirm-password label
	reg->lblSafcod=gtk_label_new("安全码：");//create a safecod label
	reg->etyUsrname=gtk_entry_new();//create a username entry
	reg->etyPasswd=gtk_entry_new();//create a password entry
	reg->etyCfpsw=gtk_entry_new();//create a confirm-password entry
	reg->etySafcod=gtk_entry_new();//create a safecode entry
	reg->btnConf=gtk_button_new_with_label("确认");//create a button with label "确认" for confirming
	reg->btnCancl=gtk_button_new_with_label("取消");//create a button with label "取消" for cancelling
	gtk_entry_set_max_length(GTK_ENTRY(reg->etyUsrname),12);//set the max sizeof inserted text of entry "etyUsrname"
//========take into box=======
	gtk_box_pack_start(GTK_BOX(reg->nameHBox),reg->lblUsrname,TRUE,FALSE,10);
	gtk_box_pack_start(GTK_BOX(reg->nameHBox),reg->etyUsrname,TRUE,FALSE,10);
	gtk_box_pack_start(GTK_BOX(reg->pswHBox),reg->lblPasswd,TRUE,FALSE,10);
	gtk_box_pack_start(GTK_BOX(reg->pswHBox),reg->etyPasswd,TRUE,FALSE,10);
	gtk_box_pack_start(GTK_BOX(reg->cfpswHBox),reg->lblCfpsw,TRUE,FALSE,10);
	gtk_box_pack_start(GTK_BOX(reg->cfpswHBox),reg->etyCfpsw,TRUE,FALSE,10);
	gtk_box_pack_start(GTK_BOX(reg->sfcdHBox),reg->lblSafcod,TRUE,FALSE,10);
	gtk_box_pack_start(GTK_BOX(reg->sfcdHBox),reg->etySafcod,TRUE,FALSE,10);
	gtk_box_pack_start(GTK_BOX(reg->btnHBox),reg->btnConf,TRUE,FALSE,10);
	gtk_box_pack_start(GTK_BOX(reg->btnHBox),reg->btnCancl,TRUE,FALSE,10);
	gtk_box_pack_start(GTK_BOX(reg->NPCSVBox),reg->nameHBox,FALSE,FALSE,10);
	gtk_box_pack_start(GTK_BOX(reg->NPCSVBox),reg->pswHBox,FALSE,FALSE,10);
	gtk_box_pack_start(GTK_BOX(reg->NPCSVBox),reg->cfpswHBox,FALSE,FALSE,10);
	gtk_box_pack_start(GTK_BOX(reg->NPCSVBox),reg->sfcdHBox,FALSE,FALSE,10);
	gtk_box_pack_start(GTK_BOX(reg->NPCSVBox),reg->btnHBox,FALSE,FALSE,10);
	gtk_container_add(GTK_CONTAINER(reg->window),reg->NPCSVBox);
//========event & signal=====
	g_signal_connect(G_OBJECT(reg->window),"delete_event",G_CALLBACK(cancel),NULL);//close the window with a "delete_event" signal 
	g_signal_connect(G_OBJECT(reg->btnConf),"clicked",G_CALLBACK(btnConf_clicked),reg);
	g_signal_connect(G_OBJECT(reg->btnCancl),"clicked",G_CALLBACK(btnCancl_clicked),reg);
	return reg;
}
void register_run(REG *reg)
{
	gtk_widget_show_all(reg->window);
}