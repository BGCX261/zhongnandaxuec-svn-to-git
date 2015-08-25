#include<stdio.h>
#include<WINSOCK2.H>
#include<windows.h>

struct para 
{
	SOCKET sockClient;
	SOCKADDR_IN addSrv;
	SOCKADDR_IN addClient;
	char sendBuf[100];
	char recvBuf[100];
	int len;
};


DWORD WINAPI SendMsg(LPVOID lpPara);
DWORD WINAPI RecvMsg(LPVOID lpPara);
void main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	wVersionRequested = MAKEWORD( 1, 1 );
	
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		return;
	}
	
	/* Confirm that the WinSock DLL supports 2.2.*/
	/* Note that if the DLL supports versions greater    */
	/* than 2.2 in addition to 2.2, it will still return */
	/* 2.2 in wVersion since that is the version we      */
	/* requested.                                        */
	
	if ( LOBYTE( wsaData.wVersion ) != 1 ||
        HIBYTE( wsaData.wVersion ) != 1 ) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		WSACleanup( );
		return; 
	}

	SOCKET sockClient=socket(AF_INET,SOCK_DGRAM,0);	//create a socket for client
	SOCKADDR_IN addSrv;	//define the sever address
	printf("please input the server ip address: ");
	char ip[15];
	scanf("%s",&ip);
//	gets(ip);
	addSrv.sin_addr.S_un.S_addr=inet_addr(ip);
	addSrv.sin_family=AF_INET;
	addSrv.sin_port=htons(6000);
//	char sendbuf[100];
//	char recvbuf[100];
	int len=sizeof(SOCKADDR);

	HANDLE threadSend;
	HANDLE threadRecv;
	para pa;
	pa.sockClient=sockClient;
	pa.len=len;
	pa.addSrv=addSrv;
	threadSend=CreateThread(NULL,0,SendMsg,&pa,0,NULL);
	threadRecv=CreateThread(NULL,0,RecvMsg,&pa,0,NULL);
	CloseHandle(threadSend);
	CloseHandle(threadRecv);
	while(1)
	{
		if (pa.sendBuf[0]=='q')
		{
			break;
		}
		else
		{
			Sleep(1);
		}
	}
//	Sleep(10000000);
/*	while (1)
	{
		printf("please input your message: ");
		scanf("%s",sendbuf);
		sendto(sockClient,sendbuf,strlen(sendbuf)+1,0,(SOCKADDR*)&addSrv,sizeof(SOCKADDR));	//send message to sever
		if (sendbuf[0]=='q')
		{
			break;
		}
		else
		{
			recvfrom(sockClient,recvbuf,100,0,(SOCKADDR*)&addSrv,&len);
			printf("%s",recvbuf);
		}
	}
	
	closesocket(sockClient);
	WSACleanup();
*/
}
DWORD WINAPI SendMsg(LPVOID lpPara)
{
	while(1)
	{
		para* pa=(para*)lpPara;
		//printf("please input the message to send: ");
		scanf("%s",pa->sendBuf);
		sendto(pa->sockClient,pa->sendBuf,strlen(pa->sendBuf)+1,0,(SOCKADDR*)&pa->addSrv,pa->len);
		Sleep(1);
	}
	return 0;
}
DWORD WINAPI RecvMsg(LPVOID lpPara)
{
	while(1)
	{
		//printf("aaaa");
		para* pa=(para*)lpPara;
		if(SOCKET_ERROR==recvfrom(pa->sockClient,pa->recvBuf,100,0,(SOCKADDR*)&pa->addSrv,&pa->len))
		{
			Sleep(1);
		}
		else
		{
			printf("\n%s Says: %s\n",inet_ntoa(pa->addSrv.sin_addr),pa->recvBuf);
		}
		Sleep(1);
	}
	return 0;
}
