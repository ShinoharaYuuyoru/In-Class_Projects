#makefile for email
Cdb = ./database/*.c
Cfrm = ./formwindow/*.c
Cclient = ./socket/soClient.c
Cservice= ./socket/soService.c
P = `pkg-config --libs --cflags gtk+-2.0`
I = -I ./include -I /usr/include/mysql 
L = -L ./include -L /usr/lib/mysql
Ddb = ./database
Dfrm = ./formwindow
Dso = ./socket
Di = ./include
gcc:$
	gcc  $(Cdb) $(Cfrm) $(Cclient) main.c $(P) -o test1 $(I) $(L) -lmysqlclient;./test1
show:$
	cd $(Ddb);vi dbShow.c;cd ..
validate:$
	cd $(Ddb);vi dbValidate.c;cd ..
insert:$
	cd $(Ddb);vi dbInsert.c;cd ..
submit:$
	cd $(Ddb);vi dbSubmit.c;cd ..
login:$
	cd $(Dfrm);vi frmLogin.c;cd ..
register:$
	cd $(Dfrm);vi frmRegister.c;cd ..
mail:$
	cd $(Dfrm);vi frmMail.c;cd ..
edit:$
	cd $(Dfrm);vi frmEdit.c;cd ..
color:$
	cd $(Dfrm);vi frmColor.c;cd ..
font:$
	cd $(Dfrm);vi frmFont.c;cd ..
add:$
	cd $(Dfrm);vi frmAdd.c;cd ..
client:$
	cd $(Dso);vi soClient.c;cd ..
service:$
	cd $(Dso);vi soService.c;cd ..
sr:$
	gcc $(Cservice) -o sr.exe;./sr.exe;rm -f sr.exe 
db:$
	cd $(Di);vi database.h;cd ..
frm:$
	cd $(Di);vi formwindow.h;cd ..
va:$
	cd $(Di);vi variable.h;cd ..


