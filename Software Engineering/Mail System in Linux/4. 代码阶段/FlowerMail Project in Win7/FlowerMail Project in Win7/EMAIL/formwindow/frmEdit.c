#include "variable.h"
#include "database.h"
#include "formwindow.h"

void E_init_list()
{
	Edit_renderer = gtk_cell_renderer_text_new();
	Edit_column = gtk_tree_view_column_new_with_attributes("   联系人", Edit_renderer, "text", 0, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(Edit_list), Edit_column);
	Edit_store = gtk_list_store_new(1, G_TYPE_STRING);
	gtk_tree_view_set_model(GTK_TREE_VIEW(Edit_list), GTK_TREE_MODEL(Edit_store));
}

void E_add_to_list(gchar *str)
{
	Edit_store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(Edit_list)));
	gtk_list_store_append(Edit_store, &Edit_iter);
	gtk_list_store_set(Edit_store, &Edit_iter, 0, str, -1);
}

void E_add_list()
{
	Edit_list = gtk_tree_view_new();
	Edit_scrolled_list = gtk_scrolled_window_new(NULL, NULL);//生成滚动条的窗口
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(Edit_scrolled_list), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);//滚动条属性
	gtk_container_add(GTK_CONTAINER(Edit_scrolled_list), Edit_list);
	//gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(Edit_list), FALSE);  
	E_init_list();
	//E_add_to_list("	李逍遥");
	//E_add_to_list("	林月如");
	//E_add_to_list("	赵灵儿");
	//E_add_to_list("	阿奴");
	showListName();
}

