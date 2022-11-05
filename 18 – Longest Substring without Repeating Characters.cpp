#include <string>
#include <iostream>
#include <set>
#include <vector>

// works: slow on leetcode, but considerably faster on here in release mode
int lengthOfLongestSubstring(const std::string &s) {
    // edge case for .size() of 0 or 1
    if (s.size() < 2) { return s.size(); }
    
    // create containers for current and greatest sub-string lengths
    int current_substring_length = 1, longest_substring_length = 1;
    
    auto temp_it = s.begin();
    for (auto it = s.begin() + 1; it != s.end(); ++it) {
        // std::cout << "temp_it: " << *temp_it << ", it: " << *it << std::endl;
        // std::cout << "duplicates of " << *it << " = " << std::count(temp_it, it, *it) << std::endl;
        if (std::count(temp_it, it, *it) == 0) { ++current_substring_length; }
        else { current_substring_length = 1; ++temp_it; it = temp_it; }
        longest_substring_length = std::max(longest_substring_length, current_substring_length);
        // std::cout << "current substring: " << current_substring_length << " (longest: " << longest_substring_length << ")\n" << std::endl;
    }
    
    // std::cout << "Answer: " << longest_substring_length << std::endl;
    return longest_substring_length;
}

// faster solution on leetcode
int lengthOfLongestSubstring2(const std::string &s) {
    // bucket with 256 values, all equal to "-1"
    // 256, because there are a total of 256 English letters, digits, symbols and spaces (extended ASCII)
    std::vector<int> dict(256, -1);
    
    // containers for max and current
    int maxLen = 0, start = -1;
    
    // traverse through string
    for (int i = 0; i != s.length(); i++) {
        // std::cout << "i = " << i << std::endl;
        // std::cout << "dict[s[i]]: " << dict[s[i]] << ", start: " << start << std::endl;
        
        // characters translated into ASCII code
        if (dict[s[i]] > start)
            start = dict[s[i]];
        
        // std::cout << "dict[s[i]]: " << dict[s[i]] << ", start: " << start << std::endl;
        
        // set that character in the bucket to i
        dict[s[i]] = i;
        
        // std::cout << "maxLen (" << maxLen << ") vs i - start (" << i - start << ")" << std::endl;
        
        // i - start will give current substring length
        // if character repeats, maxLen will be greater than i - start
        maxLen = std::max(maxLen, i - start);
        
        // std::cout << "maxLen: " << maxLen << std::endl << std::endl;
    }
    // std::cout << "Answer: " << maxLen << std::endl;
    return maxLen;
}


int main()
{
    std::string s = "abcabcbb";
    std::string s2 = "asldjbfeuaubdsadiasobsadsadipnadiogbdonfsaifhdgbfgndklfhoeqbfoadfjslnjldnaslnakdlnoasdiasndsaasdqwertyuiopasdfghjklzxcvbnmsadpgbnjsaljbvdibasaslkdnbsaoudqwerty";
    std::string s3 = "pwwkew";
    std::string s4 = "dvdf";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    std::cout << lengthOfLongestSubstring(s) << std::endl;
    std::cout << lengthOfLongestSubstring(s2) << std::endl;
    std::cout << lengthOfLongestSubstring(s3) << std::endl;
    std::cout << lengthOfLongestSubstring(s4) << std::endl << std::endl;
    
    std::cout << lengthOfLongestSubstring2(s) << std::endl;
    std::cout << lengthOfLongestSubstring2(s2) << std::endl;
    std::cout << lengthOfLongestSubstring2(s3) << std::endl;
    std::cout << lengthOfLongestSubstring2(s4) << std::endl << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    t1 = std::chrono::high_resolution_clock::now();
    lengthOfLongestSubstring(s);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "lengthOfLongestSubstring(s)  took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    lengthOfLongestSubstring(s2);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "lengthOfLongestSubstring(s2) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
    lengthOfLongestSubstring(s3);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "lengthOfLongestSubstring(s3) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    lengthOfLongestSubstring(s4);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "lengthOfLongestSubstring(s4) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds.\n" << std::endl;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    t1 = std::chrono::high_resolution_clock::now();
    lengthOfLongestSubstring2(s);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "lengthOfLongestSubstring2(s)  took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    lengthOfLongestSubstring2(s2);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "lengthOfLongestSubstring2(s2) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
    lengthOfLongestSubstring2(s3);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "lengthOfLongestSubstring2(s3) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    lengthOfLongestSubstring2(s4);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "lengthOfLongestSubstring2(s4) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds.\n" << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    return 0;
}
