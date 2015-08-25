#include "BusinessObject.h"

class A : public CommandObject
{
	Declare_DynCreate(A)
		
public:
	A()
	{};
	~A()
	{};
	
	// 必须重载
	virtual void GetInfo(const CString &sSerXml){};
	
protected:
	
private:
	
};

Implement_DynCreate(A, CommandObject)


class B : public ObjectClass
{
	Declare_DynCreate(B)
		
public:
	B()
	{};
	~B()
	{};
	
	// 必须重载
	virtual void GetInfo(const CString &sSerXml){};
	
protected:
	
private:
	
};

Implement_DynCreate(B, ObjectClass)


class C : public ObjectClass
{
	Declare_DynCreate(C)
		
public:
	C()
	{};
	~C()
	{};
	
	// 必须重载
	virtual void GetInfo(const CString &sSerXml){};
	
protected:
	
private:
	
};

Implement_DynCreate(C, ObjectClass)



class D : public C
{
	Declare_DynCreate(D)
		
public:
	D()
	{};
	~D()
	{};
	
	// 必须重载
	virtual void GetInfo(const CString &sSerXml){};
	
protected:
	
private:
	
};

Implement_DynCreate(D, C)

class E : public D
{
	Declare_DynCreate(E)
		
public:
	E()
	{};
	~E()
	{};
	
	// 必须重载
	virtual void GetInfo(const CString &sSerXml){};
	
protected:
	
private:
	
};

Implement_DynCreate(E, D)


