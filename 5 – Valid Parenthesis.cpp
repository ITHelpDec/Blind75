#include <string>
#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include <chrono>

bool isValid(const std::string &s) {
    std::stack<char> cstack;
    
    for (const auto &e : s) {
        // push opening brackets to stack
        if ( (e == '(') || e == ('[') || e == ('{') ) { cstack.push(e); }
        
        // otherwise, if top() is closing bracket, pop()
        else if ( !(cstack.empty()) &&
                 (
                  ( (cstack.top() == '(') && (e == ')') ) ||
                  ( (cstack.top() == '[') && (e == ']') ) ||
                  ( (cstack.top() == '{') && (e == '}') )
                  )
                 ) { cstack.pop(); }
        
        // return false is neither condition met
        else return false;
    }
    return cstack.empty();
}

bool isValidOther(const std::string &s) {
    std::stack<char> cstack;
    
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '(' or s[i] == '{' or s[i] == '[')
            cstack.push(s[i]);
        else if((s[i] == ')' or s[i] == '}' or s[i] == ']') and cstack.empty())
            return false;
        else if((s[i] == ')' and cstack.top() == '(') or (s[i] == '}' and cstack.top() == '{') or (s[i] == ']' and cstack.top() == '['))
            cstack.pop();
        else
            return false;
    }
    
    if(cstack.empty()) { return true; }
    
    return false;
}


bool isValidOtherTwo(const std::string &s) {
    std::stack<char> st;  //taking stack for keep tracking the order of the brackets..
    for(const auto &i : s)  //iterate over each and every elements
    {
        if(i=='(' or i=='{' or i=='[') st.push(i);  //if current element of the string will be opening bracket then we will just simply push it into the stack
        else  //if control comes to else part, it means that current element is a closing bracket, so check two conditions  current element matches with top of the stack and the stack must not be empty...
        {
            if(st.empty() or
               (st.top()=='(' and i!=')') or
               (st.top()=='{' and i!='}') or
               (st.top()=='[' and i!=']'))
                
                return false;
            st.pop();  //if control reaches to that line, it means we have got the right pair of brackets, so just pop it.
        }
    }
    return st.empty();  //at last, it may possible that we left something into the stack unpair so return checking stack is empty or not..
}

int main()
{
//    auto t0 = std::chrono::high_resolution_clock::now();
    
    auto t1 = std::chrono::high_resolution_clock::now();
    isValid("{[]}}");
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "This programme took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << " nanoseconds to complete." << std::endl;

    auto t3 = std::chrono::high_resolution_clock::now();
    isValidOther("{[]}");
    auto t4 = std::chrono::high_resolution_clock::now();
    std::cout << "This programme took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t4 - t3).count() << " nanoseconds to complete." << std::endl;
    
    auto t5 = std::chrono::high_resolution_clock::now();
    isValidOtherTwo("{[]}");
    auto t6 = std::chrono::high_resolution_clock::now();
    std::cout << "This programme took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t6 - t5).count() << " nanoseconds to complete." << std::endl;
    
    return 0;
}
