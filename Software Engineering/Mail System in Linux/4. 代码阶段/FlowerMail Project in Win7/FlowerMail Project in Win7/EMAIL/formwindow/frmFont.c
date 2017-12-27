#include "variable.h"
#include "database.h"
#include "formwindow.h"

void fontInit(GtkWidget *widget,gpointer data)
{
	GtkResponseType result;
	GtkWidget *dialog=gtk_font_selection_dialog_new("字体");
	result=gtk_dialog_run(GTK_DIALOG(dialog));
	if(result==GTK_RESPONSE_OK||result==GTK_RESPONSE_APPLY)
	{
		PangoFontDescription *font_desc;
		char *fontname=gtk_font_selection_dialog_get_font_name(GTK_FONT_SELECTION_DIALOG(dialog));
		font_desc=pango_font_description_from_string(fontname);
		gtk_widget_modify_font(GTK_WIDGET(data),font_desc);
		g_free(fontname);
	}
	gtk_widget_destroy(dialog);
}