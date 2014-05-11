<html>
<body>
<pre>
<h1>Build Log</h1>
<h3>
--------------------Configuration: EgumaWinCE - Win32 (WCE x86) Debug--------------------
</h3>
<h3>Command Lines</h3>
Creating temporary file "C:\Users\ADMINI~1\AppData\Local\Temp\2\RSPD573.tmp" with contents
[
commctrl.lib coredll.lib corelibc.lib   /nologo /base:"0x00100000" /stack:0x10000,0x1000 /entry:"_DllMainCRTStartup" /dll /incremental:yes /pdb:"X86Dbg/Eguma.pdb" /debug /nodefaultlib:"OLDNAMES.lib" /nodefaultlib:libc.lib /nodefaultlib:libcd.lib /nodefaultlib:libcmt.lib /nodefaultlib:libcmtd.lib /nodefaultlib:msvcrt.lib /nodefaultlib:msvcrtd.lib /out:"X86Dbg/Eguma.dll" /implib:"X86Dbg/Eguma.lib" /subsystem:windowsce,4.00 /MACHINE:IX86   
.\X86Dbg\StdAfx.obj
.\X86Dbg\EgumaWinCE.obj
]
Creating command line "link.exe @C:\Users\ADMINI~1\AppData\Local\Temp\2\RSPD573.tmp"
<h3>Output Window</h3>
Linking...
   Creating library X86Dbg/Eguma.lib and object X86Dbg/Eguma.exp
Creating temporary file "C:\Users\ADMINI~1\AppData\Local\Temp\2\RSPD787.bat" with contents
[
@echo off
xcopy D:\Projects\EgumaWinCE\X86Dbg\Eguma.dll D:\Projects\EgumaWinCE\EgumaWinCETester\bin\Debug\Eguma.dll /Y
]
Creating command line "C:\Users\ADMINI~1\AppData\Local\Temp\2\RSPD787.bat"

Does D:\Projects\EgumaWinCE\EgumaWinCETester\bin\Debug\Eguma.dll specify a file name
or directory name on the target
(F = file, D = directory)? ?
Does D:\Projects\EgumaWinCE\EgumaWinCETester\bin\Debug\Eguma.dll specify a file name
or directory name on the target
(F = file, D = directory)? 
Error executing c:\windows\system32\cmd.exe.



<h3>Results</h3>
Eguma.dll - 1 error(s), 0 warning(s)
</pre>
</body>
</html>
