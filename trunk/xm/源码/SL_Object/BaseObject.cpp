// CObjectClass.cpp

#include "StdAfx.h"
#include "BaseObject.h"

RuntimeClass* RuntimeClass::pFirstClass = NULL;

static TCHAR szBaseClass[]= _T("BaseClass");

RuntimeClass ObjectClass::RuntimeClassObjectClass ={szBaseClass, NULL, NULL, NULL};

static ClassList InitBaseClass(&ObjectClass::RuntimeClassObjectClass);

ClassList::ClassList(RuntimeClass* pNewClass)
{
    pNewClass->pNextClass=RuntimeClass::pFirstClass;
    RuntimeClass::pFirstClass=pNewClass;
}

RuntimeClass* RuntimeClass::LoadByName(const CString &sLoadClassName)
{
    RuntimeClass* pRc;
    for (pRc = pFirstClass; pRc != NULL; pRc = pRc->pNextClass)
    {
		if (!sLoadClassName.CompareNoCase(pRc->szClassName))
		{
			return pRc;
		}      
    }
    return NULL;
}

ObjectClass* ObjectClass::LoadClass(CString &sClassName)
{
	RuntimeClass* pRc=NULL;
	pRc = RuntimeClass::LoadByName(sClassName);
	if (pRc && pRc->pCreateFn)
	{
		return (*pRc->pCreateFn)();	
	}
	else
		return NULL;
}

VOID RuntimeClass::DumpClass()
{
    RuntimeClass* pRc;
    for (pRc = pFirstClass; pRc != NULL; pRc = pRc->pNextClass)
    {
		if (pRc)
		{
			TRACE(pRc->szClassName);
			TRACE(_T("---"));
			if (pRc->pBaseClass)
			{
				TRACE(pRc->pBaseClass->szClassName);
			}
			else
			{
				TRACE(_T("Non base class"));
			}
			TRACE(_T("\n"));
		}      
    }
}