#include<gtk/gtk.h>
#include"include.h"
//#include"interface.h"
//#include"write.h"
#include<stdio.h>
#include<string.h>
//*******************************************************************
//* Function Name :theme_conf                       
//* Description   :用户主题默认选择配置函数	          
//* Created       :12/09/09
//* Parameter     :MWIN      *mwin    窗口属性参数结构体指针  输出参数
//*		  :gint      isTheme  主题判断参数           输入参数
//* Return Code   :void
//* Author        :T3_shenyan
//*******************************************************************
void theme_conf(MWIN *mwin,gint isTheme)
{
	if(1==isTheme)
	{
		gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(mwin->tlNew),GTK_WIDGET(mwin->theme1->New));
		gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(mwin->tlRcv),GTK_WIDGET(mwin->theme1->Rcv));
		gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(mwin->tlDel),GTK_WIDGET(mwin->theme1->Del));
		gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(mwin->tlFind),GTK_WIDGET(mwin->theme1->Find));
		gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(mwin->tlThem),GTK_WIDGET(mwin->theme1->Them));
	}
	if(2==isTheme)
	{
		gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(mwin->tlNew),GTK_WIDGET(mwin->theme2->New));
		gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(mwin->tlRcv),GTK_WIDGET(mwin->theme2->Rcv));
		gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(mwin->tlDel),GTK_WIDGET(mwin->theme2->Del));
		gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(mwin->tlFind),GTK_WIDGET(mwin->theme2->Find));
		gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(mwin->tlThem),GTK_WIDGET(mwin->theme2->Them));
	}
}
//*******************************************************************
//* Function Name :tree_changed                       
//* Description   :邮箱树状图列表项焦点改变事件回调函数		          
//* Created       :12/09/07
//* Parameter     :GtkWidget *widget  窗口指针                             输入参数
//*		  :MWIN      *mwin    窗口属性参数结构体指针      输出参数
//* Return Code   :void
//* Author        :T3_shenyan
//*******************************************************************
void tree_changed(GtkWidget *widget, MWIN* mwin)
{
	GtkTreeIter iter;
	GtkTreeModel *model;
	char *value;
	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(widget), &model, &iter)) 
	{
		gtk_tree_model_get(model, &iter, 0, &value, -1);
		if(0==strcmp(value,"发件箱"))
				gtk_tree_view_column_set_title(GTK_TREE_VIEW_COLUMN(mwin->column1),"收件人\t\t");
				
		else if(0==strcmp(value,"全部邮件"))
				gtk_tree_view_column_set_title(GTK_TREE_VIEW_COLUMN(mwin->column1),"发件人\t\t");
		else if(0==strcmp(value,"未读邮件"))
				gtk_tree_view_column_set_title(GTK_TREE_VIEW_COLUMN(mwin->column1),"发件人\t\t");
		else if(0==strcmp(value,"收件箱"))
				gtk_tree_view_column_set_title(GTK_TREE_VIEW_COLUMN(mwin->column1),"发件人\t\t");
		else if(0==strcmp(value,"草稿箱"))
				gtk_tree_view_column_set_title(GTK_TREE_VIEW_COLUMN(mwin->column1),"收件人\t\t");	
		else if(0==strcmp(value,"垃圾箱"))
				gtk_tree_view_column_set_title(GTK_TREE_VIEW_COLUMN(mwin->column1),"发件人\t\t");		
		else 
				printf("error!!!!\n");
		g_free(value);
	}
}
//*******************************************************************
//* Function Name :list_changed                       
//* Description   :邮箱邮件列表项焦点改变事件回调函数		          
//* Created       :12/09/09
//* Parameter     :GtkWidget *widget  窗口指针                             输入参数
//*		  :MWIN      *mwin    窗口属性参数结构体指针      输出参数
//* Return Code   :void
//* Author        :T3_shenyan
//*******************************************************************
void list_changed(GtkWidget *widget, MWIN* mwin)
{
}
//*******************************************************************
//* Function Name :btnClose_clicked                       
//* Description   :笔记本控件标签条关闭按钮单击事件回调函数		          
//* Created       :12/09/07
//* Parameter     :GtkWidget *widget  窗口指针                输入参数
//*		  :MWIN      *mwin    窗口属性参数结构体指针   输出参数
//* Return Code   :void
//* Author        :T3_shenyan
//*******************************************************************
void btnClose_clicked(GtkButton   *button,GtkNotebook *notebook )
{


    gint page;
    
    page = gtk_notebook_get_current_page (notebook);
	printf("%d\n",page);
    gtk_notebook_remove_page (notebook, page);
    /* 需要刷新构件 -- 
     这会迫使构件重绘自身。 */
    //gtk_widget_queue_draw (GTK_WIDGET (notebook));


}
//*******************************************************************
//* Function Name :close_win                          
//* Description   :用户点击X，退出窗口		          
//* Created       :12/09/04
//* Parameter     :GtkWidget *widget  窗口指针                              输入参数
//*		  :MWIN      *mwin    窗口属性参数结构体指针       输入参数
//* Return Code   :gint               TRUE      不发送destroy信号
//*    				      FALSE     发送destroy信号给窗口
//* Author        :T3_shenyan
//*******************************************************************
gint close_win(GtkWidget *widget,MWIN *mwin)
{
	GtkWidget *dialog;
	gint isOK=0;
	dialog = gtk_message_dialog_new(GTK_WINDOW(mwin->window),GTK_DIALOG_MODAL,GTK_MESSAGE_QUESTION,GTK_BUTTONS_OK_CANCEL,"确定要退出程序吗？");//模态有点问题
	isOK=gtk_dialog_run(GTK_DIALOG(dialog));
	if(isOK==GTK_RESPONSE_OK)
	{
		gtk_main_quit();
	}
	if(isOK==GTK_RESPONSE_CANCEL)
	{
		gtk_widget_destroy(dialog);
	}
	return TRUE;
}
//*******************************************************************
//* Function Name :btntlNew_clicked                        
//* Description   :工具条新建按钮单击事件回调函数		          
//* Created       :12/09/04
//* Parameter     :GtkWidget *widget  窗口指针                             输入参数
//*		  :MWIN      *mwin    窗口属性参数结构体指针      输出参数
//* Return Code   :void
//* Author        :T3_shenyan
//*******************************************************************
void btntlNew_clicked(GtkWidget *widget,MWIN *mwin)
{
	gint i=0;
	GtkWidget *lblHBox;
	GtkWidget *image;
	GtkWidget *image_close;
	GtkWidget *btnClose;
	btnClose=gtk_button_new();
//================test button===========用后删除	
	GtkWidget *button;
	button=gtk_button_new_with_label("huadasb");
	 gtk_widget_set_size_request (button, 100, 75);
    gtk_widget_show (button);
//=======================================
	//GtkWidget *WRwin;
	//WRwin=write();
	//MWIN all[20];
	lblHBox=gtk_hbox_new(FALSE,0);
	gtk_widget_set_size_request(lblHBox,120,20);
	image=gtk_image_new_from_stock(GTK_STOCK_EDIT,GTK_ICON_SIZE_SMALL_TOOLBAR);
	image_close=gtk_image_new_from_stock(GTK_STOCK_CLOSE,GTK_ICON_SIZE_MENU);
	mwin->labelNew=gtk_label_new("  新建邮件   ");
	gtk_button_set_image(GTK_BUTTON(btnClose),image_close);
	gtk_button_set_relief(GTK_BUTTON(btnClose),GTK_RELIEF_NONE);
	gtk_box_pack_start(GTK_BOX(lblHBox),image,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(lblHBox),mwin->labelNew,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(lblHBox),btnClose,FALSE,FALSE,0);
	gtk_widget_show_all(lblHBox);
	i=gtk_notebook_get_current_page(GTK_NOTEBOOK(mwin->notebook));
	gtk_notebook_insert_page(GTK_NOTEBOOK(mwin->notebook),button,lblHBox,i+1);//insert new page
	gtk_notebook_set_current_page(GTK_NOTEBOOK(mwin->notebook),i+1);
	g_signal_connect(G_OBJECT (btnClose),"clicked",G_CALLBACK (btnClose_clicked),mwin->notebook);
}
//*******************************************************************
//* Function Name :btntlDel_clicked                        
//* Description   :工具条删除按钮单击事件回调函数		          
//* Created       :12/09/09
//* Parameter     :GtkWidget *widget  窗口指针                输入参数
//*		  :MWIN      *mwin    窗口属性参数结构体指针   输出参数
//* Return Code   :void
//* Author        :T3_shenyan
//*******************************************************************
void btntlDel_clicked(GtkWidget *widget,MWIN *mwin)
{
	GtkTreeSelection *selection;	
	GtkTreeIter iter;
	GtkTreeModel *model;
	char *value;
	selection=gtk_tree_view_get_selection(GTK_TREE_VIEW(mwin->listview));
	if(gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter))
	{
		gtk_list_store_remove(GTK_LIST_STORE(mwin->liststore),&iter);
	}
	else
	{
		printf("None Mail!\n");
	}
}
//*******************************************************************
//* Function Name :btntlFind_clicked                        
//* Description   :工具条查找按钮单击事件回调函数		          
//* Created       :12/09/04
//* Parameter     :GtkWidget *widget  窗口指针                输入参数
//*		  :MWIN      *mwin    窗口属性参数结构体指针   输出参数
//* Return Code   :void
//* Author        :T3_shenyan
//*******************************************************************
void btntlFind_clicked(GtkWidget *widget,MWIN *mwin)
{
	


}
//*******************************************************************
//* Function Name :btntlThem_clicked                        
//* Description   :工具条主题按钮单击事件回调函数		          
//* Created       :12/09/07
//* Parameter     :GtkWidget *widget  窗口指针                输入参数
//*		  :MWIN      *mwin    窗口属性参数结构体指针   输出参数
//* Return Code   :void
//* Author        :T3_shenyan
//*******************************************************************
void btntlThem_clicked(GtkWidget *widget,MWIN *mwin)
{
	theme_creat(mwin);
}
//*******************************************************************
//* Function Name :on_button_press_event                       
//* Description   :列表项双击事件回调函数		          
//* Created       :12/09/07
//* Parameter     :GtkWidget *widget       窗口指针           输入参数
//*		  :GdkEventButton *event   事件指针 	     输入参数
//*		  :gpointer  data          回调函数参数       输入参数    
//* Return Code   :void
//* Author        :T3_shenyan
//*******************************************************************
gboolean on_button_press_event(GtkWidget *widget,   GdkEventButton  *event, gpointer data)
{    
	if ((event->type == GDK_2BUTTON_PRESS )&&( event->button == 0x1)) 
	{        
		printf("double click left mouse\n");   
	}
        if ((event->type == GDK_2BUTTON_PRESS) && (event->button == 0x3))
        {
        	printf("double click right mouse\n");
	}    
	return FALSE;
}
//*******************************************************************
//* Function Name :init_list                          
//* Description   :初始化树状图		          
//* Created       :12/09/04
//* Parameter     :MWIN*        mwin   窗口属性参数结构体指针  输出参数
//*               :gint         i      树状图类型判断变量      输入参数
//* Return Code   :void
//* Author        :T3_shenyan
//*******************************************************************
void init_list(MWIN *mwin,gint i)
{
	
	GtkTreeIter child;
	GtkTreeIter top;	
	mwin->renderer=gtk_cell_renderer_text_new();//create a renderer
	if(0==i)
	{
		mwin->listview=gtk_tree_view_new();//create a list view
		mwin->column1=gtk_tree_view_column_new_with_attributes("发件人\t\t",mwin->renderer, "text",0,NULL);//create a column with some attributes
		mwin->column2=gtk_tree_view_column_new_with_attributes("主题\t\t\t\t\t\t\t\t",mwin->renderer, "text",1,NULL);//create a column with some attributes
		mwin->column3=gtk_tree_view_column_new_with_attributes("日期\t",mwin->renderer, "text",2,NULL);//create a column with some attributes
		gtk_tree_view_append_column(GTK_TREE_VIEW(mwin->listview),mwin->column1);//add the column to the list
		gtk_tree_view_append_column(GTK_TREE_VIEW(mwin->listview),mwin->column2);//add the column to the list
		gtk_tree_view_append_column(GTK_TREE_VIEW(mwin->listview),mwin->column3);//add the column to the list
		mwin->liststore=gtk_list_store_new(3,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);//create a store,it declare how much column we need 
		gtk_tree_view_set_model(GTK_TREE_VIEW(mwin->listview),GTK_TREE_MODEL(mwin->liststore));//link the store with the list
		g_object_unref(G_OBJECT(mwin->liststore));//destroy the column ,store and renderer when the list destroyed
	}
	if(1==i)
	{
		mwin->treeview=gtk_tree_view_new();//create a tree view to display type of mailbox		
		mwin->column4=gtk_tree_view_column_new_with_attributes("欢迎使用",mwin->renderer, "text",0,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(mwin->treeview),mwin->column4);
		mwin->treestore=gtk_tree_store_new(1,G_TYPE_STRING);
		gtk_tree_store_append(mwin->treestore,&top,NULL);
		gtk_tree_store_set(mwin->treestore,&top,0,"收件箱",-1);
		gtk_tree_store_append(mwin->treestore,&child,&top);
		gtk_tree_store_set(mwin->treestore,&child,0,"全部邮件",-1);
		gtk_tree_store_append(mwin->treestore,&child,&top);
		gtk_tree_store_set(mwin->treestore,&child,0,"未读邮件",-1);
		gtk_tree_store_append(mwin->treestore,&top,NULL);
		gtk_tree_store_set(mwin->treestore,&top,0,"草稿箱",-1);
		gtk_tree_store_append(mwin->treestore,&top,NULL);
		gtk_tree_store_set(mwin->treestore,&top,0,"发件箱",-1);
		gtk_tree_store_append(mwin->treestore,&top,NULL);
		gtk_tree_store_set(mwin->treestore,&top,0,"垃圾箱",-1);
		gtk_tree_view_set_model(GTK_TREE_VIEW(mwin->treeview),GTK_TREE_MODEL(mwin->treestore));
		g_object_unref(GTK_TREE_MODEL(mwin->treestore));
	}
}
//*******************************************************************
//* Function Name :add_to_list                        
//* Description   :邮件窗口列表项添加函数		          
//* Created       :12/09/03
//* Parameter     :MWIN*           mwin    窗口属性参数结构体指针    输出参数
//*		  :const gchar*    sender  收、发件人姓名字符串       输入参数
//*		  :const gchar*    subject 收、发邮件主题字符串       输入参数
//*		  :const gchar*    date    收、发邮件日期字符串       输入参数
//* Return Code   :void
//* Author        :T3_shenyan
//*******************************************************************
void add_to_list(MWIN *mwin,const gchar *sender,const gchar *subject,const gchar *date)
{
	GtkTreeIter iter;
	gtk_list_store_append(mwin->liststore,&iter);//create a empty row
	gtk_list_store_set(mwin->liststore,&iter,0,sender,1,subject,2,date,-1);//add the string on the end of list
}
//*******************************************************************
//* Function Name :mainWin_creat                       
//* Description   :新建并配置主窗口属性参数		          
//* Created       :12/09/03
//* Parameter     :void
//* Return Code   :MWIN*            
//* Author        :T3_shenyan
//*******************************************************************
MWIN* mainWin_creat(gint isTheme)
{
	MWIN *mwin=(MWIN*)calloc(1,sizeof(MWIN));
	mwin->theme1=(THEME*)calloc(1,sizeof(THEME));
	mwin->theme2=(THEME*)calloc(1,sizeof(THEME));
	GtkTreeSelection *selection;
	GtkTreeSelection *selection1;
//=============test===========

//=========window=========
	mwin->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);//create a window
	gtk_window_set_title(GTK_WINDOW(mwin->window),"FlowerMali邮件客户端");//set title of this window
	gtk_window_set_resizable (GTK_WINDOW (mwin->window), FALSE);//set the window user unresizable
	gtk_widget_set_size_request(GTK_WIDGET(mwin->window),800,600);//set the default size of this window
	gtk_window_set_position(GTK_WINDOW(mwin->window),GTK_WIN_POS_CENTER);//set position of the window
	mwin->scrwin1=gtk_scrolled_window_new(NULL, NULL);//create a scrolled window
	mwin->scrwin2=gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (mwin->scrwin1),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);//set the scrolled window automatic
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (mwin->scrwin2),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	GTK_WINDOW(mwin->window)->allow_shrink = FALSE;//do not allow to shrink
//==========box===========
	mwin->allVBox=gtk_vbox_new(FALSE,0);//create a vbox contains all widgets
	mwin->HomeBox=gtk_hbox_new(FALSE,0);
	gtk_widget_set_size_request(mwin->HomeBox,120,20);
