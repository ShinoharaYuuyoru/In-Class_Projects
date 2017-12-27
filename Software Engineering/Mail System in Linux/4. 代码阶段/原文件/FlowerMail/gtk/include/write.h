#include<gtk/gtk.h>
void select_font(GtkWidget *widget, gpointer view);
void select_cfont(GtkWidget *widget, gpointer view);
void file_ok_sel( GtkWidget *w,GtkFileSelection *fs );
gint delete_event();
void gtk_filew(void file_ok_sel());
static GtkWidget* write();
