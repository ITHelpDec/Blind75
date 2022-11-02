#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// iterative reversal
// this seems to be the faster of the tow
ListNode* reverseList(ListNode* head) {
    // create two pointers – previous_node and next_node
    ListNode *previous_node = NULL, *next_node;
    
    while (head) { // for as long as "head" is a valid pointer to a node
        
        // (1) set the next_node to next
        next_node = head->next;
        
        // (2) change the direction of the current pointer
        //     we do this by overwriting the current node's "next" to the prevoous node
        head->next = previous_node;
        
        // (3) shift the previous node forward one
        previous_node = head;
        
        // (4) shift the current node forward one and repeat
        head = next_node;
    }
    // "head" is now NULL, so we point to our last valid node
    return previous_node;
}

// another example – this time, recursively
ListNode* reverseList2(ListNode *head) {
    // if head isn't valid, or has no valid next node, return head
    if ( !head || !head->next ) { return head; }
    
    // create a recursive function using head->next as the argument
    ListNode* head_next = reverseList2(head->next);
    
    // set the next NEXT node to our current node
    head->next->next = head;
    
    // set our next node to nullptr
    head->next = nullptr;
    
    // go down the rabbit hole!...
    return head_next;
}

int main()
{
    // set up linked list with values from 1-5
    ListNode head5(5);
    ListNode head4(4, &head5);
    ListNode head3(3, &head4);
    ListNode head2(2, &head3);
    ListNode head(1, &head2);
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // create nod pointer from first node
    std::cout << "ascending:  ";
    ListNode *lnp = &head;
    
    // traverse through nodes
    while (lnp) { std::cout << lnp->val << "->"; lnp = lnp->next; } std::cout << "NULL\n" << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        
    // set pointer to first node...
    std::cout << "descending: ";
    lnp = &head;
    
    // ...reverse iteratively...
    t1 = std::chrono::high_resolution_clock::now();
    reverseList(lnp);
    t2 = std::chrono::high_resolution_clock::now();
    
    // ...set to final node, then traverse in reverse order
    lnp = &head5;
    while (lnp) { std::cout << lnp->val << "->"; lnp = lnp->next; } std::cout << "NULL" << std::endl;
    
    std::cout << "reverseList(head) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds.\n" << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // start from end node this time...
    std::cout << "ascending:  ";
    lnp = &head5;
    
    // ...reverse recursively...
    t1 = std::chrono::high_resolution_clock::now();
    reverseList2(lnp);
    t2 = std::chrono::high_resolution_clock::now();
    
    // ...set the first node, then traverse
    lnp = &head;
    while (lnp) { std::cout << lnp->val << "->"; lnp = lnp->next; } std::cout << "NULL" << std::endl;
    
    std::cout << "reverseList2(head) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds.\n" << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    return 0;
}
