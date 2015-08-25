// SL_Kernel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



// CRITICAL_SECTION cs;
// 
// 初始化一个临界区变量
// InitializeCriticalSection(&cs);
// 进入临界区
// EnterCriticalSection(&cs);
// 出来
// LeaveCriticalSection(&cs);
// 删除一个临界区资源
// DeleteCriticalSection(&cs);
// 
// 
// 创建一个事件 
// HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
// 激活事件
// SetEvent(hEvent);
// 等待事件为激活状态
// WaitForSingleObject(hEvent, INFINITE);
// 置事件为非激活状态
// ResetEvent(hEvent);
// 释放句柄
// CloseHandle(hEvent);
// 
// 创建一个互斥量
// HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
// 等待拥有互斥量
// WaitForSingleObject(hMutex, INFINITE);
// 释放互斥量拥有权
// ReleaseMutex(hMutex);
// 释放句柄
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

// 创建一个互斥量
// HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
// 等待拥有互斥量
// WaitForSingleObject(hMutex, INFINITE);
// 释放互斥量拥有权
// ReleaseMutex(hMutex);
// 释放句柄
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