//=========widget=========
/************toolbar************/
	mwin->toolbar=gtk_toolbar_new();//create a toolbar
	gtk_toolbar_set_style(GTK_TOOLBAR(mwin->toolbar),GTK_TOOLBAR_ICONS);//set the style of toolbar
	mwin->tlNew=gtk_tool_button_new_from_stock(GTK_STOCK_NEW);//create a toolbutton NEW 
	gtk_toolbar_insert(GTK_TOOLBAR(mwin->toolbar),mwin->tlNew,-1);//insert NEW button into toolbar
	mwin->tlRcv=gtk_tool_button_new_from_stock(GTK_STOCK_GOTO_BOTTOM);
	gtk_toolbar_insert(GTK_TOOLBAR(mwin->toolbar),mwin->tlRcv,-1);
	mwin->tlDel=gtk_tool_button_new_from_stock(GTK_STOCK_DELETE);
	gtk_toolbar_insert(GTK_TOOLBAR(mwin->toolbar),mwin->tlDel,-1);
	mwin->tlFind=gtk_tool_button_new_from_stock(GTK_STOCK_FIND);
	gtk_toolbar_insert(GTK_TOOLBAR(mwin->toolbar),mwin->tlFind,-1);
	mwin->tlThem=gtk_tool_button_new_from_stock(GTK_STOCK_SELECT_COLOR);
	gtk_toolbar_insert(GTK_TOOLBAR(mwin->toolbar),mwin->tlThem,-1);
	
