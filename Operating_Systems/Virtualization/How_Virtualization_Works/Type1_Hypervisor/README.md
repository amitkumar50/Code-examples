## How Type1 Hypervisor works?
- Lets consider only 1 guest OS is placed over hypervisor.
- **Modes:**
  - Kernel Mode: Hypervisors is present in Actual kernel mode
  - User Mode: Compelte Guest OS is in User mode.
    - Guest OS Kernel mode: is actually a virtual kernel mode. 
    - Guest OS User mode: is actual user mode.
- **[Protection Rings](/Operating_Systems/Linux/Protection_Rings/What_is_Protection_Ring.md):** 
  - Ring 0: Hypervisor = Kernel mode
  - Ring 1: Guest OS Kernel is placed
  - Ring 3: User space of Guest OS
- **Executing system call in Guest OS User space:** Call reaches guest OS kernel mode which trap to the hypervisor. The hypervisor does some sanity checks and then performs the instructions on the guest’s behalf.

<img src=How_Type1_Hypervisor_works.jpg width=1000 />
