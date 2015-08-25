#include <iostream>

#define PI 3.14

enum eu_Day
{
	Mon = 1,
	Thu,
	Web
};

class Base
{
public:
	Base(){};
	~Base(){};
protected:
private:
};

/// using namespace std;
int Max(int a, int b)
{
	return (a>b?a:b);
}


int main()
{
	int iA=1;
	char *pInfo={"1234567890"};
	std::cout << "First progmmame" << std::endl;
	if (1)
	{
		__asm int(3);
		iA=2;	
	}
	else
	{
		
	}
	iA = Max(1,2);
	return 0;
}