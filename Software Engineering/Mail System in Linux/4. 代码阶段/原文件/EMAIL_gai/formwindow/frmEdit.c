#include "variable.h"
#include "database.h"
#include "formwindow.h"

void E_init_list()
{
  E_renderer = gtk_cell_renderer_text_new();
  E_column = gtk_tree_view_column_new_with_attributes(" ▽ 联系人",E_renderer, "text", 0, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(E_list), E_column);
  E_store = gtk_list_store_new(1, G_TYPE_STRING);
  gtk_tree_view_set_model(GTK_TREE_VIEW(E_list),GTK_TREE_MODEL(E_store));
}

void E_add_to_list(gchar *str)
{
  E_store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(E_list)));
  gtk_list_store_append(E_store, &E_iter);
  gtk_list_store_set(E_store, &E_iter, 0, str, -1);
}

void E_add_list()
{
	E_list=gtk_tree_view_new();
	E_scrolled_list = gtk_scrolled_window_new(NULL,NULL);//生成滚动条的窗口
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(E_scrolled_list),GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);//滚动条属性
        gtk_container_add(GTK_CONTAINER(E_scrolled_list),E_list);
	//gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(E_list), FALSE);  
	E_init_list();
	//E_add_to_list("	李逍遥");
	//E_add_to_list("	林月如");
	//E_add_to_list("	赵灵儿");
	//E_add_to_list("	阿奴");
	showListName();
}

