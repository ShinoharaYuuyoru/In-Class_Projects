#include "variable.h"
#include "database.h"
#include "formwindow.h"

void fileInit(GtkWidget *widget, gpointer data)	//头文件有更改！！！！！！
{
	GtkWidget *SelectFile;

	SelectFile = gtk_file_chooser_dialog_new("选择文件", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OK, GTK_RESPONSE_ACCEPT, NULL);
	if (gtk_dialog_run(GTK_DIALOG(SelectFile)) == GTK_RESPONSE_ACCEPT)
	{
		data = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(SelectFile));

		gchar *PrintFileName = '\0';
		PrintFileName = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(SelectFile));
		g_print("%s\n", PrintFileName);
		
		gtk_widget_destroy(SelectFile);
	}
	else
	{
		gtk_widget_destroy(SelectFile);
	}
}