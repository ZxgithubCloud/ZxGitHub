#pragma once
class Base
{

publc:
	void function1()
	{
		cout << "Base " << endl;
	}
};

class Derived :public Base
{
public:
	using Base::function;
};