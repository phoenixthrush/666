@echo off

mode con: cols=100 lines=20
if not exist lock (echo > lock) else (
	echo instance running already!
	echo.
	echo.
	echo	            _,'^|             _.-''``-...___..--'^;^)
	echo           /_ \'.      __..-' ,      ,--...--'''
	echo          ^<\    .`--'''       `     /'
	echo           `-';'               ;   ; ;
	echo     __...--''     ___...--_..'  .;.'
	echo    ^(,__....----'''       ^(,..--''

	timeout 5 >nul 
	exit
)

SETLOCAL EnableDelayedExpansion
for /F "tokens=1,2 delims=#" %%a in ('"prompt #$H#$E# & echo on & for %%b in (1) do rem"') do (set "DEL=%%a")

call :colorEcho 0C "[Info] Tool made by 'Phoenixthrush UwU'" && echo. && echo.

if not exist .\dist (mkdir dist)
if not exist .\tools (mkdir tools)
del .\dist\*.* /q

if not exist .\tools\7z2107-extra (
	call :colorEcho 0A "[Info] downloading the 7z package" && echo.
	powershell -Command "Invoke-WebRequest https://github.com/phoenixthrush/7z2107-extra/releases/download/21.07/7z2107-extra.zip -OutFile .\tools\7z2107-extra.zip"	
	call :colorEcho 0A "[Info] extracting the 7z package" && echo.
	powershell -Command "Expand-Archive -Path .\tools\7z2107-extra.zip -DestinationPath .\tools" && echo.
	del .\tools\7z2107-extra.zip /q
)

if not exist .\tools\mingw64 (
	call :colorEcho 0A "[Info] downloading the mingw64 package" && echo.
	powershell -Command "Invoke-WebRequest https://github.com/phoenixthrush/winlibs_mingw/releases/download/12.1.0-14.0.4-10.0.0-ucrt-r2/winlibs-x86_64-posix-seh-gcc-12.1.0-mingw-w64ucrt-10.0.0-r2.7z -OutFile .\tools\mingw64.7z"	
	call :colorEcho 0A "[Info] extracting the mingw64 package" && echo. && echo.
	cd .\tools && .\7z2107-extra\7za.exe x mingw64.7z >nul && cd ..
	del .\tools\mingw64.7z /q
)

if not exist .\tools\upx-3.96-win64 (
	call :colorEcho 0A "[Info] downloading the upx package" && echo.
	powershell -Command "Invoke-WebRequest https://github.com/phoenixthrush/upx/releases/download/v3.96/upx-3.96-win64.zip -OutFile .\tools\upx-3.96-win64.zip"	
	call :colorEcho 0A "[Info] extracting the upx package" && echo.
	powershell -Command "Expand-Archive -Path .\tools\upx-3.96-win64.zip -DestinationPath .\tools\upx-3.96-win64" && echo.
	del .\tools\upx-3.96-win64.zip /q
)

call :colorEcho 0B "[Info] compiling executable "
call :colorEcho 0F " (666.exe)" && echo.
cd ./source
..\tools\mingw64\bin\windres.exe 666.rc 666.o
..\tools\mingw64\bin\gcc -O3 -Os -s -o 666.exe 666.c 666.o
..\tools\upx-3.96-win64\upx.exe 666.exe >nul
del 666.o
move 666.exe ..\dist >nul
cd ..
del lock /q

echo.
call :colorEcho 0D "[Info] finished!" && echo.
call :colorEcho 0D "[Info] exiting in 3 seconds!" && echo.
timeout 3 >nul
exit

:colorEcho
@echo off
< nul set /p ".=%DEL%" > "%~2"
findstr /v /a:%1 /R "^$" "%~2" nul
del "%~2" > nul 2>&1
