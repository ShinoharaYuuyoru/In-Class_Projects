/*应用程序图标的制作*/
//#include <gtk/gtk.h>
//
//GdkPixbuf *create_pixbuf(const gchar * filename)
//{
//	GdkPixbuf *pixbuf;
//	GError *error = NULL;
//	pixbuf = gdk_pixbuf_new_from_file(filename, &error);
//	if (!pixbuf) {
//		fprintf(stderr, "%s\n", error->message);
//		g_error_free(error);
//	}
//
//	return pixbuf;
//}
//
//int main(int argc, char *argv[])
//{
//	GtkWidget *window;
//
//	gtk_init(&argc, &argv);
//
//	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//	gtk_window_set_title(GTK_WINDOW(window), "icon");
//	gtk_window_set_default_size(GTK_WINDOW(window), 230, 150);
//	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
//	gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("web.png"));
//	gtk_widget_show(window);
//
//	g_signal_connect_swapped(G_OBJECT(window), "destroy",
//		G_CALLBACK(gtk_main_quit), NULL);
//
//	gtk_main();
//
//	return 0;
//}

/*增加和减少*/
//#include <gtk/gtk.h>
//
//gint count = 0;
//char buf[5];
//
//void increase(GtkWidget *widget, gpointer *label)
//{
//	count++;
//
//	sprintf(buf, "%d", count);
//	gtk_label_set_text(label, buf);
//}
//
//void decrease(GtkWidget *widget, gpointer *label)
//{
//	count--;
//
//	sprintf(buf, "%d", count);
//	gtk_label_set_text(label, buf);
//}
//
//int main(int argc, char** argv)
//{
//	GtkWidget *label;
//	GtkWidget *window;
//	GtkWidget *frame;
//	GtkWidget *plus;
//	GtkWidget *minus;
//
//	gtk_init(&argc, &argv);
//
//	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//	gtk_window_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
//	gtk_window_set_default_size(GTK_WINDOW(window), 250, 180);
//	gtk_window_set_title(GTK_WINDOW(window), "PandM");
//
//	frame = gtk_fixed_new();
//	gtk_container_add(GTK_CONTAINER(window), frame);
//
//	plus = gtk_button_new_with_label("+");
//	gtk_widget_set_size_request(plus, 80, 35);
//	gtk_fixed_put(GTK_FIXED(frame), plus, 50, 20);
//
//	minus = gtk_button_new_with_label("-");
//	gtk_widget_set_size_request(minus, 80, 35);
//	gtk_fixed_put(GTK_FIXED(frame), minus, 50, 80);
//
//	label = gtk_label_new("0");
//	gtk_fixed_put(GTK_FIXED(frame), label, 190, 58);
//
//	gtk_widget_show_all(window);
//
//	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
//
//	g_signal_connect(plus, "clicked", G_CALLBACK(increase), label);
//	g_signal_connect(minus, "clicked", G_CALLBACK(decrease), label);
//
//	gtk_main();
//
//	return 0;
//}

/*简单的菜单示列*/
//#include "gtk/gtk.h"
//
//int main(int argc, char *argv[])
//{
//	GtkWidget *window;
//	GtkWidget *vbox;
//
//	GtkWidget *menubar;
//	GtkWidget *filemenu;
//	GtkWidget *file;
//	GtkWidget *quit;
//
//	gtk_init(&argc, &argv);
//
//	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
//	gtk_window_set_default_size(GTK_WINDOW(window), 250, 200);
//	gtk_window_set_title(GTK_WINDOW(window), "menu");
//
//	vbox = gtk_vbox_new(FALSE, 0);
//	gtk_container_add(GTK_CONTAINER(window), vbox);
//
//	menubar = gtk_menu_bar_new();
//	filemenu = gtk_menu_new();
//
//	file = gtk_menu_item_new_with_label("File");
//	quit = gtk_menu_item_new_with_label("Quit");
//
//	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
//	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
//	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
//	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 3);
//
//	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
//	g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(gtk_main_quit), NULL);
//
//	gtk_widget_show_all(window);
//
//	gtk_main();
//
//	return 0;
//}

/*图象菜单, mnemonics &accelerators*/
//#include "gtk/gtk.h"
//#include "gdk/gdkkeysyms.h"
//
//int main(int argc, char *argv[])
//{
//	GtkWidget *window;
//	GtkWidget *vbox;
//
//	GtkWidget *menubar;
//	GtkWidget *filemenu;
//	GtkWidget *file;
//	GtkWidget *New;	//C++项目里不可用new 故采用New
//	GtkWidget *open;
//	GtkWidget *quit;
//
//	GtkWidget *sep;
//
//	GtkAccelGroup *accel_group = NULL;
//
//	gtk_init(&argc, &argv);
//
//	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
//	gtk_window_set_default_size(GTK_WINDOW(window), 250, 200);
//	gtk_window_set_title(GTK_WINDOW(window), "menu");
//
//	vbox = gtk_vbox_new(FALSE, 0);
//	gtk_container_add(GTK_CONTAINER(window), vbox);
//
//	menubar = gtk_menu_bar_new();
//	filemenu = gtk_menu_new();
//
//	accel_group = gtk_accel_group_new();
//	gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);
//
//	file = gtk_menu_item_new_with_mnemonic("_File");
//	New = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW, NULL);
//	open = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, NULL);
//	sep = gtk_separator_menu_item_new();
//	quit = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, accel_group);
//
//	gtk_widget_add_accelerator(quit, "activate", accel_group, GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
//	
//	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
//	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), New);
//	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open);
//	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), sep);
//	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
//	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
//	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 3);
//
//	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
//
//	g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(gtk_main_quit), NULL);
//
//	gtk_widget_show_all(window);
//
//	gtk_main();
//
//	return 0;
//}