void E_init_menu()//创建菜单
{
        E_accel_group=gtk_accel_group_new();
        E_menubar=gtk_menu_bar_new();
        E_menuitem1=gtk_menu_item_new_with_mnemonic("文件(_F)");
        E_menuitem10=gtk_menu_new();
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(E_menuitem1),E_menuitem10);
	E_menuitem11=gtk_menu_item_new_with_mnemonic("新建(_N)");
        gtk_widget_add_accelerator(E_menuitem11,"activate",E_accel_group,GDK_N,(GdkModifierType)GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
	E_separatormenuitem1=(GtkWidget*)gtk_separator_menu_item_new();
	E_menuitem12=gtk_menu_item_new_with_mnemonic("保存(_S)");
        gtk_widget_add_accelerator(E_menuitem12,"activate",E_accel_group,GDK_S,(GdkModifierType)GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
	E_menuitem13=gtk_menu_item_new_with_mnemonic("发送(_X)");
        gtk_widget_add_accelerator(E_menuitem13,"activate",E_accel_group,GDK_X,(GdkModifierType)GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
	E_separatormenuitem2=(GtkWidget*)gtk_separator_menu_item_new();
	E_menuitem19=gtk_menu_item_new_with_mnemonic("关闭(_E)");
        gtk_widget_add_accelerator(E_menuitem19,"activate",E_accel_group,GDK_E,(GdkModifierType)GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
        E_menuitem2=gtk_menu_item_new_with_mnemonic("编辑(_E)");
        E_menuitem20=gtk_menu_new();
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(E_menuitem2),E_menuitem20);
	E_menuitem21=gtk_menu_item_new_with_mnemonic("颜色(_C)");
        gtk_widget_add_accelerator(E_menuitem21,"activate",E_accel_group,GDK_C,(GdkModifierType)GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
	E_menuitem22=gtk_menu_item_new_with_mnemonic("字体(_F)");
        gtk_widget_add_accelerator(E_menuitem22,"activate",E_accel_group,GDK_F,(GdkModifierType)GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
	E_separatormenuitem3=(GtkWidget*)gtk_separator_menu_item_new();
	//E_menuitem23=gtk_menu_item_new_with_mnemonic("附件(_B)");
        //gtk_widget_add_accelerator(E_menuitem23,"activate",E_accel_group,GDK_B,(GdkModifierType)GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
        E_menuitem3=gtk_menu_item_new_with_mnemonic("帮助(_H)");
        E_menuitem30=gtk_menu_new();
	E_menuitem31=gtk_menu_item_new_with_mnemonic("关于(_A)");
        gtk_widget_add_accelerator(E_menuitem31,"activate",E_accel_group,GDK_A,(GdkModifierType)GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(E_menuitem3),E_menuitem30);
        gtk_container_add(GTK_CONTAINER(E_menuitem10),E_menuitem11);
        gtk_container_add(GTK_CONTAINER(E_menuitem10),E_separatormenuitem1);
        gtk_container_add(GTK_CONTAINER(E_menuitem10),E_menuitem12);
        gtk_container_add(GTK_CONTAINER(E_menuitem10),E_menuitem13);
        gtk_container_add(GTK_CONTAINER(E_menuitem10),E_separatormenuitem2);
        gtk_container_add(GTK_CONTAINER(E_menuitem10),E_menuitem19);
        gtk_container_add(GTK_CONTAINER(E_menuitem20),E_menuitem21);
        gtk_container_add(GTK_CONTAINER(E_menuitem20),E_menuitem22);
        gtk_container_add(GTK_CONTAINER(E_menuitem30),E_menuitem31);
        //gtk_container_add(GTK_CONTAINER(E_menuitem20),E_separatormenuitem3);
        //gtk_container_add(GTK_CONTAINER(E_menuitem20),E_menuitem23);
        gtk_container_add(GTK_CONTAINER(E_menubar),E_menuitem1);
        gtk_container_add(GTK_CONTAINER(E_menubar),E_menuitem2);
        gtk_container_add(GTK_CONTAINER(E_menubar),E_menuitem3);
}

void E_destroy(GtkWidget *widget,gpointer data)
{
	gtk_main_quit();
	gtk_widget_show(M_window);
}

void E_toolbtn1_on_clicked(GtkWidget *widget,gpointer data)
{
	gtk_entry_set_text(GTK_ENTRY(E_txt1),"");
	gtk_entry_set_text(GTK_ENTRY(E_txt2),"");
	gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(E_txt3)),"",-1);
}

void E_toolbtn2_on_clicked(GtkWidget *widget,gpointer selection)
{
        //printf("in\n");
        GtkTreeIter iter;
        GtkTreeModel *model;
        GtkTextBuffer *buffer;//缓冲区
        GtkTextIter start,end;
        char title[50];
        char sper[50];
        char sadd[50];
        char *rper;
        char radd[50];
        char *content;//文本视图取出的指针类型
        strcpy(title,gtk_entry_get_text(GTK_ENTRY(E_txt2)));
        strcpy(sper,loginerName);
        strcpy(sadd,loginerAddress);
	if(ME_flag==5)//如果是回复的话
	{
		//printf("%s**\n",ME_rper);
		//printf("%s**\n",ME_radd);
		rper=&ME_rper[0];//指针取字符串的首地址
		strcpy(radd,ME_radd);
	}
	else
	{
        	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection),&model,&iter))
        	{
                	gtk_tree_model_get(model,&iter,0,&rper,-1);
                	submitString(rper,1);
                	strcpy(radd,rper);
                	submitAddressFromName(radd);//输出转换
        	}
	}
        buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(E_txt3));
        gtk_text_buffer_get_start_iter(buffer,&start);
        gtk_text_buffer_get_end_iter(buffer,&end);
        content=(char *)gtk_text_buffer_get_text(buffer,&start,&end,FALSE);
        //printf("content=%s\n",content);
        //strcpy(content,"gagagaaggaagagagga");
	E_flag=2;
        insertEmailInfo("2",title,sper,sadd,rper,radd,content);
        updateType(0);//保存为草稿
	//关闭窗体
	gtk_widget_destroy(E_window);
        gtk_widget_show(M_window);
}

void E_toolbtn3_on_clicked(GtkWidget *widget,gpointer selection)
{
	//printf("in\n");
	GtkTreeIter iter;
        GtkTreeModel *model;
	GtkTextBuffer *buffer;//缓冲区
	GtkTextIter start,end;
	char title[50];
	char sper[50];
	char sadd[50];
	char *rper;
	char radd[50];
	char *content;//文本视图取出的指针类型
	strcpy(title,gtk_entry_get_text(GTK_ENTRY(E_txt2)));
	strcpy(sper,loginerName);
	strcpy(sadd,loginerAddress);
	if(ME_flag==5)//如果是回复的话
        {
                //printf("%s**\n",ME_rper);
                //printf("%s**\n",ME_radd);
                rper=&ME_rper[0];//指针取字符串的首地址
                strcpy(radd,ME_radd);
        }
	else
	{
		if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection),&model,&iter))
		{
			gtk_tree_model_get(model,&iter,0,&rper,-1);
			submitString(rper,1);
			strcpy(radd,rper);
			submitAddressFromName(radd);//输出转换
		}
	}
	buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(E_txt3));
	gtk_text_buffer_get_start_iter(buffer,&start);
	gtk_text_buffer_get_end_iter(buffer,&end);
	content=(char *)gtk_text_buffer_get_text(buffer,&start,&end,FALSE);	
	//printf("content=%s\n",content);
	//strcpy(content,"gagagaaggaagagagga");
	E_flag=7;
	insertEmailInfo("2",title,sper,sadd,rper,radd,content);
	updateType(1);//正常邮件
	//关闭窗体
	gtk_widget_destroy(E_window);
        gtk_widget_show(M_window);
}

