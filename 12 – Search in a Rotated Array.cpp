#include <vector>
#include <algorithm>
#include <chrono>
#include <iostream>

// this ran extremely quickly!
// first run 0ms, 11ms, then 3ms
int search(const std::vector<int> &nums, int target) {
    if (std::find(nums.begin(), nums.end(), target) == nums.end())
        return -1;
    return *std::find(nums.begin(), nums.end(), target);
}

int search2(const std::vector<int> &nums, int target) {
    int low = 0, high = nums.size() - 1;
    
    // find the index of the smallest value using binary search.
    // Loop will terminate since mid < hi, and lo or hi will shrink by at least 1.
    // Proof by contradiction that mid < hi: if mid==hi, then lo==hi and loop would have been terminated.
    while (low < high) {
        int mid = (low + high) / 2;
        
        if (nums[mid] > nums[high]) { low = mid + 1; }
        else { high = mid; }
    }
    
    // lo==hi is the index of the smallest value and also the number of places rotated.
    int rot = low;
    low = 0; high = nums.size() - 1;
    
    // The usual binary search and accounting for rotation.
    while (low <= high) {
        int mid = (low + high) / 2;
        int real_mid = (mid + rot) % nums.size();
        
        if (nums[real_mid] == target) { return real_mid; }
        if (nums[real_mid] < target) { low = mid + 1; }
        else { high = mid-1; }
    }
    
    return -1;
}

int search3(const std::vector<int> &nums, int target) {
    int lo = 0, hi = nums.size();
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        
        double num = (nums[mid] < nums[0]) == (target < nums[0])
                   ? nums[mid]
                   : target < nums[0] ? - INT_MAX : INT_MAX;
                   
        if (num < target)
            lo = mid + 1;
        else if (num > target)
            hi = mid;
        else
            return mid;
    }
    return -1;
}



int main()
{
    search( { 4, 5, 6, 7, 0, 1, 2 }, 0);
    search( { 4, 5, 6, 7, 0, 1, 2 }, 3);
    search( { 13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,1,2,3,4,5,6,7,8,9,10,11,12 }, 28);
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    t1 = std::chrono::high_resolution_clock::now();
    search( { 4, 5, 6, 7, 0, 1, 2 }, 0);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "search(nums):   " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    search2( { 4, 5, 6, 7, 0, 1, 2 }, 0);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "search2(nums):  " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    search3( { 4, 5, 6, 7, 0, 1, 2 }, 0);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "search3(nums):  " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl << std::endl;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    t1 = std::chrono::high_resolution_clock::now();
    search( { 4, 5, 6, 7, 0, 1, 2 }, 3);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "search(nums2):   " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    search2( { 4, 5, 6, 7, 0, 1, 2 }, 3);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "search2(nums2):  " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    search3( { 4, 5, 6, 7, 0, 1, 2 }, 3);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "search3(nums2):  " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl << std::endl;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    t1 = std::chrono::high_resolution_clock::now();
    search( { 1 }, 0);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "search(nums3):   " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    search2( { 1 }, 0);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "search2(nums3):  " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    search3( { 1 }, 0);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "search2(nums3):  " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl << std::endl;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    return 0;
}
