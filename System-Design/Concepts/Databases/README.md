**Databases**

- **Comparisons**
  - [Object, Block, File Storage](#obf)
  - [SQL/Relational/Structured vs NoSQL/nonRelational/unStructured](#sn)
  - [Database vs Datawarehouse](#dd)
- [2. IMDB / In Memory DB](#imdb)
  - [2.1 Problem with IMDB = Availability,Expensive](#prob)
  - [2.2 What data should be stored on IMDB](#dataimdb)
  - [2.3 IMDB vs DBCache](#imdb_vs_cache)
  - [2.4 Why Redis is cache & imdb both?](#whyredis)


## Comparisons
<a name=obf></a>
### Object vs Block vs File storage
```c
DB           |   Object                           | Block                    |                 File
-------------|------------------------------------|--------------------------|-------------------------------
Stores       | objects{ID,metaData+data}          | raw blocks(xfs,ext4 etc) | data in file, with limited meta-data
Scaling      | Easy                               | Tough(on high volume becomes unmanagable)
Suitable for |Static data(docs,photos,songs,videos)
Consistency  | Eventual consistent                | Strongly consistent
Use cases    | Not good for transactional 
               data(bcoz of eventual consistency)
Examples     | Amazon S3,ceph, openstack swift    | Amazon EBS, SAN-Arrays   |  Amazon EFS
```

<a name=sn></a>
### SQL vs noSQL
Today most organization are using SQL+noSQL DB combinations. 2019 stats:   MySQL + MongoDB: 34.15%,  MySQL + PostgreSQL: 9.76%
```c
  DB               |  SQL, Relational, Structured                         | noSQL, nonRelational, unStructured
-------------------|------------------------------------------------------|--------------------------------------------
Storage format     | Table(Records searched using primary key)            | key-value or xml or json or objects
Huge data support  | no(becomes slow)                                     | yes
Storage            | May be on 1 or multiple servers                      | Always on multiple low cost nodes[commodity hardware]
Scaling            | Vertical                                             | Horizontal, cheaper, raw data can be pushed:no schema, pro
Tech Support       | Good, query-writing:simple                           | Poor, query-writing:complex
Schema             | fixed                                                | not fixed. defining schema for unstructured data is very tough
Examples           | Amazon S3, MySQL, postgreSQL                         | SEMI:    Amazon S3, Apache Cassandra,dynamoDB
                                                                            UNSTRU:  Amazon S3, Apache CouchDB, MongoDB
Types              |ORDBMS(Object RDBMS):RDBMS build on OOD.Eg:PostGreSQL | a. KEY-VALUE DB Eg: redis, dynamoDB, Voldemort
                    RDBMS: mySQL                                          | b. WIDE-COLUMN DB: Stores data as columns instead of rows. 
                                                                          |    Eg: Cassandra, HBase
                                                                          | c. DOCUMENT DB: data is stored in documents(XML, JSON, binary) 
                                                                               Eg: mongoDB, dynamoDB
                                                                          | d. GRAPH DB: Data is stored in form of graph.
                                                                               Eg: Neo4J, HyperGraphDB</li></ul>
```  

<a name=dd></a>
### Database vs Datawarehouse
```c
                 |     Database                            | Datawarehouse
-----------------|-----------------------------------------|-------------------
Purpose          | Stores customer data                    | helps analyze data
Contians         | related data                            | Historical & commutative data
Orientation      | application-oriented-collection of data | subject-oriented collection of data
Uses             | Online Transactional Processing (OLTP)  |  Online Analytical Processing (OLAP)
Modelling Techniques | ER modeling techniques              | data modeling
used 
```

<a name=imdb></a>
### 2. IMDB(In Memory DB) / MMDB(Main Memory DB)
- Stores all data in main memory/RAM not on hard-disk. 
- **Examples** VoltDB, [Redis](/System-Design/Concepts/Cache)
- **Advantages**
  - Faster. Since disk access is always slower than RAM
- **Applications?** Where response time is critical. Eg: Telecom equiments, Jet communications etc

<a name=prob></a> 
### 2.1 Problems
#### A. [RAM is volatile = Availability](/System-Design/Concepts/Terms) 
- Means data is lost as power is gone or some failure.
- **How imdb solves this?**
  - _1._ Snapshot files, or, checkpoint images, which record the state of the database at a given moment in time.
  - _2._ Transaction logging, which records changes to the database in a journal file
  - _3._ Non-Volatile DIMM (NVDIMM)
  - _4._ Non-volatile random-access memory (NVRAM)
  - _5._ Replication
#### B. Expensive
- RAM is always costlier than Disk, Huge amounts cannot be stored here.

<a name=dataimdb></a>
### 2.2 Which data should be stored?
- Most frequently accessed data.

<a name=imdb_vs_cache></a>  
### 2.3 IMDB vs [DBCache](/System-Design/Concepts/Cache)
- DBCache stores: Mostly used, less frequently changing data is stored in cache.
- IMDB stores: Frequently changing data.

<a name=whyredis></a>  
### 2.4 Why Redis is cache & imdb both?
- Redis has features of a Cache plus processing/querying capabilities. Redis supports multiple data structures and you can query the data in the Redis (examples like get last 10 accessed items, get the most used item etc).
