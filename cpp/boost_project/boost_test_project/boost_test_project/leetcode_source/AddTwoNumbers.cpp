
#include <iostream>
#include <vector>
#include "AddTwoNumbers.h"
#include <map>
#include <algorithm>

using namespace std;

ListNode* Solution::addTwoNumbers(ListNode* l1, ListNode* l2)
{
    ListNode*  ptrNewListNode = NULL;
    ListNode*  ptrListNodeHead = NULL;
    long int  l1Value = 0;
    long int  l2Value = 0;
    long int  Sum = 0;
    long int  coefficient = 1;
    
    //compute sum
    while ( NULL != l1  || NULL != l2 )
    {
        if ( NULL != l1 )
        {
           l1Value = l1->val * coefficient;
        }

        if ( NULL != l2 )
        {
			l2Value = l2->val * coefficient;
        }

        Sum = Sum + l1Value + l2Value;
         
        if (NULL != l1)
        l1 = l1->next;

		if (NULL != l2)
        l2 = l2->next;

        coefficient = coefficient * 10;
        l1Value = 0;
        l2Value = 0;
    }
   
    std::cout<<"Sum value is: "<<Sum<<std::endl;
    int Mod = 0;
    
    if (Sum == 0)
    {
        ptrNewListNode = new ListNode(0);
    }

    while (Sum != 0 )
    {
        Mod = Sum % 10;
        Sum = Sum / 10;
        if ( ptrNewListNode == NULL )
        {
            ptrNewListNode = new ListNode(Mod);
            ptrListNodeHead = ptrNewListNode;
        }
        else
        {
           ptrListNodeHead->next = new ListNode(Mod);
           ptrListNodeHead = ptrListNodeHead->next;                
        }
      
        std::cout<<"Mod value is: "<<Mod<<std::endl;
        std::cout<<"Sum value is: "<<Sum<<std::endl;
    }

    
  
    //output the ptr 
    return ptrNewListNode;

}

/*

ListNode* Solution::addTwoNumbers(ListNode* l1, ListNode* l2)
{
    std::vector<int>  

    while ( NULL != l1  || NULL != l2 )
    {
        if ( NULL != l1 )
        {
           l1Value = l1->val * coefficient;
        }

        if ( NULL != l2 )
        {
			l2Value = l2->val * coefficient;
        }

        Sum = Sum + l1Value + l2Value;
         
        if (NULL != l1)
        l1 = l1->next;

		if (NULL != l2)
        l2 = l2->next;

        coefficient = coefficient * 10;
        l1Value = 0;
        l2Value = 0;
    }



}


*/
int Solution::lengthOfLongestSubstring(string s)
{
    
    std::vector<char>  keyVector{};
    std::vector<string>  subStrVector{};
    string subStr;
     
    int reStartPoint = 0;
    int strLength = s.length();
    int maxLength = 0;
    int tempIndex = 0;
    bool isStrEndFlag = false;

    std::cout<<"input string is: "<<s.c_str()<<std::endl;

    while ( (reStartPoint < strLength) && !isStrEndFlag)
    {
        subStr.clear();
        keyVector.clear();

        for( tempIndex = reStartPoint; tempIndex < strLength; tempIndex++ )
        {
            auto iterKeyVector =  std::find(keyVector.cbegin(), keyVector.cend(), s[tempIndex]);
            if ( iterKeyVector == keyVector.cend() )
            {
               subStr = subStr + s[tempIndex];
               keyVector.emplace_back(s[tempIndex]);
               if(tempIndex == strLength - 1)
               {
                   reStartPoint = strLength;
                   std::cout<<std::endl<<"not repeat subStr is: "<< subStr<<std::endl;
                   if ( subStr.length() > maxLength )
                   {
 					   maxLength = subStr.length();
                       std::cout<<std::endl<<"update the maxLength:"<<maxLength<<std::endl;
                   }
                   subStrVector.emplace_back(subStr);
                   std::cout<<std::endl<<"check string complete: reStartPoint = strLength"<<std::endl;    
               }
               continue;
            }
            
            std::cout<<std::endl;
            std::cout<<"char["<<s[tempIndex]<<"]"<<" is repeat in subStr:"<< subStr <<std::endl;
            
			if (subStr.length() > maxLength)
			{
				maxLength = subStr.length();
                std::cout << std::endl << "update the maxLength:" << maxLength << std::endl;
			}
            subStrVector.emplace_back(subStr);
            //update reStartPoint 
            int keyNumber = 0;
            keyNumber = iterKeyVector - keyVector.begin();
            std::cout<<std::endl<<"The key number NO. is: "<<keyNumber<<std::endl;
            reStartPoint = reStartPoint + keyNumber + 1;
            
            if (tempIndex == strLength - 1 )
            {
               isStrEndFlag = true;
               std::cout<<std::endl<<"check string complete: tempIndex == strLength - 1"<<std::endl;
            } 
            
            break;
        }
    }
    
    std::cout << std::endl << "The maxLength is:" << maxLength << std::endl;
    std::cout << std::endl << "The subStr is:" <<subStr<< std::endl;
    return maxLength;
}


