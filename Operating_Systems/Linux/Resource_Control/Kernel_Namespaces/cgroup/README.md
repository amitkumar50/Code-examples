## Cgroups / Control Groups
- **What?** 
  - Group of 1 or more processes whose CPU, memory, disk I/O and network's usage can monitored and controlled. 
  - Limitations on memory,CPU,IO are applied on cgroups. This way, it is possible to set limits on resources consumed by the service during its runtime.
  - Example:
    - cgroup1 has 4 processes(p1,p2,p3,p4), cgroup2 has 2 processes(p5,p6). We can limit cgroup1 to use Max 20% of RAM and cgroup2 to use max 60%. if p1 uses 21% of RAM, it will be killed by OOM(Out of Memory) killer.

- **Methods of Achieving cgroups?**
  - **1. RHEL provided cgroups**
  - **2. Working directly with cgroups on kernel**