void E_init_menu()//创建菜单
{
	Edit_accel_group = gtk_accel_group_new();
	Edit_menubar = gtk_menu_bar_new();
	Edit_menuitem1 = gtk_menu_item_new_with_mnemonic("文件(_F)");
	Edit_menuitem10 = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(Edit_menuitem1), Edit_menuitem10);
	Edit_menuitem11 = gtk_menu_item_new_with_mnemonic("新建(_N)");
	gtk_widget_add_accelerator(Edit_menuitem11, "activate", Edit_accel_group, GDK_N, (GdkModifierType)GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	Edit_separatormenuitem1 = (GtkWidget*)gtk_separator_menu_item_new();
	Edit_menuitem12 = gtk_menu_item_new_with_mnemonic("保存(_S)");
	gtk_widget_add_accelerator(Edit_menuitem12, "activate", Edit_accel_group, GDK_S, (GdkModifierType)GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	Edit_menuitem13 = gtk_menu_item_new_with_mnemonic("发送(_X)");
	gtk_widget_add_accelerator(Edit_menuitem13, "activate", Edit_accel_group, GDK_X, (GdkModifierType)GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	Edit_separatormenuitem2 = (GtkWidget*)gtk_separator_menu_item_new();
	Edit_menuitem19 = gtk_menu_item_new_with_mnemonic("关闭(_E)");
	gtk_widget_add_accelerator(Edit_menuitem19, "activate", Edit_accel_group, GDK_E, (GdkModifierType)GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	Edit_menuitem2 = gtk_menu_item_new_with_mnemonic("编辑(_E)");
	Edit_menuitem20 = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(Edit_menuitem2), Edit_menuitem20);
	Edit_menuitem21 = gtk_menu_item_new_with_mnemonic("颜色(_C)");
	gtk_widget_add_accelerator(Edit_menuitem21, "activate", Edit_accel_group, GDK_C, (GdkModifierType)GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	Edit_menuitem22 = gtk_menu_item_new_with_mnemonic("字体(_F)");
	gtk_widget_add_accelerator(Edit_menuitem22, "activate", Edit_accel_group, GDK_F, (GdkModifierType)GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	Edit_separatormenuitem3 = (GtkWidget*)gtk_separator_menu_item_new();
	//Edit_menuitem23=gtk_menu_item_new_with_mnemonic("附件(_B)");
		//gtk_widget_add_accelerator(Edit_menuitem23,"activate",Edit_accel_group,GDK_B,(GdkModifierType)GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
	Edit_menuitem3 = gtk_menu_item_new_with_mnemonic("帮助(_H)");
	Edit_menuitem30 = gtk_menu_new();
	Edit_menuitem31 = gtk_menu_item_new_with_mnemonic("关于(_A)");
	gtk_widget_add_accelerator(Edit_menuitem31, "activate", Edit_accel_group, GDK_A, (GdkModifierType)GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(Edit_menuitem3), Edit_menuitem30);
	gtk_container_add(GTK_CONTAINER(Edit_menuitem10), Edit_menuitem11);
	gtk_container_add(GTK_CONTAINER(Edit_menuitem10), Edit_separatormenuitem1);
	gtk_container_add(GTK_CONTAINER(Edit_menuitem10), Edit_menuitem12);
	gtk_container_add(GTK_CONTAINER(Edit_menuitem10), Edit_menuitem13);
	gtk_container_add(GTK_CONTAINER(Edit_menuitem10), Edit_separatormenuitem2);
	gtk_container_add(GTK_CONTAINER(Edit_menuitem10), Edit_menuitem19);
	gtk_container_add(GTK_CONTAINER(Edit_menuitem20), Edit_menuitem21);
	gtk_container_add(GTK_CONTAINER(Edit_menuitem20), Edit_menuitem22);
	gtk_container_add(GTK_CONTAINER(Edit_menuitem30), Edit_menuitem31);
	//gtk_container_add(GTK_CONTAINER(Edit_menuitem20),Edit_separatormenuitem3);
	//gtk_container_add(GTK_CONTAINER(Edit_menuitem20),Edit_menuitem23);
	gtk_container_add(GTK_CONTAINER(Edit_menubar), Edit_menuitem1);
	gtk_container_add(GTK_CONTAINER(Edit_menubar), Edit_menuitem2);
	gtk_container_add(GTK_CONTAINER(Edit_menubar), Edit_menuitem3);
}

void E_destroy(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
	gtk_widget_show(M_window);
}

void E_toolbtn1_on_clicked(GtkWidget *widget, gpointer data)
{
	gtk_entry_set_text(GTK_ENTRY(Edit_txt1), "");
	gtk_entry_set_text(GTK_ENTRY(Edit_txt2), "");
	gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(Edit_txt3)), "", -1);
}

/*草稿*/
void E_toolbtn2_on_clicked(GtkWidget *widget, gpointer selection)
{
	//printf("in\n");
	GtkTreeIter iter;
	GtkTreeModel *model;
	GtkTextBuffer *buffer;//正文缓冲区
	GtkTextIter start, end;
	char title[50];	//文章标题
	char sper[50];	//记录用户名
	char sadd[50];	//记录用户的IP地址
	char *rper;	//回复人的用户名
	char radd[50];	//回复人的地址
	char *content;//文本视图取出的指针类型   即文本
	strcpy(title, gtk_entry_get_text(GTK_ENTRY(Edit_txt2)));
	strcpy(sper, loginerName);
	strcpy(sadd, loginerAddress);

	if (ME_flag == 5)//如果是回复
	{
		//printf("%s**\n",ME_rper);
		//printf("%s**\n",ME_radd);
		rper = &ME_rper[0];	//指针取字符串的首地址
		strcpy(radd, ME_radd);	//复制回复人的地址
	}
	else
	{
		if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter))
		{
			gtk_tree_model_get(model, &iter, 0, &rper, -1);
			submitString(rper, 1);
			strcpy(radd, rper);
			submitAddressFromName(radd);//输出转换
		}
	}

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Edit_txt3));	//获得正文
	gtk_text_buffer_get_start_iter(buffer, &start);	//获得正文开头
	gtk_text_buffer_get_end_iter(buffer, &end);	//获得正文结尾
	content = (char *)gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
	//printf("content=%s\n",content);
	//strcpy(content,"gagagaaggaagagagga");
	Edit_flag = 2;
	insertEmailInfo("2", title, sper, sadd, rper, radd, content);	//保存标题 送达人用户名 IP地址 发送人用户名 发送人地址 文章内容
	updateType(0);//保存为草稿

	//关闭窗体
	gtk_widget_destroy(Edit_window);
	gtk_widget_show(M_window);
}