/*选择（Check）菜单选项 （menu item）*/
//#include "gtk/gtk.h"
//
//void toggle_statusbar(GtkWidget *widget, gpointer *statusbar)
//{
//	if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget)))
//	{
//		gtk_widget_show(statusbar);
//	}
//	else
//	{
//		gtk_widget_hide(statusbar);
//	}
//}
//
//int main(int argc, char *argv[])
//{
//	GtkWidget *window;
//	GtkWidget *vbox;
//	
//	GtkWidget *menubar;
//	GtkWidget *viewmenu;
//	GtkWidget *view;
//	GtkWidget *tog_stat;
//	GtkWidget *statusbar;
//
//	gtk_init(&argc, &argv);
//
//	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
//	gtk_window_set_default_size(GTK_WINDOW(window), 250, 200);
//	gtk_window_set_title(GTK_WINDOW(window), "view statusbar");
//
//	vbox = gtk_vbox_new(FALSE, 0);
//	gtk_container_add(GTK_CONTAINER(window), vbox);
//
//	menubar = gtk_menu_bar_new();
//	viewmenu = gtk_menu_new();
//
//	view = gtk_menu_item_new_with_label("View");
//	tog_stat = gtk_check_menu_item_new_with_label("View Statusbar");
//	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(tog_stat), TRUE);
//
//	gtk_menu_item_set_submenu(GTK_MENU_ITEM(view), viewmenu);
//	gtk_menu_shell_append(GTK_MENU_SHELL(viewmenu), tog_stat);
//	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), view);
//	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 3);
//
//	statusbar = gtk_statusbar_new();
//	gtk_box_pack_end(GTK_BOX(vbox), statusbar, FALSE, TRUE, 1);
//
//	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
//	g_signal_connect(G_OBJECT(tog_stat), "activate", G_CALLBACK(toggle_statusbar), statusbar);
//
//	gtk_widget_show_all(window);
//
//	gtk_main();
//
//	return 0;
//}

/*工具栏（A toolbar）*/
//#include "gtk/gtk.h"
//
//int main(int argc, char*argv[])
//{
//	GtkWidget *window;
//	GtkWidget *vbox;
//
//	GtkWidget *toolbar;
//	GtkToolItem *New;
//	GtkToolItem *open;
//	GtkToolItem *save;
//	GtkToolItem *sep;
//	GtkToolItem *exit;
//
//	gtk_init(&argc, &argv);
//
//	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
//	gtk_window_set_default_size(GTK_WINDOW(window), 250, 200);
//	gtk_window_set_title(GTK_WINDOW(window), "toolbar");
//
//	vbox = gtk_vbox_new(FALSE, 0);
//	gtk_container_add(GTK_CONTAINER(window), vbox);
//
//	toolbar = gtk_toolbar_new();
//	gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
//
//	gtk_container_set_border_width(GTK_CONTAINER(toolbar), 2);
//
//	New = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
//	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), New, -1);
//
//	open = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
//	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), open, -1);
//
//	save = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
//	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), save, -1);
//
//	sep = gtk_separator_tool_item_new();
//	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1);
//
//	exit = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
//	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), exit, -1);
//
//	gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);
//
//	g_signal_connect(G_OBJECT(exit), "clicked", G_CALLBACK(gtk_main_quit), NULL);
//	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
//
//	gtk_widget_show_all(window);
//
//	gtk_main();
//
//	return 0;
//}

