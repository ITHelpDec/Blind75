#include <vector>
#include <algorithm>
#include <iostream>
#include <set>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// works, but other designs use a "fast / slow" concept
bool hasCycle(ListNode *head) {
    // store next locations (not values) and check for duplicates
    // we store locations as there may be duplicate values, but there cannot be duplicate locations
    std::vector<ListNode*> next_node_vector;
    
    while (head) { // for as many nodes are in the linked list
        
        // has this location appeared before? if so, return true
        if (std::find(next_node_vector.begin(), next_node_vector.end(), head) != next_node_vector.end())
        { return true; }
        
        // otherwise, add it to the list and keep going
        next_node_vector.push_back(head);
        head = head->next;
    }
    
    // return false if we reach the end of the list with no cycles
    return false;
}

// another example using fast and slow pointers
bool hasCycle2(ListNode *head) {
    ListNode *slow = head;
    ListNode* fast = head;
    
    // provided the list is cyclic...
    // ...move slow forward one space, and fast forward two
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        
        // if they meet, the list is cyclic
        if (slow == fast) { return true; }
    }
    
    // if they don't meet, the list is not cyclic
    return false;
}

// now try with sets to see if faster
// much faster at times than vector, but not as fast as runners
bool hasCycle3(ListNode *head) {
    // store next locations (not values) and check for duplicates
    // we store locations as there may be duplicate values, but there cannot be duplicate locations
    std::set<ListNode*> next_node_set;
    
    while (head) { // for as many nodes are in the linked list
        
        // has this location appeared before? if so, return true
        if (next_node_set.find(head) != next_node_set.end())
        { return true; }
        
        // otherwise, add it to the list and keep going
        next_node_set.insert(head);
        head = head->next;
    }
    
    // return false if we reach the end of the list with no cycles
    return false;
}

int main()
{
    // 3, 2, 0 4 (back to 2)
    ListNode node1(3), node2(2), node3(0), node4(4);
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node2;
    
    // 1, 2 (back to 1)
    ListNode node5(1), node6(2);
    node5.next = &node6;
    node6.next = &node5;
    
    // 0 (no cycle)
    ListNode node7(0);
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    ListNode *llp = &node1;
    std::cout << "hasCycle(head):  " << (hasCycle(llp) ? "Has cycle." : "No cycle.") << std::endl;
    llp = &node1;
    std::cout << "hasCycle2(head): " << (hasCycle2(llp) ? "Has cycle." : "No cycle.") << std::endl;
    llp = &node1;
    std::cout << "hasCycle3(head): " << (hasCycle3(llp) ? "Has cycle.\n" : "No cycle.\n") << std::endl;
    
    llp = &node5;
    std::cout << "hasCycle(head2):  " << (hasCycle(llp) ? "Has cycle." : "No cycle.") << std::endl;
    llp = &node5;
    std::cout << "hasCycle2(head2): " << (hasCycle2(llp) ? "Has cycle." : "No cycle.") << std::endl;
    llp = &node5;
    std::cout << "hasCycle3(head2): " << (hasCycle3(llp) ? "Has cycle.\n" : "No cycle.\n") << std::endl;
    
    llp = &node7;
    std::cout << "hasCycle(head3):  " << (hasCycle(llp) ? "Has cycle." : "No cycle.") << std::endl;
    llp = &node7;
    std::cout << "hasCycle2(head3): " << (hasCycle2(llp) ? "Has cycle." : "No cycle.") << std::endl;
    llp = &node7;
    std::cout << "hasCycle3(head3): " << (hasCycle3(llp) ? "Has cycle.\n" : "No cycle.\n") << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    llp = &node1;
    t1 = std::chrono::high_resolution_clock::now();
    hasCycle(llp);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "hasCycle(head)  took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;

    llp = &node1;
    t1 = std::chrono::high_resolution_clock::now();
    hasCycle2(llp);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "hasCycle2(head) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;
    
    llp = &node1;
    t1 = std::chrono::high_resolution_clock::now();
    hasCycle3(llp);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "hasCycle3(head) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds.\n" << std::endl;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    llp = &node5;
    t1 = std::chrono::high_resolution_clock::now();
    hasCycle(llp);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "hasCycle(head2)  took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;

    llp = &node5;
    t1 = std::chrono::high_resolution_clock::now();
    hasCycle2(llp);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "hasCycle2(head2) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;
    
    llp = &node5;
    t1 = std::chrono::high_resolution_clock::now();
    hasCycle3(llp);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "hasCycle3(head2) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds.\n" << std::endl;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    llp = &node7;
    t1 = std::chrono::high_resolution_clock::now();
    hasCycle(llp);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "hasCycle(head3)  took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;

    llp = &node7;
    t1 = std::chrono::high_resolution_clock::now();
    hasCycle2(llp);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "hasCycle2(head3) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;
    
    llp = &node7;
    t1 = std::chrono::high_resolution_clock::now();
    hasCycle3(llp);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "hasCycle3(head3) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds.\n" << std::endl;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    return 0;
}
