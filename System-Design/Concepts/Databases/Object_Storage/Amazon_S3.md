## S3(Simple Storage Service)
- Each object has Metadata(name of the object, size and date) and object itself.
- S3 has buckets(there are stored as per regions) for storing the objects. each bucket can have 100's of objects.
```c
  |          |    |          |
  |o1 o3 o100|    |o7 o5 o239|
  ------------    ------------
    Bucket-1        Bucket-n
```
- **S3 Storage classes**

|Class|What|
|---|---|
|1. S3|Durable, immediately available and frequently accessed|
|2. S3-IA(Infrequently accessed)|For data that is accessed less frequently|
|3. S3 – RRS (Reduced Redundancy Storage)| Less durable with availabilty. Used for data that is easily reproducible, such thumbnails|
      
![ImgUrl](https://i.ibb.co/q0xNcyW/s3.png)
