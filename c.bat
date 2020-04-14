@echo off

del *.exe

set ICLCFG=icl64.cfg
set icl=C:\IntelJ2190\bin-intel64\icl2d.bat 

call %icl% pmd.cpp

del *.obj
