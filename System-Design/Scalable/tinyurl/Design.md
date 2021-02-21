# Tinyurl
- **What?** This service will provide shortened aliases redirecting to long URLs. Users are redirected to longURL as they hit short URL.
- **Why?** Short links save a lot of space when displayed, printed, messaged, or tweeted. Additionally, users are less likely to mistype shorter URLs.

- **This is Read Heavy Application. Read:Write=100:1**
  - Read Request = Redirection = 100
  - Write Request = Create shortURL = 1

## [To Cover](/System-Design/Scalable/README.md)

## 1. Requirements
- **a. Functional**
  - Given a URL, service should generate a shorter and unique alias of it.
  - When users access short link, our service should redirect them to the original link.
  - Users should be able to pick a custom short link for their URL.
  - Links should expire after default time span.
- **b. Non-Functional**
  - Highly available. 
  - Minimum latency
- **c. Extended**
  - Analytics; e.g., how many times a redirection happened?

## 2. BOE

|World Population|InternetUsers(60%)|TinyURL Writes(10-15% of Internet users)/month|
|---|---|---|
|7 Billion //Year 2020|7 x 0.6 = 4.2 Billion|4.2 x 0.15 = 630 Million|

- Writes=630M/month. Reads=630x100=63B/month

- **Traffic Estimates/QPS(Queries per sec)**
  - Writes = 630M / 30x24x60x60 = 240~250 Requests/sec = 250
  - Reads = 250x1000 = 250k
  - Total = 250k/sec

- **Storage Estimates**
  - Writes:
    - Long URL length=256 bytes, Short URL=6 bytes. 1 request requires 256+6=262 bytes.
    - 630M(month) x 12x5 = 38 Billion. 38 x 262 = 10 TB to be stored for 5 years
  - Reads: 10TBx100 = 1PB for 5 years

- **Bandwidth Estimates**
  - Writes: Incoming reuqests:250/sec. Each request size=250bytes. 250x250 = 62kB/sec
  - Reads: 62MB/sec
  
- **Cache Estimates**
  - To improve performance lets cache some URLs. Let's assume we will cache data for 1 day.
  - Following 80:20 rule, 20% of URLs are often hit.
    - Total requests/day = 250k x 12 = 30000k = 30M
    - We will Cache only 20%. 30M x .2 = 6M. //there will be many duplicate requests (of the same URL), our actual memory usage will be less than 6M
    
    
## 3. System APIs
### creating the short URL
```
    //REST API
createURL(api_dev_key, original_url, custom_alias=None, user_name=None, expire_date=None)    
  Parameters
    api_dev_key(string): Developer key of registered account.
    original_url(string): To be shortened
    custom_alias(optional): Custom key for URL
    user_name(optional): Username to be used for encoding
    expire_date(string): Optional expiration date of URL
  Returns
    short_url(string)
    
deleteURL(api_dev_key, url_key)    
  url_key: String representing the shortened URL to be retrieved; a successful deletion returns ‘URL Removed’.
```

## 5. HLD / System Design

**Steps**
- *1. to 6.* Same as [Facebook newsFeed](/System-Design/Scalable/facebook/News%20Feed/README.md)
- *7.* Web Server will redirect request to Shortening-service(May be part of Web-server or maybe not).
- *8.* Shortening service will generate short-url/keys (See below)
- *9.* Shortening service sends short-url to DB-updater, to store short url in DB via [DB-Cache](/System-Design/Concepts/Cache/Where_Cache_Can_Be_Placed/README.md).
```c
    Shortening-service          DB-updater   Cache     DB
                    -short url-> 
                                       --short url-->
                                            <-Duplicate-
                                    regenerate & store
```

