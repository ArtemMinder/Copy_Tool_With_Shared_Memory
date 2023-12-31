@echo off
setlocal EnableDelayedExpansion

set fileName=source.txt
set fileSize=100000000
echo Creating %fileName%...

fsutil file createnew %fileName% %fileSize%

echo File creation completed.

type nul > target.txt

set "startTime=%time%"

start..\Debug\Copy_Tool_With_Shared_Memory.exe source.txt target.txt shm
start..\Debug\Copy_Tool_With_Shared_Memory.exe source.txt target.txt shm
set "endTime=%time%"

set "end=!endTime:%time:~8,1%=%%100)*100+1!"  &  set "start=!startTime:%time:~8,1%=%%100)*100+1!"
set /A "elap=((((10!end:%time:~2,1%=%%100)*60+1!%%100)-((((10!start:%time:~2,1%=%%100)*60+1!%%100), elap-=(elap>>31)*24*60*60*100"

set /A speed = (%fileSize%/1000000)/%elap%

set /A "cc=elap%%100+100,elap/=100,ss=elap%%60+100,elap/=60,mm=elap%%60+100,hh=elap/60+100"

echo Start:    %startTime%
echo End:      %endTime%
echo Elapsed:  %hh:~1%%time:~2,1%%mm:~1%%time:~2,1%%ss:~1%%time:~8,1%%cc:~1%
echo Speed: %speed% mb/s

rem del source.txt

pause