#include "variable.h"
#include "database.h"
#include "formwindow.h"

void colorInit(GtkWidget *widget,gpointer data)
{
	GtkColorSelection *colorsel;
	GtkResponseType response;
	GtkWidget *colorseldlg;
	GdkColor color;
	colorseldlg = gtk_color_selection_dialog_new ("颜色选择");
	colorsel = GTK_COLOR_SELECTION (GTK_COLOR_SELECTION_DIALOG (colorseldlg)->colorsel);
	gtk_color_selection_set_has_opacity_control(colorsel,TRUE);
	response = gtk_dialog_run (GTK_DIALOG (colorseldlg));
	if(response==GTK_RESPONSE_OK)
	{
		gtk_color_selection_get_current_color (colorsel, &color);
		gtk_widget_modify_text(data, GTK_STATE_NORMAL, &color);
  		//gtk_widget_modify_bg (data, GTK_STATE_NORMAL, &color);
	}

	gtk_widget_destroy(colorseldlg);
}