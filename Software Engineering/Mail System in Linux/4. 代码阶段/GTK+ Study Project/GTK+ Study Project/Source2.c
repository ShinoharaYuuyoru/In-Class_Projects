/*GtkTable*/
//#include <gtk/gtk.h>
//
//int main(int argc, char *argv[])
//{
//	GtkWidget *window;
//
//	GtkWidget *table;
//	GtkWidget *button;
//
//	char *values[16] =
//	{ "7", "8", "9", "/",
//		"4", "5", "6", "*",
//		"1", "2", "3", "-",
//		"0", ".", "=", "+"
//	};
//
//	gtk_init(&argc, &argv);
//
//	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
//	gtk_window_set_default_size(GTK_WINDOW(window), 250, 180);
//	gtk_window_set_title(GTK_WINDOW(window), "GtkTable");
//
//	gtk_container_set_border_width(GTK_CONTAINER(window), 5);
//
//	table = gtk_table_new(4, 4, TRUE);	//生成了一个新的GtkTable 布局构件，并设置为4行与4列。
//	gtk_table_set_row_spacings(GTK_TABLE(table), 2);
//	gtk_table_set_col_spacings(GTK_TABLE(table), 2);	//设置了每行与每列的距离。
//
//	/*以下代码将生成16个按钮并把他们布局在GtkTable容器构件中。*/
//	int i = 0;
//	int j = 0;
//	int pos = 0;
//
//	for (i = 0; i < 4; i++) {
//		for (j = 0; j < 4; j++) {
//			button = gtk_button_new_with_label(values[pos]);
//			gtk_table_attach_defaults(GTK_TABLE(table), button, j, j + 1, i, i + 1);
//			pos++;
//		}
//	}
//
//	gtk_container_add(GTK_CONTAINER(window), table);
//
//	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), G_OBJECT(window));
//
//	gtk_widget_show_all(window);
//
//	gtk_main();
//
//	return 0;
//}

/*GtkAlignment*/
//#include <gtk/gtk.h>
//
//int main(int argc, char *argv[])
//{
//	GtkWidget *window;
//	GtkWidget *ok;
//	GtkWidget *close;
//
//	GtkWidget *vbox;
//	GtkWidget *hbox;
//	GtkWidget *halign;
//	GtkWidget *valign;
//
//	gtk_init(&argc, &argv);
//
//	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
//	gtk_window_set_default_size(GTK_WINDOW(window), 350, 200);
//	gtk_window_set_title(GTK_WINDOW(window), "GtkAlignment");
//	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
//
//	vbox = gtk_vbox_new(FALSE, 5);
//
//	/*
//	关于gtk_alignment_new(xalign,yalign,xscale,yscale)
//
//	xalign=1表示这个构件里面的widget在对齐构件里面是右对齐的，如果为0，则表示左对齐。
//	yalign=1表示这个构件里面的widget在对齐构件里面是在最底部，如果为0，则表示在顶部。
//	xscale=1表示这个构件里面的widget在对齐构件里面在水平x轴方向会全部占满空间（这样的效果就是两个按钮的大小在水平x轴方向会随着你的窗口大小的改变而改变），如果为0，则表示在对齐构件里面的widget的大小不会改变。
//	yscale=1表示这个构件里面的widget在对齐构件里面在对齐构件里面在竖直y轴方向会全部占满空间（这样的效果就是两个按钮的大小在竖直y轴方向会随着你的窗口大小的改变而改变），如果为0，则表示在对齐构件里面的widget的大小不会改变。
//	*/
//	valign = gtk_alignment_new(0, 1, 0, 0);	//表示widget在对齐容器构件的下方，并左对齐
//	gtk_container_add(GTK_CONTAINER(vbox), valign);
//	gtk_container_add(GTK_CONTAINER(window), vbox);
//
//	hbox = gtk_hbox_new(TRUE, 3);
//
//	ok = gtk_button_new_with_label("OK");
//	gtk_widget_set_size_request(ok, 70, 30);
//	gtk_container_add(GTK_CONTAINER(hbox), ok);
//	close = gtk_button_new_with_label("Close");
//	gtk_container_add(GTK_CONTAINER(hbox), close);
//
//	halign = gtk_alignment_new(1, 0, 0, 0);
//	gtk_container_add(GTK_CONTAINER(halign), hbox);
//
//	gtk_box_pack_start(GTK_BOX(vbox), halign, FALSE, FALSE, 0);
//
//	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), G_OBJECT(window));
//
//	gtk_widget_show_all(window);
//
//	gtk_main();
//
//	return 0;
//}

