#include<gtk/gtk.h>	
#include"include.h"
//=====global variable=======
gint LoginCount=0;//count the times of login

//===========================
int main(int argc,char *argv[])
{
	
	LOGIN *login;
	gtk_init (&argc, &argv);
	login=login_creat();
	login_run(login);
	gtk_main ();
	return 0;
}
