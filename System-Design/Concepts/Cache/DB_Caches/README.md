## Location
```c
App/Webserver <--->[Cache]<-->[Database]
```

### Comparison
||Memcached|Redis|
|---|---|---|
|Key-value pair| y (key<250B, value<1MB)| y (key<512MB, value<512MB)|
|Overhead|less. It does not have any inbuilt datatypes|More. Bcoz it supports datatypes as(string,hash,list,set)|
|opensource | y | y |
|Language|C|C|
|How internally implemented|Slab Allocator|encapsulated version of the malloc/free|
|Scaling|Multi-threaded. Scales vertically. Give more cores, more memory|Single Threaded. Scales horizontally|
|Replication||2 slave nodes with master|
|Purging policy|LRU|6 different policies|
|Speed|less|more(since it supports different datatypes)|