/*功能失效（Undo redo）*/
//#include "gtk/gtk.h"
//#include "string.h"
//
//void undo_redo(GtkWidget *widget, gpointer *item)
//{
//	static int count = 2;
//	const char *name = gtk_widget_get_name(widget);
//
//	if (strcmp(name, "undo"))
//	{
//		count++;
//	}
//	else
//	{
//		count--;
//	}
//
//	if (count < 0)
//	{
//		gtk_widget_set_sensitive(widget, FALSE);
//		gtk_widget_set_sensitive(item, TRUE);
//	}
//
//	if (count > 5)
//	{
//		gtk_widget_set_sensitive(widget, FALSE);
//		gtk_widget_set_sensitive(item, TRUE);
//	}
//}
//
//int main(int argc, char *argv[])
//{
//	GtkWidget *window;
//	GtkWidget *vbox;
//	GtkWidget *toolbar;
//	GtkToolItem *undo;
//	GtkToolItem *redo;
//	GtkToolItem *sep;
//	GtkToolItem *exit;
//
//	gtk_init(&argc, &argv);
//
//	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
//	gtk_window_set_default_size(GTK_WINDOW(window), 250, 200);
//	gtk_window_set_title(GTK_WINDOW(window), "undoredo");
//
//	vbox = gtk_vbox_new(FALSE, 0);
//	gtk_container_add(GTK_CONTAINER(window), vbox);
//
//	toolbar = gtk_toolbar_new();
//	gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
//
//	gtk_container_set_border_width(GTK_CONTAINER(toolbar), 2);
//
//	undo = gtk_tool_button_new_from_stock(GTK_STOCK_UNDO);
//	gtk_widget_set_name(GTK_WIDGET(undo), "undo");
//	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), undo, -1);
//
//	redo = gtk_tool_button_new_from_stock(GTK_STOCK_REDO);
//	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), redo, -1);
//
//	sep = gtk_separator_tool_item_new();
//	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1);
//
//	exit = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
//	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), exit, -1);
//
//	gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);
//
//	g_signal_connect(G_OBJECT(undo), "clicked", G_CALLBACK(undo_redo), redo);
//
//	g_signal_connect(G_OBJECT(redo), "clicked", G_CALLBACK(undo_redo), undo);
//
//	g_signal_connect(G_OBJECT(exit), "clicked", G_CALLBACK(gtk_main_quit), NULL);
//
//	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
//
//	gtk_widget_show_all(window);
//
//	gtk_main();
//
//	return 0;
//}

/*GtkFixed*/
//#include <gtk/gtk.h>
//
//int main(int argc, char *argv[])
//{
//	GtkWidget *window;
//	GtkWidget *fixed;
//
//	GtkWidget *button1;
//	GtkWidget *button2;
//	GtkWidget *button3;
//
//	gtk_init(&argc, &argv);
//
//	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//	gtk_window_set_title(GTK_WINDOW(window), "GtkFixed");
//	gtk_window_set_default_size(GTK_WINDOW(window), 290, 200);
//	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
//
//	fixed = gtk_fixed_new();
//	gtk_container_add(GTK_CONTAINER(window), fixed);
//
//	button1 = gtk_button_new_with_label("Button1");
//	gtk_fixed_put(GTK_FIXED(fixed), button1, 150, 50);
//	gtk_widget_set_size_request(button1, 80, 35);
//
//	button2 = gtk_button_new_with_label("Button2");
//	gtk_fixed_put(GTK_FIXED(fixed), button2, 15, 15);
//	gtk_widget_set_size_request(button2, 80, 35);
//
//	button3 = gtk_button_new_with_label("Button3");
//	gtk_fixed_put(GTK_FIXED(fixed), button3, 100, 100);
//	gtk_widget_set_size_request(button3, 80, 35);
//
//	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
//
//	gtk_widget_show_all(window);
//
//	gtk_main();
//
//	return 0;
//}

/*GtkVBoxGtkHbox*/
//#include <gtk/gtk.h>
//
//int main(int argc, char *argv[])
//{
//	GtkWidget *window;
//	GtkWidget *vbox;
//
//	GtkWidget *settings;
//	GtkWidget *accounts;
//	GtkWidget *loans;
//	GtkWidget *cash;
//	GtkWidget *debts;
//
//	gtk_init(&argc, &argv);
//
//	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
//	gtk_window_set_default_size(GTK_WINDOW(window), 230, 250);
//	gtk_window_set_title(GTK_WINDOW(window), "GtkVBox");
//	gtk_container_set_border_width(GTK_CONTAINER(window), 5);
//
//	vbox = gtk_vbox_new(TRUE, 1);
//	gtk_container_add(GTK_CONTAINER(window), vbox);
//
//	settings = gtk_button_new_with_label("Settings");
//	accounts = gtk_button_new_with_label("Accounts");
//	loans = gtk_button_new_with_label("Loans");
//	cash = gtk_button_new_with_label("Cash");
//	debts = gtk_button_new_with_label("Debts");
//
//	gtk_box_pack_start(GTK_BOX(vbox), settings, TRUE, TRUE, 0);
//	gtk_box_pack_start(GTK_BOX(vbox), accounts, TRUE, TRUE, 0);
//	gtk_box_pack_start(GTK_BOX(vbox), loans, TRUE, TRUE, 0);
//	gtk_box_pack_start(GTK_BOX(vbox), cash, TRUE, TRUE, 0);
//	gtk_box_pack_start(GTK_BOX(vbox), debts, TRUE, TRUE, 0);
//
//	g_signal_connect_swapped(G_OBJECT(window), "destroy",
//		G_CALLBACK(gtk_main_quit), G_OBJECT(window));
//
//	gtk_widget_show_all(window);
//
//	gtk_main();
//
//	return 0;
//}