gcc src/loader.c -o dist/main
upx dist/main.exe

timeout 3 >nul