// SL_Kernel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



// CRITICAL_SECTION cs;
// 
// ��ʼ��һ���ٽ�������
// InitializeCriticalSection(&cs);
// �����ٽ���
// EnterCriticalSection(&cs);
// ����
// LeaveCriticalSection(&cs);
// ɾ��һ���ٽ�����Դ
// DeleteCriticalSection(&cs);
// 
// 
// ����һ���¼� 
// HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
// �����¼�
// SetEvent(hEvent);
// �ȴ��¼�Ϊ����״̬
// WaitForSingleObject(hEvent, INFINITE);
// ���¼�Ϊ�Ǽ���״̬
// ResetEvent(hEvent);
// �ͷž��
// CloseHandle(hEvent);
// 
// ����һ��������
// HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
// �ȴ�ӵ�л�����
// WaitForSingleObject(hMutex, INFINITE);
// �ͷŻ�����ӵ��Ȩ
// ReleaseMutex(hMutex);
// �ͷž��
// CloseHandle(hMutex);

#define THREAD_NUM 5

CRITICAL_SECTION g_cs;
HANDLE           g_hThread[THREAD_NUM];
HANDLE           g_hMutex;
HANDLE           g_hEvent;

unsigned int __stdcall ThreadCB(void *pParam)
{
	int i=0;
	int nThreadNo = (int)pParam;
	while (nThreadNo<1000)
	{
		if (WAIT_OBJECT_0 == WaitForSingleObject(g_hEvent, 1))
		{
			break;
		}
//		EnterCriticalSection(&g_cs);
//		WaitForSingleObject(g_hMutex, INFINITE);
		
		printf("Thread no: %d, run %d ... \n", nThreadNo, i++);
//		Sleep(1000);
		if (nThreadNo==1)
		{
			printf("aaaaaaaaaaaaaaaaaaaaaaaaa\n");
		}
		else if (nThreadNo == 2)
		{
			printf("bbbbbbbbbbbbbbbbbbbbbbbbb\n");
		}
		else if (nThreadNo == 3)
		{
			printf("ccccccccccccccccccccccccc\n");
		}
		else if (nThreadNo == 4)
		{
			printf("ddddddddddddddddddddddddd\n");
		}
//		ResetEvent(g_hEvent);
//		ReleaseMutex(g_hMutex);
//		LeaveCriticalSection(&g_cs);
	}
	printf("Thread no: %d exits.\n", nThreadNo);
	return 0;
}


void CreateThreadFun()
{
	int nThreadNo=1;
	unsigned nAddr;
	while(nThreadNo < 5)
	{
		HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadCB, (void*)nThreadNo, 0, &nAddr);
		CloseHandle(hThread);
		nThreadNo++;
	}
}

// ����һ��������
// HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
// �ȴ�ӵ�л�����
// WaitForSingleObject(hMutex, INFINITE);
// �ͷŻ�����ӵ��Ȩ
// ReleaseMutex(hMutex);
// �ͷž��
// CloseHandle(hMutex);


int main(int argc, char* argv[])
{
	InitializeCriticalSection(&g_cs);
	g_hMutex = CreateMutex(NULL, FALSE, NULL);
	g_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	CreateThreadFun();
	while(1)
	{
		Sleep(10000);
		break;
	}
	SetEvent(g_hEvent);
	Sleep(2000);
	CloseHandle(g_hEvent);
	CloseHandle(g_hMutex);
	DeleteCriticalSection(&g_cs);
	return 0;
}



