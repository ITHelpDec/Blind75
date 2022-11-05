#include <vector>
#include <map>
#include <iostream>
#include <queue>
#include <utility>

void printMatrix(const std::vector<std::vector<char>> &grid) {
    for (const auto &row_vec : grid) {
        for (const auto &c : row_vec) {
            std::cout << c << " ";
        } std::cout << std::endl;
    } std::cout << std::endl;
}

// attempt (does not solve all edge cases)
// wasn't aware of BFS or DFS prior to this, but idea was similar
int numIslands(const std::vector<std::vector<char>> &grid) {
    // edge case for [[1]] or [[0]] – can only be an island if surrounded by water
    if (grid.size() == 1) { return 0; }
    
    // edge case for either all 1's or all 0's
    int one_count = 0;
    for (const auto &cvec : grid)
        for (const auto &c : cvec)
            if (c == '1') { ++one_count; }
    if (one_count == 0) { return 0; }
    
    // create container for number of islands
    int island_number = 1;
    
    // printMatrix(grid);
    // std::cout << std::endl;
    
    for (int i = 1; i != grid.size(); ++i) {
        for (int j = 1; j != grid.size(); ++j) {
            if ( (grid[i][j] == '1' && grid[i - 1][j - 1] == '1' && grid[i][j - 1] == '0' && grid[i - 1][j] == '0') ||
                (grid[i][j] == '0' && grid[i - 1][j - 1] == '0' && grid[i][j - 1] == '1' && grid[i - 1][j] == '1'))
                 ++island_number;
        }
    }
    
    // std::cout << "Answer: " << island_number << std::endl << std::endl;
    return island_number;
}

// cleaner solution using a breadth-first search
int numIslands2(std::vector<std::vector<char>> grid) {
    // rows (may be zero!)
    int number_of_rows = grid.size();
    
    // columns - original version used the line below?
    // int number_of_columns = number_of_rows ? grid[0].size() : 0;
    int number_of_columns = grid[0].size();// number_of_rows ? grid[0].size() : 0;
    
    // container to hold final answer
    int number_of_islands = 0;
    
    // "offset" vector to navigate neighbouring cells i.e.
    // [k][k + 1] ... [i][j+1] [i+1][j] [i][j-1] [i-1][j]
    std::vector<int> offset_vector = { 0, 1, 0, -1, 0 };
    
    // print grind for reference
    // printMatrix(grid);
    
    // traverse through the grid
    // std::cout << "Searching for land mass...\n";
    for (int row = 0; row != number_of_rows; ++row)
        for (int column = 0; column != number_of_columns; ++column) {
            
            // find our first spot of land
            if (grid[row][column] == '1') {
                // std::cout << "New land mass found! How far does it go?...\n\n";
                ++number_of_islands;
                // std::cout << "Number of islands: " << number_of_islands << std::endl << std::endl;
                
                // change value of cell to prevent further counts
                grid[row][column] = '#';
                // printMatrix(grid);
                
                // create a [row, coloumn] queue for our breadth first search (FIFO)
                std::queue<std::pair<int, int>> breadth_first_search;
                
                // add our first pair to the queue
                breadth_first_search.push({ row, column });
                
                // perform our breadth first search until all branches are complete
                while (!(breadth_first_search.empty())) {
                    
                    // pop our first pair off the queue and store it temporarily to work from
                    std::pair<int, int> p = breadth_first_search.front();
                    breadth_first_search.pop();
                    
                    // visit neighbouring cells and add them to the queue if they are a land mass
                    for (int i = 0; i != offset_vector.size() - 1; ++i) {
                        
                        // create coordinates
                        int x = p.first + offset_vector[i], y = p.second + offset_vector[i + 1];
                        
                        // check coordinates are not our of bounds
                        if (x >= 0 && x < number_of_rows && y >= 0 && y < number_of_columns && grid[x][y] == '1') {
                            
                            // change value to prevent recounting and push suitable coordinates to the queue for processing
                            grid[x][y] = '#';
                            // printMatrix(grid);
                            breadth_first_search.push({ x, y });
                        }
                    }
                }
            }
        }
    // std::cout << "Answer: " << number_of_islands << std::endl;
    return number_of_islands;
}

