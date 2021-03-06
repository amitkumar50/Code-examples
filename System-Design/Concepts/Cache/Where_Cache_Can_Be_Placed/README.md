## Places to Place cache

### [1. HTTP Cache](/Networking/OSI-Layers/Layer5/Protocols/HTTP/HTTP_Caching/README.md)

### 2. Web Browser Cache
- **What?** Browser stores local copies of web resources for faster retrieval the next time the resource is required.
 - Eg: Once browser downloads CSS, JS files, images (for a session) there is no need again to download from same server and can be cached.
<img src="https://i.ibb.co/svd6H2Z/werb-browser-cache.png" width="600" />

- **CACHE-CONTROL HEADER** HTTP server instructs browser(http client) to cache a particular content for TTL duration in cache control header. Format: Response Header {cache-control: public, max-age: 45223}

<img src="https://www.imperva.com/learn/wp-content/uploads/sites/13/2019/01/response-headers.jpg.webp" width="600" />

### 3. Web Proxy Cache
- *1.* Web client asks content from Web-server. Request reaches Web proxy. Web proxy checks its cache, if content available serves it
- *2.* If content is not available Web Proxy checks from other web proxies over **high-speed** link.
<img src="https://i.ibb.co/Kz5Nsx2/distributed-webproxy-cache.png" width="600" />

### 4. [Application Server](https://github.com/amitkumar50/Code-examples/blob/master/networking/OSI-Layers/Layer5/ApplicationServer_WebServer.md) and DB
#### 1. Memcached 
- **What** 
  - Distributed Hash-Table ie <key,value> across multiple nodes.
  - Implemented as LRU.
  - Sits on separate machine b/w Application server and DB. Multiple servers work in conjunction to act as single larger logical data cache. 
 - **Stores** User sessions, User profile, some historical data etc.
```
          WebServer   App-server/DB-Client     DB-frontEnd          MEMCACHED         DB
                                  ---query table1--->    ---table1---->
                                                         <--NULL------
                                                  --------query table1------------>
                                                <-table1-    table1|expiry-time ------
```
 - **Redis**
