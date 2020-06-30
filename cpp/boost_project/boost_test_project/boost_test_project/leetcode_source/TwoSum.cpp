
#include <vector>
#include <iostream>
#include <tuple>
#include <algorithm>
#include "TwoSum.h"

using namespace std;

std::tuple<int,int> TwoSum(std::vector<int> nums, int target)
{
    //int firstIndex = 0;
    using NumsIter = std::vector<int>::iterator;

	NumsIter numsIter;
	int firstIndex = 0;

    //for ( auto numIter : nums )
    for ( numsIter = nums.begin(), firstIndex = 0;numsIter <= nums.end(); numsIter++, firstIndex++ )
    {
        if (*numsIter > target)
        {
            continue;
        }

		auto findIter = std::find(numsIter,nums.end(),target - *numsIter);
        if ( findIter != nums.end() )
        {
            return std::make_tuple(firstIndex, firstIndex + findIter - numsIter);
        }     
    }

    return std::make_tuple(0xffffffff, 0xffffffff);
}