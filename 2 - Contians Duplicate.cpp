/*
 Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.
 
 Example 1:

 Input: nums = [1,2,3,1]
 Output: true
 Example 2:

 Input: nums = [1,2,3,4]
 Output: false
 Example 3:

 Input: nums = [1,1,1,3,3,4,3,2,4,2]
 Output: true
  

 Constraints:

 1 <= nums.length <= 105
 -109 <= nums[i] <= 109
 
*/

#include <vector>
#include <algorithm>
#include <iostream>

class Solution {
public:
    bool containsDuplicate(std::vector<int> &nums) {
        std::sort(nums.begin(), nums.end());
        return (std::adjacent_find(nums.begin(), nums.end()) != nums.end());
    }
};

int main()
{
    std::vector<int> ivec = { 0, 1, 2, 3, 4, 5, 6};
    
    Solution sol;
    std::cout << sol.containsDuplicate(ivec) << std::endl;
    
    return 0;
}
