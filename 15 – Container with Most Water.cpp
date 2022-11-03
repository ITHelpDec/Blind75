#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>

// uses a similar concept to 3Sum
int maxArea(const std::vector<int> &height) {
    // "n" can be no less than 2
    if (height.size() == 2) { return std::min(height[0], height[1]); }
    
    // create container for greatest area
    int water = 0;
    
    // initialise left and right iterators
    auto bucket_left = height.begin();
    auto bucket_right= height.end() - 1;
    
    while (bucket_left < bucket_right) {
        water = std::max(water, static_cast<int>(bucket_right - bucket_left) * std::min(*bucket_left, *bucket_right));
        if (*bucket_left < *bucket_right) { ++bucket_left; }
        else { --bucket_right; }
    }
    
    return water;
}

// this time while internal while loops to move iterators
int maxArea2(const std::vector<int> &height) {
    // "n" can be no less than 2
    if (height.size() == 2) { return std::min(height[0], height[1]); }
    
    // create container for greatest area
    int water = 0;
    
    // initialise left and right iterators
    auto bucket_left = height.begin();
    auto bucket_right= height.end() - 1;
    
    while (bucket_left < bucket_right) {
        int bucket_rim = std::min(*bucket_left, *bucket_right);
        water = std::max(water, static_cast<int>(bucket_right - bucket_left) * bucket_rim);
        while (*bucket_left <= bucket_rim && bucket_left < bucket_right) { ++bucket_left; }
        while (*bucket_right <= bucket_rim && bucket_left < bucket_right) { --bucket_right; }
    }
    
    return water;
}

int main()
{
    std::vector<int> height = { 1, 8, 6, 2, 5, 4, 8, 3, 7 };
    std::vector<int> height2 = { 1, 2, 4, 3 };
    std::vector<int> height3 = { 1, 2 };
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    std::cout << maxArea(height) << std::endl;
    std::cout << maxArea2(height) << std::endl;
    
    std::cout << maxArea(height2) << std::endl;
    std::cout << maxArea2(height2) << std::endl;
    
    std::cout << maxArea(height3) << std::endl;
    std::cout << maxArea2(height3) << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    t1 = std::chrono::high_resolution_clock::now();
    maxArea(height);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "maxArea(height) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    maxArea2(height);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "maxArea2(height) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds.\n" << std::endl;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    t1 = std::chrono::high_resolution_clock::now();
    maxArea(height2);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "maxArea(height2) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    maxArea2(height2);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "maxArea2(height2) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds.\n" << std::endl;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    t1 = std::chrono::high_resolution_clock::now();
    maxArea(height3);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "maxArea(height3) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    maxArea2(height3);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "maxArea2(height3) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds.\n" << std::endl;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    return 0;
}
