#include<gtk/gtk.h>
#include "include.h"
extern LoginCount;

//========global variable=====
gint timer;//timer

//*******************************************************************
//* Function Name :closeWin                          
//* Description   :用户点击X，退出窗口		          
//* Created       :12/09/02
//* Parameter     :GtkWidget *widget  窗口指针                     输入参数
//*		  :GdkEvent  *event   事件指针                     输入参数
//*		  :gpointer  data     回调函数输入参数        输入参数
//* Return Code   :gint               TRUE      不发送destroy信号
//*    				      FALSE     发送destroy信号给窗口
//* Author        :T3_shenyan
//*******************************************************************
gint closeWin(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	return FALSE;
}
//*******************************************************************
//* Function Name :destroy                          
//* Description   :退出gtk_run,结束进程		          
//* Created       :12/09/02
//* Parameter     :GtkWidget *widget  窗口指针                     输入参数
//*		  :gpointer  data     回调函数输入参数        输入参数
//* Return Code   :void
//* Author        :T3_shenyan
//*******************************************************************
void destroy(GtkWidget *widget, gpointer data)
{
	
	gtk_main_quit();
}
//*******************************************************************
//* Function Name :progress_timeout                          
//* Description   :定时计数器		          
//* Created       :12/09/02
//* Parameter     :gpointer  pbar     回调函数输入参数        输入参数
//* Return Code   :gint               TRUE      回调函数执行成功
//*    				      FALSE     回调函数执行失败
//* Author        :T3_shenyan
//*******************************************************************
gint progress_timeout( gpointer pbar )

{
	gtk_progress_bar_pulse (GTK_PROGRESS_BAR (pbar));//progress-bar pulse
	return TRUE;
}
//*******************************************************************
//* Function Name :btnLogin_clicked                        
//* Description   :登录按钮单击事件的回调函数		          
//* Created       :12/09/03
//* Parameter     :GtkWidget *widget  窗口指针              输入参数
//*		  :LOGIN     *login   窗口参数结构体指针     输出参数
//* Return Code   :void
//* Author        :T3_shenyan
//*******************************************************************
void btnLogin_clicked(GtkWidget *widget, LOGIN *login)
{
	if(LoginCount==0)//点击登陆一次，等待服务器回复 ，期间不响应登陆键
	{	
		MWIN *mwin;
		gtk_progress_bar_set_text(GTK_PROGRESS_BAR(login->pbar),"正在登陆......");//set the text of progress bar 
		timer = gtk_timeout_add (120, progress_timeout,login->pbar);//set timer state
		LoginCount+=1;
//================链接服务器，允许登陆执行，不允许无动作
		gtk_widget_hide(login->window);
		mwin=mainWin_creat(0);
		mainWin_run(mwin);
	}
}
//*******************************************************************
//* Function Name :btnRegister_clicked                         
//* Description   :注册按钮单击事件回调函数	          
//* Created       :12/09/03
//* Parameter     :GtkWidget *widget  窗口指针                     输入参数
//*		  :gpointer  data     回调函数输入参数        输入参数
//* Return Code   :void
//* Author        :T3_shenyan
//*******************************************************************
void btnRegister_clicked(GtkWidget *widget, gpointer data)
{
	if(LoginCount==0)//点击登陆一次，等待服务器回复，期间不响应注册键
	{
		REG *reg;
		LoginCount+=1;	
		reg=register_creat();
		register_run(reg);
	}
}
//*******************************************************************
//* Function Name :login_creat                        
//* Description   :创建登录窗口，配置窗口属性和参数		          
//* Created       :12/09/03
//* Parameter     :void
//* Return Code   :LOGIN*     窗口属性参数的结构体指针
//* Author        :T3_shenyan
//*******************************************************************
LOGIN* login_creat(void)
{
	LOGIN *login=(LOGIN*)malloc(sizeof(LOGIN));
//========window========
	login->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);//create a window
	gtk_window_set_title(GTK_WINDOW(login->window),"FlowerMail");
	gtk_window_set_position(GTK_WINDOW(login->window),GTK_WIN_POS_CENTER);//set the window at center of the screen