/************treeview**************/	
	init_list(mwin,0);	
	init_list(mwin,1);
	selection=gtk_tree_view_get_selection(GTK_TREE_VIEW(mwin->treeview));
	selection1=gtk_tree_view_get_selection(GTK_TREE_VIEW(mwin->listview));
/************notebook***************/
	mwin->lblIndex=gtk_label_new("  主  页  ");//notebook's label
	mwin->HomeImage=gtk_image_new_from_stock(GTK_STOCK_HOME,GTK_ICON_SIZE_SMALL_TOOLBAR);
	gtk_box_pack_start(GTK_BOX(mwin->HomeBox),mwin->HomeImage,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(mwin->HomeBox),mwin->lblIndex,FALSE,FALSE,0);
	gtk_widget_show_all(mwin->HomeBox);
	add_to_list(mwin,"发件人          ","主题                                                 ","日期    ");//存在问题 add_to_list
	mwin->panPri=gtk_hpaned_new();//notebook's primary paned
	mwin->panMin=gtk_vpaned_new();//notebook's minor paned
	mwin->notebook=gtk_notebook_new();//create a notebook
	gtk_notebook_set_scrollable(GTK_NOTEBOOK(mwin->notebook),TRUE);//set the notebook automatic srolled
	gtk_paned_set_position(GTK_PANED(mwin->panMin),350);//设置分栏窗口2个部分的比例
	gtk_paned_set_position(GTK_PANED(mwin->panPri),150);
	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(mwin->notebook),GTK_POS_TOP);//set the position of notebook's tab
	gtk_notebook_insert_page(GTK_NOTEBOOK(mwin->notebook),mwin->panPri,mwin->HomeBox,0);
