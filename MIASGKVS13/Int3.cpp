#include "Int3.h"

Int3::Int3(int a, int b, int c)
{
	this->a = a;
	this->b = b;
	this->c = c;
}


Int3::~Int3()
{
}

void Int3::display()
{
	std::cout << "Int3 = (" << this->a << ", " << this->b << ", " << this->c << ")" << std::endl;;
}