#define K 3

int Solution::threeSumClosest(vector<int>& nums, int target)
{
    using recodeResultMap = std::map<int,int>;
    int result = 0;
    int MinSum = 0; 
       
    std::sort(nums.begin(), nums.end());

	int index = 0;
    for ( index = 0;  index < K; index++)
    {
        MinSum = MinSum + nums[index]; 
		if (target > 0)
		{
			result = target - MinSum;
		}
		else
		{
			result = MinSum - target;
		}
    }

    std::cout<<std::endl<<"result is : "<<result<<std::endl;

    for (int index1 = 0; index1 < nums.size() - K; index1++)
    {
        MinSum = MinSum - nums[index1] + nums[index1+K];

		if (target > 0)
		{
			result = (target - MinSum) > result ? result : (target - MinSum);
		}
		else
		{
			result = (MinSum - target) > result ? result : (MinSum - target);
		}

		std::cout<<std::endl<<"result is : "<<result<<std::endl;                   
    } 
 
	std::cout << std::endl << "loop  result is : " << result << std::endl;
	if (target > 0)
	{
		result = target - result;
	}
	else
	{
		result = result + target;
	}

    std::cout<<std::endl<<"output result is : "<< result<<std::endl;
    return result;

}

//42. Trapping Rain Water
int Solution::trap(vector<int> &height)
{
    if (height.size() < 3)
    {
        return 0;
    }

    int length = height.size();
    vector<int> l_max(length, 0);
    vector<int> r_max(length, 0);
    vector<int> water(length, 0);
    int sumWater = 0;
    int index = 0;

    for (index = 1; index < length - 1; index++)
    {
        l_max[index] = *std::max_element(height.begin(), height.begin() + (index - 1));
        //l_max[index] = *std::max_element(height.begin(), height.begin() + index );
    }

    for (index = 0; index < length - 1; index++)
    {
        r_max[index] = *std::max_element(height.begin()+ index, height.end() - 1);
    }

    for (index = 1; index < length - 1; index++)
    {
        water[index] = std::max(l_max[index], r_max[index]) - height[index];
        std::cout << std::endl
                  << "i is: " << index << " ,water[i] is: " << water[index] << std::endl;
        sumWater = sumWater + water[index];
    }

    std::cout << std::endl << "sum water is: " << sumWater << std::endl;

}



/*
Given a m x n grid filled with non-negative numbers, 
find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

Input:
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
Output: 7
Explanation: Because the path 1→3→1→1→1 minimizes the sum.

*/
using CostValue = unsigned int;
using NodeNo = int;
using FatherNodeNo = int;
using NodeInfo = std::map<NodeNo, CostValue>;
using Neighbors = std::map<NodeNo, CostValue>;
using Graps = std::map<NodeNo, Neighbors>;
using Costs = std::map<NodeNo, CostValue>;
using Parents = std::map<NodeNo, FatherNodeNo>;
using ProcessedNode = std::vector<NodeNo>;
//using ProcessedNode = std::map<NodeNo,CostValue>;

//const NodeNo InvalidNodeNo{0xffffffff};
const NodeNo InvalidNodeNo = 0xffffffff;
const CostValue MaxCostValue = 0xffffffff;

