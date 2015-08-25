// testDll.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../Dll.h"

#include <windows.h>

int main(int argc, char* argv[])
{
	CDll dll;

	dll.SayHello();

	printf("nDll=%d, fnDll return %d\n", nDll, fnDll());

	nDll = 1000;

	printf("nDll=%d, fnDll return %d\n", nDll, fnDll());

	Dll.SayHello();

	return 0;
}

