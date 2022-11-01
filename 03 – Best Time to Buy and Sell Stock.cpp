
#include <vector>
#include <iostream>
#include <chrono>
#include <string>

int maxProfit(const std::vector<int> &prices)
{
    int smallest = INT_MAX;
    int best_profit = 0;
    int profit_today = 0;
    
    for (std::vector<int>::const_iterator buy = prices.begin(); buy != prices.end(); ++buy) {
        if (*buy < smallest) { smallest = *buy; }
        profit_today = *buy - smallest;
        if (best_profit < profit_today) { best_profit = profit_today; }
    }
    return best_profit;
}

int maxProfitTheirs(const std::vector<int> &prices)
{
    int left = 0;
    int right = 1;
            
    int max_profit = 0;
    while (right < prices.size()) {
        int currentProfit = prices[right] - prices[left];
        if (prices[left] < prices[right])
            max_profit = std::max(currentProfit, max_profit);
        else
            left = right;
        right += 1;
    }
    return max_profit;
}

int maxProfitTheirs2(const std::vector<int> &prices) {
    int smallest_value = INT_MAX;
    int overall_profit = 0;
    int profit_today = 0;
    
    for(int i = 0; i < prices.size(); i++){
        if(prices[i] < smallest_value){
            smallest_value = prices[i];
        }
        profit_today = prices[i] - smallest_value;
        if(overall_profit < profit_today){
            overall_profit = profit_today;
        }
    }
    return overall_profit;
}

int maxProfitFinal(std::vector<int> &prices) {
    int min_price = 1e5;
    int ans = 0;
    for (auto p : prices) {
        min_price = std::min(min_price, p);
        ans = std::max(ans, p - min_price);
    }
    return ans;
}

int main()
{
    std::vector<int> ivec = { 7,1,5,3,6,4 };
    std::vector<int> ivec2 = { 7,6,4,3,1 };
    std::vector<int> ivec3 = { 1, 2 };
    std::vector<int> ivec4 = { 2, 4, 1 };
    
    std::cout << maxProfit(ivec) << " " << maxProfitTheirs(ivec) << " " << maxProfitTheirs2(ivec) << " " << maxProfitFinal(ivec) << std::endl;
    std::cout << maxProfit(ivec2) << " " << maxProfitTheirs(ivec2) << " " << maxProfitTheirs2(ivec2) << " " << maxProfitFinal(ivec2) << std::endl;
    std::cout << maxProfit(ivec3) << " " << maxProfitTheirs(ivec3) << " " << maxProfitTheirs2(ivec3) << " " << maxProfitFinal(ivec3) << std::endl;
    std::cout << maxProfit(ivec4) << " " << maxProfitTheirs(ivec4) << " " << maxProfitTheirs2(ivec4) << " " << maxProfitFinal(ivec4) << std::endl;
    
    auto t1 = std::chrono::high_resolution_clock::now();
    maxProfit(ivec4);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Programme took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << " nanoseconds to complete." << std::endl;
    
    auto t3 = std::chrono::high_resolution_clock::now();
    maxProfitTheirs(ivec4);
    auto t4 = std::chrono::high_resolution_clock::now();
    std::cout << "Programme took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t4 - t3).count() << " nanoseconds to complete." << std::endl;
    
    auto t5 = std::chrono::high_resolution_clock::now();
    maxProfitTheirs2(ivec4);
    auto t6 = std::chrono::high_resolution_clock::now();
    std::cout << "Programme took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t6 - t5).count() << " nanoseconds to complete." << std::endl;
    
    auto t7 = std::chrono::high_resolution_clock::now();
    maxProfitFinal(ivec4);
    auto t8 = std::chrono::high_resolution_clock::now();
    std::cout << "Programme took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t8 - t7).count() << " nanoseconds to complete." << std::endl;
    
    return 0;
}
