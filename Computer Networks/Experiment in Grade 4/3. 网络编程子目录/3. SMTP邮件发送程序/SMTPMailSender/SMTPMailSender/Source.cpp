#include <stdio.h>
#include <WinSock2.h>
#include <string.h>

using namespace std;

#define WSWENS MAKEWORD(2,0)		// MAKEWORD(a, b) -> bbbbbbbb aaaaaaaa

char code[100] = "";				// Base64 Code

int base64code(char str[]);			// Change a normal string to a base64 code, return the code's length.
char base64(char a);				// Base64 code Changer.

int main()
{
	printf("***** This is just a Hello Mail Sender. Cannot edit the subject. *****\n");

	WSADATA wsadata;
	if (WSAStartup(WSWENS, &wsadata) != 0)			// Start up.
		printf("Startup failed.\n");

	sockaddr_in sin;
	SOCKET s = socket(PF_INET, SOCK_STREAM, 0);

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;						// AF_INET for IPv4    AF_INET6 for IPv6.
	sin.sin_port = htons(25);						// Port 25 for SMTP protocol.
	hostent* hptr = gethostbyname("smtp.sina.com");	// Host entry
	memcpy(&sin.sin_addr.S_un.S_addr, hptr->h_addr_list[0], hptr->h_length);

	printf("S: IP of smpt.sina.com is : %d:%d:%d:%d\n",
		sin.sin_addr.S_un.S_un_b.s_b1,
		sin.sin_addr.S_un.S_un_b.s_b2,
		sin.sin_addr.S_un.S_un_b.s_b3,
		sin.sin_addr.S_un.S_un_b.s_b4);
	if (connect(s, (sockaddr*)&sin, sizeof(sin)))
	{
		printf("S: Connection failed.\n");

		exit(0);
	}
	else
	{
		printf("S: Connection success.\n");
	}
	
	// Connection OK. Start mail.
	char bufferresv[10240];							// Receive buffer.
	int len = recv(s, bufferresv, 10240, 0);		// Receive.
	bufferresv[len] = '\0';							// Set string bufferresv's stop point.
	printf("R: %s\n", bufferresv);

	// Send "ehlo"
	char bufferHello[32] = "EHLO\r\n";
	printf("S: EHLO...\n");						// HELO and extend HELO.
	send(s, bufferHello, strlen(bufferHello), 0);
	len = recv(s, bufferresv, 10240, 0);
	bufferresv[len] = '\0';
	printf("R: %s\n", bufferresv);

	// Send "auth login"
	char bufferLogin[32] = "AUTH LOGIN\r\n";			// Auth login.
	printf("S: AUTH LOGIN...\n");
	send(s, bufferLogin, strlen(bufferLogin), 0);
	len = recv(s, bufferresv, 10240, 0);
	bufferresv[len] = '\0';
	printf("R: %s\n", bufferresv);
	
	char bufferUserName[128];
	char bufferPsw[128];
	int bufferStrLen = 0;
	
	// Send Username
	printf("S: Please input Username(Sina Mail):\n");
	scanf("%s", bufferUserName);
	bufferStrLen = base64code(bufferUserName);
	code[bufferStrLen] = '\r';
	code[bufferStrLen + 1] = '\n';
	send(s, code, strlen(code), 0);
	len = recv(s, bufferresv, 10240, 0);
	bufferresv[len] = '\0';
	printf("R: %s\n", bufferresv);

	// Send Password
	printf("S: Please input Password:\n");
	scanf("%s", bufferPsw);
	bufferStrLen = base64code(bufferPsw);
	code[bufferStrLen] = '\r';
	code[bufferStrLen + 1] = '\n';
	send(s, code, strlen(code), 0);
	len = recv(s, bufferresv, 10240, 0);
	bufferresv[len] = '\0';
	printf("R: %s\n", bufferresv);

	//Send sender.
	printf("S: Mail from:<%s>...\n", bufferUserName);
	char bufferMailFrom[192] = "MAIL FROM:<";						// Get sender username used to send to SMTP server.
	strcat(bufferMailFrom, bufferUserName);
	bufferStrLen = strlen(bufferMailFrom);
	bufferMailFrom[bufferStrLen] = '>';
	bufferMailFrom[bufferStrLen + 1] = '\r';
	bufferMailFrom[bufferStrLen + 2] = '\n';
	send(s, bufferMailFrom, strlen(bufferMailFrom), 0);
	len = recv(s, bufferresv, 10240, 0);
	bufferresv[len] = '\0';
	printf("R: %s\n", bufferresv);

	//Send receiver.
	char bufferRcptUserName[128];
	printf("Please input the receiver username you want to send to.\n");	// Input receiver username.
	scanf("%s", bufferRcptUserName);
	printf("S: RCPT TO:<%s>...\n", bufferRcptUserName);

	char bufferRcptTo[192] = "RCPT TO:<";									// Get receiver username used to send to SMTP server.
	strcat(bufferRcptTo, bufferRcptUserName);
	bufferStrLen = strlen(bufferRcptTo);
	bufferRcptTo[bufferStrLen] = '>';
	bufferRcptTo[bufferStrLen + 1] = '\r';
	bufferRcptTo[bufferStrLen + 2] = '\n';
	send(s, bufferRcptTo, strlen(bufferRcptTo), 0);
	len = recv(s, bufferresv, 10240, 0);
	bufferresv[len] = '\0';
	printf("R: %s\n", bufferresv);

	// Send data
	char bufferData[32] = "DATA\r\n";
	printf("S: DATA...\n");
	send(s, bufferData, strlen(bufferData), 0);
	len = recv(s, bufferresv, 10240, 0);
	bufferresv[len] = '\0';
	printf("R: %s\n", bufferresv);

	// From and To
	char bufferFrom[192] = "FROM:";
	strcat(bufferFrom, bufferUserName);
	bufferStrLen = strlen(bufferFrom);
	bufferFrom[bufferStrLen] = '\r';
	bufferFrom[bufferStrLen + 1] = '\n';
	send(s, bufferFrom, strlen(bufferFrom), 0);
	bufferFrom[bufferStrLen + 2] = '\0';
	printf("S: FROM:%s...\n", bufferUserName);

	char bufferTo[192] = "TO:";
	strcat(bufferTo, bufferRcptUserName);
	bufferStrLen = strlen(bufferTo);
	bufferTo[bufferStrLen] = '\r';
	bufferTo[bufferStrLen + 1] = '\n';
	send(s, bufferTo, strlen(bufferTo), 0);
	bufferTo[bufferStrLen + 2] = '\0';
	printf("S: TO:%s...\n", bufferRcptUserName);

	// Subject
	char bufferSubject[256] = "SUBJECT: Hello mail from ";
	strcat(bufferSubject, bufferUserName);
	bufferStrLen = strlen(bufferSubject);
	bufferSubject[bufferStrLen] = '\r';
	bufferSubject[bufferStrLen + 1] = '\n';
	send(s, bufferSubject, strlen(bufferSubject), 0);
	bufferSubject[bufferStrLen + 2] = '\0';
	printf("S: SUBJECT:Hello mail from %s...\n", bufferUserName);

	// Data
	char bufferMailData[10240] = "";
	printf("S: Please input the mail data, end of an ENTER.\n");
	getchar();
	int i = 0;
	for (i = 0;i < 10238;i++)
	{
		char temp;
		temp = getchar();
		if (temp == '\n')
		{
			break;
		}
		else
		{
			bufferMailData[i] = temp;
		}
	}
	if (i == 10238)
	{
		printf("THE MAIL IS TOO LONG. THE PROGRAM WILL QUIT.\n");

		return 1;
	}
	bufferStrLen = strlen(bufferMailData);
	bufferMailData[bufferStrLen] = '\r';
	bufferMailData[bufferStrLen + 1] = '\n';
	send(s, bufferMailData, strlen(bufferMailData), 0);
	
	// End of mail
	char bufferPoint[32] = "\r\n.\r\n";
	send(s, bufferPoint, strlen(bufferPoint), 0);
	len = recv(s, bufferresv, 10240, 0);
	bufferresv[len] = '\0';
	printf("R: %s\n", bufferresv);

	// Quit
	char bufferQuit[32] = "QUIT\r\n";
	send(s, bufferQuit, strlen(bufferQuit), 0);
	printf("S: QUIT.\n");
	len = recv(s, bufferresv, 10240, 0);
	bufferresv[len] = '\0';
	printf("R: %s\n", bufferresv);

	return 0;
}

