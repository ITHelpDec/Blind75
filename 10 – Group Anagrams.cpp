#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <chrono>

// pleased with this result, although i'm sure it could be better
std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string> &strs) {
    // create container for final solution
    std::vector<std::vector<std::string>> solution;
    
    // create local copy of strings
    std::vector<std::string> svec(strs);
    
    // sort strings alphabetically whilst retaining order
    for (auto &s : svec) { std::sort(s.begin(), s.end()); }
    
    // create unordered maps to store sorted string and indices
    std::unordered_map<std::string, std::vector<std::string>> smap;
    
    // add our string permutations and their corresponding index to our map
    for (int i = 0; i != strs.size(); ++i) { smap[svec[i]].push_back(strs[i]); }
    
    // traverse through map, adding each vector to our solution
    for (const auto &[s, svec] : smap) { solution.push_back(svec); }
    
    return solution;
}

// not too different to my answer, albeit slightly cleaner
std::vector<std::vector<std::string>> groupAnagrams2(const std::vector<std::string> &strs) {
    // create container for solution
    std::vector<std::vector<std::string>> solution;
    solution.reserve(strs.size());
    
    // create map to store sorted string and vector of permutations
    std::unordered_map<std::string, std::vector<std::string>> smap;
    smap.reserve(strs.size());
    
    // main loop to populate map
    for (const std::string &s : strs) {
        std::string s_sorted = s;
        sort(s_sorted.begin(), s_sorted.end());
        smap[s_sorted].push_back(s);
    }
    
    // second loop to populate answer
    for (const auto &[s, svec] : smap) { solution.push_back(svec); }
            
    return solution;
}

void printSolution(const std::vector<std::vector<std::string>> &solution)
{
    for (const auto &svec : solution) {
        for (const auto &s : svec) {
            std::cout << "\"" << s << "\" ";
        } std::cout << std::endl;
    } std::cout << std::endl;
}

int main()
{
    std::vector<std::string> svec = { "eat", "tea", "tan", "ate", "nat", "bat" };
    std::vector<std::string> svec2 = { "" };
    std::vector<std::string> svec3 = { "a" };
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    printSolution(groupAnagrams(svec));
    printSolution(groupAnagrams2(svec));
    
    printSolution(groupAnagrams(svec2));
    printSolution(groupAnagrams2(svec2));
    
    printSolution(groupAnagrams(svec3));
    printSolution(groupAnagrams2(svec3));
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    t1 = std::chrono::high_resolution_clock::now();
    groupAnagrams(svec);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "groupAnagrams(svec):   " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    groupAnagrams2(svec);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "groupAnagrams2(svec):  " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl << std::endl;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    t1 = std::chrono::high_resolution_clock::now();
    groupAnagrams(svec2);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "groupAnagrams(svec2):   " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    groupAnagrams2(svec2);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "groupAnagrams2(svec2):  " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    t1 = std::chrono::high_resolution_clock::now();
    groupAnagrams(svec3);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "groupAnagrams(svec3):   " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    groupAnagrams2(svec3);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "groupAnagrams2(svec3):  " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    return 0;
}
