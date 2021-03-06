## [Problem leetcode](https://leetcode.com/problems/number-of-islands/)
- Given matrix '1's (land) and '0's (water) count islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
- Example
```c++
Input:
11110
11010
11000
00000
Output: 1
```

## Logic-1(Using visited array)
```c++
1. Take visited[][] vector same sized as original 2D vector.
2. Mark all adjacent `1's` as visited using recursion.
        -> Do not use queue/stack because it will slow adding and removing elements
           to queue.
3. Traverse whole array and check unvisited `1's`:
        -> count++ whenever unvisited 1 is found.
```

## Code-1
```c++
#include<vector>
#include<iostream>
#include<queue>
#include<chrono>
using namespace std::chrono;
using namespace std;

class Solution {
public:
  void markConnectedVisited(vector<vector<char>>& grid, vector<vector<int>>& vis, int f, int s, int row, int col){
    vis[f][s]=1;
    if (f>0 && (vis[f-1][s] == false) && (grid[f-1][s] == '1')){        //Above Element
      markConnectedVisited (grid, vis, f-1, s, row, col);
     }
    if (s>0 && (vis[f][s-1] == false) &&  (grid[f][s-1] == '1')){       //Left Element
      markConnectedVisited (grid, vis, f, s-1, row, col);
    }
    if ((s<=col-2) && (vis[f][s+1] == false) && (grid[f][s+1] == '1')){ //Right Element
      markConnectedVisited (grid, vis, f, s+1, row, col);
    }
    if ((f<=row-2) && (vis[f+1][s] == false) && (grid[f+1][s] == '1')){ //Below element
      markConnectedVisited (grid, vis, f+1, s, row, col);
    }
  }

  int numIslands(vector<vector<char>>& grid){
    int rows = grid.size(), cols=grid[0].size(), count = 0;
    if(rows == 0)
        return 0;

    vector<vector<int>> vis(rows, vector<int>(cols,0)); //Visited Array of same size as grid, init to 0

    for(int i=0; i<rows; i++)                              //O(mn)
      for(int j=0; j<cols; j++)
                        
        if(vis[i][j]==0 && grid[i][j]=='1'){
          count++;
          markConnectedVisited (grid, vis, i, j, rows, cols);
        }
     return count;
   }
};
```

## Logic-2(Modifying incoming array, No extra Space)
- Each visited node is marked as 2
- Start from index=0,0. Mark Island as 2.
```c++
   1  1  1  1  0
   1  1  0  1  0
   1  1  0  0  0
   0  0  0  0  0
--become-->   
   2  2  2  2  0
   2  2  0  2  0
   2  2  0  0  0
   0  0  0  0  0
```
### Code-2
```c++
void MarkIslandVisited(std::vector<std::vector<int>>& grid,
                        int i/*row*/, int j/*col*/, int& MaxRows, int& MaxCols){
  grid[i][j]=2;
  
  if (i<=MaxRows-2 and grid[i+1][j]==1)   //below
    MarkIslandVisited(grid,i+1,j,MaxRows,MaxCols);

  if (j<=MaxCols-2 and grid[i][j+1]==1)     //right
    MarkIslandVisited(grid,i,j+1,MaxRows,MaxCols);

  if (j>0 and grid[i][j-1]==1)    //back
    MarkIslandVisited(grid,i,j-1,MaxRows,MaxCols);

  if (i>0 and grid[i-1][j]==1)    //above
    MarkIslandVisited(grid,i-1,j,MaxRows,MaxCols);
}

int numIslands(std::vector<std::vector<int>> grid){
  int MaxRows = grid.size();
  int MaxCols = grid[0].size();
  int count = 0;

  for (int i=0; i<MaxRows; ++i)
    for (int j=0; j<MaxCols; ++j)
      if (grid[i][j] == 1){
        ++count;
        MarkIslandVisited(grid,i,j,MaxRows,MaxCols);
      }
  return count;
}
```
