- **Containers**
  - [Adv, Disadv of containers](#add)
  - [Container vs VM](#vs)
  - [Issues without containers](#isc)



## Containers
- Isolated(Isolation is achieved using kernel namespace, [cgroups](/Operating_Systems/Linux/Resource_Control)) processes running on single host. Isolated from other processes.
- Only 1 Application can run inside container and all its dependent libraries. Each container has its own: Network interface, IP address, file system, All containers share the kernel of the host.
- **Containerization** Packaging software code and all its dependencies in a bundle.

<img src=TraditionalOS_vs_Containers.jpg width=400 />

<a name=add></a>
#### Advantages
- *1. lightweight* Use less memory:* Simple web application running inside container takes 100MB space.
- *2. Secure:* Reduces the chance that malicious code present in one container impacting other containers or invade the host system.
- *3. Portable:* abstraction from the host operating system makes containerized applications portable ie able to run on any OS,VM.
#### Disadvantages 
Some application may not be suited for a containerized environment. Ex: applications accessing low-level hardware information.

<a name=vs></a>
#### Container vs VM
```c
                 Container   |     VM
-----------|-----------------|--------------------  
size       |    smaller      | Bigger wrt container
capability |    smaller      | big
What       | Pacakaged s/w   | Copy of OS 
```

<a name=isc></a>
#### Issues without containers
- When an company develops an S/W-Application, its tightly coupled with Libraries provided by particular OS Version. 
- If OS update happens, libraries would get updated and Application may break, as it depends on particular OS version libraries.

