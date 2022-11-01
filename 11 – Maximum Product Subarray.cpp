#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

// try remember maxSubarray() question...
// provides correct answers, but heap overflow on leetcode
// both solutions below this are considerably faster
int maxProduct(std::vector<int> &nums) {
    // create reference copy to traversal
    std::vector<int> reference_ivec(nums);
    
    // set reference_ivec[i] to whichever is greater
    // a new subarray – or – the current running subarray
    for (int i = 1; i != nums.size(); ++i) {
        if (nums[i-1] * nums[i] * nums[i+1] > 0 && i + 1 != nums.size()) {
            ++i; reference_ivec[i] = nums[i] * nums[i-1] * nums[i-2]; }
        else reference_ivec[i] = std::max(nums[i], nums[i] * reference_ivec[i-1]);
    }
    
    // return the largest answer from our reference vector
    return *std::max_element(reference_ivec.begin(), reference_ivec.end());
}

// other solution
int maxProduct2(const std::vector<int> &nums) {
    int r = nums[0];
    
    // imax/imin stores the max/min product of
    // subarray that ends with the current number A[i]
    for (int i = 1, imax = r, imin = r; i < nums.size(); i++) {
        // multiplied by a negative makes big number smaller, small number bigger
        // so we redefine the extremums by swapping them
        if (nums[i] < 0)
            std::swap(imax, imin);
        
        // max/min product for the current number is either the current number itself
        // or the max/min by the previous number times the current one
        imax = std::max(nums[i], imax * nums[i]);
        imin = std::min(nums[i], imin * nums[i]);
        
        // the newly computed max value is a candidate for our global result
        r = std::max(r, imax);
    }
    return r;
}

// and another using the left/right principle
int maxProduct3(const std::vector<int> &nums) {
        int n = nums.size(), res = nums[0], l = 0, r = 0;
        for (int i = 0; i < n; i++) {
            l =  (l ? l : 1) * nums[i];
            r =  (r ? r : 1) * nums[n - 1 - i];
            res = std::max(res, std::max(l, r));
        }
        return res;
    }

int main()
{
    std::vector<int> nums = { 2, 3, -2, 4 };
    std::vector<int> nums2 = { -2, 0, -1 };
    std::vector<int> nums3 = { -2, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 13, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 3, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 7, -2, -4, 5 };
    std::vector<int> nums4 = { -2, -3, 4 };
    std::vector<int> nums5 = { 7, -2, -4 };
    std::vector<int> nums6 = { -2, 3, 4 };
    std::vector<int> nums7 = { -2, -3, -4 };
    std::vector<int> nums8 = { -3, -1, -1 };
    std::vector<int> nums9 = { -3 };
    std::vector<int> nums10 = { -3, -4 };
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    std::cout << maxProduct(nums) << " ";
    std::cout << maxProduct(nums) << " ";
    std::cout << maxProduct(nums) << std::endl;
    
    std::cout << maxProduct(nums2) << " ";
    std::cout << maxProduct(nums2) << " ";
    std::cout << maxProduct(nums2) << std::endl;
    
    std::cout << maxProduct(nums3) << " ";
    std::cout << maxProduct(nums3) << " ";
    std::cout << maxProduct(nums3) << std::endl;
    
    std::cout << maxProduct(nums4) << " ";
    std::cout << maxProduct(nums4) << " ";
    std::cout << maxProduct(nums4) << std::endl;
    
    std::cout << maxProduct(nums5) << " ";
    std::cout << maxProduct(nums5) << " ";
    std::cout << maxProduct(nums5) << std::endl;
    
    std::cout << maxProduct(nums6) << " ";
    std::cout << maxProduct(nums6) << " ";
    std::cout << maxProduct(nums6) << std::endl;
    
    std::cout << maxProduct(nums7) << " ";
    std::cout << maxProduct(nums7) << " ";
    std::cout << maxProduct(nums7) << std::endl;
    
    std::cout << maxProduct(nums8) << " ";
    std::cout << maxProduct(nums8) << " ";
    std::cout << maxProduct(nums8) << std::endl;
    
    std::cout << maxProduct(nums9) << " ";
    std::cout << maxProduct(nums9) << " ";
    std::cout << maxProduct(nums9) << std::endl;
    
    std::cout << maxProduct(nums10) << " ";
    std::cout << maxProduct(nums10) << " ";
    std::cout << maxProduct(nums10) << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    t1 = std::chrono::high_resolution_clock::now();
    maxProduct(nums);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "maxProduct(nums):   " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
    maxProduct2(nums);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "maxProduct2(nums):  " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    maxProduct3(nums);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "maxProduct3(nums):  " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl << std::endl;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    t1 = std::chrono::high_resolution_clock::now();
    maxProduct(nums2);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "maxProduct(nums2):   " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
    maxProduct2(nums2);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "maxProduct2(nums2):  " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    maxProduct3(nums2);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "maxProduct3(nums2):  " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl << std::endl;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    t1 = std::chrono::high_resolution_clock::now();
    maxProduct(nums3);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "maxProduct(nums3):   " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
    maxProduct2(nums3);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "maxProduct2(nums3):  " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    maxProduct3(nums3);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "maxProduct3(nums3):  " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    return 0;
}
//
