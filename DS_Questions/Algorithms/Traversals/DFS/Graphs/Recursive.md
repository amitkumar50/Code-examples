**Recursive DFS**
- [Logic](#l)
- [Pseudo code](#pc)

### Recursive DFS
**Question:** Find cost of reaching dst node from src in Directed,Cyclic Graph.
<a name=l></a>
#### Logic
- _1._ Let graph is stored as [Hashmap of hashmap](/DS_Questions/Data_Structures/Graphs/Directed_Undirected#hmhm). Now we need find cost from `a to c`.
- _2._ Take a visited array. 
- _3._ Pass graph, visited to dfs() function.
  - _a._ Inside dfs(), Insert starting node into visited
  - _b._ Find whether starting node is present in graph or not. if not found return -1; 
  - _c._ if dst is directly connected neighbour?
    - _c1._ Yes. return cost
    - _c2._ No. Check all connected neighbours of neighbour to be equal to dst.
      - _c21._ if neighbour is already visited(ie present in visited array). Do nothing
      - _c22._ jump to unvisited neighbour.
  - _d._ When all neighbours of present node are searched, delete present node from visited.

<a name=pc></a>
#### Pseudo code
```c
  a ---2.0----> b -----3.0----> c
  /\           | /\             |
  |---1/2.0----| |------1/3.0---|

main() {
  unordered_map<char, unordered_map<char, double>> umGraph;   //stores graph  //1
  unordered_set<char> visited;                                                //2
  dfs (a, c, cost);
}

double dfs (char src, char dst, double pro, umGraph, visited) {               //3
  visited.insert(src);                                                          //a
  auto it = umGraph.find(src);                                                  //b
  auto it1 = it->second.find(dst);                                              //c
  if (it1 != it->second.end())                                                  //c1
    return cost;
  else {                                                                        //c2
    for (all neighbours(k) of neighbour) {
      if (k is in visited array)                                                //c21
        continue;
      dfs (src=neighbour(k), dst, pro, graph, visited);                         //c22
    }
  }
  visited.erase(src);                                                           //d
}
```
