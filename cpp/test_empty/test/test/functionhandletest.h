#pragma once

#include <iostream>
#include <functional>
#include <memory>
#include <string>


using namespace std;
using  voidFunction = std::function<void(void)>;
using  stringFunction = std::function<void(string)>;



class  E1Procedure
{
public:

	E1Procedure(){ std::cout<<std::endl<<" create E1Procedure for function handle..."<< std::endl; }
	~E1Procedure() { std::cout << std::endl << " deconstruct E1Procedure..." << std::endl; }

	void start(stringFunction, stringFunction);

	void CallResponseCallback();
	void CallTimeoutCallback();

	
private:

	//voidFunction ResponseCallback;
	//voidFunction TimeoutCallback;
	stringFunction ResponseCallback;
	stringFunction TimeoutCallback;

};

class RegisterHandle
{
     public:
		 RegisterHandle() { i = 0; std::cout << std::endl << "RegisterHandle class cretae." << std::endl; }
		 ~RegisterHandle() { std::cout << std::endl << "RegisterHandle class deconstruct." << std::endl; }
		 void RegisterHandlePrint(string );
		 void RegisterHandleProcess(E1Procedure&);
		 void SetValue() 
		 { 
			 i++; 
			 std::cout << std::endl << "SetValue is: " << i<<std::endl;
		 };
	 private:
		 int i; 

};


void RegisterFunctionHandle(E1Procedure&);
void RegisterFunctionHandleUsedFunction(E1Procedure&);
void TestFunctionHandle();
