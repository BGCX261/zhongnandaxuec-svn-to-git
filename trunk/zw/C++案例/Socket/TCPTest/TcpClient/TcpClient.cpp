#include <Winsock2.H>
#include <stdio.h>

void main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD( 1, 1 );	
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		return;
	}
	if ( LOBYTE( wsaData.wVersion ) != 1 ||
        HIBYTE( wsaData.wVersion ) != 1 ) {
		WSACleanup( );
		return; 
	}
	while (1)
	{
		SOCKET sockClient=socket(AF_INET,SOCK_STREAM,0);
		
		SOCKADDR_IN addrSrv;
		addrSrv.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
		addrSrv.sin_family=AF_INET;
		addrSrv.sin_port =htons(6000);
		connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
		
		char recvBuf[100];
		recv(sockClient,recvBuf,100,0);
		printf("%s\n",recvBuf);
		
		printf("请输入需要发送内容：\n");
		char sendBug[100];
		scanf("%s",sendBug);
		send(sockClient,sendBug,strlen(sendBug)+1,0);
		closesocket(sockClient);
		WSACleanup();
	}




}