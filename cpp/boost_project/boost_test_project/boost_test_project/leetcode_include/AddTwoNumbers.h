#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <ctime>

using namespace std;

using UINT = unsigned int;

#define PrintLog(...)        \
    {                        \
        printf(__VA_ARGS__); \
    }

struct emptyStruct
{
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class TimeCount {
public:
    TimeCount()
    {
       start = clock(); 
    };

    ~TimeCount()
    {
       end = clock();
       std::cout<<std::endl<<"The summery of time is : "<<end - start <<std::endl;  
    };

    clock_t start, end;

     
};

class Solution
{
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2);
    int lengthOfLongestSubstring(string s);
    //16 : 3Sum Closest
    int threeSumClosest(vector<int> &nums, int target);
    int trap(vector<int> &height);
    int minPathSum_no_time(vector<vector<int>>& grid);
    int minPathSum(vector<vector<int>>& grid);
};
