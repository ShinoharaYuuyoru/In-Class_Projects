#include "variable.h"
#include "database.h"
#include "formwindow.h"

void dbStringInit()//远程数据库参数字符串初始化
{	
	strcpy(ipadd,"10.10.35.43");
	strcpy(dbusername,"root");
	strcpy(dbuserpwd,"neusoft");
	strcpy(dbdataname,"db_email");
	ip=&ipadd[0];
	username=&dbusername[0];
	userpwd=&dbuserpwd[0];
	dataname=&dbdataname[0];
	//printf("ip=%s\n",ip);
        //printf("username=%s\n",username);
        //printf("userpwd=%s\n",userpwd);
        //printf("dataname=%s\n",dataname);
}

int main()
{
	dbStringInit();
	clientInit();	
	//registerInit();
	//loginInit();
	//mailInit();
	//editInit();
	return 0;
}