void E_toolbtn4_on_clicked(GtkWidget *widget,gpointer data)
{
	colorInit(widget,data);
}

void E_toolbtn5_on_clicked(GtkWidget *widget,gpointer data)
{
        fontInit(widget,data);
}

void E_toolbtn6_on_clicked(GtkWidget *widget,gpointer data)
{
	
}

void E_menuitem11_on_clicked(GtkWidget *widget,gpointer data)
{
        E_toolbtn1_on_clicked(widget,data);
}

void E_menuitem12_on_clicked(GtkWidget *widget,gpointer data)
{
        E_toolbtn2_on_clicked(widget,data);
}

void E_menuitem13_on_clicked(GtkWidget *widget,gpointer data)
{
        E_toolbtn3_on_clicked(widget,data);
}

void E_menuitem19_on_clicked(GtkWidget *widget,gpointer data)
{
	gtk_widget_destroy(E_window);
        gtk_widget_show(M_window);
}

void E_menuitem21_on_clicked(GtkWidget *widget,gpointer data)
{
        E_toolbtn4_on_clicked(widget,data);
}

void E_menuitem22_on_clicked(GtkWidget *widget,gpointer data)
{
        E_toolbtn5_on_clicked(widget,data);
}

void E_menuitem31_on_clicked(GtkWidget *widget,gpointer data)
{
	
}

void E_list_selection_on_changed(GtkWidget *widget, gpointer data) 
{  
  	GtkTreeIter iter;  
 	GtkTreeModel *model;  
  	char *name;
	char address[100];  
	char nameAndAddress[100];//sprintf的实参数
  	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(widget),&model,&iter)) 
	{  
    		gtk_tree_model_get(model,&iter,0,&name,-1);  
		//printf("1:%s\n",name);
		submitString(name,1);//把'/t'去掉,提取/t之后的内容
		strcpy(address,name);
		//printf("%s\n",name);
		submitAddressFromName(address);//输出转换
		//printf("2:%s\n",address);
		sprintf(nameAndAddress,"<%s> %s;",address,name);
		//printf("naa:%s\n",nameAndAddress);
		gtk_entry_set_text(GTK_ENTRY(E_txt1),nameAndAddress);
    		//g_free(name);  
  	}  
}  

