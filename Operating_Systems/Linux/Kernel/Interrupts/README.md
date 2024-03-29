- [Interrupt](#i)
- [Types](#t)
- [Sources](#sr)
- [ISR / Interrupt Handler](#isr)
  - [mutex or semaphore of spinlock in ISR](#mss)
- [IVT(Interrupt Vector Table) / (IDT) Interrupt Descriptor Table](#ivt)
- [Things CPU does after getting interrupt](#thing)
- [High Number of Interrupts](#high)
- [/proc/interrupts and /proc/stat](/Operating_Systems/Linux/FileSystem/FileSystem_Tree/proc/)
  - How many interrupts have been delivered to each CPU. Total interrupts received on System.


<a name=i></a>
## Interrupt
- Interrupt is event generated by H/W(Eg: clock, keyboard) or S/W which is sent to CPU by Interrupt Controller. CPU is asked to perform some high priority task wrt what its doing.
- Information from interrupt is converted to character and stored in buffer to be later used by ISR. 
#### Interrupt Numbers
```c
256 types of Interrupts(0-255). Examples: 

Interrupt Number     |    Meaning
---------------------|--------------
0                    | Pointer Divide Error
1                    | Pointer single Step
       2             | Pointer Non-maskable
       3             | Pointer I-Byte NIT Instruction
       4             | Pointer Overflow
     5-31            | Reserved for future use
```

#### Interrupt Flow/Hardware Interrupt reaching CPU
- User is watching a movie and presses key on keyboard(hardware device).
- Hardware device/Periheral generates H/W Interrupt sends to [Interrupt Controller-8952 on IR0-IR7 lines](/Motherboard/8952_PIC). IC decides priority of Interrupt and forwards to CPU on [INTR(Interrupt) PIN](/Motherboard/CPU/Microprocessors/8086).
- CPU stops what it is doing and does the [following](#thing).
- Finds [ISR(Interrupt Service Routine/Interrupt Handler)](#isr) from [IVT(Interrupt Vector Table)](IVT), executes ISR. After completing the ISR resumes the task what it was doing.
<img src="./interrupt.jpg" width=1000 />

<a name=t></a>
## Types of Interrupts
### 1. Hardware, Software Interrupt
- **a. Hardware:** Caused by signal from H/W. Examples: Key press on keyboard, mouse movement, timers
- **b. Software:** Originated in software(process in user mode), CPU need to switch to kernel mode. Generated using system calls: 
```c
APIs to make s/w interrupt
open(), socket()
trap() //also used by gdb
abort(): Program error eg: divide by 0, access invalid memory address.

How S/W Interrupt flows?
mov rax,4    ;Store system-call number in rax register
mov rbx,arg1    ;Store arguments of system-call in rbx,rcx,rdx,rsi,rdp registers
mov rcx,arg2
int 0x80        ;Call S/W Interrupt. Just call int function with Interrupt number.    //As int is called Control Reaches IVT, Interrupt Vector table
```        

### 2. Vectored & Non Vectored
- **a. Vectored?** The interrupts which have fixed address location ie ISR to be executed on occurence of Interrupt.
- **b. Non Vectored?** The interrupts which does not have fixed address location for ISR to be executed at occurence

### 3. Maskable & Non Maskable Interrupts
- **a. Maskable?** Interrupt handling can be delayed by CPU for some time. Eg: H/W device generating a interrupt.
- **b. Non Maskable(NMI)?** Interrupts which cannot be ignored by CPU and need to be processed immediately. Eg: Hardware error.

### 4. Precise & Imprecise Interrupts
- **a. Precise?** This interrupt that leaves the machine in a well-defined state. 4 properties of precise interrupts:
    - *1.* The [PC (Program Counter)](/Motherboard/CPU/Memory/CPU_Registers/User_Accessible_Registers) is saved and PC is made to point to new ISR. [PSW](/Motherboard/CPU/Memory/CPU_Registers/User_Accessible_Registers) must not be modified.
    - *2.* All instructions before the one pointed to by the PC have completed.
    - *3.* No instruction beyond the one pointed to by the PC has finished.
    - *4.* The execution state of the instruction pointed to by the PC is known.
- **b. Imprecise?** Interrupts have completed in parts.
    - *Disadvantages of Imprecise Interrupts:*
      - *1.* The code for handling imprecise is exceedingly complex.
      - *2.* Huge stacks are created contaning information of all states.
      - *3.* Slow system, saving a large amount of information to memory on every interrupt makes interrupts slow and recovery even worse.

<img src=precise_imprecise_interrupts.JPG width=500 />

<a name=sr></a>
## Sources of Interrupt
- **1. Hardware / IO Devices:** 8259(PIC) sends interrupt signal on NMI or INTR inupt pins of 8086.
- **2. Software / Special Intruction in Software:** int(interrupt instruction) in program. See above.
- **3. Software / Condition produced in program:** some condition produced in the program by the execution of an instruction. Eg: Divide by 0.  

<a name=isr></a>
## ISR(Interrupt Service Routine) / Interrupt Handler
- ISR is function/process that processes the interrupt. ie this process is executed when interrupt is received. Every device has seperate ISR.
- There is some part of ISR always written in assembly language because:
  - _1. _High-level languages deep low level access to CPU hardware. For Ex
    - ISR is required to enable and disable the interrupt servicing a particular device, or 
    - to manipulate data within a process’ stack area.
  - _2._ Interrupt service routines must execute as rapidly as possible.
- **ISR is divided into two parts**:
  - **1. Top-half or First-Level Interrupt Handler (FLIH):** Executed immediately at occurance of interrupt. Example:
    - Acknowledging interrupt
    - Resetting hardware(if needed)
    - Recording any information ie only available at time of interrupt. 
  - **2. Bottom-half or Second-Level Interrupt Handlers (SLIH):** Non-critical processing is deferred for this.
#### Registering ISR
```c
int request_irq(unsigned int irq,		                      //1
	irqreturn_t (*handler)(int, void *, struct pt_regs *),    //2
	unsigned long flags,                                     //3
	const char *dev_name,	                                 //4
	void *dev_id);                                           //5
            
1. irq=3(Interrupt no): Interrupt number to which this handler should be registered.
2. Interrupts Handler: Implemented as Function pointer, when interrupt happens code jumps to that location
3. Flags:
  SA_INTERRUPT: “fast” interrupt handler: Fast Interrupt executed with interrupts disabled on the current processor
  SA_SHIRQ: shared interrupt
  SA_SAMPLE_RANDOM: generated interrupts can contribute to the entropy pool used by /dev/random and /dev/urandom
4. owner of interrupt  
5. For shared Interrupt line. if interrupt is not shared. dev_id=NULL. But it a good idea anyway to use this item
  to point to the device structure
```

<a name=mss></a>
#### [mutex or semaphore of spinlock](/Threads_Processes_IPC/IPC/synchronization/) in ISR
https://stackoverflow.com/questions/3464700/why-spinlocks-are-used-in-interrupt-handlers

<a name=ivt></a>
## IVT(Interrupt Vector Table) / (IDT) Interrupt Descriptor Table
- Contains ISR(Interrupt service routine)/Handler/Address to which CPU jumps at occurrence of interrupt. Present in 1st 1K of physical memory.
- Starting address of IVT is stored in dedicated register (IDTR). 
- **How its created?** IDT is created when the system initially boots and reflects the specific system configuration.
- IVT is filled using [Probing](#prob).
- Interrupt number is used as index in IVT. CPU goes to IVT's index, gets [Instruction Pointer/Program counter](https://sites.google.com/site/amitinterviewpreparation/c-1/assembly-language) and starts Interrupt service procedure. Once CPU starts ISP, Device Acks Interrupt controller
```c
            | 0x420932 ISR of Int0 |      |     |     |
Interrupt No>       0                 1       2     3

    CPU                    Hardware_Device
       <- Interrupt3=signal-
 Find & runs ISR3 for Intr3
    isr3(){..}
```
<a name=prob></a>
#### Probing
- Finding which Interrupt line Hardware Device is going to use?
- **How?** Device driver tells the Hardware device to generate interrupts and watches the IRQ line and finds which line device is using.
```c
unsigned long probe_irq_on(void);
This function returns a bit maskof unassigned interrupts.
The driver must preserve the returned bit mask, and pass it to probe_irq_off later.
```
- **Other Method?** The interrupt handler can be installed either at driver initialization or when the device is first opened. Installing isr at device initialization causes interrupt line to be occupied even device is not used.

<a name=thing></a>
## Things CPU does after getting interrupt
- CPU is executing a function1() and interrupt occured.
  - *a.* CPU saves: 
    - Contents of stack-frame(Input_parameters, Return_address, Local_variables of function1()) on current process's [STACK](/Threads_Processes_IPC/Processes/).
    - Registers:
      - [PC(Program Counter) = rip(Instruction pointer)](/Motherboard/CPU/Memory/CPU_Registers). Saved IP points to the first instruction which will be loaded into the processor after the interrupt handler completes.
      - [Accumulator(rax), PSW](/Motherboard/CPU/Memory/CPU_Registers) holding Intermidiate results of calculations.
      - [rflags](/Motherboard/CPU/Memory/CPU_Registers/) holding arithematic logical operation results.
  - *b.* Get [ISR](#isr) from [IVT](#ivt), place ISR address into [rip(Instruction pointer)](/Motherboard/CPU/Memory/CPU_Registers). Jumps to ISR.
  - *c.* Create [STACK](/Threads_Processes_IPC/Processes/) for ISR inside kernel(Kernel stack). Copy arguments, local variables from Registers to ISR stack.
```
Q: Why new kernel stack is allocated for ISR?
Ans:
  1. Interrupted user process stack may not have enough space to accomodate ISR's stack.
  2. If kernel uses User space stack for ISR, then after processing ISR kernel will leave data there. User space program/malicious users may use this data to find information about other processes.
```
  - *d.* Perform [Context Switch](/Threads_Processes_IPC/Terms/#cos):
    - Swaps new page in RAM ie changes [MMU, Page Table, TLB](https://sites.google.com/site/amitinterviewpreparation/c-1/memory-management/virtual-memory)
  - *e.* ACK interrupt controller
  - *f.* Finishes ISR routine execution.
  - *g. Resumption:* Means resuming the interrupted task which CPU has left inbetween.
    - iret instruction executed.
      - clear ISR stack.
      - clear [rflags, rip registers](/Motherboard/CPU/Memory/CPU_Registers).
      - Control goes back to interrupted process stack.

<a name=high></a>
## High Number of Interrupts
- Interrupts are a normal way for H/W(device) and CPU to communicate. Interrupts should not take too much of CPU(should be < 5%).
- High CPU usage by System Interrupts means there is issue in hardware driver(ISR) or hardware itself.
- Solutions? 
  - *1.* Check whether you're using recent Driver. 
  - *2.* Disable/remove each indivisual driver and check CPU status to find culprit device.
  - *3.* (if disabling driver did not helped). Check for malfunctioning hardware and try installing it new.
  - *4.* Check disabling all sound effect, check how many interrupts generated now?
  - *5.* Update BIOS, restart.

