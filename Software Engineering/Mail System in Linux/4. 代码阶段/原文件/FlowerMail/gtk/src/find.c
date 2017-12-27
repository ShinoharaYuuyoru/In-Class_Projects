void find_creat()
{
	GtkWidget *window;
	GtkWidget *etyFind;
	GtkWidget *lblFind;
	GtkWidget *btnOk;
	GtkWidget *btnCancl;
	GtkWidget *btnHBox;
	GtkWidget *findHBox;
	GtkWidget *allVBox;
	
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_widget_set_size_request(GTK_WIDGET(window),200,100);
	gtk_window_set_title(GTK_WINDOW(window), "查找");
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_modal(GTK_WINDOW(window),TRUE);
	etyFind=gtk_entry_new();
	label=gtk_label_new("查找：");
	btnOk=gtk_button_new_with_label("查找");
	btnCancl=gtk_button_new_with_label("取消");
	btnHBox=gtk_hbox_new(FALSE,0);
	findHBox=gtk_hbox_new(FALSE,0);
	allVBox=gtk_vbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(btnHBox),btnOk,TRUE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(btnHBox),btnCancl,TRUE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(findHBox),lablFind,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(findHBox),etyFind,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(allVBox),findHBox,TRUE,TRUE,0);
	gtk_box_pack_end(GTK_BOX(allVBox),btnHBox,FALSE,FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),allVBox);
	gtk_widget_show_all(window);
}
	
