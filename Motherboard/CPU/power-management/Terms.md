## 2. POWERPLAY
- **What** Set of technologies for the reduction of the energy consumption in AMD's GPUs & APUs supported by graphics device driver "Catalyst".
- **Functions** Reduce energy consumption, lower the noise levels created by the cooling in desktop, mobile devices.
- This succeeds AMD's powertune.

## 3. DPM(Dynamic power management)
- **What?** This is collaboration project between the IBM Austin Research Lab and MontaVista Software. Project aims at making power consumption low by using open source software.
GPU and memory clocks adjust dynamically on load & saves power. This results in very low fan noise and heating.
- **Enabling AMD RADEON DPM in Ubuntu 13.0** Will work for Radeon HD 2000 graphics cards and newer. In Ubuntu 14.0 this may be enabled by default.
```c++
# vim /etc/default/grub
  GRUB_CMDLINE_LINUX_DEFAULT="quiet splash" radeon.dpm=1
# sudo update-grub
# reboot
```

## 4. ACPI(Advanced Configuration and Power Interface)
- **What** 
  - This is a open standard that Operating Systems can use for configuring hardware for least ***power management***.
  - ACPI brings the power management under the control of the operating system, earlier it was controlled by BIOS & platform-specific firmware.
- **How It works** 
  - Putting unused components to sleep
  - Perform status monitoring.
- ACPI replaces ***Advanced Power Management (APM)*** & ***Plug and Play BIOS (PnP) Specification***. 
- **(ACPICA) ACPI Component Architecture**
[Official URL](https://acpica.org/)
  - provides an operating system (OS)-independent reference implementation of the Advanced Configuration and Power Interface Specification (ACPI).
  
## 5. SMU(System Management Unit)
- This is an advanced internal subsystem introduced in 2004 with the iMac G5 and Power Mac G5 series computers.
- **What it does**
  - Power management. Earlier done by PMU(Power managment unit)
  - Cooling functions.
  - keeping audible noise to a minimum
  - OS monitors power consumption and temperature & sends to SMU. The SMU makes the changes, slowing down or speeding up fans as necessary.
- **PMU (Power Management Unit)**