### Generating short-url/keys by shortening service
- **Steps of Generating short-url**
  - *a.* Calculate [SHA3(512 bit) or MD5(128bit) hash](https://sites.google.com/site/amitinterviewpreparation/networking/layer3/security).
```c
  long-url > |SHA3 or MD5 Hash|  > XXX
```
  - *b.* if we return 8 character short URL. Total possible combinations: 64<sup>8</sup> = 2.8 x 10<sup>14</sup> = 280 Trillion. <<Huge Enough
  - Now we need to Convert 128bit hash to [Base-64 format](/System-Design/Concepts/Number_System).
```c
- Base-2 uses 2 bits to create a word : 2=2^1
- Base-8 uses 3 bits to create word : 8=2^3
- Base-16 uses 4 bits to create word: 16=2^4
- Base-64 uses 6 bits to create word: 64=2^6
  - Hash = 128 bits. 128/6 = 21.33 = 21 characters or words. But we need only 8 characters as Output short-url.
```
  - *c.* Deducing 8 character short-url from 21 characters.
    - Return 1st 8 characters from 21 characters.
    - Problem: Differnt long URL's can produce same 1st 8 characters.
    - Solution: Append timestamp or userId with longURL and then generate the short url

- **When to Generate Short url? Runtime or offline**
  - *1.* Runtime. As we get write request, generate short-url and return
  - *2.* Offline. Pre-generate short-urls in advance, store in Key-DB for later use.
    - ***KGS(Key Generation Service)***: KGS will generate the 6-letter keys/short-url beforehand and keep in shorturl-DB.
      - Size of Short-url DB? 
        - Base-64 will have 64<sup>6</sup> = 70 Billion unique six letter short-urls.
        - 1 key = 6 characters = 6 bytes. 2<sup>8</sup>=64. Means 8 bits can represent 64 distinct numbers.
        - Total storage = 6 * 70B = 420B 
      - Advantages of before hand key generation:
        - *a.* Run Time calculations saving.
        - *b.* Collions will be saved. We already have generated keys in place hence risk of same key generation is 0
    - How KGS stores short-urls? Using seperate 2 databases.
```c
  DB-1    //stores all allocated keys
  DB-2    //stores unused keys
```

## 5. DB Design
- **Tables in [SQL Database](/System-Design/Concepts/Databases) = 2**
  - *Table-1: Stores URL mappings(long URL to short URL)*
```c
 | Long_Url(512 bytes) | Creation_date | Expiration_date | UserID |
```
  - *Table-2 Stores user’s data who created the short link*
```c
| user_name | user_email | creationDate | lastLogin |
```

- **[Replicas](/System-Design/Concepts/Databases/Database_Scaling):** For safe copy of short to long url
- **[DB Paritioning: Range-Based](/System-Design/Concepts/Databases/Database_Scaling):** To store billions of long URL to short URL mapping, we need distributed DB.

- **Cleaning/Purging of DB:** short-url to long-url mapping should be removed after 30 days or when user tells.

## 6. [Cache](/System-Design/Concepts/Cache/Where_Cache_Can_Be_Placed)
- Frequently asked long-url to short-url mappings would be stored in cache between DB-updater service and DB.
  
## Final Architecture
![Imgur](https://i.ibb.co/rtNRtTd/tiny-url.png)
```
                                        **KGS(Key Generation Service)**
                                        - Generate 68.7 Billion short urls
                                        
                                        short-url > |Hash| > hash between 1-256
                                        //Let's suppose Hash=50, store on DB50
                                        
                                        Store short-url into respective DB using hash
                                        
                                                   ---store short url->   
                                                                        Unused
                                                                        Key-DB1
                                                                        Key-DB2
                                                                        Key-DB3
                                                                        ..
                                                                        Key-DB256

                                                   
        **client        (APP-SERVER(s)  +  cache(s)[Memcached])            KGS
             -long url--->        
                            ----long url->
                                        if mapping is found
                            <--return short url--
                                        else
                                            -----------long url------>
                                                                Map long-url to short-url
                                                                Move short-url to Used-DB
                             <--------------short url------------------          
```

## [Bottleneck & Limitations](/System-Design/Concepts/Bottlenecks_of_Distributed_Systems/Bottlenecks.md)
- **Bottlenecks**
  - *1.* A malicious user can try to consume all URL for a day or month.
    - *Solution:* Each user is only allowed to write/read(redirections) configured limit per day.
  - **2. KGS:** KGS can be point of failure
    - *Solution:* Take [Replicas Servers](/System-Design/Concepts/Databases/Database_Scaling) of KGS, replicas can take over to generate and provide keys.
