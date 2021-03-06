## RSA (Ronald Rivest, Adi Shamir, Len Adleman)
### Steps of RSA
- **A. Pre-calculate Public, pvt key**
  - *1.* Choose 2 numbers p(1024 bit),q(1024 bit).  {p=3,q=11}
  - *2.* Find n = p`*`q, z =(p-1)(q-1)  {n=33, z=20}
  - *3.* Choose a number d relatively prime to z.   {d=7} //7 and 20 has no common factor
  - *4.* Find e. So that e × d = 1 mod(z)
  ```c
    e x 7 = 1 mod(20)
    e = mod(20)/7 = 3 (approx)
  ```
  - Public Key = (e,n)
  - Private Key = (d,n)
  
- **B. Divide Plain-text into blocks**  input=10101111. {block1=1010 block2=1111}

- **C. Encrypt**
  - cipher text(C) = Block-of-plain-text<sup>e</sup> (mod n) 
```c
  C = P^3 mod(33)
```
  
- **D. Decrypt**
  - Plain text(P) = C<sup>d</sup> (mod n)
```c
  P = C^7 mod(33)
```

### Other Example
```c
Public Key (n,  e)        Private Key (n, d) or 5-value
                Host-A                                                  Host-B
                        -----Prime-1=53, Prime-2=59------>    //In real calculations P & Q are large numbers (64 bytes)
                                                                   Modulus(n)=P*Q=64x64=128 bytes=1024 bit
                                                                   Phy(n)=(P-1)(Q-1)=3016
                                                                   Exponent(e)=coprime of Phy
            Public-key calculated                    Public-key= n&e
                                                                   Pvt key=2 (Phy(n) + 1)/e
           
                                                                    encryption of data: data pow(e)mod(n)
                        <---cipher-text------             89 pow(3)mod(3127)    //if data=89
        Decryption of data
        (cipher Text)pow(Pvt Key) mod(n) 
           (1394) pow(2011) mod(3127) = 89
```           
