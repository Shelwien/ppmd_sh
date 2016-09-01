@echo off

pmd c ..\book1 1
pmd d 1 2 

:ppmd /r0 ..\book1 1
:ppmd /d 1 2 

md5sum 2 ../book1
