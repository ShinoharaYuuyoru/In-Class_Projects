enum{
LOGIN,
REGISTER,
SENDMAIL,
ALL_EMAIL,
DELETE,
SEARCH,
BG_CHANGE,
TITLE_CHANGE,
NOT_SEE_EMAIL,
HAD_SEND_EMAIL,
TRASH_EMAIL,
DRAFTMAIL,
DELETEINGAIN,
RESUMEMAIL
};

typedef struct User
{
	char UserName[20];
	char Password[20];
	int theme;
	int back;
}USER;
typedef struct THEME
{
	char UserName[20];
	char Title[30];
	char BlackGround[30];
}THEME;
typedef struct Mail
{
	char From[20];
	char To[10][20];
	char Title[50];
	int SendType;
	unsigned int ColorR;
	unsigned int ColorG;
	unsigned int ColorB;
	char FontName[30];
	int FontSize;
	char AttatchName[5][30];
}MAIL;



gint login_confirm(USER user,int signal);
gint register_creat(USER user,int signal);
MAIL* GetMailNotSee(char *UserName,int signal,char read)//??????
MAIL* SeeAllMail(char *UserName,int signal,char rstatus);//????
MAIL* MailHadSend(char* UserName,int signal,char sstatus);
MAIL* MailIntoTrash(char* UserName,int signal,char sstatus,char rstatus);
MAIL* DraftMail(char* UserName,int signal,char sstatus);
MAIL* SendMail(MAIL mail,int signal);
int DeleteMail(char* UserName,int signal,int type);
int change_title(THEME theme,int signal);
int change_BlackGround(THEME theme,int signal);

