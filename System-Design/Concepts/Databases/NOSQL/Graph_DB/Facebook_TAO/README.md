## Entities in Graph?

[Information taken from this Article](https://medium.com/swlh/an-introduction-to-facebooks-system-architecture-47cfcf597101#:~:text=The%20Data%20Model%20For%20Social,a%20single%20giant%20social%20graph.&text=A%20node%20represents%20an%20entity,the%20relationships%20between%20the%20nodes.)

- FB stores (users, comments, posts, locations) as Nodes in giant graph. This graph has 5 billion+ entries.
- **Example**
  - 4 Friends(kush,amit,prasad,arpit). 
  - Kush created a post "Party"
  - Amit commented "Great party @Prasad"(tagged prasad)
  - Arpit liked comment.
  
  <img src="https://i.ibb.co/9qBgMhp/fb-friends.png" width="700" />
  
## Database(MySQL) schema?
- Relationship between entities is stored in MySQL DB using 2 tables.
- Data is stored across sharded databases. 
- **FB's Optimization on DB?** 
  - *1.* Stores Id and its association on same database, for faster and single query look up.
  - *2.* FB developed MyRocks-DB based on Log Structure Merge (LSM) tree.

- **1. Object Table**
```c
  |  id(int) |  otype(string) |                 data(byte)              |
  |----------|----------------|-----------------------------------------|
  |   567    |  user          |     kush  (max 50 characters)           |
  |   444    |  post          |     Party (max 63206 characters)        |
  |   332    |  comment       | Great Party@prasad (max 8000 characters)|
  -----------------------------------------------------------------------
```

- **2. Relation/Association/Edge Table**
```c
  |  Source-id(int) |  Dst-Id(int)  | Edge-Type(string) | key-value(Optional)(byte) |
  |-----------------|---------------|-------------------|---------------------------|
  |       567       |     999       |   friends         |   null                    |
  |       567       |     444       |   authored        |   null                    |  
  |       444       |     332       |   Comment         |   reaction:smily emoji    |
  -----------------------------------------------------------------------------------
```

## How user data/posts/comments/friend list is accessed?
#### 1. Using TAO(Distributed Data store) 
  - **What?** Database frontend(Developed at FB), which provides APIs to RW data from databases. It acts as Write-Thru cache.
  - **API Types?**
    - *1. Object access APIs:* Add/delete/query/update objects
    - *2. Edge/Association access APIs:* Add/delete/query/update associations. Example
```c
struct/class {
  long source-id;
  long dst-id;
  string edge-type;  
  unordered_map <key,value>;
}Edge;

 Edge[] Edge_get(567, friends)    //Edge_get(id1, edge-type)   
  //Returns all edges originating from id1 and having particular edge-type
  
  int Edge_count(567, friends)    //Edge_count(id, edge-type)
  //Count of All edges from id=567 having edge-type=friends
```
