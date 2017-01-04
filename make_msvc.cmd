@echo off
REM This code requires C99 standard which is not supported in MSVC
REM until the very recent version, so we compile as C++ as workaround.

REM You should run this script from MSVC command prompt.
REM Otherwise you should set these first:
REM set PATH=[msvc]\bin;%PATH%
REM set INCLUDE=[msvc]\include
REM set LIB=[msvc]\lib

set linkFlag= -out:Interface_in_C_msvc.exe -nologo

REM If possible, generate smaller exe.
link | find "NOWIN98" && (
set linkFlag=%linkFlag% -opt:nowin98
)

cl Program.c Setter.c -MD -TP -link %linkFlag%
pause
exit/b
