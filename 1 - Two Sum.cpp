/*
 Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

 You may assume that each input would have exactly one solution, and you may not use the same element twice.

 You can return the answer in any order.

  

 Example 1:

 Input: nums = [2,7,11,15], target = 9
 Output: [0,1]
 Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
 Example 2:

 Input: nums = [3,2,4], target = 6
 Output: [1,2]
 Example 3:

 Input: nums = [3,3], target = 6
 Output: [0,1]
  

 Constraints:

 2 <= nums.length <= 104
 -109 <= nums[i] <= 109
 -109 <= target <= 109
 Only one valid answer exists.
  

 Follow-up: Can you come up with an algorithm that is less than O(n2) time complexity?
*/

#include <vector>
#include <iostream>
#include <chrono>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int> &nums, int target);
    
    // I may create a random test_case generator
private:
    std::vector<int> indices;
};

// I have used an outer and an inner iterator
// no need to calculate [1] + [0] if we've already calculated [0] + [1]
// reserved two spaces in memory for the answer to prevent reallocation after .push_back()
// N.B. whilst this might work well for small vectors, nums.size() will dictate the fastest method
std::vector<int> Solution::twoSum(std::vector<int> &nums, int target)
{
    indices.reserve(2);
    for (auto outer_it = nums.begin(); outer_it != nums.end(); ++outer_it) {
        for (auto inner_it = outer_it + 1; inner_it != nums.end(); ++inner_it) {
            if (*outer_it + *inner_it == target) {
                indices.push_back(outer_it - nums.begin());
                indices.push_back(inner_it - nums.begin());
                return indices;
            }
        }
    }
    return indices;
}

int main()
{
    std::vector<int> test_case = { 1, 2, 3, 4, 5 };
    Solution sol;
    
    auto t1 = std::chrono::high_resolution_clock::now();
    sol.twoSum(test_case, 9);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "test function took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds\n";
    
    return 0;
}
