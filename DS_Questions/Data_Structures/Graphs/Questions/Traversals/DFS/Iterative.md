## Depth First Traversal
- Reach to deepest node, instead of reaching all neighbors.
```c
        0 -- 1 -- 2
         \   |   /
           \ | /
             3
                
Graph Storage: Adjacency-list
        0 -> 1,3
        1 -> 0,2,3
        2 -> 1,3
        3 -> 0,1,2

Starting node=2, dfs=2 1 0 3
```

### Logic
- *1.* Store the graph nodes in Adjacency List.
```
        vector<int> v[4];
```
- *2.* Take following datastructures:
  - `bool visited[4]` //Storing all visited nodes
  - Stack for DFS Traversal.
  - Perform these operations until stack is empty
```c
 Push 1st element on stack
 Pop top. store value in u.
 Print and mark this node as visited
 Find unvisited neighbours of this node. //Iterate through vector
   push_on_stack
   break;
```
### Code
```c++
#include<iostream>
#include<stack>
#include<vector>
using namespace std;

void dfs(vector<int> g[], int startingNode) {
  bool visited[4] = {0};
  stack<int> s;
  int u;

  s.push(startingNode);

  while (s.empty() != 1){

    u = s.top();         
    s.pop();

    visited[u] = true;
    cout<<u<<" ";

    for (auto i = g[u].begin(); i != g[u].end(); ++i){
      if (visited[*i] == false){
        s.push(*i);
        break;
      }
    }
  }//while()
}

int main() {
  vector<int> v[4];             //4 rows, variables cols
  v[0].push_back(1);
  v[0].push_back(3);              //v[0]={1,3}
  
  v[1].push_back(0);
  v[1].push_back(2); 
  v[1].push_back(3);              //v[1]={0,2,3}
  
  v[2].push_back(1); 
  v[2].push_back(3);              //v[2]={1,3}
  
  v[3].push_back(0); 
  v[3].push_back(1); 
  v[3].push_back(2);              //v[3]={0,1,2}

  int startingNode = 2;            //Let's start traversal from node=2
  cout << "Depth First Traversal:\n";
  dfs(v, startingNode);
}


/*
Output:
# ./a.out 
Starting node=2
Depth first Traversal
2 1 0 3
*/
```