void ConstructGraps(vector<vector<int>>& grid, Graps &graps)
{
    int gridLineNum = grid.size();
    int gridRowNum = grid[0].size();
    int gridNodesNumber = gridLineNum * gridRowNum;

    std::cout<<"grid line number is: "<< gridLineNum <<std::endl;
    std::cout<<"grid row number is: "<< gridRowNum <<std::endl;
    std::cout<<"node number is: "<< gridNodesNumber <<std::endl;

    for (int index = 0; index < gridNodesNumber; index++)
    {
        int lineNum = index / gridRowNum;
        int rowNum = index % gridRowNum;

        //CostValue costValue = grid[gridLineNum][gridRowNum];
        NodeNo nodeNo = index;
        Neighbors neighbors;

        //add nodes
        graps.emplace(nodeNo, neighbors);

        //two neighbors : right and down
        if (rowNum + 1 < gridRowNum)
        {
            //add neighbor node1 --> right direction
            NodeNo node1 = nodeNo + 1;
            CostValue node1CostValue = grid[lineNum][rowNum + 1];
            graps[nodeNo].emplace(node1, node1CostValue);
        }

        if (lineNum +1 < gridLineNum)
        {
             //add neighbor node2 down direction
             NodeNo node2 = nodeNo + gridRowNum;
             CostValue node2CostValue = grid[lineNum+1][rowNum];
             graps[nodeNo].emplace(node2, node2CostValue);
        }

    }
   
    std::cout<<std::endl<<"------grid to graps------"<<std::endl;
    
    for (auto &grapIter : graps)
    {
        Neighbors nodeNeighbors = grapIter.second;
        NodeNo  nodeNo = grapIter.first;
        std::cout<<std::endl<<"Node No. "<< nodeNo <<std::endl;
        //for(index = 0 ; index < nodeNeighbors.size(); index++)
        for (auto &neighborIter : nodeNeighbors)
        {
           NodeNo  neighborNodeNo = neighborIter.first; 
           std::cout<<"---->"<<"["<< neighborIter.first << ", "
           << neighborIter.second <<"]"<<std::endl;
        }
    }
 
}

void InitCostsAndParents(vector<vector<int>> &grid,
                         Graps &graps,
                         Costs &costs,
                         Parents &parents)
{
    
    costs[0] = grid[0][0];
    parents[0] = 0;
    
    for (int index = 1; index < graps.size(); index++)
    {
        costs[index] = MaxCostValue;
        parents[index] = InvalidNodeNo;
    }
    
}

/*
NodeNo find_MinCostNode(Costs &costs, ProcessedNode &processedNode)
{
    NodeNo minCostNode = InvalidNodeNo;
    CostValue minCostNodeValue = MaxCostValue;

    for (auto& costIter : costs)
    {
       NodeNo nodeNo = costIter.first;
       auto iter = processedNode.find(nodeNo);
       if (iter != processedNode.end())
       {
          continue;  
       }

       CostValue costValue = costIter.second;
       if (minCostNodeValue > costValue)
       {
           minCostNodeValue = costValue;
           minCostNode = costIter.first;
       }
    }

    std::cout << "minCostNode is: " << minCostNode << std::endl;
  
    if (minCostNode != InvalidNodeNo)
    {
        std::cout << "minCostNode cost value is: " << costs[minCostNode] << std::endl;
    }
    
    return minCostNode;
}

*/

NodeNo find_MinCostNode(Costs &costs, ProcessedNode &processedNode)
{
    NodeNo minCostNode = InvalidNodeNo;
    CostValue minCostNodeValue = MaxCostValue;

    for (auto& costIter : costs)
    {
       NodeNo nodeNo = costIter.first;
       auto iter = std::find(processedNode.begin(), processedNode.end(), nodeNo);
       if (iter != processedNode.end())
       {
          continue;  
       }

       CostValue costValue = costIter.second;
       if (minCostNodeValue > costValue)
       {
           minCostNodeValue = costValue;
           minCostNode = costIter.first;
       }
    }

    std::cout << "minCostNode is: " << minCostNode << std::endl;
    
    if (minCostNode != InvalidNodeNo)
    {
        std::cout << "minCostNode cost value is: " << costs[minCostNode] << std::endl;
    }
    
    return minCostNode;
}

