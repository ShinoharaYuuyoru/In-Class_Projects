#include<gtk/gtk.h>
#include "struct.h"
void btnIcon1_clicked(GtkWidget *widget,MWIN *mwin)
{
	gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(mwin->tlNew),GTK_WIDGET(mwin->theme1->New));
	gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(mwin->tlRcv),GTK_WIDGET(mwin->theme1->Rcv));
	gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(mwin->tlDel),GTK_WIDGET(mwin->theme1->Del));
	gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(mwin->tlFind),GTK_WIDGET(mwin->theme1->Find));
	gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(mwin->tlThem),GTK_WIDGET(mwin->theme1->Them));
}
void btnIcon2_clicked(GtkWidget *widget,MWIN *mwin)
{
	gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(mwin->tlNew),GTK_WIDGET(mwin->theme2->New));
	gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(mwin->tlRcv),GTK_WIDGET(mwin->theme2->Rcv));
	gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(mwin->tlDel),GTK_WIDGET(mwin->theme2->Del));
	gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(mwin->tlFind),GTK_WIDGET(mwin->theme2->Find));
	gtk_tool_button_set_icon_widget(GTK_TOOL_BUTTON(mwin->tlThem),GTK_WIDGET(mwin->theme2->Them));
}
void btnOk_clicked(GtkWidget *widget,MWIN *mwin)
{
	gtk_widget_show_all(mwin->window);
}
gint theme_creat(MWIN *mwin)
{
	GtkWidget *window;
	GtkWidget *btnImg1;
	GtkWidget *btnImg2;
	GtkWidget *btnImg3;
	GtkWidget *btnImg4;
	GtkWidget *btnIcon1;
	GtkWidget *btnIcon2;
	GtkWidget *image1;
	GtkWidget *image2;
	GtkWidget *image3;
	GtkWidget *image4;
	GtkWidget *btnOk;
	GtkWidget *btnCancl;
	GtkWidget *backHBox;
	GtkWidget *btnHBox;
	GtkWidget *iconHBox;
	GtkWidget *iconVBox;
	GtkWidget *allVBox;
	GtkWidget *backFrame;
	GtkWidget *themeFrame;
	GtkWidget *VBox;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	backHBox=gtk_hbox_new(FALSE,0);
	gtk_box_set_spacing(GTK_BOX(backHBox),33);
	iconHBox=gtk_hbox_new(FALSE,0);
	iconVBox=gtk_vbox_new(FALSE,0);
	btnHBox=gtk_hbox_new(FALSE,0);
	allVBox=gtk_vbox_new(FALSE,0);
	backFrame=gtk_frame_new("背景选择");
	themeFrame=gtk_frame_new("主题选择");
	gtk_widget_set_size_request(backFrame,300,90);
	gtk_widget_set_size_request(themeFrame,300,150);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_widget_set_size_request(GTK_WIDGET(window),400,300);
	gtk_window_set_title(GTK_WINDOW(window), "主题背景选择");
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_modal(GTK_WINDOW(window),TRUE);
	btnOk=gtk_button_new_with_label("确定");
	btnCancl=gtk_button_new_with_label("取消");
	btnImg1=gtk_button_new();
	btnImg2=gtk_button_new();
	btnImg3=gtk_button_new();
	btnImg4=gtk_button_new();
	btnIcon1=gtk_button_new_with_label("主题一");
	btnIcon2=gtk_button_new_with_label("主题二");
	image1=gtk_image_new_from_file("../src/image1.jpg");
	image2=gtk_image_new_from_file("../src/image2.jpg");
	image3=gtk_image_new_from_file("../src/image3.jpg");
	image4=gtk_image_new_from_file("../src/image4.jpg");
	gtk_button_set_image(GTK_BUTTON(btnImg1),image1);
	gtk_button_set_image(GTK_BUTTON(btnImg2),image2);
	gtk_button_set_image(GTK_BUTTON(btnImg3),image3);
	gtk_button_set_image(GTK_BUTTON(btnImg4),image4);
	gtk_box_pack_start(GTK_BOX(btnHBox),btnOk,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(btnHBox),btnCancl,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(iconHBox),btnIcon1,TRUE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(iconHBox),btnIcon2,TRUE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(iconVBox),iconHBox,TRUE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(backHBox),btnImg1,FALSE,FALSE,3);
	gtk_box_pack_start(GTK_BOX(backHBox),btnImg2,FALSE,FALSE,3);
	gtk_box_pack_start(GTK_BOX(backHBox),btnImg3,FALSE,FALSE,3);
	gtk_box_pack_start(GTK_BOX(backHBox),btnImg4,FALSE,FALSE,3);
	gtk_container_add(GTK_CONTAINER(backFrame),backHBox);
	gtk_container_add(GTK_CONTAINER(themeFrame),iconVBox);
	gtk_box_pack_start(GTK_BOX(allVBox),backFrame,FALSE,FALSE,3);
	gtk_box_pack_start(GTK_BOX(allVBox),themeFrame,FALSE,FALSE,3);
	gtk_box_pack_end(GTK_BOX(allVBox),btnHBox,FALSE,FALSE,3);
	gtk_container_add(GTK_CONTAINER(window),allVBox);
	gtk_widget_show_all(window);
	g_signal_connect(G_OBJECT (btnIcon1),"clicked",G_CALLBACK (btnIcon1_clicked),mwin);
	g_signal_connect(G_OBJECT (btnIcon2),"clicked",G_CALLBACK (btnIcon2_clicked),mwin);
	g_signal_connect(G_OBJECT (btnOk),"clicked",G_CALLBACK (btnOk_clicked),mwin);
}
	
