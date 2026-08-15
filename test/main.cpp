// Suite for testing parts of my code, like classes and functions/methods

#include <stdio.h>

class base 
{
public:
	virtual void print() {}
};

class der1 : public base 
{
public:
	
};

class der2 : public base 
{
public:
	void print()
	{
		printf("der2\n");
	}
};

int main()
{
	
	base fart;

}
