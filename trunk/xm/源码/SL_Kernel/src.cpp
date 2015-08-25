#include "StdAfx.h"



<<<<<<< .mine
// 进入临界区
EnterCriticalSection(&cs);

// 出来
LeaveCriticalSection(&cs);

// 删除一个临界区资源
DeleteCriticalSection(&cs);

HANDLE hThrd = _beginthreadex();


// 创建一个事件 
HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
// 激活事件
SetEvent(hEvent);
// 等待事件为激活状态
WaitForSingleObject(hEvent, INFINITE);
// 置事件为非激活状态
ResetEvent(hEvent);
// 释放句柄
CloseHandle(hEvent);

// 创建一个互斥量
HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
// 等待拥有互斥量
WaitForSingleObject(hMutex, INFINITE);
// 释放互斥量拥有权
ReleaseMutex(hMutex);
// 释放句柄
CloseHandle(hMutex);

=======
>>>>>>> .r106