/*Windows*/
//#include <gtk/gtk.h>
//
//int main(int argc, char *argv[])
//{
//	GtkWidget *window;
//	GtkWidget *table;
//
//	GtkWidget *title;
//	GtkWidget *activate;
//	GtkWidget *halign;
//	GtkWidget *halign2;
//
//	GtkWidget *valign;
//	GtkWidget *close;
//	GtkWidget *wins;
//
//	GtkWidget *help;
//	GtkWidget *ok;
//
//	gtk_init(&argc, &argv);
//
//	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
//	gtk_widget_set_size_request(window, 300, 250);
//	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
//
//	gtk_window_set_title(GTK_WINDOW(window), "Windows");
//
//	gtk_container_set_border_width(GTK_CONTAINER(window), 15);
//
//	table = gtk_table_new(8, 4, FALSE);
//	gtk_table_set_col_spacings(GTK_TABLE(table), 3);
//
//	title = gtk_label_new("Windows");
//	halign = gtk_alignment_new(0, 0, 0, 0);
//	gtk_container_add(GTK_CONTAINER(halign), title);
//	gtk_table_attach(GTK_TABLE(table), halign, 0, 1, 0, 1, GTK_FILL, GTK_FILL, 0, 0);
//
//	wins = gtk_text_view_new();
//	gtk_text_view_set_editable(GTK_TEXT_VIEW(wins), FALSE);
//	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(wins), FALSE);
//	gtk_table_attach(GTK_TABLE(table), wins, 0, 2, 1, 3, GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 1, 1);
//
//	activate = gtk_button_new_with_label("Activate");
//	gtk_widget_set_size_request(activate, 50, 30);
//	gtk_table_attach(GTK_TABLE(table), activate, 3, 4, 1, 2,
//		GTK_FILL, GTK_SHRINK, 1, 1);
//
//	valign = gtk_alignment_new(0, 0, 0, 0);
//	close = gtk_button_new_with_label("Close");
//
//	gtk_widget_set_size_request(close, 70, 30);
//	gtk_container_add(GTK_CONTAINER(valign), close);
//	gtk_table_set_row_spacing(GTK_TABLE(table), 1, 3);
//	gtk_table_attach(GTK_TABLE(table), valign, 3, 4, 2, 3, GTK_FILL, GTK_FILL | GTK_EXPAND, 1, 1);
//
//	halign2 = gtk_alignment_new(0, 1, 0, 0);
//	help = gtk_button_new_with_label("Help");
//	gtk_container_add(GTK_CONTAINER(halign2), help);
//	gtk_widget_set_size_request(help, 70, 30);
//	gtk_table_set_row_spacing(GTK_TABLE(table), 3, 6);
//	gtk_table_attach(GTK_TABLE(table), halign2, 0, 1, 4, 5, GTK_FILL, GTK_FILL, 0, 0);
//
//	ok = gtk_button_new_with_label("OK");
//	gtk_widget_set_size_request(ok, 70, 30);
//	gtk_table_attach(GTK_TABLE(table), ok, 3, 4, 4, 5, GTK_FILL, GTK_FILL, 0, 0);
//
//	gtk_container_add(GTK_CONTAINER(window), table);
//
//	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), G_OBJECT(window));
//
//	gtk_widget_show_all(window);
//	gtk_main();
//
//	return 0;
//}

