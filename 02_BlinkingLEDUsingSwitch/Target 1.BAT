SET PATH=C:\Keil\ARM\ARMCC\bin\;c:\cygwin64\bin;C:\Python312\Scripts\;C:\Python312\;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files\Microsoft SQL Server\Client SDK\ODBC\110\Tools\Binn\;C:\Program Files (x86)\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files\Microsoft SQL Server\120\DTS\Binn\;C:\Program Files (x86)\Microsoft SQL Server\120\Tools\Binn\ManagementStudio\;C:\Program Files (x86)\Microsoft SQL Server\120\DTS\Binn\;C:\Program Files\HP\HP One Agent;C:\Program Files\nodejs\;C:\ProgramData\chocolatey\bin;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files\Git\cmd;C:\TDM-GCC-64\bin;C:\MinGW\bin;C:\Users\KOPPOLU MOUNIKA\AppData\Local\Microsoft\WindowsApps;C:\Users\KOPPOLU MOUNIKA\AppData\Local\Programs\Microsoft VS Code\bin;C:\Users\KOPPOLU MOUNIKA\AppData\Roaming\npm;C:\MinGW\bin;
SET CPU_TYPE=LPC2148
SET CPU_VENDOR=NXP
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x00B71B00
"C:\Keil\ARM\ARMCC\bin\ArmAsm" --Via ".\startup._ia"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\blinking_led_using_switch.__i"
"C:\Keil\ARM\ARMCC\bin\ArmLink" --Via ".\blinking_led_using_switch.lnp"
"C:\Keil\ARM\ARMCC\bin\fromelf.exe" ".\blinking_led_using_switch.axf" --i32combined --output ".\blinking_led_using_switch.hex"
