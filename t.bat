@echo off

del 1 2 1w 2w

pmd.exe c ..\book1 1
pmd.exe d 1 2

for %%a in (1,2) do (
  echo %%a - %%~za
)

md5sum ../book1 2

del 1 2 1w 2w
