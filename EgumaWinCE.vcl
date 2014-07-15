<html>
<body>
<pre>
<h1>Build Log</h1>
<h3>
--------------------Configuration: EgumaWinCE - Win32 (WCE x86) Debug--------------------
</h3>
<h3>Command Lines</h3>
Creating temporary file "C:\Users\ADMINI~1\AppData\Local\Temp\2\RSP765.tmp" with contents
[
/nologo /W3 /Zi /Od /D "DEBUG" /D _WIN32_WCE=400 /D "WCE_PLATFORM_STANDARDSDK" /D "_i386_" /D UNDER_CE=400 /D "UNICODE" /D "_UNICODE" /D "_X86_" /D "x86" /D "EGUMAWINCE_EXPORTS" /Fp"X86Dbg/EgumaWinCE.pch" /Yu"stdafx.h" /Fo"X86Dbg/" /Fd"X86Dbg/" /Gs8192 /GF /c 
"D:\Projects\EgumaWinCE\EgumaWinCE.cpp"
]
Creating command line "cl.exe @C:\Users\ADMINI~1\AppData\Local\Temp\2\RSP765.tmp" 
Creating temporary file "C:\Users\ADMINI~1\AppData\Local\Temp\2\RSP766.tmp" with contents
[
commctrl.lib coredll.lib corelibc.lib /nologo /base:"0x00100000" /stack:0x10000,0x1000 /entry:"_DllMainCRTStartup" /dll /incremental:yes /pdb:"X86Dbg/Eguma.pdb" /debug /nodefaultlib:"OLDNAMES.lib" /nodefaultlib:libc.lib /nodefaultlib:libcd.lib /nodefaultlib:libcmt.lib /nodefaultlib:libcmtd.lib /nodefaultlib:msvcrt.lib /nodefaultlib:msvcrtd.lib /out:"X86Dbg/Eguma.dll" /implib:"X86Dbg/Eguma.lib" /subsystem:windowsce,4.00 /MACHINE:IX86 
.\X86Dbg\EgumaWinCE.obj
.\X86Dbg\StdAfx.obj
.\X86Dbg\version.res
]
Creating command line "link.exe @C:\Users\ADMINI~1\AppData\Local\Temp\2\RSP766.tmp"
<h3>Output Window</h3>
Compiling...
EgumaWinCE.cpp
C:\Program Files (x86)\Windows CE Tools\wce400\STANDARDSDK\Include\x86\xstring(724) : warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify -GX
        C:\Program Files (x86)\Windows CE Tools\wce400\STANDARDSDK\Include\x86\xstring(720) : while compiling class-template member function 'void __thiscall std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >::_Copy(unsigned int)'
Linking...
Creating temporary file "C:\Users\ADMINI~1\AppData\Local\Temp\2\RSP9B7.bat" with contents
[
@echo off
xcopy D:\Projects\EgumaWinCE\X86Dbg\Eguma.dll D:\Projects\EgumaWinCE\EgumaWinCETester\bin\Debug\Eguma.dll /Y
]
Creating command line "C:\Users\ADMINI~1\AppData\Local\Temp\2\RSP9B7.bat"

D:\Projects\EgumaWinCE\X86Dbg\Eguma.dll
1 File(s) copied



<h3>Results</h3>
Eguma.dll - 0 error(s), 1 warning(s)
</pre>
</body>
</html>
