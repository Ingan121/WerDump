# WerDump
* Forked from [Lsass_Shtinkering](https://github.com/deepinstinct/Lsass-Shtinkering)
<br><br>
* Dump or suspend *some* protected processes by abusing the Windows Error Reporting service.
* It sends a message to the service with the ALPC protocol to report an exception on a specified process.
* This report will cause the service to dump the process's memory.
<br><br>
* Somehow this can kill MS Defender processes (MsMpEng, MpDefenderCoreService, and NisSrv) plus SgrmBroker.
* Does nothing on some other PPL-protected processes. Tested with AhnLab V3 Lite, Kaspersky Free, and PPL-protected Notepad launched with [KDU](https://github.com/hfiref0x/KDU), LSASS, and CSRSS.
<br><br>
* Also does some random behavior if the target process is protected by a kernel-mode driver. For example, WerFault may fail to dump the process and keep it suspended for a long time.
* This suspension is not permanent. WerFault will give it up and resume the process after some time passes.
* Suspending only works on **some** processes with nonstandard kernel-mode protections. Doesn't work on standard PPL protected processes.
* You can dump these suspended protected processes by dumping the newly created child process into the target process instead.

## MSFT Response
```
Currently, MSRC prioritizes vulnerabilities that are assessed as “Important” or “Critical’ severities for immediate servicing.

 
You have reported the capability to cause certain PPL processes to crash, which necessitates SYSTEM level privileges.

This does not constitute a security boundary, as possessing SYSTEM level privileges inherently provides numerous methods to achieve this outcome.

After careful investigation, this case has been assessed as not a vulnerability and does not meet MSRC’s bar for immediate servicing.
```
`¯\_(ツ)_/¯`
* Is it patched now? I don't know. At least it still works on my Win10 22H2 (10.0.19045.5131) machine.

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
