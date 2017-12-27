#include "variable.h"
#include "database.h"
#include "formwindow.h"

void connectdb()
{
	MYSQL *mysql;
	mysql=mysql_init(NULL);
	if(mysql_real_connect(mysql,ip,username,userpwd,dataname,0,NULL,0))
	{
		//printf("ip=%s\n",ip);
                //printf("username=%s\n",username);
                //printf("userpwd=%s\n",userpwd);
                //printf("dataname=%s\n",dataname);
		printf("success!\n");
	}
	else
	{
		fprintf(stderr,"Connection Ererr:%s",mysql_error(mysql));
	}
	mysql_close(mysql);
}

void itos(char *id,int n)
{
    	int i=1,j;
	id[0]='<';
        while(n!=0)
        {
            id[i++]=n%10+'0';
            n/=10;
        }
        for(j=i;j<idLength-1;j++)
        {
            id[j]=' ';
        }
	id[j]='>';
        id[idLength]='\0';
}

void titleAddBlank(char *title)
{
    	int i,j;
	char temp[titleLength+1];
	temp[0]='[';
	for(i=0,j=1;i<strlen(title);i++,j++)
	{
		temp[j]=title[i];
	}
	temp[j++]=']';
	temp[j]='\0';
	strcpy(title,temp);
}

void perAddBlank(char *per)
{
	int i,j;
	char temp[perLength+1];
	temp[0]='<';
	for(i=0,j=1;i<strlen(per);i++,j++)
	{
		temp[j]=per[i];
	}
	temp[j++]=';';
	temp[j]='\0';
	strcpy(per,temp);
}

void addAddBlank(char *add)
{
    	int i,j;
	char temp[addLength+1];
	for(i=0;i<strlen(add);i++)
	{
		temp[i]=add[i];
	}
	temp[i++]='>';
	temp[i]='\0';
	strcpy(add,temp);
}

void dateAddBlank(char *date)
{
	int i,j;
        char temp[dateLength+1];
        temp[0]='[';
        for(i=0,j=1;i<strlen(date);i++,j++)
        {
                temp[j]=date[i];
        }
        temp[j++]=']';
        temp[j]='\0';
        strcpy(date,temp);
}

void showCombine(char *combine,int n,char *title,char *per,char *add,char *date)
{
	char id[idLength+1];
	int i=0,j=0;
	//更新id
	itos(id,n);
	//printf("%s",id);
	//更新主题
	titleAddBlank(title);
	//printf("%s",title);
	//更新人
	perAddBlank(per);
	//printf("%s",per);
	//更新地址
	addAddBlank(add);
	//printf("%s",add);
	//更新时间
	dateAddBlank(date);
	//printf("%s\n",date);
	for(i=0;i<strlen(id);i++)
	{
		combine[j++]=id[i];
	}
	for(i=0;i<strlen(title);i++)
	{
		combine[j++]=title[i];
	}
	for(i=0;i<strlen(per);i++)
	{
		combine[j++]=per[i];
	}
	for(i=0;i<strlen(add);i++)
	{
		combine[j++]=add[i];
	}
	for(i=0;i<strlen(date);i++)
	{
		combine[j++]=date[i];
	}
	//printf("j=%d\n",j);
	combine[j]='\0';
}

void showUserInfo()
{
	MYSQL *mysql;
	mysql=mysql_init(NULL);
	MYSQL_RES *res;
	MYSQL_ROW row;
	int t=0;
	int i=0;
	//if(mysql_real_connect(mysql,"localhost","root","","db_email",0,NULL,0))
	if(mysql_real_connect(mysql,ip,username,userpwd,dataname,0,NULL,0))
	{	
		t=mysql_query(mysql,"select * from t_userInfo");
		if(!t)
		{
			res=mysql_store_result(mysql);
			while(row=mysql_fetch_row(res))
			{
				for(i=0;i<mysql_num_fields(res);i++)	
				{
					printf("%s ",row[i]);
				}	
				printf("\n");
			}
		}
		else
		{
			fprintf(stderr,"%s\n",mysql_error(mysql));
		}
		//printf("success!\n");
		mysql_free_result(res);
		
	}
	else
	{
		fprintf(stderr,"Connection Ererr:%s",mysql_error(mysql));
	}	
	mysql_close(mysql);
}

