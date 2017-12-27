#include "variable.h"
#include "database.h"
#include "formwindow.h"

int validateLogin(char *name,char *password)
{
        MYSQL *mysql;
        mysql=mysql_init(NULL);
        MYSQL_RES *res;
        MYSQL_ROW row;
        int t=0;
        int i=0;
	int ret=0;//返回值
        /*if(mysql_real_connect(mysql,ip,username,userpwd,dataname,0,NULL,0))
        {
                t=mysql_query(mysql,"select name,password from t_userInfo");
                if(!t)
                {
                        res=mysql_store_result(mysql);
                        while(row=mysql_fetch_row(res))
                        {
				if(strcmp(name,row[0])==0)//存在昵称
				{
					if(strcmp(password,row[1])==0)//密码相同
					{
						ret=1;
						break;
					}
					else
					{
						ret=-1;
						break;
					}
				}
                        }
			//printf("该用户不存在,请注册!\n");
                }
                else
                {
                        fprintf(stderr,"%s\n",mysql_error(mysql));
                }
                mysql_free_result(res);
        }
        else
        {
                fprintf(stderr,"Connection Ererr:%s",mysql_error(mysql));
        }
        mysql_close(mysql);*/
	return ret;
}

int validateName(char *name,char *password,char *address,char *phone)
{
	MYSQL *mysql;
        mysql=mysql_init(NULL);
        MYSQL_RES *res;
        MYSQL_ROW row;
        int t=0;
        int i=0;
        int flag=0;//退出标志
        char sql[100];
	if(mysql_real_connect(mysql,ip,username,userpwd,dataname,0,NULL,0))
        {
                //遍历表
                t=mysql_query(mysql,"select * from t_userInfo");
                if(!t)
                {
                        res=mysql_store_result(mysql);
                        while(row=mysql_fetch_row(res))
                        {
                                if(!strcmp(name,row[0]))
                                {
                                        flag=1;//存在
                                        break;
                                }
                        }
                        mysql_free_result(res);//释放结果集
                }
                else
                {
                        fprintf(stderr,"%s\n",mysql_error(mysql));
                }
       }
       else
       {
                fprintf(stderr,"Connection Ererr:%s",mysql_error(mysql));
       }
       mysql_close(mysql);
       return flag;
}
