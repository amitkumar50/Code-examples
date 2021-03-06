```diff
- Only Read Modern-Operating-System-Tanenbaum.pdf because internet is Garbage
```
# Virtual Memory & Physical Memory

# A. Understating Virtual Memory on 16 bit System
- 16 Bit System means Bus Size=16 Bit. 16 bit=2 byte bus can access 2 bytes from (216 = 65535 = 64KB) memory. To address 65536 17 bits are needed.
- On 16 bit system you can plug huge Hard disk but that will be no use, since in 1 go Only 2 bytes can be accessed.

### A1. Conversion of Virtual to Physical Address  (16 Bit system)
> Consider a 16 bit system having following.

||Virtual Memory/Hard Disk|Physical Memory/RAM|
|---|---|---|
|Size|64KB|32KB|
|Count|64k/4k = 16 Pages|32k/4k = 8 Frames|

- Page Size = 4KB = 4`*`1024 = 4096 Bytes. In Real systems Page sizes might be as large as 64KB.
![ImgURL](https://i.ibb.co/pbTrjFn/virtual-physical.png)

- **Ex1. MOV REG 0**
  - Program tries to access virtual address 0. Virtual address is sent to MMU for translation. 
```c++
Code-Segment    
  MOV REG 0 ----> CPU
                   --Get Physical Address for 0--> MMU
                   <--Physical Address 8192-  Page-0 maps to Frame-2
//MMU has mapped all virtual addresses between 0-4095 onto physical addresses 8192-12287.                   
```                   
- **Ex2. MOV REG 8192**
```c++
Code-Segment    
  MOV REG 8192 -> CPU
                   --Get Physical Address for 8192-->       MMU
                   <--Physical Add (24k=24x1024=24576)-- Page-3 maps to Frame-6
```
- **Ex3. MOV REG 20500**
  - 1stPage(0-4095), 2nd(4096-8191), 3rd(8192-12281), 4th(12282-16383), 5th(16384-20479), 6th(20480-24576)
  - 20500 falls 20 byte inside 6th Page.
```c++
Code-Segment    
  MOV REG 20500 -> CPU
                    -Get Physical Address for 20500-->       MMU
                                                        Page-6 maps to Frame3
                    <--Physical Add 12302---- Frame-3-start:12282. PhysicalAdd=12282+20=12302
```
- **Ex4. MOV REG 24576** Request to reference a unmapped address(ie MMU does not have mapping).
  - **Page Fault**? CPU issues trap() system call. OS picks a LRU Frame(from Physical Memory/RAM) and moves/writes back to the Hard-Disk/Virtual-Memory. Then copies Page into RAM. MMU updates mapping.
  - **Page Eviction:** Movement of pages in/out of RAM is done by SWAPPER.
```c++
Code-Segment
  MOV REG 24576 ---> CPU
                      --Return PhyAdd for 24576-> MMU
                      <---Not present--------------
                    trap() --Map 24576------------>
                                                      RAM(PM)                             Hard-Disk(VM)
                                                        --Frame=0 moved to VM-------------->
                                                        <-Page 24576 loaded in RAM(at address 0)--
                                            MMU(Updates Mapping)
                                            Page(12K not mapped)  
                                            Page-24K maps to Frame0
                      <---Virtual Address 0----
```

### A2. 16 bit system = Page-No(4 bits) + Offset(12 bits)
**32 bit system**:    Page-No(20 bits) + Offset(12 bits)    //anywhere offset is always 12 bit

- To access every bit of 64 kilibytes memory, we would need 16 bits. 2<sup>16</sup> = 65535 = 64KB
- 1 page=4KB=4096 bytes. 64x1024/4x1024 = 16 Pages. 64KB will have 16 pages.
- 2<sup>4</sup> = 16. With 4 bits we can access every 16 page.
- 2<sup>12</sup> = 4096. With 12 bits we can access every bit in page.
- **How Physical Address is converted to Virtual Address?**
  - Offset(12 bits) are copied as such. From Page-No(4 bit), frame number is constructed.
  
![ImgURL](https://i.ibb.co/86bzCf4/MMU-opearation.png)   

### A3. Page Table/Virtual Table Entry

| |caching disabled(1 bit)|referenced(1 bit)|modified(1 bit)|protection(1 bit)|present/absent(1 bit)|Page Frame number|
|---|---|---|---|---|---|---|

- **Present/Absent bit** 1 means page is present in RAM, 0 means page absent in RAM. Accessing page with this bit=0 causes page fault.
- **Protection bit** 1=RW, 0=RO
- **Modified bit** 1=means page is written in RAM ie dirty page
- **Referenced bit** 1=means page is referenced either by reading or writing
- **Caching Disabled** 1=means disable caching for the page.

# MOVING TO 32 and 64 BIT SYSTEM
- 32 bit system. Bus size=32 bit. At a time 32 bits can be sent. Maximum address that can be reached  using 32 bit(2<sup>32</sup> = 4,294,967,296). 
- 64 bit system. Bus size=64 bit. At a time 64 bits can be sent. Maximum address that can be reached  using 64 bit (2<sup>64</sup> = 18x1018). 18 Exa bytes
- **Problem with 32 & 64 bit =Huge Virtual Page Table**: 32 bit (4294967296/4096 = 1 Million Page entries in Virtual Page Table). 64 bit huge
## Solution-1 TLB (Translation Lookaside Buffer) 
- Practically from complete PT only a small fraction of the page table entries are heavily read; the rest are barely used. 
- This is hardware inside MMU which stores only few entries(8-256) for Virtual-to-Physical mapping. 
- TLB Example: Request for Virtual Page comes to TLB 
  - if  TLB entry found-> TLB Hit 
  - else TLB miss(goes to Page Table), find entry updates Page Table. restarts trap instruction.

|Valid|Virtual Page No|Modified|Protection|Frame No|
|---|---|---|---|---|
|1|140|1|RW|31|

### Problem with TLB: 
- TLB being small, if it happens process tries to get unused page every time, there will be lot of TLB misses
- Solution: Software to maintain a cache internally.

## Solution-2 (Multilevel Page Tables) 32 Bit system
- 32 bit system (232 = 4,294,967,296) can support up to 4GB RAM/Physical Memory. 4294967296/4096 bytes = 1,048,576 Pages.
- 32 bit address = 10 Bit(Page-Table-1) + 10 Bit(Page-Table-2) + 12 Bit(offset). 
    - Page-Table-1 contains 1024 entries. Each entry can be reached using 10 bits. 210 = 1024. Each entry points to 4MB Memory chunk.
    - Page-Table-2 contains 1024 entries. 4MB = 4x1024x1024. 4MB/1024 = 4096 Bytes = 1 Page Size
![ImgURL](multilevel-page-table.PNG)
