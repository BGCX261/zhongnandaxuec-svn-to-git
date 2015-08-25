#ifndef _BUSINESS_OBJECT__
#define _BUSINESS_OBJECT__

#include "BaseObject.h"

class CommandObject : public ObjectClass
{
	Declare_DynCreate(CommandObject)
		
public:
	CommandObject()
	{};
	~CommandObject()
	{};
	
	// 必须重载
	virtual void GetInfo(const CString &sSerXml){};
	
protected:
	
private:
	
};

Implement_DynCreate(CommandObject, ObjectClass)

//////////////////////////////////////////////////////////////////////////

class NotifyOject : public ObjectClass
{
	Declare_DynCreate(NotifyOject)
		
public:
	NotifyOject()
	{};
	~NotifyOject()
	{};
	
	// 必须重载
	virtual void GetInfo(const CString &sSerXml){};
	
protected:
	
private:
	
};

Implement_DynCreate(NotifyOject, ObjectClass)

#endif