// Dll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Dll.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}


// This is an example of an exported variable
DLL_API int nDll=100;

// This is an example of an exported function.
DLL_API int fnDll(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see Dll.h for the class definition
CDll::CDll()
{ 
	cout << "In CDll" << endl;
}

CDll::~CDll()
{
	cout << "Out CDll" << endl;
}
	
void CDll::SayHello()
{
	cout << "Hello in CDll" << endl;
}


DLL_API CDll Dll;