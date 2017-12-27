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
//	table = gtk_table_new(4, 4, TRUE);	//������һ���µ�GtkTable ���ֹ�����������Ϊ4����4�С�
//	gtk_table_set_row_spacings(GTK_TABLE(table), 2);
//	gtk_table_set_col_spacings(GTK_TABLE(table), 2);	//������ÿ����ÿ�еľ��롣
//
//	/*���´��뽫����16����ť�������ǲ�����GtkTable���������С�*/
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
//	����gtk_alignment_new(xalign,yalign,xscale,yscale)
//
//	xalign=1��ʾ������������widget�ڶ��빹���������Ҷ���ģ����Ϊ0�����ʾ����롣
//	yalign=1��ʾ������������widget�ڶ��빹������������ײ������Ϊ0�����ʾ�ڶ�����
//	xscale=1��ʾ������������widget�ڶ��빹��������ˮƽx�᷽���ȫ��ռ���ռ䣨������Ч������������ť�Ĵ�С��ˮƽx�᷽���������Ĵ��ڴ�С�ĸı���ı䣩�����Ϊ0�����ʾ�ڶ��빹�������widget�Ĵ�С����ı䡣
//	yscale=1��ʾ������������widget�ڶ��빹�������ڶ��빹����������ֱy�᷽���ȫ��ռ���ռ䣨������Ч������������ť�Ĵ�С����ֱy�᷽���������Ĵ��ڴ�С�ĸı���ı䣩�����Ϊ0�����ʾ�ڶ��빹�������widget�Ĵ�С����ı䡣
//	*/
//	valign = gtk_alignment_new(0, 1, 0, 0);	//��ʾwidget�ڶ��������������·����������
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
///*��ɫ�ı䴦���ź�*/
//void color_changed_cb(GtkWidget *widget, GtkColorSelection *colorsel)
//{
//	GdkColor ncolor;
//
//	gtk_color_selection_get_current_color(colorsel, &ncolor);
//	gtk_widget_modify_bg(drawingarea, GTK_STATE_NORMAL, &ncolor);
//}
//
///*��ͼ���¼�������*/
//gint area_event(GtkWidget *widget, GdkEvent *event, gpointer client_data)
//{
//	gint handled = FALSE;
//	gint response;
//	GtkColorSelection *colorsel;
//
//	/*����Ƿ��յ���갴������*/
//
//	if (event->type == GDK_BUTTON_PRESS) {
//		handled = TRUE;
//
//		/*������ɫѡ��Ի���*/
//		if (colorseldlg == NULL) {
//			/*����һ����������ɫѡ�񹹼�������Ҫ�������ĳ���Ի���*/
//			colorseldlg = gtk_color_selection_dialog_new("ѡ�񱳾���ɫ");
//		}
//		/*��ȡ��ɫѡ�񹹼�*/
//		colorsel = GTK_COLOR_SELECTION(GTK_COLOR_SELECTION_DIALOG(colorseldlg)->colorsel);
//		gtk_color_selection_set_previous_color(colorsel, &color);
//		gtk_color_selection_set_current_color(colorsel, &color);
//		gtk_color_selection_set_has_palette(colorsel, TRUE);
//
//		/*Ϊcolor_changed �ź����ûص����������û���������Ϊ��ɫѡ�񹹼�*/
//		g_signal_connect(GTK_OBJECT(colorsel), "color_changed", G_CALLBACK(color_changed_cb), (gpointer)colorsel);
//
//		/*��ʾ�Ի���*/
//		response = gtk_dialog_run(GTK_DIALOG(colorseldlg));
//
//		if (response == GTK_RESPONSE_OK) {
//			/*��ȡ��ǰ��ɫ�������浽color��*/
//			gtk_color_selection_get_current_color(colorsel, &color);
//		}
//		else {
//			/*���ó�ԭ������ɫ*/
//			gtk_widget_modify_bg(drawingarea, GTK_STATE_NORMAL, &color);
//		}
//
//		gtk_widget_hide(colorseldlg);
//	}
//	/*ֻ�з���True�����ܵ�����ɫѡ��ؼ�*/
//	return handled;
//}
//
///*�رա��˳��¼�������*/
//gint destroy_window(GtkWidget *widget, GdkEvent *event, gpointer client_data)
//{
//	gtk_main_quit();
//	return TRUE;
//}
//
//int main(int   argc, char *argv[])
//{
//	/* GtkWidget �ǹ����Ĵ洢���� */
//	GtkWidget *window;
//	GtkWidget *button;
//
//	/* ������������е� GTK ����Ҫ���á��������������н������������͵��ó�����*/
//	gtk_init(&argc, &argv);
//	/* ����һ���´��� */
//	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//
//	/*���ô��ڱ���*/
//	gtk_window_set_title(GTK_WINDOW(window), "My first program helloworld!");
//
//	/**/
//	gtk_window_set_policy(GTK_WINDOW(window), TRUE, TRUE, TRUE);
//	/* �������յ� "delete_event" �ź� (����ź��ɴ��ڹ�����������ͨ���ǡ��رա�
//	* ѡ����Ǳ������ϵĹرհ�ť������)����������������ǰ�涨��� destroy_window() ������
//	* �����ص������� data ����ֵ�� NULL�����ᱻ�ص��������ԡ�*/
//	g_signal_connect(GTK_OBJECT(window), "delete_event", G_CALLBACK(destroy_window), (gpointer)window);
//
//	/*������ͼ�������óߴ磬��׽��갴���¼�*/
//	drawingarea = gtk_drawing_area_new();
//
//	color.red = 0;
//	color.blue = 65535;
//	color.green = 0;
//
//	/*���ñ�����ɫ*/
//	gtk_widget_modify_bg(drawingarea, GTK_STATE_NORMAL, &color);
//
//	/*�趨��ͼ����Ĵ�С*/
//	gtk_widget_set_size_request(GTK_WIDGET(drawingarea), 200, 200);
//
//	/*���óɰ�ť�¼�*/
//	gtk_widget_set_events(drawingarea, GDK_BUTTON_PRESS_MASK);
//
//	g_signal_connect(GTK_OBJECT(drawingarea), "event", GTK_SIGNAL_FUNC(area_event), (gpointer)drawingarea);
//
//	gtk_container_add(GTK_CONTAINER(window), drawingarea);
//	/* ���һ������ʾ�´����İ�ť�ʹ��� */
//	gtk_widget_show(drawingarea);
//	gtk_widget_show(window);
//
//	/* ���е� GTK ���������һ�� gtk_main() ��������������ͣ������
//	* �ȴ��¼� (������¼�������¼�) �ķ�����*/
//	gtk_main();
//
//	return 0;
//}