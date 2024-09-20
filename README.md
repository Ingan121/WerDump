# WerDump
* Forked from [Lsass_Shtinkering](https://github.com/deepinstinct/Lsass-Shtinkering)
<br><br>
* Dump or suspend any* protected processes by abusing the Windows Error Reporting service.
* It sends a message to the service with the ALPC protocol to report an exception on a specified process.
* This report will cause the service to dump the memory of the process.
* If the target process is protected by a kernel-mode driver, the service will fail to dump the process and keep it suspended.
* The suspension is not permanent. WerFault will give it up and resume the process after some time passes.
* You can dump the protected process by dumping the newly created child process into the target process instead.
* Suspending only works on nonstandard kernel-mode protections. Doesn't work on standard PPL protected processes.
<br><br>
* Somehow this is capable of killing MS Defender processes (MsMpEng, MpDefenderCoreService, and NisSrv) plus SgrmBroker. I just discovered this while writing this readme. Weirdly they just die as soon as WerFaultSecure finishes its job.
* Does nothing on other PPL-protected antiviruses. Tested with AhnLab V3 Lite and Kaspersky Free. Maybe because they use both PPL and their own kernel-mode protections.

## Prerequisites
The registry value "DumpType" under "HKLM\SOFTWARE\Microsoft\Windows\Windows Error Reporting\LocalDumps" should be set to 2.

## Usage
```
WerDump.exe <PID>
```
The process must be running as SYSTEM.<br>
Use PsExec, gsudo, or something similar to run as SYSTEM.

## Credits

* [deepinstinct](https://github.com/deepinstinct)
* [Asaf Gilboa](https://twitter.com/asaf_gilboa)

## References
- https://media.defcon.org/DEF%20CON%2030/DEF%20CON%2030%20presentations/Asaf%20Gilboa%20-%20LSASS%20Shtinkering%20Abusing%20Windows%20Error%20Reporting%20to%20Dump%20LSASS.pdf
