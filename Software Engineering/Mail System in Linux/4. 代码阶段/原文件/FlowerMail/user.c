#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
struct newmail
{
GtkWidget *window;//主窗体
GtkWidget *addressee_label;//收件人标签
GtkWidget *title_label;//主题标签
GtkWidget *content_label;//内容标签
GtkWidget *copy_label;//抄送标签
GtkWidget *file_label;//附件标签
GtkWidget *send_button;//发送按钮
GtkWidget *save_button;//保存
GtkWidget *cancel_button;//关闭
GtkWidget *hbox1;
GtkWidget *hbox2;
GtkWidget *hbox3;
GtkWidget *hbox4;
GtkWidget *hbox5;
GtkWidget *hbox6;
GtkWidget *vbox;
GtkWidget *scrollwindow;
GtkWidget *toolbar;
GtkToolItem *sep;//分割
GtkToolItem *font;//字体
GtkToolItem *cfont;//颜色
GtkToolItem *ofile;//附件
//***********************************************************************
//点击关闭按钮后
GtkWidget *cancel_window;//关闭窗口
GtkWidget *cancel_vbox;
GtkWidget *cancel_hbox;
GtkWidget *cancel_bbox;
GtkWidget *cancel_buttonl;//按钮盒中的按钮
GtkWidget *cancel_label;
GtkWidget *cancel_image;
GtkWidget *cancel_sep;
};
//********************************************************************
//全局变量
static GtkWidget *addressee_entry,*title_entry,*content_entry,*mc_entry,*copy_entry,*file_entry;
static GtkWidget *view;
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
//******************************************************************************
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
//附件选择确定按钮回调函*******************************************************************************

void on_file_select_ok(GtkWidget * button,GtkFileSelection *fs)
{
    GtkWidget * dialog;	//对话框
    gchar message[1024];	//路径缓存
    const gchar * filename;//路径或文件名
    
    //从参数 fs 中获取路径
    filename = gtk_file_selection_get_filename(fs);
    
    //判断是否为目录
    if(g_file_test(filename,G_FILE_TEST_IS_DIR))		
		sprintf(message,"你选择的目录是:%s",filename);	//字符串连接
    else
		
                sprintf(message,"你选择的文件是:%s",filename);
                gtk_entry_set_text(GTK_ENTRY(file_entry),filename);
                 
    dialog = gtk_message_dialog_new(NULL,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,message,NULL);
    
    gtk_widget_destroy(GTK_WIDGET(fs));	//销毁文件选则对话框 fs
    gtk_dialog_run(GTK_DIALOG(dialog));	//显示dialog对话框并等待按钮,在有按钮按下之后继续
    gtk_widget_destroy(dialog);	        //销毁dialog对话框
}
//*******************************************************************************************

//附件按钮回调函数******************************************************************************

void on_button_clicked(GtkWidget * button,gpointer userdata)
{
    GtkWidget * dialog;
    
    //创建文件选择对话框
    dialog = gtk_file_selection_new("请选择一个文件活目录：");
    gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
    gtk_signal_connect(GTK_OBJECT(dialog),"destroy",
	    GTK_SIGNAL_FUNC(gtk_widget_destroy),&dialog);
	
	// 给确定按钮添加回掉函数
    g_signal_connect(
			GTK_OBJECT(GTK_FILE_SELECTION(dialog)->ok_button),
			 "clicked",
		    GTK_SIGNAL_FUNC(on_file_select_ok),
		    GTK_FILE_SELECTION(dialog));
//			G_CALLBACK(on_file_select_ok),
//			GTK_FILE_SELECTION(dialog));

	//给取消按钮添加回掉函数
	gtk_signal_connect_object(
			GTK_OBJECT(GTK_FILE_SELECTION(dialog)->cancel_button),
			"clicked",
			GTK_SIGNAL_FUNC(gtk_widget_destroy),
			GTK_OBJECT(dialog));

	gtk_widget_show(dialog);
}
//************************************************************************
/* 点击关闭后再点击"确认"按钮的回调函数 */
void on_ok_clicked(GtkButton *button,gpointer data)
{
	g_print("你选择的是确认.\n");
        //gtk_widget_destroy(window);
}

