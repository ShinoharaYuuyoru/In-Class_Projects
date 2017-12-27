#include <malloc.h>
#include <string.h>
#include <memory.h>
#include "struct.h"
void destroy(GtkWidget *widget, gpointer data);
gint theme_creat(MWIN *mwin);
LOGIN* login_creat();
void login_run(LOGIN *login);
REG* register_creat();
void register_run(REG *reg);
MWIN* mainWin_creat(gint isTheme);
void mainWin_run();
