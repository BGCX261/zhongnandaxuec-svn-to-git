
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#include<iostream>
using namespace std;

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#pragma message("dllexport")
#else
#define DLL_API __declspec(dllimport)
#pragma message("dllimport")
#endif

// This class is exported from the Dll.dll
class DLL_API CDll {
public:
	CDll();//{cout << "In CDll" << endl;};
	~CDll();//{cout << "Out CDll" << endl;};
	void SayHello();//{cout << "Hello in CDll" << endl;};
	// TODO: add your methods here.
};

extern DLL_API int nDll;
extern DLL_API CDll Dll;

DLL_API int fnDll(void);

