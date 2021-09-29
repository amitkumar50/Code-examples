**Certificates**
- [Advantages, Disadvantages](#ad)
- [Cert Example](#ex)

<a name=ad></a>
### Advantages, Dis
**Advantages**
- _1._ More secure wrt [Pre shared keys](/Networking/OSI-Layers/Layer-3/Security/AAA_Authentication_Authorization_Accounting/Authentication/Type_Of_Authentication/)
- _2._ More ideal in larger scale environments with numerous peer sites that should not all share a preshared key.
- _3._ Certificate Revocation status can be checked, which's not the case with Pre shared keys.
- _4._ Certificates are not easily vulnerable to visual eavesdropping.

**Disadvantages**
- _1._ certificates can be compromised if access to filesystem on which they are stored is obtained.
- _2._ Complex process wrt psk.
- _3._ Takes more resources wrt psk.

<a name=ex></a>
### Certificate Example
```c
Certificate:
    Data:
        Version: 3 (0x2)                                                            //Version of X.509 standard
        Serial Number: 3 (0x3)    
        Signature Algorithm: sha512WithRSAEncryption     //Digital Signature Algorithm. Algo used by CA to sign cert
        Issuer:                                                                         //CA that Issued the Certificate
            C=ZA,         //country
            ST=Western Cape,     //State
            L=Cape Town,         //Locality
            O=Thawte Consulting cc,         
            OU=Certification Services Division,     //Organization Unit name
            CN=Thawte Server CA/emailAddress=server-certs@thawte.com     //Common Name. FQDN, IP Address.
        Validity
            Not Before: Aug 18 22:15:01 2015 GMT        
            Not After : Aug 17 22:15:01 2016 GMT
        Subject:                                                        //Owner/Requester of Certificate, Person For which Certificate is Issued
                C=US, 
                ST=Maryland, 
                L=Pasadena, 
                O=Brent Baccala, 
                OU=FreeSoft, 
                CN=www.freesoft.org/emailAddress=baccala@freesoft.org
        Subject Public Key Info:
            Public Key Algorithm: rsaEncryption     
                Public-Key: (2048 bit)                                           //Owner's Public Key [modulus + exponent]
                Modulus:                                                             //Public Key Part1
                    00:bc:fb:b6:45:55:ac:18:b7:65:d2:ea:1a:d0:a1:
                    0c:48:82:8b:e3:a3:a8:02:1a:f2:95:5b:3a:06:6c:
                    b3..cb:e2:95:d6:7b:df:c5:eb:bb:56:6a:98:
                    8c:09
                Exponent: 65537 (0x10001)                                //Public Key Part 2
        X509v3 extensions:                                                //Additional Information is related to use/handling of certificates
            X509v3 Subject Alternative Name:
                DNS:vpn.lfg.com
            X509v3 Key Usage: critical
                Digital Signature, Key Encipherment
            X509v3 Authority Key Identifier:
                keyid:F9:D7:3A:BA:EE:79:9A:23:4B:C1:24:A3:A6:89:C7:D5:28:70:E0:84
            X509v3 Subject Key Identifier:
                4D:AD:52:86:BD:16:5C:CC:57:C4:9B:EF:73:F3:E2:6A:84:23:A1:A0
    Signature Algorithm: sha512WithRSAEncryption                //Digital Signature of CA/Issuing Authority
         a6:07:1e:60:42:15:85:ae:7c:71:c4:ec:1b:4e:58:ab:c9:05:
         fb:a3:b0:f3:38:ed:55:d1:b5:61:39:b1:0b:e1:cb:06:64:64:
         f1:2b:33:0a:ea:03:f9:01:b6:96:4c:c0:59:86:8d:e5:37:c0:
         4d:7f:b9:3f:50:1e:dd:51:fc..
```
