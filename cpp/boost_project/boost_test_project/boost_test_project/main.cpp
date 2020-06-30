#include <iostream>
#include <stdio.h>
#include <boost/optional.hpp>
#include <boost/variant.hpp>             
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/variant.hpp>
#include <vector>
//#include <function>
#include <memory>
#include <algorithm>
#include "template_test.hpp"
#include "TwoSum.h"
#include "AddTwoNumbers.h"
#include "LeetCodeTest.h"

using namespace std;

/*
void foo(int&)
{
	std::cout << "1";
}

void foo(int&&)
{
	std::cout << "2";
}

*/

void foo1()
{

   const int& i =0;
   auto j = i;
   j = 1;
   std::cout<<i<<std::endl;

}

void foo2()
{

	const int& i = 0;
	auto j = i;
	j = 1;
	std::cout << j << std::endl;

}


void change(int* a, int& b, int c)
{
	c = *a;
	b = 3;
	*a = 2;

}

/*
void handle(int n, const std::function &cb)
{
	cb(n);
}
*/

using TVector = std::vector<int>;
using Fp = void(*)(int, int);

using  ShowTypeInfor = boost::variant<int, char>;

class PrintTypeInfor
{
public:   
	void operator()(int value)
    {
        std::cout<<"int value : "<<value<<std::endl;
    } 

    void operator()(char value)
    {
        std::cout<<"char value : "<<value<<std::endl;
    } 


};

enum class PdcpReestablishment : int
{
	enumTrue
};



int main()
{
    boost::optional<int> int_optin;

	int_optin = 1;
	int_optin.get();
    cout<<"boost test start. gets "<< int_optin.get();
    cout<<"boost test start. value "<< int_optin.value();


    cout<<std::endl<<"boost test boost::aplyvistor : "<< std::endl;
     
    ShowTypeInfor testType;
    testType = 4;
    boost::apply_visitor(PrintTypeInfor(),testType);
   

	boost::optional<int> plmnId{100};

	int a = 100;
	std::cout << "optional: " << plmnId.get();

	if (plmnId == a)
	{
		cout << std::endl << "boost null is ";
	}
	boost::optional<int> plmnIdtest;
	plmnIdtest = true ? boost::optional<int>{1} : boost::none;
	
	boost::optional<PdcpReestablishment> test1111;
	test1111 = true ? boost::optional<PdcpReestablishment>{PdcpReestablishment::enumTrue} : boost::none;
	//test1111 = true ? PdcpReestablishment::enumTrue : boost::none;

    //
    int  *pInt = new int(1);
	
	//fail 1
	auto  pmake_unique = std::make_unique<int>();
	std::shared_ptr<int> pShare = std::move(pmake_unique);   //success
	//std::shared_ptr<int> pShare = pmake_unique;// fail
	//std::shared_ptr<int> pShare;
	//pShare = pmake_unique;
	//std::shared_ptr<int> pShare(pmake_unique);
	
	//success
	//std::shared_ptr<int> pShare = std::make_unique<int>();
    //std::make_unique<int>();
   
	*pShare = 100;
	std::cout << std::endl << " value is : "<< *pShare << std::endl;
   
   
   
    std::cout<<std::endl<<" leet code test ..."<<std::endl;
    std::cout<<std::endl<<" leet code test : Two Sum begin : "<<std::endl;
    
    std::vector<int>  testNums{9,5,19,6,5,3,9,10};

    auto resultTuple = TwoSum(testNums, 9);

    std::cout<<std::endl<<"Two Sum result: firstIndex is: "<<std::get<0>(resultTuple)<<std::endl;
    std::cout<<std::endl<<"Two Sum result: secondeIndex is: "<< std::get<1>(resultTuple) <<std::endl;

	std::cout << std::endl << " leet code test ..." << std::endl;
	std::cout << std::endl << " leet code test :  Add Two Numbers : " << std::endl;

	//std::vector<int>  l1value{3,4,5,7,8};
    //std::vector<int>  l2value{1,3,9,6};
    std::vector<int>  l1value{9};
    std::vector<int>  l2value{1,9,9,9,9,9,9,9,9,9};

    struct ListNode* l1 = NULL;
    ListNode* l2 = NULL;
	
    ListNode*  ptrHead = NULL;

    for (auto l1iter:l1value)
    {
         if ( NULL != l1)
         {
             ptrHead->next = new ListNode(l1iter);
             ptrHead = ptrHead->next;    
         }
         else
         {
             /* code */
             l1 = new ListNode(l1iter);
             ptrHead = l1; 
         }
    }

    ptrHead = NULL;
    for (auto l1iter:l2value)
    {
         if ( NULL != l2)
         {
             ptrHead->next = new ListNode(l1iter);
             ptrHead = ptrHead->next;    
         }
         else
         {
             /* code */
             l2 = new ListNode(l1iter);
             ptrHead = l2;
         }
    }
    
    Solution solution;
    auto ptrResult = solution.addTwoNumbers(l1,l2);

    std::cout << std::endl << " leet code test: Longest Substring Without Repeating Characters."<< std::endl;
    string s = "abcdead";
    auto maxLength = solution.lengthOfLongestSubstring(s);


	emptyStruct emptyLen;
	int empty1[1];

	std::cout<<std::endl<< "emptyLen length is :" << sizeof(emptyLen);
	std::cout << std::endl << "emptyLen int empty[0] length is :" << sizeof(empty1);

    //std::cout<<std::endl<< " Three sum closest test."<<std::endl;
    PrintLog("Three sum closest test.");
	//std::cout << std::endl << "emptyLen int empty[0] length is :" << sizeof(empty1);
    //PrintLog
    //std::vector<int> nums{-1, 2, 1, -4};
    //solution.threeSumClosest(nums,1);
    std::vector<int> nums{1, 1, 1, 0};
    solution.threeSumClosest(nums,-100);
    

/*
    char const*  s1 ="template1.";
    char const*  s2 ="template2.";
    auto s3 = ::max1(s1,s2);
	

    const char* s11 = "frederic"; 
    const char* s22 = "anica"; 
    const char* s33 = "lucas"; 
    auto s44 = ::max(s11, s22, s33);

    cout << endl << "test share_ptr...."<<endl;

    auto cell = std::shared_ptr<int>();
    
    if (NULL == cell)
    { 
        cout << endl << "cell is null.";
    }
    
    
    cout << endl << "vector erase.";
    std::vector<int> vec{ 1, 4, 3, 2, 5, 2 };
	auto result = std::find(vec.begin(),vec.end(),10);
	//vec.erase(vec.end());
	if (result == vec.end())
	{
		std::cout << "not find the valud 10 in vector." << std::endl;
	}
	vec.erase(result);

*/
    LeetCodeTest leetCodeTest;

    leetCodeTest.trapTest();

    std::vector<std::vector<int>> grid{{1,3,1},{1,5,1},{4,2,1}};
	/*
    // time test case:
    solution.minPathSum(grid);
    */
    solution.minPathSum_no_time(grid);

    cout<<endl<<"please input 'q' or 'Q' to exit.";
    char  flag = getchar();
    while( true )
    {
        if('q' == flag  || 'Q' == flag)
        {
            break;
        }
        else
        {
            flag = getchar();
        }
           
    } 

    return 1;
}