/*点击关闭后再点击"取消"按钮的回调函数 */
void on_cancel_clicked(GtkButton *button,gpointer data)
{
	g_print("你选择的是取消.\n");
}
void cancel_button_clicked(GtkWidget * Widget,gpointer userdata)
{
        GtkWidget *cancel_window;
	GtkWidget *cancel_vbox;
	GtkWidget *cancel_hbox;
	GtkWidget *cancel_bbox;
	GtkWidget *cancel_buttonl;
	GtkWidget *cancel_label;
	GtkWidget *cancel_image;
	GtkWidget *cancel_sep;
	
	/* 创建一个最上层的主窗口 */
	cancel_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(cancel_window),"destory",G_CALLBACK(gtk_main_quit),NULL);
	/* 设置窗口标题 */
	gtk_window_set_title(GTK_WINDOW(cancel_window),"确定/取消对话框");
	/* 设置窗口位置在屏幕中央 */                        
	gtk_window_set_position(GTK_WINDOW(cancel_window),GTK_WIN_POS_CENTER);
	/* 设置窗口边框的宽度 */
	gtk_container_set_border_width(GTK_CONTAINER(cancel_window),10);
	cancel_vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(cancel_window),cancel_vbox);
	cancel_hbox = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(cancel_vbox),cancel_hbox,FALSE,FALSE,5);
	/* 警告图标 */
	cancel_image = gtk_image_new_from_stock(GTK_STOCK_DIALOG_WARNING,GTK_ICON_SIZE_DIALOG);
	gtk_box_pack_start(GTK_BOX(cancel_hbox),cancel_image,FALSE,FALSE,5);
	cancel_label = gtk_label_new("这是一个保存/取消对话框.\n根据选择做出相应的操作.");
	gtk_box_pack_start(GTK_BOX(cancel_hbox),cancel_label,FALSE,FALSE,5);
	/* 分割线 */
	cancel_sep = gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(cancel_vbox),cancel_sep,FALSE,FALSE,5);
	/* 按钮盒 */
	cancel_bbox = gtk_hbutton_box_new();
	/* 为按钮盒设置布局 */
	gtk_button_box_set_layout(GTK_BUTTON_BOX(cancel_bbox),GTK_BUTTONBOX_SPREAD);
	gtk_box_pack_start(GTK_BOX(cancel_vbox),cancel_bbox,FALSE,FALSE,5);
	/* 创建一个"确定"按钮 */
	cancel_buttonl = gtk_button_new_from_stock(GTK_STOCK_SAVE);
	g_signal_connect(G_OBJECT(cancel_buttonl),"clicked",G_CALLBACK(on_ok_clicked),NULL);
	/* 关闭对话框 */
	g_signal_connect_swapped(G_OBJECT(cancel_buttonl),"clicked",G_CALLBACK(gtk_widget_destroy),cancel_window);
	gtk_box_pack_start(GTK_BOX(cancel_bbox),cancel_buttonl,FALSE,FALSE,0);
	
	/* 创建一个"取消"按钮 */
	cancel_buttonl = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
	g_signal_connect(G_OBJECT(cancel_buttonl),"clicked",G_CALLBACK(on_cancel_clicked),NULL);
	/* 关闭对话框 */
	g_signal_connect_swapped(G_OBJECT(cancel_buttonl),"clicked",G_CALLBACK(gtk_widget_destroy),cancel_window);	
	gtk_box_pack_start(GTK_BOX(cancel_bbox),cancel_buttonl,FALSE,FALSE,0);
	/* 显示所有窗体 */
	gtk_widget_show_all(cancel_window);
}


//主函数＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
int main (int argc, char *argv[])
{
  GtkWidget *window;
 GtkWidget *addressee_label,*title_label,*content_label,*mc_label,*copy_label,*file_label;
 
  
  GtkWidget *send_button,*save_button,*cancel_button;
  GtkWidget *hbox1, *hbox2,*hbox3,*hbox4,*hbox5,*hbox6;
  GtkWidget *vbox;
  GtkWidget *scrollwindow;
  GtkToolItem *sep;
  GtkWidget *toolbar;
  GtkToolItem *font;
  GtkToolItem *cfont;
  GtkToolItem *ofile;
  gtk_init(&argc, &argv);

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
  hbox4 = gtk_hbox_new ( FALSE, 5 );
  hbox5 = gtk_hbox_new ( FALSE, 5 );
  hbox6 = gtk_hbox_new ( FALSE, 5 );
  vbox = gtk_vbox_new ( FALSE, 10);
  
  

  gtk_box_pack_start(GTK_BOX(hbox1), addressee_label, FALSE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(hbox1), addressee_entry, TRUE, TRUE, 5);

  gtk_box_pack_start(GTK_BOX(hbox2), title_label, FALSE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(hbox2), title_entry,  TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(hbox5), copy_label, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(hbox5), copy_entry, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(hbox6), file_label, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(hbox6), file_entry, TRUE, TRUE, 5);
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
  
  g_signal_connect(G_OBJECT(cancel_button), "clicked",G_CALLBACK(cancel_button_clicked), NULL);

 g_signal_connect(G_OBJECT(ofile), "clicked",G_CALLBACK(on_button_clicked), NULL);//附件按钮信号
  
 
  g_signal_connect(G_OBJECT(cfont), "clicked", G_CALLBACK(select_cfont),//颜色信号
view);
  
  g_signal_connect(G_OBJECT(font), "clicked", G_CALLBACK(select_font),//字体信号
view);

  g_signal_connect_swapped(G_OBJECT(window),
"destroy",G_CALLBACK(gtk_main_quit), NULL);

  gtk_container_add(GTK_CONTAINER(window), vbox);
 
  gtk_widget_show_all(window);
  gtk_main ();

  return 0;

} 