void showListName()
{	
	MYSQL *mysql;
        mysql=mysql_init(NULL);
        MYSQL_RES *res;
        MYSQL_ROW row;
        int t=0;
        int i=0;
	char name[30];
        if(mysql_real_connect(mysql,ip,username,userpwd,dataname,0,NULL,0))
	{
                t=mysql_query(mysql,"select name from t_userInfo");
                if(!t)
                {
                        res=mysql_store_result(mysql);
                        while(row=mysql_fetch_row(res))
                        {
				sprintf(name,"\t%s",row[0]);
				E_add_to_list(name);
                        }
                }
                else
                {
                        fprintf(stderr,"%s\n",mysql_error(mysql));
                }
                //printf("success!\n");
                mysql_free_result(res);

        }
        else
        {
                fprintf(stderr,"Connection Ererr:%s",mysql_error(mysql));
        }
        mysql_close(mysql);
}

void showListEmail(char *typeid,int choice)
{
        MYSQL *mysql;
        mysql=mysql_init(NULL);
        MYSQL_RES *res;
        MYSQL_ROW row;
        int t=0;
	int n=0;//计数变量
	char sper[perLength+1];//发件人
	char sadd[addLength+1];//发件人地址
	char rper[perLength+1];//收件人
	char radd[addLength+1];//收件人地址
	char title[titleLength+1];//主题
	char content[1000];//内容
	char date[dateLength+1];//时间
	char combine[1000];//组合体
	char sql[100];
	if(mysql_real_connect(mysql,ip,username,userpwd,dataname,0,NULL,0))
        {
		//printf("loginerName:%s\n",loginerName);
		if(choice==1)//显示发件人
		{
			sprintf(sql,"select * from t_emailInfo where type=\"%s\" and rper=\"%s\"",typeid,loginerName);		
		}
		else if(choice==2||choice==3)//显示收件人
		{
			sprintf(sql,"select * from t_emailInfo where type=\"%s\" and sper=\"%s\"",typeid,loginerName);		
		}
		else if(choice==4)//显示垃圾
		{
			sprintf(sql,"select * from t_emailInfo where rper=\"%s\" or sper=\"%s\" and type=\"%s\"",loginerName,loginerName,typeid);
		}
                t=mysql_query(mysql,sql);
                if(!t)
                {
                        res=mysql_store_result(mysql);
                        while(row=mysql_fetch_row(res))
                        {
				n++;
				strcpy(title,row[5]);
                                strcpy(date,row[7]);
				//strcpy(content,row[6]);
				if(choice==1||choice==4)
				{
                                	strcpy(sper,row[1]);
                                	strcpy(sadd,row[2]);
					showCombine(combine,n,title,sper,sadd,date);
					//sprintf(combine,"%5d %s %s %s %s",n,title,sper,sadd,date);
				}
				else if(choice==2||choice==3)
				{
					strcpy(rper,row[3]);
                                        strcpy(radd,row[4]);
					showCombine(combine,n,title,rper,radd,date);
					//submitDate(date);
					//printf("date=%s**\n",date);
					//sprintf(combine,"%5d %s %s %s %s",n,title,rper,radd,date);
				}
				//printf("%s\n",combine);
                                M_add_to_list2(combine);
				//gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(M_txt)),content,-1);//测试写入文本视图区内容
                        }
                }
                else
                {
                        fprintf(stderr,"%s\n",mysql_error(mysql));
                }
                //printf("success!\n");
                mysql_free_result(res);
        }
        else
        {
                fprintf(stderr,"Connection Ererr:%s",mysql_error(mysql));
        }
        mysql_close(mysql);
}

void showContent(char *date)
{
	MYSQL *mysql;
	mysql=mysql_init(NULL);
        MYSQL_RES *res;
        MYSQL_ROW row;
        int t=0;
	char sql[100];
	char content[1000];
	if(mysql_real_connect(mysql,ip,username,userpwd,dataname,0,NULL,0))
        {
		sprintf(sql,"select * from t_emailInfo where date=\"%s\"",date);
		//printf("date=%s\n",date);
                t=mysql_query(mysql,sql);
                if(!t)
                {
                        res=mysql_store_result(mysql);
                        while(row=mysql_fetch_row(res))
                        {
				strcpy(content,row[6]);
				//printf("content=%s\n",content);	
				gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(M_txt)),content,-1);//测试写入文本视图区内容
                        }
                }
                else
                {
                        fprintf(stderr,"%s\n",mysql_error(mysql));
                }
                //printf("success!\n");
                mysql_free_result(res);

        }
        else
        {
                fprintf(stderr,"Connection Ererr:%s",mysql_error(mysql));
        }
        mysql_close(mysql);

}

