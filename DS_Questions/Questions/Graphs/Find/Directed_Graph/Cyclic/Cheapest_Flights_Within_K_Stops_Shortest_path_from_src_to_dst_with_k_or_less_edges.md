**Cheapest Flights Within K Stops**
- [Logic](#l)
- [Code](#co)

## [Cheapest Flights Within K Stops](https://leetcode.com/problems/cheapest-flights-within-k-stops/)
<a name=l></a>
#### Logic
- Similar to Dijstra's Shortest path Algo we will take `minHeap<cost,node,stops>`
- Fill neighbours, increase stops by 1.
- When (stops > K) continue;    //ie if any node is reachable with stops > k, then its no use to consider it.

<a name=co></a>
#### Code
```cpp
using VecI = vector<int>;
using VecVecI = vector<VecI>;
using UsI = unordered_set<int>;

                //cost_to_reach_this_node, node, stops_to_reach_this_Node
using tple = tuple<int, int, int>;

class Solution {
    //priority_queue <mpair, vector<mpair>, greater<mpair>> minHeap;
    priority_queue <tple, vector<tple>, greater<tple>> minHeap;
    unordered_map<int/*src*/, unordered_map<int/*dst*/, int/*cost*/>> graph;

    void create_weighted_graph(int cities, VecVecI& flights) {
        for (int i=0;i<flights.size();++i) {
            int src = flights[i][0];
            int dst = flights[i][1];
            int cost = flights[i][2];
            graph[src].insert(make_pair(dst,cost));
        }
    }

public:
    int findCheapestPrice(int n, VecVecI& flights, int start, int dst, int K) {

        //Create a Adjacency List
        create_weighted_graph(n, flights);
        
        vector<int> cost_from_start_node(n+1, INT_MAX);

        //Cost of reaching start node=0 is 0 with stops=0
        minHeap.emplace(0, start, 0);

        while( !minHeap.empty() ) {
            auto [cost, node, stop] = minHeap.top(); minHeap.pop();

            if( node == dst )
                return cost;

                //Optimization to avoid TLE
            if(cost_from_start_node[node] < stop)
                continue;

            cost_from_start_node[node] = stop;

            if(stop >K ) 
                continue;
            
            for( auto it : graph[node] ) {
                auto [neighbour, cost_to_reach_neighbour] = it;
                minHeap.emplace(cost+cost_to_reach_neighbour,
                                neighbour,
                                stop+1);
            }
        }
        return -1;
    }
};
```