//=========box==========
	login->nameHBox=gtk_hbox_new(FALSE,0);
	login->pswHBox=gtk_hbox_new(FALSE,0);
	login->btnHBox=gtk_hbox_new(FALSE,0);
	login->NPVBox=gtk_vbox_new(FALSE,0);
//========widget========
	login->btnLogin=gtk_button_new_with_label("登陆");//create a login button
	login->btnRegister=gtk_button_new_with_label("注册");//create a register button
	login->lblUsrname=gtk_label_new("用户名：");//create a username label
	login->lblPasswd=gtk_label_new( "密  码：");//create a password label
	login->etyUsrname=gtk_entry_new();//create a username entry
	login->etyPasswd=gtk_entry_new();//creat a passwd entry
	login->pbar=gtk_progress_bar_new();//create a progress bar
	gtk_entry_set_max_length(GTK_ENTRY(login->etyUsrname),12);//maxsize of inserted text
	gtk_entry_set_visibility(GTK_ENTRY(login->etyPasswd),FALSE);//entered password invisible
	gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(login->pbar),GTK_PROGRESS_LEFT_TO_RIGHT);//set the bar moved from left to right
//========take into box======
	/*label & entry   ==>username*/
	gtk_box_pack_start(GTK_BOX(login->nameHBox),login->lblUsrname,TRUE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(login->nameHBox),login->etyUsrname,TRUE,FALSE,0);
	/*label & entry   ==>password*/
	gtk_box_pack_start(GTK_BOX(login->pswHBox),login->lblPasswd,TRUE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(login->pswHBox),login->etyPasswd,FALSE,FALSE,1);
	/*button          ==>login & register*/
	gtk_box_pack_start(GTK_BOX(login->btnHBox),login->btnLogin,TRUE,FALSE,3);
	gtk_box_pack_start(GTK_BOX(login->btnHBox),login->btnRegister,TRUE,FALSE,3);
	gtk_widget_show(login->btnRegister);
	/*box  into topbox   */
	gtk_box_pack_start(GTK_BOX(login->NPVBox),login->nameHBox,FALSE,FALSE,3);
	gtk_box_pack_start(GTK_BOX(login->NPVBox),login->pswHBox,FALSE,FALSE,3);	
	gtk_box_pack_start(GTK_BOX(login->NPVBox),login->btnHBox,FALSE,FALSE,3);
	gtk_box_pack_start(GTK_BOX(login->NPVBox),login->pbar,TRUE,TRUE,0);//progress_bar  to show "正在登陆....."
	/*topbox add to window*/
	gtk_container_add(GTK_CONTAINER(login->window),login->NPVBox);//add the topbox to window
//=======event & signal===========
	g_signal_connect(G_OBJECT(login->window),"delete_event",G_CALLBACK(closeWin),NULL);//close the window with a "delete_event" signal 
	g_signal_connect(G_OBJECT(login->window),"destroy",G_CALLBACK(destroy),NULL);//goto destroy function to quit gtk_main when gotten the signal "destroy";
	g_signal_connect(G_OBJECT(login->btnLogin),"clicked",G_CALLBACK(btnLogin_clicked),login);
	g_signal_connect(G_OBJECT(login->btnRegister),"clicked",G_CALLBACK(btnRegister_clicked),NULL);
	return login;
}
//*******************************************************************
//* Function Name :login_run                         
//* Description   :显示窗口		          
//* Created       :12/09/03
//* Parameter     :LOGIN*        login  窗口属性参数结构体指针
//* Return Code   :void           
//* Author        :T3_shenyan
//*******************************************************************
void login_run(LOGIN *login)
{
	gtk_widget_show_all(login->window);
}
