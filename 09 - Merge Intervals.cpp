#include <vector>
#include <iostream>
#include <algorithm>

// attempt ran, but not well
// potentially more complicated than it needed to be, but better run times than previous attempts
std::vector<std::vector<int>> merge(const std::vector<std::vector<int>> &intervals) {
    if (intervals.size() == 1) { return intervals; }
    // try n-1 approach
    std::vector<std::vector<int>> solution;
    solution.reserve(intervals.size());
    
    // initialise first vector e.g. { 1, 6 } )
    if (
        ( ((intervals[0][1] <= intervals[1][1]) && (intervals[1][0] >= intervals[0][0]))
        ||  // left outer vs right outer
        ((intervals[0][1] >= intervals[1][1]) && (intervals[1][0] <= intervals[0][0])) ) &&
        (intervals[0][1] >= intervals[1][0])
        ) {
            // return min of left-values, max of right-values
            solution.push_back( { std::min(intervals[0][0], intervals[1][0]),
                                   std::max(intervals[0][1], intervals[1][1]) } );
            
            if (intervals.size() == 2) { return solution; }
        }
    
    else { if (intervals.size() == 2) { return intervals; }
        solution.push_back( { std::min(intervals[0][0], intervals[1][0]),
                               std::max(intervals[0][1], intervals[1][1]) } );
    }
    
    auto left_iterator = solution.begin();
    auto right_iterator = intervals.begin() + 2;
    
    for ( ; right_iterator != intervals.end(); ++right_iterator) {
        if (
            (left_iterator->data()[1] <= right_iterator->data()[1]) &&
            (right_iterator->data()[0] >= left_iterator->data()[0]) &&
            (left_iterator->data()[1] >= right_iterator->data()[0])
            )
            { solution.push_back( { left_iterator->data()[0] , right_iterator->data()[1] } ); }
        else
            solution.push_back(*right_iterator);
            ++left_iterator;

    }
    
    return solution;
}

// faster of the three functions
std::vector<std::vector<int>> merge2(std::vector<std::vector<int>> &intervals)
{
    // edge case for intervals having one vector
    if (intervals.size() == 1 ) { return intervals; }
    
    // sort intervals for easier comparison
    std::sort(intervals.begin(), intervals.end());
    // std::sort(intervals.begin(), intervals.end(), [](const std::vector<int> &v1, const std::vector<int> &v2) { return v1[0] < v2[0]; } );
    
    // create container for our answers
    std::vector<std::vector<int>> output;
    
    // mirror first elements of each vector before loop
    output.push_back(intervals[0]);
    
    //traverse through vectors
    for (int i = 1; i < intervals.size(); ++i) {
        // check left-outer vs right inner
        if (output.back()[1] >= intervals[i][0])
            // change left-outer to greater of the two and carry on
            output.back()[1] = std::max(output.back()[1] , intervals[i][1]);
        // otherwise, add interval element
        else output.push_back(intervals[i]);
    }
    return output;
}

// this also looks good
std::vector<std::vector<int>> merge3(std::vector<std::vector<int>> &intervals) {
    // create container for answer
    std::vector<std::vector<int>> solution;
    
    
    // if(v.size() == 0) return ans;
    std::sort(intervals.begin(), intervals.end());
    
    std::vector<int> reference_vector = intervals[0];
    
    for (const auto &ivec : intervals) {
        if (ivec[0] <= reference_vector[1]) { reference_vector[1] = std::max(reference_vector[1] , ivec[1]); }
        else {
            solution.push_back(reference_vector);
            reference_vector = ivec;
        }
    }
    
    solution.push_back(reference_vector);
    
    return solution;
}

void printSolution(const std::vector<std::vector<int>> &solution)
{
    for (const auto &ivec : solution) {
        for (const auto &e : ivec) {
            std::cout << e << ", ";
        } std::cout << "|| ";
    } std::cout << std::endl;
}

int main()
{
    std::vector<std::vector<int>> intervals = { { 1, 3 }, { 2, 6 }, { 8, 10 } , { 15, 18 } };
    std::vector<std::vector<int>> intervals2 = { { 1, 4 } , { 5, 6 } };
    std::vector<std::vector<int>> intervals3 =  { { 1, 4 }, { 0, 4 } };
    std::vector<std::vector<int>> intervals4 =  { { 1, 4 }, { 2, 3 } };
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    printSolution(merge(intervals));
    printSolution(merge2(intervals));
    printSolution(merge3(intervals));
    
    printSolution(merge(intervals2));
    printSolution(merge2(intervals2));
    printSolution(merge3(intervals2));
    
    printSolution(merge(intervals3));
    printSolution(merge2(intervals3));
    printSolution(merge3(intervals3));
    
    printSolution(merge(intervals4));
    printSolution(merge2(intervals4));
    printSolution(merge3(intervals4));
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    t1 = std::chrono::high_resolution_clock::now();
    merge(intervals);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "merge(intervals):    " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    merge2(intervals);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "merge2(intervals):  " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
    merge3(intervals);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "merge3(intervals):  " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    t1 = std::chrono::high_resolution_clock::now();
    merge(intervals2);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "merge(intervals2):    " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    merge2(intervals2);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "merge2(intervals2):   " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
    merge3(intervals2);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "merge3(intervals2):   " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl << std::endl;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    t1 = std::chrono::high_resolution_clock::now();
    merge(intervals3);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "merge(intervals3):    " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
    merge2(intervals3);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "merge2(intervals3):   " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
    merge3(intervals3);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "merge3(intervals3):   " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl << std::endl;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    t1 = std::chrono::high_resolution_clock::now();
    merge(intervals4);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "merge(intervals4):    " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
    merge2(intervals4);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "merge2(intervals4):   " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
    merge3(intervals4);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "merge3(intervals4):   " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " ns." << std::endl << std::endl;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    return 0;
}
