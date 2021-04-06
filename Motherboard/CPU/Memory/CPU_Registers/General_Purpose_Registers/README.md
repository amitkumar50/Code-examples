## General Purpose Registers
- **Usage?** Used for logical, arithmetic, address calculations, Temporary storage.

### Types
> RAX, RBX, RCX, RDX, RDI, RSI, RSP, RBP, R8 through R15. 

- **RAX(64 bit)accumulator** can be read as EAX(32 bit), AX(16 bit), AH(8 bit), AL(8 bit). Each register is divided into 16bit, 8bits parts.
  - **Usages:**
    - *a.* Stores intermidiate sum,subtract,divide within the function
    - *b.* Store return values of function. Larger return types like structs are returned using the stack.
- RBX: Memory pointer, base register
- RCX: loop counter
- RDX: Divide & Multiply
- RSI: String instruction source pointer, index register
- RSP(stack pointer): points to head of stack
- RBP(base pointer): points to base of stack
- AVX(Advanced Vector Extensions): 64 byte Registor present in Intel and AMD.

- **edi/rdi, rsi, rdx, rcx, r8, r9:** Stores 1st 6 arguments to function. If there are more than 6 parameters, then the program’s stack is used to pass in additional parameters to the function.
