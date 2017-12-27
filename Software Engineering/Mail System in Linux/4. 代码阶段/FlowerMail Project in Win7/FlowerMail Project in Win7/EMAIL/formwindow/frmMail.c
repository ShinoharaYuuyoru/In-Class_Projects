#include "variable.h"
#include "database.h"
#include "formwindow.h"

void M_init_list()	//********************************************************************
{
	M_renderer = gtk_cell_renderer_text_new();
	//list
	M_column = gtk_tree_view_column_new_with_attributes("     菜单项", M_renderer, "text", 0, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(M_list), M_column);
	M_store = gtk_list_store_new(1, G_TYPE_STRING);
	gtk_tree_view_set_model(GTK_TREE_VIEW(M_list), GTK_TREE_MODEL(M_store));
	//list1
	M_column = gtk_tree_view_column_new_with_attributes("<序号> [主题] <发件人|收件人;地址> [日期]", M_renderer, "text", 0, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(M_list1), M_column);
	M_store = gtk_list_store_new(1, G_TYPE_STRING);
	gtk_tree_view_set_model(GTK_TREE_VIEW(M_list1), GTK_TREE_MODEL(M_store));
	//list2
	M_column = gtk_tree_view_column_new_with_attributes("item", M_renderer, "text", 0, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(M_list2), M_column);
	M_store = gtk_list_store_new(1, G_TYPE_STRING);
	gtk_tree_view_set_model(GTK_TREE_VIEW(M_list2), GTK_TREE_MODEL(M_store));
}

void M_add_to_list(gchar *str)
{
	M_store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(M_list)));
	gtk_list_store_append(M_store, &M_iter);
	gtk_list_store_set(M_store, &M_iter, 0, str, -1);
}

void M_add_to_list2(gchar *str)	/*不可删*/
{
	M_store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(M_list2)));
	gtk_list_store_append(M_store, &M_iter);
	gtk_list_store_set(M_store, &M_iter, 0, str, -1);
}

void M_add_list()
{
	M_list = gtk_tree_view_new();
	M_list1 = gtk_tree_view_new();
	M_list2 = gtk_tree_view_new();
	M_scrolled_list2 = gtk_scrolled_window_new(NULL, NULL);//生成滚动条的窗口
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(M_scrolled_list2), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);//滚动条属性
	gtk_container_add(GTK_CONTAINER(M_scrolled_list2), M_list2);
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(M_list2), FALSE);//list2隐身
	M_init_list();
	M_add_to_list("\t收件箱");
	M_add_to_list("\t已发邮件");
	M_add_to_list("\t草稿箱");
	M_add_to_list("\t垃圾箱");
	//test-list2
	M_store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(M_list2)));
	gtk_list_store_append(M_store, &M_iter);
	//gtk_list_store_set(M_store, &M_iter, 0, "1011           南宫煌            	      yintai_good@163.com      	     2013/01/29 17:59:48 ", -1);
	//showListEmail("1");
}

