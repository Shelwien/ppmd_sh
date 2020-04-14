@echo off

set incs=-DNDEBUG -DSTRICT 

set opts=-fstrict-aliasing -fomit-frame-pointer -ffast-math -fpermissive -fno-exceptions -fno-rtti -fno-stack-protector -fno-stack-check -fno-check-new -fpermissive

set gcc=C:\MinGW820x\bin\g++.exe -march=skylake
set path=%gcc%\..\

del *.exe

%gcc% -std=gnu++11 -O9 -s %incs% %opts% -static pmd.cpp -o pmd.exe

del *.o
                                                                          