/*正常发送*/
void E_toolbtn3_on_clicked(GtkWidget *widget, gpointer selection)
{
	//printf("in\n");
	GtkTreeIter iter;
	GtkTreeModel *model;
	GtkTextBuffer *buffer;//缓冲区
	GtkTextIter start, end;
	char title[50];
	char sper[50];
	char sadd[50];
	char *rper;
	char radd[50];
	char *content;//文本视图取出的指针类型
	strcpy(title, gtk_entry_get_text(GTK_ENTRY(Edit_txt2)));
	strcpy(sper, loginerName);
	strcpy(sadd, loginerAddress);
	if (ME_flag == 5)//如果是回复的话
	{
		//printf("%s**\n",ME_rper);
		//printf("%s**\n",ME_radd);
		rper = &ME_rper[0];//指针取字符串的首地址
		strcpy(radd, ME_radd);
	}
	else
	{
		if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter))
		{
			gtk_tree_model_get(model, &iter, 0, &rper, -1);
			submitString(rper, 1);
			strcpy(radd, rper);
			submitAddressFromName(radd);//输出转换
		}
	}
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Edit_txt3));
	gtk_text_buffer_get_start_iter(buffer, &start);
	gtk_text_buffer_get_end_iter(buffer, &end);
	content = (char *)gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
	//printf("content=%s\n",content);
	//strcpy(content,"gagagaaggaagagagga");
	Edit_flag = 7;
	insertEmailInfo("2", title, sper, sadd, rper, radd, content);
	updateType(1);//正常邮件
	//关闭窗体
	gtk_widget_destroy(Edit_window);
	gtk_widget_show(M_window);
}

void E_toolbtn4_on_clicked(GtkWidget *widget, gpointer data)
{
	colorInit(widget, data);
}

void E_toolbtn5_on_clicked(GtkWidget *widget, gpointer data)
{
	fontInit(widget, data);
}

void E_toolbtn6_on_clicked(GtkWidget *widget,gpointer data)
{
	fileInit(widget, data);
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
	gtk_widget_destroy(Edit_window);
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
	Edit_dialog = gtk_dialog_new_with_buttons("关于我们", GTK_WINDOW(L_window), GTK_DIALOG_MODAL, GTK_STOCK_OK, GTK_RESPONSE_OK, NULL);
	Edit_lbld = gtk_label_new("私たちは偉大なワルキューレ！アイドル万歳！");
	gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(Edit_dialog)->vbox), Edit_lbld);//标签加入到对话框里
	gtk_widget_show_all(Edit_dialog);//显示对话框里的信息
	if (gtk_dialog_run(GTK_DIALOG(Edit_dialog)) == GTK_RESPONSE_OK)
	{
		gtk_widget_destroy(Edit_dialog);//ro不是or
	}
}

void E_list_selection_on_changed(GtkWidget *widget, gpointer data)
{
	GtkTreeIter iter;
	GtkTreeModel *model;
	char *name;
	char address[100];
	char nameAndAddress[100];//sprintf的实参数
	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(widget), &model, &iter))
	{
		gtk_tree_model_get(model, &iter, 0, &name, -1);
		//printf("1:%s\n",name);
		submitString(name, 1);//把'/t'去掉,提取/t之后的内容
		strcpy(address, name);
		//printf("%s\n",name);
		submitAddressFromName(address);//输出转换
		//printf("2:%s\n",address);
		sprintf(nameAndAddress, "<%s> %s;", address, name);
		//printf("naa:%s\n",nameAndAddress);
		gtk_entry_set_text(GTK_ENTRY(Edit_txt1), nameAndAddress);
		//g_free(name);  
	}
}