void M_init_menu()//创建菜单
{
	M_accel_group = gtk_accel_group_new();
	M_menubar = gtk_menu_bar_new();
	M_menuitem1 = gtk_menu_item_new_with_mnemonic("文件(_F)");
	M_menuitem10 = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(M_menuitem1), M_menuitem10);
	M_menuitem11 = gtk_menu_item_new_with_mnemonic("收取(_S)");
	gtk_widget_add_accelerator(M_menuitem11, "activate", M_accel_group, GDK_S, (GdkModifierType)GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	M_separatormenuitem1 = (GtkWidget*)gtk_separator_menu_item_new();
	M_menuitem18 = gtk_menu_item_new_with_mnemonic("注销(_L)");
	gtk_widget_add_accelerator(M_menuitem18, "activate", M_accel_group, GDK_L, (GdkModifierType)GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	//M_menuitem19=gtk_menu_item_new_with_mnemonic("退出(_Q)");
	//gtk_widget_add_accelerator(M_menuitem19,"activate",M_accel_group,GDK_Q,(GdkModifierType)GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
	M_menuitem2 = gtk_menu_item_new_with_mnemonic("编辑(_E)");
	M_menuitem20 = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(M_menuitem2), M_menuitem20);
	M_menuitem22 = gtk_menu_item_new_with_mnemonic("撰写(_W)");
	gtk_widget_add_accelerator(M_menuitem22, "activate", M_accel_group, GDK_W, (GdkModifierType)GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	M_menuitem23 = gtk_menu_item_new_with_mnemonic("编辑(_E)");
	gtk_widget_add_accelerator(M_menuitem23, "activate", M_accel_group, GDK_E, (GdkModifierType)GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	M_menuitem24 = gtk_menu_item_new_with_mnemonic("转发(_C)");
	gtk_widget_add_accelerator(M_menuitem24, "activate", M_accel_group, GDK_C, (GdkModifierType)GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	M_menuitem25 = gtk_menu_item_new_with_mnemonic("回复(_R)");
	gtk_widget_add_accelerator(M_menuitem25, "activate", M_accel_group, GDK_R, (GdkModifierType)GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	M_separatormenuitem2 = (GtkWidget*)gtk_separator_menu_item_new();
	M_menuitem26 = gtk_menu_item_new_with_mnemonic("删除(_D)");
	gtk_widget_add_accelerator(M_menuitem26, "activate", M_accel_group, GDK_D, (GdkModifierType)GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	M_menuitem3 = gtk_menu_item_new_with_mnemonic("帮助(_H)");
	M_menuitem30 = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(M_menuitem3), M_menuitem30);
	M_menuitem31 = gtk_menu_item_new_with_mnemonic("关于(_A)");
	gtk_widget_add_accelerator(M_menuitem31, "activate", M_accel_group, GDK_A, (GdkModifierType)GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	//gtk_container_add(GTK_CONTAINER(M_menuitem10),M_menuitem11);
	//gtk_container_add(GTK_CONTAINER(M_menuitem10),M_separatormenuitem1);
	gtk_container_add(GTK_CONTAINER(M_menuitem10), M_menuitem18);
	//gtk_container_add(GTK_CONTAINER(M_menuitem10),M_menuitem19);
	gtk_container_add(GTK_CONTAINER(M_menuitem20), M_menuitem22);
	gtk_container_add(GTK_CONTAINER(M_menuitem20), M_menuitem23);
	gtk_container_add(GTK_CONTAINER(M_menuitem20), M_menuitem24);
	gtk_container_add(GTK_CONTAINER(M_menuitem20), M_menuitem25);
	gtk_container_add(GTK_CONTAINER(M_menuitem20), M_separatormenuitem2);
	gtk_container_add(GTK_CONTAINER(M_menuitem20), M_menuitem26);
	gtk_container_add(GTK_CONTAINER(M_menuitem30), M_menuitem31);
	gtk_container_add(GTK_CONTAINER(M_menubar), M_menuitem1);
	gtk_container_add(GTK_CONTAINER(M_menubar), M_menuitem2);
	gtk_container_add(GTK_CONTAINER(M_menubar), M_menuitem3);
}

void M_toolbtn2_on_clicked(GtkWidget *widget, gpointer data)
{
	gtk_widget_hide(M_window);
	ME_flag = 2;//以撰写的方式打开窗体
	editInit();
}

void M_toolbtn3_on_clicked(GtkWidget *widget, gpointer selection)
{
	GtkTreeModel *model;
	GtkTextBuffer *buffer;//缓冲区
	GtkTextIter start, end;
	GtkTreeIter iter;
	char *combine;
	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter))
	{
		gtk_tree_model_get(model, &iter, 0, &combine, -1);
	}
	submitPerAdd(combine);
	submitTitle(combine);
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(M_txt));
	gtk_text_buffer_get_start_iter(buffer, &start);
	gtk_text_buffer_get_end_iter(buffer, &end);
	ME_content = (char *)gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
	//跨窗体
	gtk_widget_hide(M_window);
	ME_flag = 3;//以编辑的方式打开
	editInit();
}

void M_toolbtn4_on_clicked(GtkWidget *widget, gpointer selection)
{
	GtkTreeModel *model;
	GtkTextBuffer *buffer;//缓冲区
	GtkTextIter start, end;
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(M_txt));
	gtk_text_buffer_get_start_iter(buffer, &start);
	gtk_text_buffer_get_end_iter(buffer, &end);
	ME_content = (char *)gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
	//printf("content=%s\n",ME_content);
	//跨窗体
	ME_flag = 4;//以转发的方式打开
	editInit();
}

void M_toolbtn5_on_clicked(GtkWidget *widget, gpointer selection)
{
	GtkTreeIter iter;
	GtkTreeModel *model;
	char *combine;
	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter))
	{
		gtk_tree_model_get(model, &iter, 0, &combine, -1);
		//submitDate(combine);
	}
	//跨窗体传值出现错误
	//editInit();
	//gtk_widget_hide(E_window);
	//gtk_entry_set_text(GTK_ENTRY(E_txt1),combine);
	//gtk_widget_show(E_window);
	//跨窗体
	submitPerAdd(combine);
	//printf("peradd=%s**\n",ME_peradd);
	submitTitle(combine);
	//printf("title=%s\n",ME_title);
	gtk_widget_hide(M_window);
	ME_flag = 5;//以回复的方式打开
	editInit();
}

