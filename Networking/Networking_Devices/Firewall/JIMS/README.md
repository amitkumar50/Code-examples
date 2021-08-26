**JIMS / Juniper Identity Management Service**
- [JIMS b/w AD and SRX](#bw)
  - [JIMS Clients](#clients)
- **Queries to JIMS**
  - [IP Query](#ip)
  - [Batch Query](#bq)

## What
JIMS is a Windows Application which sits on layer-5 and between SRX devices and AD or Exchange Servers(in AD). Why?
  - It fetch user information(device,username,groups) from AD, creates a report & provides to SRX or vSRX device.
  - It can Supports upto 250 Domain Controllers, 250k users, 100 SRX devices.
```c
  AD                      JIMS
   -----user,group info-->
                         create report                  SRX_Device
                                <-------- btach query-----
                                      ----report----> 
                                                      Enforce user policies
```

<a name=bw></a>
## JIMS b/w AD and SRX
- _1._ JIMS communicates with Microsoft Domain Controllers or  in AD(Active Directory) domains & collect event log information. 
  - Using the event log information, JIMS determines the IP-addresses(devices) associated with users, stores in cache.
- _2._ JIMS gets group information from AD. ie groups to which user belongs, stored in cache.
- _3._ With IP address(device),username, and group relationship information, JIMS generates a report and sends it to the SRX Series devices. if CSO is present report is sent to that as well.
- _4._ Each SRX Series device receives the report(IP address(device),username,user group relationship information) and generates authentication entries that are used to enforce user-based and group-based security policy control over access to protected corporate resources and the Internet.
<img src=JIMS_SRX.JPG width=700/>
<img src=JIMS.jpg width=700/>

## Queries to JIMS
<a name=ip></a>
#### IP Query
This is a feature to be enabled on SRX device. SRX will send query message(over HTTP/HTTPS) to JIMS to get user information based on IP Address of user's device.
```c
                  JIMS                                          SRX_Device (IP Query enabled)
                    <-- Give user info (IP=x.y.z.g)/HTTP_HTTPS---
                    
/////////SRX///////////
user@host# set services user-identification device-information authentication-source network-access-controller option-1
option-1
  no-ip-query	: Disable IP query. IP query is enabled by default.
  query-delay-time : Time after which the SRX Series device sends the query. Rather than allow the SRX Series device to respond automatically by sending a user query immediately, you can set a query-delay-time parameter, specified in seconds, that allows the SRX Series device to wait for a period of time before sending the query. Default: 15. Range: 0-60 seconds
```
<a name=bq></a>
#### batch query
Get information for group of users.
