#include "StdAfx.h"



<<<<<<< .mine
// �����ٽ���
EnterCriticalSection(&cs);

// ����
LeaveCriticalSection(&cs);

// ɾ��һ���ٽ�����Դ
DeleteCriticalSection(&cs);

HANDLE hThrd = _beginthreadex();


// ����һ���¼� 
HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
// �����¼�
SetEvent(hEvent);
// �ȴ��¼�Ϊ����״̬
WaitForSingleObject(hEvent, INFINITE);
// ���¼�Ϊ�Ǽ���״̬
ResetEvent(hEvent);
// �ͷž��
CloseHandle(hEvent);

// ����һ��������
HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
// �ȴ�ӵ�л�����
WaitForSingleObject(hMutex, INFINITE);
// �ͷŻ�����ӵ��Ȩ
ReleaseMutex(hMutex);
// �ͷž��
CloseHandle(hMutex);

=======
>>>>>>> .r106