/************textview**************/
	mwin->txtview=gtk_text_view_new();//create a text view 
	gtk_text_view_set_editable(GTK_TEXT_VIEW(mwin->txtview),FALSE);//set the textview uneditable
/***********button***************/
	
//======take into box=====
	gtk_container_add(GTK_CONTAINER(mwin->scrwin1),mwin->listview);
	gtk_paned_add1(GTK_PANED(mwin->panMin),mwin->scrwin1);
	gtk_container_add(GTK_CONTAINER(mwin->scrwin2),mwin->txtview);
	gtk_paned_add2(GTK_PANED(mwin->panMin),mwin->scrwin2);
	gtk_paned_add1(GTK_PANED(mwin->panPri),mwin->treeview);
	gtk_paned_add2(GTK_PANED(mwin->panPri),mwin->panMin);
	gtk_box_pack_start(GTK_BOX(mwin->allVBox),mwin->toolbar,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(mwin->allVBox),mwin->notebook,TRUE,TRUE,0);
	gtk_container_add(GTK_CONTAINER(mwin->window),mwin->allVBox);
//======event & signal====
	g_signal_connect(G_OBJECT(mwin->window),"delete_event",G_CALLBACK(close_win),NULL);//close the window with a "delete_event" signal
	g_signal_connect(G_OBJECT(mwin->tlNew),"clicked",G_CALLBACK(btntlNew_clicked),mwin);//toolbar button tlNew -> create
	g_signal_connect(G_OBJECT(mwin->tlThem),"clicked",G_CALLBACK(btntlThem_clicked),mwin);//toolbar button tlThem ->theme
	g_signal_connect(G_OBJECT(mwin->tlFind),"clicked",G_CALLBACK(btntlFind_clicked),mwin);//toolbar button tlFind ->find mail
	g_signal_connect(G_OBJECT(mwin->tlDel),"clicked",G_CALLBACK(btntlDel_clicked),mwin);//toolbar button tiDel ->del main
	g_signal_connect(selection, "changed", G_CALLBACK(tree_changed),mwin);
	g_signal_connect(selection1,"changed",G_CALLBACK(list_changed),mwin);
