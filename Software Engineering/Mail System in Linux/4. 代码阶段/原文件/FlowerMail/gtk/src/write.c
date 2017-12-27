#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
//字体选择函数***********************************************************************************
void select_font(GtkWidget *widget, gpointer view)
{
GtkResponseType result;
GtkWidget *dialog = gtk_font_selection_dialog_new("Select Font");
result = gtk_dialog_run(GTK_DIALOG(dialog));
if (result == GTK_RESPONSE_OK || result == GTK_RESPONSE_APPLY)
{
PangoFontDescription *font_desc;
gchar *fontname = gtk_font_selection_dialog_get_font_name(GTK_FONT_SELECTION_DIALOG(dialog));
font_desc = pango_font_description_from_string(fontname);
gtk_widget_modify_font(GTK_WIDGET(view), font_desc);
g_free(fontname);
}
gtk_widget_destroy(dialog);
}
//颜色选择函数************************************************************************************
void select_cfont(GtkWidget *widget, gpointer view)
{
GtkResponseType result;
GtkColorSelection *colorsel;
GtkWidget *dialog = gtk_color_selection_dialog_new("Font Color");
result = gtk_dialog_run(GTK_DIALOG(dialog));
if (result == GTK_RESPONSE_OK) 
{
GdkColor color;
colorsel = GTK_COLOR_SELECTION
(
GTK_COLOR_SELECTION_DIALOG(dialog)->colorsel);
gtk_color_selection_get_current_color(colorsel, &color);
gtk_widget_modify_fg(GTK_WIDGET(view),GTK_STATE_NORMAL,&color);
}
gtk_widget_destroy(dialog);
}
//******************************************************************************
void file_ok_sel( GtkWidget        *w,
                  GtkFileSelection *fs )
{
    g_print ("%s\n", gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs)));
}
//*********************************************************************************
gint delete_event()
{
	
	
}
//打开文件函数＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
void gtk_filew(void file_ok_sel())
{
  
    GtkWidget *filew;
    GtkResponseType result;
   // gtk_init (&argc, &argv);
    
    /* 创建一个新的文件选择构件 */
    filew = gtk_file_selection_new ("File selection");
    
  //  g_signal_connect (G_OBJECT (filew), "destroy",
	             // G_CALLBACK (delete_event), NULL);
    /* 为ok_button按钮设置回调函数，连接到file_ok_sel function函数 */
    g_signal_connect (G_OBJECT (GTK_FILE_SELECTION (filew)->ok_button),
		      "clicked", 
                      G_CALLBACK (file_ok_sel), filew);
    
    /* 为cancel_button设置回调函数，销毁构件 */
   // g_signal_connect_swapped (G_OBJECT (GTK_FILE_SELECTION (filew)->cancel_button),
	                    //  "clicked", 
                             // G_CALLBACK (gtk_widget_destroy), filew);
    
    /* 设置文件名，比如这个一个文件保存对话框，我们给了一个缺省文件名 */
   // gtk_file_selection_set_filename (GTK_FILE_SELECTION(filew), 
				     //"penguin.png");
gtk_widget_show (filew);
}

//主函数＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
static GtkWidget* write()
{
  GtkWidget *window;
 GtkWidget *addressee_label,*title_label,*content_label,*mc_label,*copy_label,*file_label;
 GtkWidget *addressee_entry,*title_entry,*content_entry,*mc_entry,*copy_entry,*file_entry;
  GtkWidget *view;
  GtkWidget *send_button,*save_button,*cancel_button;
  GtkWidget *hbox1, *hbox2,*hbox3,*hbox4,*hbox5,*hbox6;
  GtkWidget *vbox;
  GtkWidget *scrollwindow;
  //GtkTextBuffer *a;
  //GtkWidget *filew;
  GtkToolItem *sep;
  GtkWidget *toolbar;
  GtkToolItem *font;
  GtkToolItem *cfont;
  GtkToolItem *ofile;
 

//窗口设置
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "新建邮件");
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);

//标签显示文本
  addressee_label = gtk_label_new("收件人:");
  title_label = gtk_label_new("  主题:");
  copy_label=gtk_label_new("  抄送:");
  content_label=gtk_label_new("  内容:");
  file_label=gtk_label_new("  附件:");
  scrollwindow=gtk_scrolled_window_new(NULL,NULL);
  view = gtk_text_view_new();
  gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(view),GTK_WRAP_WORD_CHAR);
  gtk_container_add(GTK_CONTAINER(scrollwindow), view);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrollwindow),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
  //a=gtk_text_view_get_buffer(view);

  toolbar = gtk_toolbar_new();
  gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
  gtk_container_set_border_width(GTK_CONTAINER(toolbar), 2);
  font = gtk_tool_button_new_from_stock(GTK_STOCK_SELECT_FONT);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), font, -1);
  cfont = gtk_tool_button_new_from_stock(GTK_STOCK_SELECT_COLOR);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), cfont, -1);
  sep = gtk_separator_tool_item_new();
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1);
  ofile = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), ofile, -1);
   
  
    
//
  addressee_entry = gtk_entry_new();
  title_entry = gtk_entry_new();
  content_entry = gtk_entry_new();
  copy_entry = gtk_entry_new();	
  file_entry = gtk_entry_new();
//按钮显示文本
  send_button = gtk_button_new_with_label("发送");
  save_button = gtk_button_new_with_label("保存");
  cancel_button = gtk_button_new_with_label("关闭");
  

 

  hbox1 = gtk_hbox_new ( FALSE, 5 );
  hbox2 = gtk_hbox_new ( FALSE, 5 );
  hbox3 = gtk_hbox_new ( FALSE, 5 );
  hbox4 = gtk_hbox_new ( FALSE, 5 );//
  hbox5 = gtk_hbox_new ( FALSE, 5 );
  hbox6 = gtk_hbox_new ( FALSE, 5 );
  vbox = gtk_vbox_new ( FALSE, 10);
  
  

  gtk_box_pack_start(GTK_BOX(hbox1), addressee_label, FALSE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(hbox1), addressee_entry, FALSE, TRUE, 5);

  gtk_box_pack_start(GTK_BOX(hbox2), title_label, FALSE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(hbox2), title_entry, FALSE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(hbox5), copy_label, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(hbox5), copy_entry, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(hbox6), file_label, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(hbox6), file_entry, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(hbox3), content_label, FALSE, FALSE, 5);
  
  gtk_box_pack_start(GTK_BOX(hbox4), send_button, TRUE, FALSE, 5);//
  gtk_box_pack_start(GTK_BOX(hbox4), save_button, TRUE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(hbox4), cancel_button, TRUE, FALSE, 5);

  gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);//

  gtk_box_pack_start(GTK_BOX(vbox), hbox1, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), hbox2, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), hbox5, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), hbox6, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), hbox3, FALSE, FALSE,0);

  gtk_box_pack_start(GTK_BOX(vbox), scrollwindow, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), hbox4, FALSE, FALSE, 0);//

 g_signal_connect(G_OBJECT(ofile), "clicked",G_CALLBACK(gtk_filew), NULL);//附件按钮信号
  
 
  g_signal_connect(G_OBJECT(cfont), "clicked", G_CALLBACK(select_cfont),//颜色信号
view);
  
  g_signal_connect(G_OBJECT(font), "clicked", G_CALLBACK(select_font),//字体信号
view);

  g_signal_connect_swapped(G_OBJECT(window),
"destroy",G_CALLBACK(gtk_main_quit), NULL);

  gtk_container_add(GTK_CONTAINER(window), vbox);
 
  gtk_widget_show_all(window);
 

  return window;

} 

