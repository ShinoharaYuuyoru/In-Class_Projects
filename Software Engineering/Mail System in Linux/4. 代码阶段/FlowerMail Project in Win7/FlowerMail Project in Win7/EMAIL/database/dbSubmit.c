#include "variable.h"
#include "database.h"
#include "formwindow.h"

void submitString(char *str,int index)//截取字符串
{
	char temp[100];
	strcpy(temp,str);
	int i,j;
	for(i=index,j=0;*(str+i)!='\0';i++)
	{
		temp[j++]=*(str+i);
	}
	temp[j]='\0';
	strcpy(str,temp);
}

void submitDate(char *date)//提取日期
{
	int i,j;
	char temp[dateLength+1];
	for(i=strlen(date)-dateLength+1,j=0;i<strlen(date)-1;i++,j++)
	{
		temp[j]=date[i];
	}
	strcpy(date,temp);
}

void submitPerAdd(char *combine)//从复合字符串中提取姓名和地址
{
	int i,j,k;
	char peradd[perLength+addLength+1];
	for(i=0,j=0;;i++)
	{
		if(combine[i]=='<')
		{
			j++;
		}
		if(j==2)//遇到第二个'<'代表找到了per与add的组合
		{
			i++;
			break;
		}
	}	
	for(j=i,k=0;combine[j]!='>';j++,k++)
	{
		peradd[k]=combine[j];
	}
	peradd[k]='\0';
	//更新ME_rper和ME_radd
	for(i=0;peradd[i]!=';';i++)//人
	{
		ME_rper[i]=peradd[i];
	}
	ME_rper[i]='\0';
	for(j=i+1,k=0;peradd[j]!='\0';j++,k++)//地址
	{
		ME_radd[k]=peradd[j];
	}
	ME_radd[k]='\0';
	//更新ME_peradd字符串
	ME_peradd[0]='<';
	for(i=0;;i++)
	{
		if(peradd[i]==';')//找到地址
		{
			i++;
			break;
		}
	}
	for(j=i,k=1;peradd[j]!='\0';j++,k++)
	{
		ME_peradd[k]=peradd[j];
	}
	ME_peradd[k++]='>';
	ME_peradd[k++]=' ';
	for(j=0;peradd[j]!=';';j++)
	{
		ME_peradd[k++]=peradd[j];
	}
	ME_peradd[k++]=';';
	ME_peradd[k]='\0';
}

void submitTitle(char *combine)//从复合字符串中提取主题
{
	int i,j,k;
        for(i=0;;i++)
        {
                if(combine[i]=='[')
		{
			i++;
			break;
                }
        }
	ME_title[0]='R';
	ME_title[1]='e';
	ME_title[2]=':';
        for(j=i,k=3;combine[j]!=']';j++,k++)
        {
                ME_title[k]=combine[j];
        }
        ME_title[k]='\0';
}

void submitAddressFromName(char *name)
{
	MYSQL *mysql;
        mysql=mysql_init(NULL);
        MYSQL_RES *res;
        MYSQL_ROW row;
        int t=0;
	char sql[100];
	//submitString(name,1);//把'/t'去掉,提取/t之后的内容
	//printf("str:%s",name);
	if(mysql_real_connect(mysql,ip,username,userpwd,dataname,0,NULL,0))
        {
		sprintf(sql,"select address from t_userInfo where name=\"%s\"",name); //之前要截取字符串,否则传的是/tstr 
                t=mysql_query(mysql,sql);
                if(!t)
                {
                        res=mysql_store_result(mysql);
                        while(row=mysql_fetch_row(res))
                        {
				//printf("in\n");
				strcpy(name,row[0]);	
                        }
			//printf("str:%s\n",name);
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
        mysql_close(mysql);
	
}