void M_toolbtn6_on_clicked(GtkWidget *widget, gpointer selection)
{
	GtkTreeIter iter;
	GtkTreeModel *model;
	char *combine;
	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter))
	{
		gtk_tree_model_get(model, &iter, 0, &combine, -1);
		submitDate(combine);
		if (M_flag == 1)//如果是收件箱,则放入垃圾箱
		{
			modifyType(combine);
		}
		else
		{
			deleteType(combine);
		}
	}
	//更新显示
	gtk_list_store_clear(M_store);
	if (M_flag == 1)//收件箱
	{
		showListEmail("1", 1);
	}
	else if (M_flag == 2)//已发邮件
	{
		showListEmail("1", 2);
	}
	else if (M_flag == 3)//草稿箱
	{
		showListEmail("0", 3);
	}
	else if (M_flag == 4)//垃圾箱
	{
		showListEmail("-1", 4);
	}
	//文本视区清空
	gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(M_txt)), "", -1);
}

void M_menuitem18_on_clicked(GtkWidget *widget, gpointer data)
{
	gtk_widget_destroy(M_window);
	gtk_widget_show(L_window);//显示登录窗体
}

void M_menuitem19_on_clicked(GtkWidget *widget, gpointer data)
{
	gtk_widget_destroy(M_window);
	gtk_widget_show(L_window);//显示登录窗体
}

void M_menuitem22_on_clicked(GtkWidget *widget, gpointer data)
{
	M_toolbtn2_on_clicked(widget, data);
}

void M_menuitem23_on_clicked(GtkWidget *widget, gpointer data)
{
	M_toolbtn3_on_clicked(widget, data);
}

void M_menuitem24_on_clicked(GtkWidget *widget, gpointer data)
{
	M_toolbtn4_on_clicked(widget, data);
}

void M_menuitem25_on_clicked(GtkWidget *widget, gpointer data)
{
	M_toolbtn5_on_clicked(widget, data);
}

void M_menuitem26_on_clicked(GtkWidget *widget, gpointer data)
{
	M_toolbtn6_on_clicked(widget, data);
}

void M_menuitem31_on_clicked(GtkWidget *widget, gpointer data)
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

void M_destroy(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
	gtk_widget_show(L_window);//显示登录窗体
}

void M_btnInsensitive()//设置按钮不可用
{
	gtk_widget_set_sensitive((GtkWidget*)M_toolbtn1, FALSE);
	gtk_widget_set_sensitive((GtkWidget*)M_toolbtn3, FALSE);
	gtk_widget_set_sensitive((GtkWidget*)M_toolbtn4, FALSE);
	gtk_widget_set_sensitive((GtkWidget*)M_toolbtn5, FALSE);
	gtk_widget_set_sensitive((GtkWidget*)M_toolbtn6, FALSE);
	gtk_widget_set_sensitive((GtkWidget*)M_menuitem11, FALSE);
	gtk_widget_set_sensitive((GtkWidget*)M_menuitem23, FALSE);
	gtk_widget_set_sensitive((GtkWidget*)M_menuitem24, FALSE);
	gtk_widget_set_sensitive((GtkWidget*)M_menuitem25, FALSE);
	gtk_widget_set_sensitive((GtkWidget*)M_menuitem26, FALSE);
}

