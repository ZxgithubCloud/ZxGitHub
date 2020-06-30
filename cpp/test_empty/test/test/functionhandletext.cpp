

#include <iostream>
#include <functional>
#include <memory>
#include <string>

#include  "functionhandletest.h"

using namespace std;

void E1Procedure::start(stringFunction  responseCallback, stringFunction  timeoutCallback)
{
	ResponseCallback = std::move(responseCallback);
	TimeoutCallback = std::move(timeoutCallback);
	//ResponseCallback = responseCallback;
	//TimeoutCallback = timeoutCallback;
}

void E1Procedure::CallResponseCallback()
{
	ResponseCallback("ResponseCallback");
}

void E1Procedure::CallTimeoutCallback()
{
	TimeoutCallback("TimeoutCallback");
}


void RegisterHandle::RegisterHandlePrint(string inputstring)
{
	std::cout << std::endl << inputstring.c_str()<<std::endl;
}

void RegisterHandle::RegisterHandleProcess(E1Procedure& e1Procedure)
{
	i++;

	auto responseHandle = [this](string inputstring) {
		std::cout << std::endl << " register ResponseCallback " << std::endl;
		for (int i = 0; i < 10; i++)
		{
			std::cout << std::endl << i;
		}

		this->RegisterHandlePrint(inputstring);
		this->SetValue();
	};


	auto timeoutHandle = [this](string inputstring) {
		std::cout << std::endl << " register TimeoutCallback " << std::endl;
		RegisterHandlePrint(inputstring);
		this->SetValue();
	};

	//e1Procedure.start(std::move(responseHandle), std::move(timeoutHandle));
	e1Procedure.start(responseHandle, timeoutHandle);
}

void RegisterFunctionHandle(E1Procedure& e1Procedure)
{

	//RegisterHandle  registerHandle;

	//std::unique_ptr<RegisterHandle> registerHandle;
	auto registerHandle = std::make_unique<RegisterHandle>();
	//RegisterHandle *registerHandle = NULL; 
	//
	//registerHandle->RegisterHandleProcess(e1Procedure);
	registerHandle->RegisterHandleProcess(e1Procedure);
}


void RegisterFunctionHandleUsedFunction(E1Procedure& e1Procedure)
{
	auto timeoutHandle = [](string inputstring) {
		std::cout << std::endl << " RegisterFunctionHandleUsedFunction TimeoutCallback " << std::endl;
		for (int i = 0; i < 10; i++)
		{
			std::cout << std::endl << i;
		}

		std::cout << std::endl << inputstring.c_str() << std::endl;
	};

	e1Procedure.start(
		[](string inputstring) {
			int i;
			std::cout << std::endl << " RegisterFunctionHandleUsedFunction ResponseCallback " << std::endl;
			for (i = 0; i < 10; i++)
			{
				std::cout << std::endl << i;
			}

			std::cout << std::endl << inputstring.c_str() << std::endl;
		},
		timeoutHandle
		);
}

void TestFunctionHandle()
{
	
	E1Procedure  e1Procedure;

/*
	auto timeoutHandle = [this] { 
				std::cout << std::endl << " register TimeoutCallback " << std::endl; 
				for (int i = 0; i < 10; i++)
				{
					std::cout << std::endl << i;
				}

				this->opertion();
	};

	e1Procedure.start(
		[] { 
			int i;
			std::cout << std::endl<<" register ResponseCallback "<<std::endl; 
			for (i = 0; i < 10; i++)
			{  
				std::cout << std::endl << i;
			}
		   },
		timeoutHandle
		//[] { std::cout << std::endl << " register TimeoutCallback " << std::endl;}
	);

*/
	//regist used class
    //RegisterFunctionHandle(e1Procedure);

	RegisterFunctionHandleUsedFunction(e1Procedure);


	std::cout<< endl << " call CallResponseCallback ";
	e1Procedure.CallResponseCallback();

	std::cout<< endl << " call CallTimeoutCallback ";
	e1Procedure.CallTimeoutCallback();


}