void PrintMinPathNode(vector<vector<int>>& grid, Parents &parents)
{
    int gridSize = parents.size();
    int gridLine, gridRow;
    gridLine = grid.size();
    gridRow = grid[0].size();

    NodeInfo pathNodeInfo;
    NodeNo fatherNodeNo = parents.at(gridSize-1);

    std::cout << "fatherNodeNo  is : " << fatherNodeNo << std::endl;
    pathNodeInfo.emplace(std::pair<NodeNo,CostValue>(0, grid[0][0]));

    while( 0 != fatherNodeNo )
    {
       //pathNodeInfo.emplace(std::pair<NodeNo,CostValue>(fatherNodeNo,));
       CostValue costvalue = grid[fatherNodeNo/gridRow][fatherNodeNo%gridRow];
       pathNodeInfo.insert(pathNodeInfo.begin(), std::pair<NodeNo,CostValue>(fatherNodeNo, costvalue));
      
       fatherNodeNo = parents.at(fatherNodeNo);
       std::cout << "fatherNodeNo  is : " << fatherNodeNo << std::endl;
    }

    pathNodeInfo.emplace(std::pair<NodeNo,CostValue>(gridSize-1, grid[gridLine-1][gridRow-1]));
    
    std::cout<<"======= min path grap ========"<<std::endl;
    int index = 0;
    for (auto &pathNodeInfoIter : pathNodeInfo) 
    {
        std::cout << "node[" << pathNodeInfoIter.first << "]"
                  << ":" << pathNodeInfoIter.second
                  << "--->";
        index++;
        if( (index) % 3 == 0)
        {
            std::cout<<std::endl;
        }
    }
}

int Solution::minPathSum_no_time(vector<vector<int>>& grid)
{
    // instrct graps
    TimeCount timeCout;
    int row, line;
    row = grid.size();
    line = grid[0].size();
    Costs costs;
    Parents parents;
    ProcessedNode processedNode;

	Graps graps;
    //funtcionttest();
    ConstructGraps(grid, graps);

    InitCostsAndParents(grid, graps, costs, parents);

    NodeNo minCostNodeNo = InvalidNodeNo;

    minCostNodeNo = find_MinCostNode(costs, processedNode);

    while (minCostNodeNo != InvalidNodeNo)
    {
        CostValue nodeCostValue = costs[minCostNodeNo];
        Neighbors neighbors;
        neighbors = graps[minCostNodeNo];
      
        for (auto& neighborIter : neighbors)
        {
           CostValue neighborNodeCost =  neighborIter.second;
           neighborNodeCost = nodeCostValue + neighborNodeCost;
           if (neighborNodeCost < costs[neighborIter.first])
           {
               //update the neighbor node cost
               costs[neighborIter.first] = neighborNodeCost;
               parents[neighborIter.first] = minCostNodeNo; 
           }
        }

        processedNode.emplace_back(minCostNodeNo);
        //processedNode.emplace(std::pair<NodeNo,CostValue>{minCostNodeNo, MaxCostValue});
        minCostNodeNo = find_MinCostNode(costs, processedNode);
    }
    CostValue minPathCost = costs[row*line -1];
    std::cout<<"min path is : "<<minPathCost <<std::endl;

    PrintMinPathNode(grid, parents);
	return minPathCost;
}


int Solution::minPathSum(vector<vector<int>>& grid)
{
    TimeCount timeCount;
    int gridLine, gridRow;
    gridLine = grid.size();
    gridRow = grid[0].size();

    std::cout << std::endl
              << "grid line is: " << gridLine;
    std::cout << std::endl
              << "grid row is: " << gridRow;

    for (int index0 = 0; index0 < gridLine; index0++)
    {
        for (int index1 = 0; index1 < gridRow; index1++)
        {

            if (index0 == 0)
            {
                if (0 == index1)
                    continue;
                grid[0][index1] = grid[0][index1] + grid[0][index1 - 1];
                continue;
            }

            if (0 == index1)
            {
                grid[index0][0] = grid[index0][0] + grid[index0 -1][0];
                continue;
            }

            grid[index0][index1] = std::min(grid[index0 - 1][index1], grid[index0][index1 - 1]) + grid[index0][index1];
        }
    }

    int costValue = grid[gridLine-1][gridRow-1];
    std::cout << std::endl
              << "The min path is : " << costValue << std::endl;
    return costValue;
}