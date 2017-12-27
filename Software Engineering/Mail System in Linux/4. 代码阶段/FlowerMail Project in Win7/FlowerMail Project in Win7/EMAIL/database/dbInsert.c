#include "variable.h"
#include "database.h"
#include "formwindow.h"

void insertUserInfo(char *name,char *password,char *address,char *phone)
{
        MYSQL *mysql;
        mysql=mysql_init(NULL);
        MYSQL_RES *res;
        MYSQL_ROW row;
        int t=0;
	int i=0;
	int flag=validateName(name,password,address,phone);//退出标志
	char sql[100];
	if(mysql_real_connect(mysql,ip,username,userpwd,dataname,0,NULL,0))
        {
		if (flag==1)//如果存在则重新注册 
		{
			R_dialog=gtk_dialog_new_with_buttons("提示",GTK_WINDOW(R_window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
                	R_lbld=gtk_label_new("该用户名存在,请重新注册!");
                	gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(R_dialog)->vbox),R_lbld);//标签加入到对话框里
                	gtk_widget_show_all(R_dialog);//显示对话框里的信息
                	if(gtk_dialog_run(GTK_DIALOG(R_dialog))==GTK_RESPONSE_OK)
                	{
                        	gtk_widget_destroy(R_dialog);//ro不是or
                	}
			//printf("该用户名存在,请重新注册!\n");
			return;
		}
		//初始化参数字符串
	        //sprintf(sql,"insert into t_userInfo(name,password,address,phone) values(\"%s\",\"%s\",\"%s\",\"%s\")",name,password,address,phone); 
	        sprintf(sql,"insert into t_userInfo(name) values(\"%s\")",name); 
                t=mysql_query(mysql,sql);


				
					t = 1;
				
                if(!t)
                {	
	        	sprintf(sql,"update t_userInfo set password=\"%s\" where name=\"%s\"",password,name); 
                	t=mysql_query(mysql,sql);
			if(!t)
			{	
	        		sprintf(sql,"update t_userInfo set address=\"%s\" where name=\"%s\"",address,name); 
                		t=mysql_query(mysql,sql);
				if(!t)
				{		
	        			sprintf(sql,"update t_userInfo set phone=\"%s\" where name=\"%s\"",phone,name); 
                			t=mysql_query(mysql,sql);
					if(!t)
					{
						R_dialog=gtk_dialog_new_with_buttons("提示",GTK_WINDOW(R_window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
                        			R_lbld=gtk_label_new("注册成功!");
                        			gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(R_dialog)->vbox),R_lbld);//标签加入到对话框里
                        			gtk_widget_show_all(R_dialog);//显示对话框里的信息
                      				if(gtk_dialog_run(GTK_DIALOG(R_dialog))==GTK_RESPONSE_OK)
                        			{
                               				 gtk_widget_destroy(R_dialog);//ro不是or
                        			}
			                        //printf("成功!\n");
						gtk_widget_destroy(R_window);
						gtk_widget_show(L_window);
					}
				}
			}
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
}
	
void updateType(int n)
{
	MYSQL *mysql;
        mysql=mysql_init(NULL);
        MYSQL_RES *res;
        MYSQL_ROW row;
	char sql[100];
	char time[100];
	int t=0;
	int flag=0;
	if(mysql_real_connect(mysql,ip,username,userpwd,dataname,0,NULL,0))
        {
		t=mysql_query(mysql,"select * from t_emailInfo");
        	if(!t)
        	{
                 res=mysql_store_result(mysql);
                 while(row=mysql_fetch_row(res))
                 {
			if(!strcmp("2",row[0]))
                        {
                                        flag=1;//存在
					strcpy(time,row[7]);
                                        break;
                        }
                 }
                 mysql_free_result(res);
        	}
        	else
        	{
			fprintf(stderr,"%s\n",mysql_error(mysql));
 	       	}
		if(flag==1)
		{
			if(n==1)
			{
        			sprintf(sql,"update t_emailInfo set type='1' where date=\"%s\"",time);
			}
			else if(n==0)
			{
				sprintf(sql,"update t_emailInfo set type='0' where date=\"%s\"",time);
			}
        		t=mysql_query(mysql,sql);
        		if(!t)
        		{
                	       //printf("修改success!\n");
        		}
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
}

void modifyType(char *date)
{
	MYSQL *mysql;
        mysql=mysql_init(NULL);
	int t=0;
	char sql[100];
	if(mysql_real_connect(mysql,ip,username,userpwd,dataname,0,NULL,0))
	{
		sprintf(sql,"update t_emailInfo set type='-1' where date=\"%s\"",date);
                t=mysql_query(mysql,sql);
		if(!t)
		{
			//printf("修改成功!!\n");
			M_dialog=gtk_dialog_new_with_buttons("提示",GTK_WINDOW(M_window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
                        M_lbld=gtk_label_new("该邮件已放入垃圾箱!");
                        gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(M_dialog)->vbox),M_lbld);//标签加入到对话框里
                        gtk_widget_show_all(M_dialog);//显示对话框里的信息
                        if(gtk_dialog_run(GTK_DIALOG(M_dialog))==GTK_RESPONSE_OK)
                        {
                                 gtk_widget_destroy(M_dialog);//ro不是or
                        }
		}
	}
}

void deleteType(char *date)
{
        MYSQL *mysql;
        mysql=mysql_init(NULL);
        int t=0;
        char sql[100];
	if(mysql_real_connect(mysql,ip,username,userpwd,dataname,0,NULL,0))
        {
                sprintf(sql,"delete from t_emailInfo where date=\"%s\"",date);
                t=mysql_query(mysql,sql);
                if(!t)
                {
                        //printf("删除成功!!\n");
                        M_dialog=gtk_dialog_new_with_buttons("提示",GTK_WINDOW(M_window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
                        M_lbld=gtk_label_new("删除成功!");
                        gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(M_dialog)->vbox),M_lbld);//标签加入到对话框里
                        gtk_widget_show_all(M_dialog);//显示对话框里的信息
                        if(gtk_dialog_run(GTK_DIALOG(M_dialog))==GTK_RESPONSE_OK)
                        {
                                 gtk_widget_destroy(M_dialog);//ro不是or
                        }
                }
        }
}

void insertEmailInfo(char *type, char *title, char *sper, char *sadd, char *rper, char *radd, char *content)
{
	MYSQL *mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	mysql = mysql_init(NULL);
	int t = 0;
	int i = 0;
	char sql[100];
	char time[100];
	if (mysql_real_connect(mysql, ip, username, userpwd, dataname, 0, NULL, 0))
	{
		//printf("type=%s ",type);
		//printf("title=%s ",title);
		//printf("sper=%s ",sper);
		//printf("sadd=%s ",sadd);
		//printf("rper=%s ",rper);
		//printf("radd=%s ",radd);
		//printf("content=%s\n",content);
		//sprintf(sql,"insert into t_emailInfo values(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\")",type,sper,sadd,rper,radd,title,content);
				//t=mysql_query(mysql,sql);
		//sprintf(sql,"insert into t_emailInfo(type,sper,sadd,rper,radd,title,content) values(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\")",
			//type,sper,sadd,rper,radd,title,content);
		sprintf(sql, "insert into t_emailInfo(type) values(\"%s\")", type);
		t = mysql_query(mysql, sql);
		if (!t)
		{
			sprintf(sql, "update t_emailInfo set sper=\"%s\",sadd=\"%s\" where type='2'", sper, sadd);
			t = mysql_query(mysql, sql);
			//printf("1\n");
			if (!t)
			{
				//printf("2\n");
				sprintf(sql, "update t_emailInfo set rper=\"%s\",radd=\"%s\" where type='2'", rper, radd);
				t = mysql_query(mysql, sql);
				if (!t)
				{
					//printf("3\n");
					sprintf(sql, "update t_emailInfo set title=\"%s\",content=\"%s\" where type='2'", title, content);
					t = mysql_query(mysql, sql);
					if (!t)
					{
						/*printf("4\n");
											t=mysql_query(mysql,"select * from t_emailInfo where type='2'");//mysql不能一直用
						if(!t)
						{
							printf("5\n");
							updateType();
						}
										printf("success!\n");*/
										//printf("发送成功!\n");
						Edit_dialog = gtk_dialog_new_with_buttons("提示", GTK_WINDOW(Edit_window), GTK_DIALOG_MODAL, GTK_STOCK_OK, GTK_RESPONSE_OK, NULL);
						if (Edit_flag == 7)
						{
							Edit_lbld = gtk_label_new("发送成功!");
						}
						else if (Edit_flag == 2)
						{
							Edit_lbld = gtk_label_new("保存成功!");
						}
						gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(Edit_dialog)->vbox), Edit_lbld);//标签加入到对话框里
						gtk_widget_show_all(Edit_dialog);//显示对话框里的信息
						if (gtk_dialog_run(GTK_DIALOG(Edit_dialog)) == GTK_RESPONSE_OK)
						{
							gtk_widget_destroy(Edit_dialog);//ro不是or
						}

					}
					//printf("success!\n");
				}
				//printf("success!\n");
			}
		}
		else
		{
			fprintf(stderr, "%s\n", mysql_error(mysql));
		}
	}
	else
	{
		fprintf(stderr, "Connection Ererr:%s", mysql_error(mysql));
	}
	mysql_close(mysql);
}