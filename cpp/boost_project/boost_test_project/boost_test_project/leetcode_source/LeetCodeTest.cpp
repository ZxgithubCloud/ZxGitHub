
#include <string>
#include <vector>
#include <iostream>

#include "AddTwoNumbers.h"
#include "LeetCodeTest.h"

LeetCodeTest::LeetCodeTest(/* args */)
{
	std::cout << "LeetCodeTest start ..." << std::endl;
}


LeetCodeTest::~LeetCodeTest()
{
}


 void LeetCodeTest::trapTest()
 {
     std::cout << std::endl
               << "42. Trapping Rain Water ...." << std::endl;
     std::vector<int> height{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

     auto waterValue = solution.trap(height);

     std::cout << "water value is : " << waterValue << std::endl;
 }