void M_list_selection1_on_changed(GtkWidget *widget, gpointer data)
{
	//文本视区清空
	gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(M_txt)), "", -1);
	GtkTreeIter iter;
	GtkTreeModel *model;
	char *choice;
	//char choice[100];//如果参数是取指针地址,那么不能用数组的地址去赋值
	gtk_list_store_clear(M_store);
	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(widget), &model, &iter))
	{
		gtk_tree_model_get(model, &iter, 0, &choice, -1);
		//printf("%s\n",choice);
		M_btnInsensitive();
		if (!strcmp(choice, "\t收件箱"))
		{
			M_flag = 1;
			gtk_widget_set_sensitive((GtkWidget*)M_toolbtn1, TRUE);
			gtk_widget_set_sensitive((GtkWidget*)M_menuitem11, TRUE);
			showListEmail("1", 1);
		}
		else if (!strcmp(choice, "\t已发邮件"))
		{
			M_flag = 2;
			showListEmail("1", 2);
		}
		else if (!strcmp(choice, "\t草稿箱"))
		{
			M_flag = 3;
			showListEmail("0", 3);
		}
		else if (!strcmp(choice, "\t垃圾箱"))
		{
			M_flag = 4;
			showListEmail("-1", 4);
		}
	}
}

void M_list_selection2_on_changed(GtkWidget *widget, gpointer data)
{
	//设置按钮是否可用
	if (M_flag == 1)//收件箱
	{
		gtk_widget_set_sensitive((GtkWidget*)M_toolbtn1, TRUE);
		gtk_widget_set_sensitive((GtkWidget*)M_toolbtn3, TRUE);
		gtk_widget_set_sensitive((GtkWidget*)M_toolbtn4, TRUE);
		gtk_widget_set_sensitive((GtkWidget*)M_toolbtn5, TRUE);
		gtk_widget_set_sensitive((GtkWidget*)M_toolbtn6, TRUE);
		gtk_widget_set_sensitive((GtkWidget*)M_menuitem11, TRUE);
		gtk_widget_set_sensitive((GtkWidget*)M_menuitem23, TRUE);
		gtk_widget_set_sensitive((GtkWidget*)M_menuitem24, TRUE);
		gtk_widget_set_sensitive((GtkWidget*)M_menuitem25, TRUE);
		gtk_widget_set_sensitive((GtkWidget*)M_menuitem26, TRUE);
	}
	if (M_flag == 2)//已发邮件
	{
		gtk_widget_set_sensitive((GtkWidget*)M_toolbtn1, FALSE);
		gtk_widget_set_sensitive((GtkWidget*)M_toolbtn3, TRUE);
		gtk_widget_set_sensitive((GtkWidget*)M_toolbtn4, TRUE);
		gtk_widget_set_sensitive((GtkWidget*)M_toolbtn5, FALSE);
		gtk_widget_set_sensitive((GtkWidget*)M_toolbtn6, TRUE);
		gtk_widget_set_sensitive((GtkWidget*)M_menuitem11, FALSE);
		gtk_widget_set_sensitive((GtkWidget*)M_menuitem23, TRUE);
		gtk_widget_set_sensitive((GtkWidget*)M_menuitem24, TRUE);
		gtk_widget_set_sensitive((GtkWidget*)M_menuitem25, FALSE);
		gtk_widget_set_sensitive((GtkWidget*)M_menuitem26, FALSE);
	}
	if (M_flag == 3)//草稿箱
	{
		gtk_widget_set_sensitive((GtkWidget*)M_toolbtn1, FALSE);
		gtk_widget_set_sensitive((GtkWidget*)M_toolbtn3, TRUE);
		gtk_widget_set_sensitive((GtkWidget*)M_toolbtn4, FALSE);
		gtk_widget_set_sensitive((GtkWidget*)M_toolbtn5, FALSE);
		gtk_widget_set_sensitive((GtkWidget*)M_toolbtn6, TRUE);
		gtk_widget_set_sensitive((GtkWidget*)M_menuitem11, FALSE);
		gtk_widget_set_sensitive((GtkWidget*)M_menuitem23, TRUE);
		gtk_widget_set_sensitive((GtkWidget*)M_menuitem24, FALSE);
		gtk_widget_set_sensitive((GtkWidget*)M_menuitem25, FALSE);
		gtk_widget_set_sensitive((GtkWidget*)M_menuitem26, FALSE);
	}
	if (M_flag == 4)//垃圾箱
	{
		gtk_widget_set_sensitive((GtkWidget*)M_toolbtn1, FALSE);
		gtk_widget_set_sensitive((GtkWidget*)M_toolbtn3, FALSE);
		gtk_widget_set_sensitive((GtkWidget*)M_toolbtn4, FALSE);
		gtk_widget_set_sensitive((GtkWidget*)M_toolbtn5, FALSE);
		gtk_widget_set_sensitive((GtkWidget*)M_toolbtn6, TRUE);
		gtk_widget_set_sensitive((GtkWidget*)M_menuitem11, FALSE);
		gtk_widget_set_sensitive((GtkWidget*)M_menuitem23, FALSE);
		gtk_widget_set_sensitive((GtkWidget*)M_menuitem24, FALSE);
		gtk_widget_set_sensitive((GtkWidget*)M_menuitem25, FALSE);
		gtk_widget_set_sensitive((GtkWidget*)M_menuitem26, FALSE);
	}
	//选项改变处理代码
	GtkTreeIter iter;
	GtkTreeModel *model;
	char *combine;
	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(widget), &model, &iter))
	{
		gtk_tree_model_get(model, &iter, 0, &combine, -1);
		//printf("combine=%s**\n",combine);
		submitDate(combine);
		//printf("date=%s!!\n",combine);
		showContent(combine);
	}
}

