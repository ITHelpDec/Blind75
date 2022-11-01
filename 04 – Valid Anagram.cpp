#include <string>
#include <algorithm>
#include <map>
#include <iostream>
#include <chrono>
#include <unordered_map>

bool isAnagramOne(const std::string &s, const std::string &t) {
    std::map<char, std::size_t> smap;
    
    for (const auto &e : s) { ++smap[e]; }
    for (const auto &e : t) { --smap[e]; }
    for (const auto &e : smap) { if (e.second > 0) return false; }
    
    return true;
}

bool isAnagramTwo(std::string &s, std::string &t) {
    std::sort(s.begin(), s.end());
    std::sort(t.begin(), t.end());
    
    return s == t;
}

bool isAnagramThree(std::string s, std::string t) {
    if (s.length() != t.length()) return false;
    int n = s.length();
    std::unordered_map<char, int> counts;
    for (int i = 0; i < n; i++) {
        counts[s[i]]++;
        counts[t[i]]--;
    }
    for (auto count : counts)
        if (count.second) return false;
    return true;
}

// fastest
bool isAnagramFour(std::string s, std::string t) {
    if (s.length() != t.length()) return false;
    int n = s.length();
    int counts[26] = {0};
    for (int i = 0; i < n; i++) {
        counts[s[i] - 'a']++;
        counts[t[i] - 'a']--;
    }
    for (int i = 0; i < 26; i++)
        if (counts[i]) return false;
    return true;
}

int main()
{
    std::string s = "anagram", t = "nagaram";
    
    auto t1 = std::chrono::high_resolution_clock::now();
    isAnagramOne(s, t);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "This programme took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << " nanoseconds." << std::endl;
    
    auto t3 = std::chrono::high_resolution_clock::now();
    isAnagramTwo(s, t);
    auto t4 = std::chrono::high_resolution_clock::now();
    std::cout << "This programme took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t4 - t3).count() << " nanoseconds." << std::endl;
    
    auto t5 = std::chrono::high_resolution_clock::now();
    isAnagramThree(s, t);
    auto t6 = std::chrono::high_resolution_clock::now();
    std::cout << "This programme took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t6 - t5).count() << " nanoseconds." << std::endl;
    
    auto t7 = std::chrono::high_resolution_clock::now();
    isAnagramFour(s, t);
    auto t8 = std::chrono::high_resolution_clock::now();
    std::cout << "This programme took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t8 - t7).count() << " nanoseconds." << std::endl;
}