// helper function for numIslands3
void depthFirstSearch(std::vector<std::vector<char>> &grid, int r, int c) {
    // set up row and column bounds again for neighbouring cell checks
    // would be useful to inherit these if incorporated into a class
    int number_of_rows = grid.size(), number_of_columns = grid[0].size();
    
    // jump out if coordinates are out of bounds (or not land)
    if (r < 0 || r == number_of_rows || c < 0 || c == number_of_columns || grid[r][c] == '0' || grid[r][c] == '#')
    { return; }
    
    // replace current cell to avoid duplicates and begin recursive searches on neighbouring cells
    if (grid[r][c] == '1') { grid[r][c] = '#'; }
    
    // printMatrix(grid); std::cout << std::endl;
    depthFirstSearch(grid, r - 1, c);
    depthFirstSearch(grid, r + 1, c);
    depthFirstSearch(grid, r, c - 1);
    depthFirstSearch(grid, r, c + 1);
}

// depth-first search – quite a bit faster on Xcode, but similar time on leetcode
int numIslands3(std::vector<std::vector<char>> grid) {
    // initialise variables as before and traverse through grid
    int number_of_rows = grid.size(), number_of_columns = grid[0].size(), number_of_islands = 0;
    for (int row = 0; row != number_of_rows; row++)
        for (int column = 0; column != number_of_columns; column++)
            // increment count when land found
            if (grid[row][column] == '1') {
                ++number_of_islands;
                // call depth first search this time
                depthFirstSearch(grid, row, column);
            }
    // std::cout << "Answer: " << number_of_islands << std::endl;
    return number_of_islands;
}


int main()
{
    std::vector<std::vector<char>> grid = {
        { '1', '1', '1', '1', '0' },
        { '1', '1', '0', '1', '0' },
        { '1', '1', '0', '0', '0' },
        { '0', '0', '0', '0', '0' }
    };
    
    std::vector<std::vector<char>> grid2 = {
        { '1', '1', '0', '0', '0' },
        { '1', '1', '0', '0', '0' },
        { '0', '0', '1', '0', '0' },
        { '0', '0', '0', '1', '1' }
    };
    
    std::vector<std::vector<char>> grid3 = {
        { '0', '0', '0', '0', '0' },
        { '0', '0', '0', '0', '0' },
        { '0', '0', '0', '0', '0' },
        { '0', '0', '0', '0', '0' }
    };
    
    std::vector<std::vector<char>> grid4 = {
        { '1', '0', '1', '1', '0', '1', '1' }
    };
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // std::cout << "numIslands(): ";
    // std::cout << numIslands(grid) << ", ";
    // std::cout << numIslands(grid2) << ", ";
    // std::cout << numIslands(grid3) << ", ";
    // std::cout << numIslands(grid4) << std::endl;
    
    std::cout << "numIslands2(): ";
    std::cout << numIslands2(grid) << ", ";
    std::cout << numIslands2(grid2) << ", ";
    std::cout << numIslands2(grid3) << ", ";
    std::cout << numIslands2(grid4) << std::endl;
    
    std::cout << "numIslands3(): ";
    std::cout << numIslands3(grid) << ", ";
    std::cout << numIslands3(grid2) << ", ";
    std::cout << numIslands3(grid3) << ", ";
    std::cout << numIslands3(grid4) << std::endl << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // t1 = std::chrono::high_resolution_clock::now();
    // numIslands(grid);
    // t2 = std::chrono::high_resolution_clock::now();
    // std::cout << "numIslands(grid)  took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
    numIslands2(grid);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "numIslands2(grid) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
    numIslands3(grid);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "numIslands3(grid) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds.\n" << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // t1 = std::chrono::high_resolution_clock::now();
    // numIslands(grid2);
    // t2 = std::chrono::high_resolution_clock::now();
    // std::cout << "numIslands(grid2)  took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
    numIslands2(grid2);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "numIslands2(grid2) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
    numIslands3(grid2);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "numIslands3(grid2) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds.\n" << std::endl;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // t1 = std::chrono::high_resolution_clock::now();
    // numIslands(grid3);
    // t2 = std::chrono::high_resolution_clock::now();
    // std::cout << "numIslands(grid3)  took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
    numIslands2(grid3);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "numIslands2(grid3) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
    numIslands3(grid3);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "numIslands3(grid3) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds.\n" << std::endl;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // t1 = std::chrono::high_resolution_clock::now();
    // numIslands(grid4);
    // t2 = std::chrono::high_resolution_clock::now();
    // std::cout << "numIslands(grid4)  took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
    numIslands2(grid4);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "numIslands2(grid4) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds." << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
    numIslands3(grid4);
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "numIslands3(grid4) took " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << " nanoseconds.\n" << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    return 0;
}