void mailInit()	//**************************************************************
{
	char title[100];
	char *p = &loginerName[0];
	GtkWidget *Logo = gtk_image_new_from_file("Logo.gif");

	sprintf(title, "%s,欢迎你!", loginerName);
	gtk_init(NULL, NULL);
	M_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(M_window), title);
	gtk_widget_set_usize(M_window, 1000, 600);
	//gtk_widget_set_uposition(M_window,300,100);
	gtk_window_set_position(GTK_WINDOW(M_window), GTK_WIN_POS_CENTER);
	//创建表格
	M_table0 = gtk_table_new(3, 1, FALSE);
	M_table1 = gtk_table_new(3, 2, FALSE);
	//创建文本列表框
	M_add_list();
	M_selection1 = gtk_tree_view_get_selection(GTK_TREE_VIEW(M_list));
	M_selection2 = gtk_tree_view_get_selection(GTK_TREE_VIEW(M_list2));
	M_txt = gtk_text_view_new();
	gtk_text_view_set_editable(GTK_TEXT_VIEW(M_txt), FALSE);
	gtk_widget_set_size_request(M_list, 190, 338);
	gtk_widget_set_size_request(M_list2, 800, 308);
	gtk_widget_set_size_request(M_txt, 800, 202);
	//创建滚动窗体
	M_scrolled_txt = gtk_scrolled_window_new(NULL, NULL);//生成滚动条的窗口
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(M_scrolled_txt), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);//滚动条属性
	gtk_container_add(GTK_CONTAINER(M_scrolled_txt), M_txt);
	//创建菜单栏
	M_init_menu();
	//创建工具栏
	M_toolbar = gtk_toolbar_new();
	gtk_toolbar_set_style(GTK_TOOLBAR(M_toolbar), GTK_TOOLBAR_TEXT);
	gtk_toolbar_set_icon_size(GTK_TOOLBAR(M_toolbar), GTK_ICON_SIZE_DIALOG);
	M_toolbtn1 = (GtkWidget*)gtk_tool_button_new(NULL, "  收取  ");
	M_toolbtn2 = (GtkWidget*)gtk_tool_button_new(NULL, "  撰写  ");
	M_separatortoolitem1 = (GtkWidget*)gtk_separator_tool_item_new();
	M_toolbtn3 = (GtkWidget*)gtk_tool_button_new(NULL, "  编辑  ");
	M_toolbtn4 = (GtkWidget*)gtk_tool_button_new(NULL, "  转发  ");
	M_toolbtn5 = (GtkWidget*)gtk_tool_button_new(NULL, "  回复  ");
	M_separatortoolitem2 = (GtkWidget*)gtk_separator_tool_item_new();
	M_toolbtn6 = (GtkWidget*)gtk_tool_button_new(NULL, "删除");
	//gtk_container_add(GTK_CONTAINER(M_toolbar),M_toolbtn1);
	gtk_container_add(GTK_CONTAINER(M_toolbar), M_toolbtn2);
	gtk_container_add(GTK_CONTAINER(M_toolbar), M_separatortoolitem1);
	gtk_container_add(GTK_CONTAINER(M_toolbar), M_toolbtn3);
	gtk_container_add(GTK_CONTAINER(M_toolbar), M_toolbtn4);
	gtk_container_add(GTK_CONTAINER(M_toolbar), M_toolbtn5);
	gtk_container_add(GTK_CONTAINER(M_toolbar), M_separatortoolitem2);
	gtk_container_add(GTK_CONTAINER(M_toolbar), M_toolbtn6);
	//加入到表格中
	gtk_container_add(GTK_CONTAINER(M_window), M_table0);
	gtk_table_attach(GTK_TABLE(M_table0), M_menubar, 0, 1, 0, 1, (GtkAttachOptions)(GTK_FILL | GTK_EXPAND), (GtkAttachOptions)(0), 0, 0);
	gtk_table_attach(GTK_TABLE(M_table0), M_toolbar, 0, 1, 1, 2, (GtkAttachOptions)(GTK_FILL | GTK_EXPAND), (GtkAttachOptions)(0), 0, 0);
	//表格1
	gtk_table_attach(GTK_TABLE(M_table0), M_table1, 0, 1, 2, 3, (GtkAttachOptions)(GTK_FILL | GTK_EXPAND), (GtkAttachOptions)(0), 0, 0);
	gtk_table_attach(GTK_TABLE(M_table1), M_list, 0, 1, 0, 2, (GtkAttachOptions)(GTK_FILL | GTK_EXPAND), (GtkAttachOptions)(0), 5, 0);
	gtk_table_attach(GTK_TABLE(M_table1), Logo, 0, 1, 2, 3, (GtkAttachOptions)(GTK_FILL | GTK_EXPAND), (GtkAttachOptions)(0), 5, 8);
	gtk_table_attach(GTK_TABLE(M_table1), M_list1, 1, 2, 0, 1, (GtkAttachOptions)(GTK_FILL | GTK_EXPAND), (GtkAttachOptions)(0), 5, 0);
	gtk_table_attach(GTK_TABLE(M_table1), M_scrolled_list2, 1, 2, 1, 2, (GtkAttachOptions)(GTK_FILL | GTK_EXPAND), (GtkAttachOptions)(0), 5, 0);
	gtk_table_attach(GTK_TABLE(M_table1), M_scrolled_txt, 1, 2, 2, 3, (GtkAttachOptions)(GTK_FILL | GTK_EXPAND), (GtkAttachOptions)(0), 5, 0);
	//设置不可用
	M_btnInsensitive();
	//事件
	g_signal_connect(G_OBJECT(M_window), "destroy", G_CALLBACK(M_destroy), NULL);
	g_signal_connect(G_OBJECT(M_toolbtn2), "clicked", G_CALLBACK(M_toolbtn2_on_clicked), NULL);
	g_signal_connect(G_OBJECT(M_toolbtn3), "clicked", G_CALLBACK(M_toolbtn3_on_clicked), M_selection2);
	g_signal_connect(G_OBJECT(M_toolbtn4), "clicked", G_CALLBACK(M_toolbtn4_on_clicked), M_selection2);
	g_signal_connect(G_OBJECT(M_toolbtn5), "clicked", G_CALLBACK(M_toolbtn5_on_clicked), M_selection2);
	g_signal_connect(G_OBJECT(M_toolbtn6), "clicked", G_CALLBACK(M_toolbtn6_on_clicked), M_selection2);

	g_signal_connect(G_OBJECT(M_selection1), "changed", G_CALLBACK(M_list_selection1_on_changed), NULL);
	g_signal_connect(G_OBJECT(M_selection2), "changed", G_CALLBACK(M_list_selection2_on_changed), NULL);

	g_signal_connect((gpointer)M_menuitem18, "activate", G_CALLBACK(M_menuitem18_on_clicked), NULL);
	//g_signal_connect((gpointer)M_menuitem19,"activate",G_CALLBACK(M_menuitem19_on_clicked),NULL);
	g_signal_connect((gpointer)M_menuitem22, "activate", G_CALLBACK(M_menuitem22_on_clicked), M_selection2);
	g_signal_connect((gpointer)M_menuitem23, "activate", G_CALLBACK(M_menuitem23_on_clicked), M_selection2);
	g_signal_connect((gpointer)M_menuitem24, "activate", G_CALLBACK(M_menuitem24_on_clicked), M_selection2);
	g_signal_connect((gpointer)M_menuitem25, "activate", G_CALLBACK(M_menuitem25_on_clicked), M_selection2);
	g_signal_connect((gpointer)M_menuitem26, "activate", G_CALLBACK(M_menuitem26_on_clicked), M_selection2);
	g_signal_connect((gpointer)M_menuitem31, "activate", G_CALLBACK(M_menuitem31_on_clicked), NULL);
	gtk_widget_show_all(M_window);
	gtk_main();
}