//=======theme===========
	mwin->theme1->New=gtk_image_new_from_file("../src/icon1/newmail.png");
	mwin->theme1->Rcv=gtk_image_new_from_file("../src/icon1/receivemail.png");
	mwin->theme1->Del=gtk_image_new_from_file("../src/icon1/delete.png");
	mwin->theme1->Find=gtk_image_new_from_file("../src/icon1/findinmail.png");
	mwin->theme1->Them=gtk_image_new_from_file("../src/icon1/color.png");
	mwin->theme2->New=gtk_image_new_from_file("../src/icon2/newmail.png");
	mwin->theme2->Rcv=gtk_image_new_from_file("../src/icon2/receivemail.png");
	mwin->theme2->Del=gtk_image_new_from_file("../src/icon2/delete.png");
	mwin->theme2->Find=gtk_image_new_from_file("../src/icon2/findinmail.png");
	mwin->theme2->Them=gtk_image_new_from_file("../src/icon2/color.png");
	theme_conf(mwin,isTheme);
	return mwin;
}
//*******************************************************************
//* Function Name :mainWin_run                     
//* Description   :显示主窗口		          
//* Created       :12/09/03
//* Parameter     :MWIN*         mwin    窗口属性参数结构体指针    输出参数
//* Return Code   :void
//* Author        :T3_shenyan
//*******************************************************************
void mainWin_run(MWIN *mwin)
{
	gtk_widget_show_all(mwin->window);
}
