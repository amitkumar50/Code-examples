## ElastiCache
- **What?** Web service acting as in-memory cache in the cloud. This improves the performance of web applications by allowing you to retrieve information from fast, managed store.
- Compliant with memcached, redis
- **Replication Support** supports master-slave replication, multi-AZ deployments
    
### Architecture
```
  Client
  
  mobile  <------>  [ELB]   <------>  [App-server]        <--------->   [mySQL-DB]
  PC                                   ElastiCache-master
                                       ElastiCache-slave
```