int base64code(char str[])
{
	memset(code, 0, 100);
	char temp;
	int len = strlen(str);
	int count = len / 3;
	int i;
	for (i = 0;i<count;i++)
	{
		temp = str[3 * i];
		code[4 * i] = str[3 * i] >> 2;    //右移两位得到第一个编码字符  
		code[4 * i] = base64(code[4 * i]);
		temp = temp & 0x03;         //得到原字符的最后两位0000 00xx  
		temp = temp << 4;           //左移四位00xx 0000  
		code[4 * i + 1] = (str[3 * i + 1] >> 4) | temp;//原第二个字符右移四位，然后与前一个字符最后两位联合，得到第二个字符  
		code[4 * i + 1] = base64(code[4 * i + 1]);
		temp = str[3 * i + 1] & 0x0F;       //得到第二个字符的后四位0000 xxxx  
		temp = temp << 2;           //左移两位，00xx xx00  
		code[4 * i + 2] = temp | (str[3 * i + 2] >> 6);//最后一个字符右移6位得到最高位两位，并与上个字符后四位联合，得到第三个字符  
		code[4 * i + 2] = base64(code[4 * i + 2]);
		code[4 * i + 3] = str[3 * i + 2] & 0x3F;    //得到原最后一个字符的低六位,即第四个字符  
		code[4 * i + 3] = base64(code[4 * i + 3]);
	}
	if (len % 3 == 1)
	{
		temp = str[(i - 1) * 3 + 3];
		char ch = '=';
		code[(i - 1) * 4 + 4] = temp >> 2;
		code[(i - 1) * 4 + 4] = base64(code[(i - 1) * 4 + 4]);
		temp = (temp & 0x03) << 4;
		code[(i - 1) * 4 + 5] = base64(temp);
		code[(i - 1) * 4 + 6] = ch;
		code[(i - 1) * 4 + 7] = ch;
	}
	if (len % 3 == 2)
	{
		temp = str[(i - 1) * 3 + 3];
		char ch = '=';
		code[(i - 1) * 4 + 4] = temp >> 2;
		code[(i - 1) * 4 + 4] = base64(code[(i - 1) * 4 + 4]);
		temp = (temp & 0x03) << 4;
		code[(i - 1) * 4 + 5] = temp;
		temp = str[(i - 1) * 3 + 4];
		code[(i - 1) * 4 + 5] = (temp >> 4) | code[(i - 1) * 4 + 5];
		code[(i - 1) * 4 + 5] = base64(code[(i - 1) * 4 + 5]);
		temp = (str[(i - 1) * 3 + 4] & 0x0F) << 2;
		code[(i - 1) * 4 + 6] = base64(temp);
		code[(i - 1) * 4 + 7] = ch;
	}
	return strlen(code);
}

char base64(char a)
{
	if ((int)a >= 0 && (int)a <= 25)
		return 'A' + (int)a;
	if ((int)a>25 && (int)a <= 51)
		return 'a' + (int)a - 26;
	if ((int)a>51)
		return '0' + (int)a - 52;
}