/*Color Change --From Internet*/
////File:color.c
////*Date:2014-01-05
////*Author:sjin
////*Mail:413977243@qq.com
//
//#include <gtk/gtk.h>  
//#include <gdk/gdk.h>  
//#include <glib.h>  
//
//GtkWidget *colorseldlg = NULL;
//GtkWidget *drawingarea = NULL;
//GdkColor color;
//
///*颜色改变处理信号*/
//void color_changed_cb(GtkWidget *widget, GtkColorSelection *colorsel)
//{
//	GdkColor ncolor;
//
//	gtk_color_selection_get_current_color(colorsel, &ncolor);
//	gtk_widget_modify_bg(drawingarea, GTK_STATE_NORMAL, &ncolor);
//}
//
///*绘图区事件处理函数*/
//gint area_event(GtkWidget *widget, GdkEvent *event, gpointer client_data)
//{
//	gint handled = FALSE;
//	gint response;
//	GtkColorSelection *colorsel;
//
//	/*检查是否收到鼠标按键按下*/
//
//	if (event->type == GDK_BUTTON_PRESS) {
//		handled = TRUE;
//
//		/*创建颜色选择对话框*/
//		if (colorseldlg == NULL) {
//			/*创建一个孤立的颜色选择构件，并需要将其放在某个对话框*/
//			colorseldlg = gtk_color_selection_dialog_new("选择背景颜色");
//		}
//		/*获取颜色选择构件*/
//		colorsel = GTK_COLOR_SELECTION(GTK_COLOR_SELECTION_DIALOG(colorseldlg)->colorsel);
//		gtk_color_selection_set_previous_color(colorsel, &color);
//		gtk_color_selection_set_current_color(colorsel, &color);
//		gtk_color_selection_set_has_palette(colorsel, TRUE);
//
//		/*为color_changed 信号设置回调函数，将用户数据设置为颜色选择构件*/
//		g_signal_connect(GTK_OBJECT(colorsel), "color_changed", G_CALLBACK(color_changed_cb), (gpointer)colorsel);
//
//		/*显示对话框*/
//		response = gtk_dialog_run(GTK_DIALOG(colorseldlg));
//
//		if (response == GTK_RESPONSE_OK) {
//			/*获取当前颜色，并保存到color中*/
//			gtk_color_selection_get_current_color(colorsel, &color);
//		}
//		else {
//			/*设置成原来的颜色*/
//			gtk_widget_modify_bg(drawingarea, GTK_STATE_NORMAL, &color);
//		}
//
//		gtk_widget_hide(colorseldlg);
//	}
//	/*只有返回True，才能弹出颜色选择控件*/
//	return handled;
//}
//
///*关闭、退出事件处理函数*/
//gint destroy_window(GtkWidget *widget, GdkEvent *event, gpointer client_data)
//{
//	gtk_main_quit();
//	return TRUE;
//}
//
//int main(int   argc, char *argv[])
//{
//	/* GtkWidget 是构件的存储类型 */
//	GtkWidget *window;
//	GtkWidget *button;
//
//	/* 这个函数在所有的 GTK 程序都要调用。参数由命令行中解析出来并且送到该程序中*/
//	gtk_init(&argc, &argv);
//	/* 创建一个新窗口 */
//	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//
//	/*设置窗口标题*/
//	gtk_window_set_title(GTK_WINDOW(window), "My first program helloworld!");
//
//	/**/
//	gtk_window_set_policy(GTK_WINDOW(window), TRUE, TRUE, TRUE);
//	/* 当窗口收到 "delete_event" 信号 (这个信号由窗口管理器发出，通常是“关闭”
//	* 选项或是标题栏上的关闭按钮发出的)，我们让它调用在前面定义的 destroy_window() 函数。
//	* 传给回调函数的 data 参数值是 NULL，它会被回调函数忽略。*/
//	g_signal_connect(GTK_OBJECT(window), "delete_event", G_CALLBACK(destroy_window), (gpointer)window);
//
//	/*创建绘图区，设置尺寸，捕捉鼠标按键事件*/
//	drawingarea = gtk_drawing_area_new();
//
//	color.red = 0;
//	color.blue = 65535;
//	color.green = 0;
//
//	/*设置背景颜色*/
//	gtk_widget_modify_bg(drawingarea, GTK_STATE_NORMAL, &color);
//
//	/*设定绘图区域的大小*/
//	gtk_widget_set_size_request(GTK_WIDGET(drawingarea), 200, 200);
//
//	/*设置成按钮事件*/
//	gtk_widget_set_events(drawingarea, GDK_BUTTON_PRESS_MASK);
//
//	g_signal_connect(GTK_OBJECT(drawingarea), "event", GTK_SIGNAL_FUNC(area_event), (gpointer)drawingarea);
//
//	gtk_container_add(GTK_CONTAINER(window), drawingarea);
//	/* 最后一步是显示新创建的按钮和窗口 */
//	gtk_widget_show(drawingarea);
//	gtk_widget_show(window);
//
//	/* 所有的 GTK 程序必须有一个 gtk_main() 函数。程序运行停在这里
//	* 等待事件 (如键盘事件或鼠标事件) 的发生。*/
//	gtk_main();
//
//	return 0;
//}