## Things CPU does after getting interrupt
- CPU is executing a function1() and interrupt occured.
  - *a.* CPU saves following on current function1()'s [STACK](https://sites.google.com/site/amitinterviewpreparation/c-1):
    - Input_parameters, Return_address, Local_variables of function1()
    - Registers:
      - [PC(Program Counter) = rip(Instruction pointer)](/Motherboard/CPU/Memory/CPU_Registers). Saved IP points to the first instruction which will be loaded into the processor after the interrupt handler completes.
      - [Accumulator(rax), PSW](/Motherboard/CPU/Memory/CPU_Registers) holding Intermidiate results of calculations.
      - [rflags](/Motherboard/CPU/Memory/CPU_Registers/) holding arithematic logical operation results.
  - *b.* Get [ISR(Interrupt service routine)](ISR) from [IVT(Interrupt Vector Table)](IVT), place ISR address into [rip(Instruction pointer)](/Motherboard/CPU/Memory/CPU_Registers). Jumps to ISR.
  - *c.* Create [STACK](https://sites.google.com/site/amitinterviewpreparation/c-1) for interrupt routine. Copy arguments, local variables from Registers to ISR stack.
  - *d.* Perform [Context Switch](https://sites.google.com/site/amitinterviewpreparation/c-1/max-threads-opened-by-webserver):
    - Swaps new page in RAM ie changes [MMU, Page Table, TLB](https://sites.google.com/site/amitinterviewpreparation/c-1/memory-management/virtual-memory)
  - *e.* ACK interrupt controller
  - *f.* Finishes ISR routine execution.
  - *g. Resumption:* Means resuming the interrupted task which CPU has left inbetween.
    - iret instruction executed.
      - clear ISR stack.
      - clear [rflags, rip registers](/Motherboard/CPU/Memory/CPU_Registers).
      - Control goes back to interrupted process stack.
