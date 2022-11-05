#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <iterator>
#include <unordered_map>

// incomplete...
// solutions below are no doubt faster, ...
// ... but would like to finish this at some point
int characterReplacement(const std::string &s, int k)
{
    // (1) store characters and iterator positions to map
    // (2) use these to create permutations
    // e.g. "A" appears in indices 0, 1, 3 & 6
    // if k = 2, print the string three times (v.size() - 1), replacing 0 & 1, 1 & 3 and 3 & 6
    // test for largest substring
    
    // A A B A B B A    (k = 1)
    
    // elements that are not A (1st char in map)
    // A A A A B B A    s2[2]->A, largest substring (4 or 2), back to s2
    // A A B A A B A    s2[4]->A, largest substring (2 or 1), back to s2
    // A A B A B A A    s2[5]->A, largest substring (2 or 1), back to s2
    
    // elements that are not B (2nd char in map)
    // B A B A B B A    s2[A][0]->B, largest substring (1 or 2), back to s2
    // A B B A B B A    s2[A][1]->B, largest substring (1 or 2), back to s2
    // A A B B B B A    s2[A][2]->B, largest substring (2 or 4), back to s2
    // A A B A B B B    s2[A][3]->B, largest substring (2 or 3), back to s2
    
   
    
    // edge case for strings 1 or 2 characters long
    if (s.size() == 1) { return 1; }
    if (s.size() == 2) { return 2; }
    
    // (1) create character map to hold character and where it appears in the string
    std::map<char, std::vector<std::vector<char>::const_iterator> > character_map;
    
    for (auto str_it = s.begin(); str_it != s.end(); ++str_it)
    { character_map[*str_it].push_back(str_it); }
    
    // incomplete
    for (const auto &[c, it_vec] : character_map) {
        for (auto it = *it_vec.begin() ; it != *it_vec.end(); ++it) {
            std::cout << std::distance(*it_vec.begin(), it) << std::endl;
            int count = k;
            std::string ref_string(s);
        }
    }
    
    return 0;
}

// good solution below
// O(n) time complexity; O(128) space
int characterReplacement2(const std::string &s, int k)
{
    // containers to hold result and maximum
    int result = 0, max_occurences = 0;
    
    // create map to hold character index and occurences of that index
    std::unordered_map<int, int> count;
    
    // go through length of string
    for (int i = 0; i < s.length(); ++i) {
        // which is greater - current occurences? or occurences of char in map?
        max_occurences = std::max(max_occurences, ++count[s[i]]);
        
        if (result - max_occurences < k) { result++; }
        else { count[s[i - result]]--; }
    }
    return result;
}

// a more traditional sliding window version
int characterReplacement3(const std::string &s, int k) {
    int max_occurences = 0, i = 0, n = s.length();
    std::vector<int> count(26);
    for (int j = 0; j < n; ++j) {
        max_occurences = std::max(max_occurences, ++count[s[j] - 'A']);
        if (j - i + 1 > max_occurences + k)
            --count[s[i++] - 'A'];
    }
    return n - i;
}

int main()
{
    std::string s = "ABAB";
    std::string s2 = "AABABBA";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // std::cout << "characterReplacement(s, 2):  " << characterReplacement(s, 2) << std::endl;
    std::cout << "characterReplacement2(s, 2): " << characterReplacement2(s, 2) << std::endl;
    std::cout << "characterReplacement3(s, 2): " << characterReplacement3(s, 2) << std::endl << std::endl;
    
    // std::cout << "characterReplacement(s2, 1):  " << characterReplacement(s2, 1) << std::endl;
    std::cout << "characterReplacement2(s2, 1): " << characterReplacement2(s2, 1) << std::endl;
    std::cout << "characterReplacement3(s2, 1): " << characterReplacement3(s2, 1) << std::endl << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // t1 = std::chrono::high_resolution_clock::now();
    // characterReplacement(s, 2);
    // t2 = std::chrono::high_resolution_clock::now();
    // std::cout << "characterReplacement(s, 2)  took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
    characterReplacement2(s, 2);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "characterReplacement2(s, 2) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
    characterReplacement3(s, 2);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "characterReplacement3(s, 2) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds.\n" << std::endl;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // t1 = std::chrono::high_resolution_clock::now();
    // characterReplacement(s2, 1);
    // t2 = std::chrono::high_resolution_clock::now();
    // std::cout << "characterReplacement2(s2, 1) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
    characterReplacement2(s2, 1);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "characterReplacement2(s2, 1) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    characterReplacement3(s2, 1);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "characterReplacement3(s2, 1) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds.\n" << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    return 0;
}