void editInit()
{
	char title[]="编辑邮件";
	gtk_init(NULL,NULL);
	E_window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(E_window),title);
	gtk_widget_set_usize(E_window,1000,500);
	//gtk_widget_set_uposition(E_window,300,100);
	gtk_window_set_position(GTK_WINDOW(E_window),GTK_WIN_POS_CENTER);
	//创建表格
	E_table0=gtk_table_new(5,1,FALSE);
	E_table1=gtk_table_new(2,2,FALSE);
	E_table2=gtk_table_new(1,2,FALSE);
	//创建菜单
	E_init_menu();
	//创建标签
	E_lbl1=gtk_label_new("   收件人:  ");
	E_lbl2=gtk_label_new("   主  题:  ");
	E_lbln=gtk_label_new("  ");
	//创建文本框
	E_txt1=gtk_entry_new_with_max_length(100);
	gtk_entry_set_editable(GTK_ENTRY(E_txt1),FALSE);//设置不可编辑              
	E_txt2=gtk_entry_new_with_max_length(100);	
	E_txt3=gtk_text_view_new();
	E_scrolled_txt3=gtk_scrolled_window_new(NULL,NULL);//生成滚动条的窗口
    	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(E_scrolled_txt3),GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);//滚动条属性
	gtk_container_add(GTK_CONTAINER(E_scrolled_txt3),E_txt3);
	E_txt4=gtk_entry_new_with_max_length(100);
	E_add_list();
	E_selection=gtk_tree_view_get_selection(GTK_TREE_VIEW(E_list));
	gtk_widget_set_size_request(E_txt1,900,30);
	gtk_widget_set_size_request(E_txt2,900,30);
	gtk_widget_set_size_request(E_txt3,780,300);
	gtk_widget_set_size_request(E_txt4,200,300);
	gtk_widget_set_size_request(E_list,100,300);	
	//创建工具栏
	E_toolbar=gtk_toolbar_new();
	gtk_toolbar_set_style(GTK_TOOLBAR(E_toolbar),GTK_TOOLBAR_BOTH);
	gtk_toolbar_set_icon_size(GTK_TOOLBAR(E_toolbar),GTK_ICON_SIZE_DIALOG);
	E_toolbtn1=(GtkWidget*)gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
	E_toolbtn2=(GtkWidget*)gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
	E_toolbtn3=(GtkWidget*)gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
	//E_toolbtn3=(GtkWidget*)gtk_tool_button_new(NULL,"发送");
	gtk_tool_button_set_label((GtkToolButton*)E_toolbtn3,"发送");
	E_separatortoolitem1=(GtkWidget*)gtk_separator_tool_item_new();
	E_toolbtn4=(GtkWidget*)gtk_tool_button_new_from_stock(GTK_STOCK_SELECT_COLOR);
	E_toolbtn5=(GtkWidget*)gtk_tool_button_new_from_stock(GTK_STOCK_SELECT_FONT);
	E_separatortoolitem2=(GtkWidget*)gtk_separator_tool_item_new();
	//E_toolbtn6=(GtkWidget*)gtk_tool_button_new_from_stock(GTK_STOCK_PASTE);
	gtk_container_add(GTK_CONTAINER(E_toolbar),E_toolbtn1);
	gtk_container_add(GTK_CONTAINER(E_toolbar),E_toolbtn2);	
	gtk_container_add(GTK_CONTAINER(E_toolbar),E_toolbtn3);
	gtk_container_add(GTK_CONTAINER(E_toolbar),E_separatortoolitem1);
	gtk_container_add(GTK_CONTAINER(E_toolbar),E_toolbtn4);
	gtk_container_add(GTK_CONTAINER(E_toolbar),E_toolbtn5);	
	//gtk_container_add(GTK_CONTAINER(E_toolbar),E_separatortoolitem2);
	//gtk_container_add(GTK_CONTAINER(E_toolbar),E_toolbtn6);	
        //加入到表格中
	gtk_container_add(GTK_CONTAINER(E_window),E_table0);
	gtk_table_attach(GTK_TABLE(E_table0),E_menubar,0,1,0,1,(GtkAttachOptions)(GTK_FILL|GTK_EXPAND),(GtkAttachOptions)(0),0,0);
	gtk_table_attach(GTK_TABLE(E_table0),E_toolbar,0,1,1,2,(GtkAttachOptions)(GTK_FILL|GTK_EXPAND),(GtkAttachOptions)(0),0,0);
	gtk_table_attach(GTK_TABLE(E_table0),E_lbln,0,1,4,5,(GtkAttachOptions)(GTK_FILL|GTK_EXPAND),(GtkAttachOptions)(0),0,0);
	//表格1
	gtk_table_attach(GTK_TABLE(E_table0),E_table1,0,1,2,3,(GtkAttachOptions)(GTK_FILL|GTK_EXPAND),(GtkAttachOptions)(0),0,0);
	gtk_table_attach(GTK_TABLE(E_table1),E_lbl1,0,1,0,1,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(E_table1),E_txt1,1,2,0,1,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(E_table1),E_lbl2,0,1,1,2,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(E_table1),E_txt2,1,2,1,2,(GtkAttachOptions)(0),(GtkAttachOptions)(0),5,5);
	//表格2
	gtk_table_attach(GTK_TABLE(E_table0),E_table2,0,1,3,4,(GtkAttachOptions)(GTK_FILL|GTK_EXPAND),(GtkAttachOptions)(0),0,0);
	gtk_table_attach(GTK_TABLE(E_table2),E_scrolled_txt3,0,1,0,1,(GtkAttachOptions)(GTK_FILL|GTK_EXPAND),(GtkAttachOptions)(0),5,5);
	gtk_table_attach(GTK_TABLE(E_table2),E_scrolled_list,1,2,0,1,(GtkAttachOptions)(GTK_FILL|GTK_EXPAND),(GtkAttachOptions)(0),5,5);
	//操作
	if(ME_flag==2)//撰写
	{
		//啥也不做
	}	
	else if(ME_flag==3)//编辑
        {
                gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(E_txt3)),ME_content,-1);//测试写入文本视图区内容
                gtk_entry_set_text(GTK_ENTRY(E_txt1),ME_peradd);
                gtk_entry_set_text(GTK_ENTRY(E_txt2),ME_title);
        }
	else if(ME_flag==4)//转发
	{
		gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(E_txt3)),ME_content,-1);//测试写入文本视图区内容
		gtk_text_view_set_editable(GTK_TEXT_VIEW(E_txt3),FALSE);//文本区不可以编辑
	}
	else if(ME_flag==5)//回复
	{
		//printf("peradd=%s\n",ME_peradd);
		gtk_entry_set_text(GTK_ENTRY(E_txt1),ME_peradd);
                gtk_entry_set_text(GTK_ENTRY(E_txt2),ME_title);
		//设置控件不可用
		//gtk_widget_set_state((GtkWidget*)E_list,GTK_STATE_INSENSITIVE);
		gtk_widget_set_sensitive((GtkWidget*)E_txt1,FALSE);
		gtk_widget_set_sensitive((GtkWidget*)E_txt2,FALSE);
		gtk_widget_set_sensitive((GtkWidget*)E_toolbtn1,FALSE);
		gtk_widget_set_sensitive((GtkWidget*)E_menuitem11,FALSE);
		gtk_widget_set_sensitive((GtkWidget*)E_list,FALSE);
		//gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(E_txt3)),ME_content,-1);//测试写入文本视图区内容
	}
	//事件
	g_signal_connect((gpointer)E_toolbtn1,"clicked",G_CALLBACK(E_toolbtn1_on_clicked),NULL);
	g_signal_connect((gpointer)E_toolbtn2,"clicked",G_CALLBACK(E_toolbtn2_on_clicked),E_selection);
	g_signal_connect((gpointer)E_toolbtn3,"clicked",G_CALLBACK(E_toolbtn3_on_clicked),E_selection);
	g_signal_connect((gpointer)E_toolbtn4,"clicked",G_CALLBACK(E_toolbtn4_on_clicked),E_txt3);
	g_signal_connect((gpointer)E_toolbtn5,"clicked",G_CALLBACK(E_toolbtn5_on_clicked),E_txt3);
	//g_signal_connect((gpointer)E_toolbtn6,"clicked",G_CALLBACK(E_toolbtn6_on_clicked),NULL);
	g_signal_connect((gpointer)E_menuitem11,"activate",G_CALLBACK(E_menuitem11_on_clicked),NULL);
	g_signal_connect((gpointer)E_menuitem12,"activate",G_CALLBACK(E_menuitem12_on_clicked),E_selection);
	g_signal_connect((gpointer)E_menuitem13,"activate",G_CALLBACK(E_menuitem13_on_clicked),E_selection);
	g_signal_connect((gpointer)E_menuitem19,"activate",G_CALLBACK(E_menuitem19_on_clicked),E_selection);
	g_signal_connect((gpointer)E_menuitem21,"activate",G_CALLBACK(E_menuitem21_on_clicked),E_txt3);
	g_signal_connect((gpointer)E_menuitem22,"activate",G_CALLBACK(E_menuitem22_on_clicked),E_txt3);
	g_signal_connect((gpointer)E_menuitem31,"activate",G_CALLBACK(E_menuitem31_on_clicked),NULL);
	//g_signal_connect((gpointer)E_menuitem23,"activate",G_CALLBACK(E_menuitem23_on_clicked),NULL);
	g_signal_connect(G_OBJECT(E_window),"destroy",G_CALLBACK(E_destroy),NULL);
	g_signal_connect(G_OBJECT(E_selection),"changed",G_CALLBACK(E_list_selection_on_changed),NULL);
	gtk_widget_show_all(E_window);
	gtk_main();
}
