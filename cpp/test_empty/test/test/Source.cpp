#include <iostream>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <string.h>


#include "sort_merge.h"
#include "functionhandletest.h"

using namespace std;

int main()
{
	cout << "merge sort test ...." << endl;
	//mergSortTest();


/*
	std::function<int(int, int)> foo = std::plus<int>();
	std::function<int(int, int)> bar;

	try {
		std::cout << foo(10, 20) << '\n';
		std::cout << bar(10, 20) << '\n';
	}
	catch (std::bad_function_call & e)
	{
		std::cout << "ERROR: Bad function call\n";
	}


*/
	try
	{
		for (int i = 0; i < 10 ; i++)
		{
			cout << endl << "TestFunctionHandle .... "<<i << endl;
			TestFunctionHandle();
		}
	}
	catch (...)
	{
		std::cout << "exception: ";
		throw std::exception();
	}

	

	cout <<endl << "plesae input Q or q to exist..."<<endl;
	char c = getchar();
	while ( 'q' == c  || 'Q' == c )
	{
		c = getchar();
	}

	return 0;
}