void editInit()
{
	char Title[] = "编辑邮件";
	gtk_init(NULL, NULL);
	Edit_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(Edit_window), Title);
	gtk_widget_set_usize(Edit_window, 1000, 500);	//设置窗口默认大小
	gtk_window_set_position(GTK_WINDOW(Edit_window), GTK_WIN_POS_CENTER);

	//创建表格
	Edit_table0 = gtk_table_new(4, 2, FALSE);	//4*2表格 不允许均匀摆放控件
	Edit_table1 = gtk_table_new(2, 2, FALSE);	//2*2 为收件人、主题表格
	Edit_table2 = gtk_table_new(1, 1, FALSE);	//1*2 为输入正文表格

	//创建菜单
	E_init_menu();

	//创建标签
	Edit_lbl1 = gtk_label_new("   收件人:  ");
	Edit_lbl2 = gtk_label_new("  主     题: ");

	//创建文本框
	Edit_txt1 = gtk_entry_new_with_max_length(100);	//收件人
	gtk_entry_set_editable(GTK_ENTRY(Edit_txt1), FALSE);//收件人现设置不可编辑            
	Edit_txt2 = gtk_entry_new_with_max_length(100);	//主题
	Edit_txt3 = gtk_text_view_new();	//正文输入框
	Edit_scrolled_txt3 = gtk_scrolled_window_new(NULL, NULL);//生成滚动条的窗口
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(Edit_scrolled_txt3), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);//滚动条属性
	gtk_container_add(GTK_CONTAINER(Edit_scrolled_txt3), Edit_txt3);	//生成可以滚动条的正文输入框
	E_add_list();	//创建联系人
	Edit_selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(Edit_list));
	gtk_widget_set_size_request(Edit_txt1, 600, 30);	//收件人
	gtk_widget_set_size_request(Edit_txt2, 600, 30);	//主题
	gtk_widget_set_size_request(Edit_txt3, 480, 300);	//正文
	gtk_widget_set_size_request(Edit_list, 100, 380);	//联系人

	//创建工具栏
	Edit_toolbar = gtk_toolbar_new();
	gtk_toolbar_set_style(GTK_TOOLBAR(Edit_toolbar), GTK_TOOLBAR_BOTH);
	gtk_toolbar_set_icon_size(GTK_TOOLBAR(Edit_toolbar), GTK_ICON_SIZE_DIALOG);
	Edit_toolbtn1 = (GtkWidget*)gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
	Edit_toolbtn2 = (GtkWidget*)gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
	Edit_toolbtn3 = (GtkWidget*)gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
	gtk_tool_button_set_label((GtkToolButton*)Edit_toolbtn3, "发送");	//特别注释为发送
	Edit_separatortoolitem1 = (GtkWidget*)gtk_separator_tool_item_new();
	Edit_toolbtn4 = (GtkWidget*)gtk_tool_button_new_from_stock(GTK_STOCK_SELECT_COLOR);
	Edit_toolbtn5 = (GtkWidget*)gtk_tool_button_new_from_stock(GTK_STOCK_SELECT_FONT);
	Edit_toolbtn6 = (GtkWidget*)gtk_tool_button_new_from_stock(GTK_STOCK_ADD);
	gtk_tool_button_set_label((GtkToolButton*)Edit_toolbtn6, "附件");	//特别注释为发送
	gtk_container_add(GTK_CONTAINER(Edit_toolbar), Edit_toolbtn1);
	gtk_container_add(GTK_CONTAINER(Edit_toolbar), Edit_toolbtn2);
	gtk_container_add(GTK_CONTAINER(Edit_toolbar), Edit_toolbtn3);
	gtk_container_add(GTK_CONTAINER(Edit_toolbar), Edit_separatortoolitem1);
	gtk_container_add(GTK_CONTAINER(Edit_toolbar), Edit_toolbtn4);
	gtk_container_add(GTK_CONTAINER(Edit_toolbar), Edit_toolbtn5);
	gtk_container_add(GTK_CONTAINER(Edit_toolbar), Edit_toolbtn6);

	//加入到表格中
	gtk_container_add(GTK_CONTAINER(Edit_window), Edit_table0);
	gtk_table_attach(GTK_TABLE(Edit_table0), Edit_menubar, 0, 2, 0, 1, (GtkAttachOptions)(GTK_FILL | GTK_EXPAND), (GtkAttachOptions)(0), 0, 0);
	gtk_table_attach(GTK_TABLE(Edit_table0), Edit_toolbar, 0, 2, 1, 2, (GtkAttachOptions)(GTK_FILL | GTK_EXPAND), (GtkAttachOptions)(0), 0, 0);

	//表格1 收件人、主题、联系人表格
	gtk_table_attach(GTK_TABLE(Edit_table0), Edit_table1, 0, 1, 2, 3, (GtkAttachOptions)(GTK_FILL | GTK_EXPAND), (GtkAttachOptions)(0), 0, 0);
	gtk_table_attach(GTK_TABLE(Edit_table1), Edit_lbl1, 0, 1, 0, 1, (GtkAttachOptions)(0), (GtkAttachOptions)(0), 5, 5);
	gtk_table_attach(GTK_TABLE(Edit_table1), Edit_txt1, 1, 2, 0, 1, (GtkAttachOptions)(GTK_FILL | GTK_EXPAND), (GtkAttachOptions)(0), 5, 5);
	gtk_table_attach(GTK_TABLE(Edit_table1), Edit_lbl2, 0, 1, 1, 2, (GtkAttachOptions)(0), (GtkAttachOptions)(0), 5, 5);
	gtk_table_attach(GTK_TABLE(Edit_table1), Edit_txt2, 1, 2, 1, 2, (GtkAttachOptions)(GTK_FILL | GTK_EXPAND), (GtkAttachOptions)(0), 5, 5);
	gtk_table_attach(GTK_TABLE(Edit_table0), Edit_scrolled_list, 1, 2, 2, 4, (GtkAttachOptions)(GTK_FILL | GTK_EXPAND), (GtkAttachOptions)(0), 5, 5);

	//表格2 正文表格
	gtk_table_attach(GTK_TABLE(Edit_table0), Edit_table2, 0, 1, 3, 4, (GtkAttachOptions)(GTK_FILL | GTK_EXPAND), (GtkAttachOptions)(0), 0, 0);
	gtk_table_attach(GTK_TABLE(Edit_table2), Edit_scrolled_txt3, 0, 1, 0, 1, (GtkAttachOptions)(GTK_FILL | GTK_EXPAND), (GtkAttachOptions)(0), 5, 5);

	//操作
	if (ME_flag == 2)//撰写
	{
		//无操作
	}
	else if (ME_flag == 3)//编辑
	{
		gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(Edit_txt3)), ME_content, -1);//测试写入文本视图区内容
		gtk_entry_set_text(GTK_ENTRY(Edit_txt1), ME_peradd);
		gtk_entry_set_text(GTK_ENTRY(Edit_txt2), ME_title);
	}
	else if (ME_flag == 4)//转发
	{
		gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(Edit_txt3)), ME_content, -1);//测试写入文本视图区内容
		gtk_text_view_set_editable(GTK_TEXT_VIEW(Edit_txt3), FALSE);	//设置文本区不可以编辑
	}
	else if (ME_flag == 5)//回复
	{
		//printf("peradd=%s\n",ME_peradd);
		gtk_entry_set_text(GTK_ENTRY(Edit_txt1), ME_peradd);
		gtk_entry_set_text(GTK_ENTRY(Edit_txt2), ME_title);
		//设置控件不可用
		//gtk_widget_set_state((GtkWidget*)E_list,GTK_STATE_INSENSITIVE);
		gtk_widget_set_sensitive((GtkWidget*)Edit_txt1, FALSE);
		gtk_widget_set_sensitive((GtkWidget*)Edit_txt2, FALSE);
		gtk_widget_set_sensitive((GtkWidget*)Edit_toolbtn1, FALSE);
		gtk_widget_set_sensitive((GtkWidget*)Edit_menuitem11, FALSE);
		gtk_widget_set_sensitive((GtkWidget*)Edit_list, FALSE);
		//gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(Edit_txt3)),ME_content,-1);//测试写入文本视图区内容
	}

	//事件
	g_signal_connect((gpointer)Edit_toolbtn1, "clicked", G_CALLBACK(E_toolbtn1_on_clicked), NULL);	//新建
	g_signal_connect((gpointer)Edit_toolbtn2, "clicked", G_CALLBACK(E_toolbtn2_on_clicked), Edit_selection);	//保存
	g_signal_connect((gpointer)Edit_toolbtn3, "clicked", G_CALLBACK(E_toolbtn3_on_clicked), Edit_selection);	//发送
	g_signal_connect((gpointer)Edit_toolbtn4, "clicked", G_CALLBACK(E_toolbtn4_on_clicked), Edit_txt3);	//颜色
	g_signal_connect((gpointer)Edit_toolbtn5, "clicked", G_CALLBACK(E_toolbtn5_on_clicked), Edit_txt3);	//字体
	g_signal_connect((gpointer)Edit_toolbtn6, "clicked", G_CALLBACK(E_toolbtn6_on_clicked), Edit_file);	//附件

	g_signal_connect((gpointer)Edit_menuitem11, "activate", G_CALLBACK(E_menuitem11_on_clicked), NULL);
	g_signal_connect((gpointer)Edit_menuitem12, "activate", G_CALLBACK(E_menuitem12_on_clicked), Edit_selection);
	g_signal_connect((gpointer)Edit_menuitem13, "activate", G_CALLBACK(E_menuitem13_on_clicked), Edit_selection);
	g_signal_connect((gpointer)Edit_menuitem19, "activate", G_CALLBACK(E_menuitem19_on_clicked), Edit_selection);
	g_signal_connect((gpointer)Edit_menuitem21, "activate", G_CALLBACK(E_menuitem21_on_clicked), Edit_txt3);
	g_signal_connect((gpointer)Edit_menuitem22, "activate", G_CALLBACK(E_menuitem22_on_clicked), Edit_txt3);
	g_signal_connect((gpointer)Edit_menuitem31, "activate", G_CALLBACK(E_menuitem31_on_clicked), NULL);

	g_signal_connect(G_OBJECT(Edit_window), "destroy", G_CALLBACK(E_destroy), NULL);
	g_signal_connect(G_OBJECT(Edit_selection), "changed", G_CALLBACK(E_list_selection_on_changed), NULL);

	gtk_widget_show_all(Edit_window);
	gtk_main();
}