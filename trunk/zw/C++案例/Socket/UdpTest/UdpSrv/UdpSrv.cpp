#include<WINSOCK2.H>
#include<windows.h>
#include<stdio.h>

DWORD WINAPI SendMsg(LPVOID lpPara);
DWORD WINAPI RecvMsg(LPVOID lpPara);
struct para 
{
	SOCKET sockSrv;
	SOCKADDR_IN addSrv;
	SOCKADDR_IN addClient;
	char sendBuf[100];
	char recvBuf[100];																																																																																																																																																																																																	
	int len;
};
//HANDLE mutix;

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

	SOCKET sockSrv=socket(AF_INET,SOCK_DGRAM,0);
	SOCKADDR_IN addSrv;
//	printf("please input ip address:");
//	char ip[15];
//	scanf("%s",ip);
	addSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	//addSrv.sin_addr.S_un.S_addr=inet_addr(ip);
	addSrv.sin_family=AF_INET;
	addSrv.sin_port =htons(6000);

	bind(sockSrv,(SOCKADDR*)&addSrv,sizeof(SOCKADDR));

//	SOCKADDR_IN addClient;
	int len=sizeof(SOCKADDR);
//	char recvBuf[100];
//	char sendbuf[100];

	HANDLE threadSend;
	HANDLE threadRecv;

	para pa;
	pa.addSrv=addSrv;
//	pa.addClient=addClient;
//	pa.recvBuf=recvBuf;
//	pa.sendBuf=sendbuf;
	pa.sockSrv=sockSrv;
	pa.len=len;
	//DWORD dwid1;
	//DWORD dwid2;
	threadSend=CreateThread(NULL,0,SendMsg,&pa,0,NULL);
	threadRecv=CreateThread(NULL,0,RecvMsg,&pa,0,NULL);
	CloseHandle(threadSend);
	CloseHandle(threadRecv);

//	Sleep(5000);
//	mutix=CreateMutex(NULL,true,NULL);
//	ReleaseMutex(mutix);
	while(1)
	{
		if ('q'==pa.recvBuf[0])
		{
			break;
		}
		else
		{
			Sleep(1);
		}
		//return;
	}

//	Sleep(10000000);
/*	while (1)
	{
		
		recvfrom(sockSrv,recvBuf,100,0,(SOCKADDR*)&addClient,&len);
		printf("%s\n",recvBuf);
		if (recvBuf[0]=='q')
		{
			closesocket(sockSrv);
			WSACleanup();
			break;
		}
		else
		{
			printf("please input your message to recv the client: ");
			scanf("%s",sendbuf);
			sendto(sockSrv,sendbuf,strlen(sendbuf)+1,0,(SOCKADDR*)&addClient,len);
		}
	}
*/
}

 DWORD WINAPI SendMsg(LPVOID lpPara)
{
	while(1)
	{
//		WaitForSingleObject(mutix,INFINITE);
		para* par=(para*)lpPara;
	//	printf("please input your message: ");
		scanf("%s",par->sendBuf);
		sendto(par->sockSrv,par->sendBuf,strlen(par->sendBuf)+1,0,(SOCKADDR*)&par->addClient,par->len);
//		ReleaseMutex(mutix);
		Sleep(1);
	}
	
	return 0;
}

 DWORD WINAPI RecvMsg(LPVOID lpPara)
{
	 while (1)
	 {
//		 WaitForSingleObject(mutix,INFINITE);
		 para* par=(para*)lpPara;
		 recvfrom(par->sockSrv,par->recvBuf,100,0,(SOCKADDR*)&par->addClient,&par->len);
		 printf("\n%s says %s\n",inet_ntoa(par->addClient.sin_addr),par->recvBuf);
//		 ReleaseMutex(mutix);
		 Sleep(1);
	 }
	
	return 0;
}