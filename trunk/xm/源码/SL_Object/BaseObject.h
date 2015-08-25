//////////////////////////CObject.h

#ifndef __OBJECT_H__
#define __OBJECT_H__

class ObjectClass;

struct RuntimeClass
{
    TCHAR *szClassName;
	RuntimeClass *pBaseClass;
    RuntimeClass *pNextClass;
	ObjectClass* (*pCreateFn)();

	static RuntimeClass *pFirstClass;
    static RuntimeClass* LoadByName(const CString &sLoadClassName);
	static VOID DumpClass();
};

struct ClassList
{
    ClassList(RuntimeClass *pNewClass);
};

#define Runtime_Class(ClassName) \
(&ClassName::RuntimeClass##ClassName)

#define Declare_DynCreate(ClassName) \
public: \
        static RuntimeClass RuntimeClass##ClassName;  \
		static RuntimeClass* GetRuntimeClass(); \
		static ObjectClass*  ClassName::CreateObject(); \

#define Implement_DynCreate(DeriveName, BaseName) \
		ObjectClass* DeriveName::CreateObject() \
		{ return new DeriveName; } \
		RuntimeClass DeriveName::RuntimeClass##DeriveName = \
		{_T(#DeriveName), Runtime_Class(BaseName), NULL, DeriveName::CreateObject}; \
		static ClassList Init##DeriveName(Runtime_Class(DeriveName)); \

class ObjectClass
{
public:
	virtual ~ObjectClass() {};

    static ObjectClass* LoadClass(CString &sClassName);

public:
    static RuntimeClass RuntimeClassObjectClass;

};




#endif