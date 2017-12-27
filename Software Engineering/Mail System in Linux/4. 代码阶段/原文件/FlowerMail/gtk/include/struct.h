typedef struct THEME
{
	GtkWidget *New;
	GtkWidget *Rcv;
	GtkWidget *Del;
	GtkWidget *Find;
	GtkWidget *Them;
}THEME;
typedef struct MWIN
{
	GtkWidget *window;
	GtkWidget *scrwin1;
	GtkWidget *scrwin2;
	GtkWidget *toolbar;
	GtkToolItem *tlNew;
	GtkToolItem *tlRcv;
	GtkToolItem *tlDel;
	GtkToolItem *tlFind;
	GtkToolItem *tlThem;
	GtkWidget *notebook;
	GtkWidget *lblIndex;
	GtkWidget *labelNew;
	GtkWidget *labelRcv;
	GtkWidget *labelSed;
	GtkWidget *labelDrf;
	GtkWidget *labelTra;
	GtkWidget *panPri;//大分栏窗口
	GtkWidget *panMin;//次分栏窗口
	GtkWidget *txtview;
	GtkWidget *listview;
	GtkWidget *treeview;
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column1;
	GtkTreeViewColumn *column2;
	GtkTreeViewColumn *column3;
	GtkTreeViewColumn *column4;
	GtkListStore *liststore;
	GtkTreeStore *treestore;
	GtkWidget *HomeBox;
	GtkWidget *HomeImage;
	GtkWidget *panBox;
	GtkWidget *allVBox; 
	THEME *theme1;
	THEME *theme2;
}MWIN;

typedef struct REG
{
	GtkWidget *window;//register window
	GtkWidget *lblUsrname;//label username
	GtkWidget *lblPasswd;//label password
	GtkWidget *lblCfpsw;//label confirm password
	GtkWidget *lblSafcod;//label safecode
	GtkWidget *etyUsrname;//entry username
	GtkWidget *etyPasswd;//entry password
	GtkWidget *etyCfpsw;//entry confirm password
	GtkWidget *etySafcod;//entry safecode
	GtkWidget *btnConf;//button confirm
	GtkWidget *btnCancl;//button Cancel
	GtkWidget *nameHBox;//username hbox
	GtkWidget *pswHBox;//password hbox
	GtkWidget *cfpswHBox;//confirm password hbox
	GtkWidget *sfcdHBox;//safecode hbox
	GtkWidget *btnHBox;//button "confirm" "cancel" hbox
	GtkWidget *NPCSVBox;//"name""psw""cfpsw""sfcd" hbox took into this vbox
}REG;

typedef struct LOGIN
{
	GtkWidget *window;//window component
	GtkWidget *nameHBox;//hbox contain username label & entry
	GtkWidget *pswHBox;//hbox contain password label &entry
	GtkWidget *btnHBox;//hbox contain login button & register button
	GtkWidget *NPVBox;//topBox
	GtkWidget *btnLogin;//login button component
	GtkWidget *btnRegister;//register button component
	GtkWidget *lblUsrname;//username label component
	GtkWidget *lblPasswd;//password label component
	GtkWidget *etyUsrname;//username entry component
	GtkWidget *etyPasswd;//password entry component
	GtkWidget *pbar;//progress bar to show the progress of login
}LOGIN;

