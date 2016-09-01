@echo off

pmd c book1 book1.pmd
pmd d book1.pmd book1.unp

fc /b book1 book1.unp

dir book1*

pause
