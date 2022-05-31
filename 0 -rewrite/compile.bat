REM g++ payload.cpp -o payload

del main.exe /q
python -m nuitka --onefile --windows-onefile-tempdir-spec=%TEMP%\\payload-data --include-data-dir=data=data --windows-uac-admin --windows-disable-console --windows-company-name="phoenixthrush" --windows-file-version=1 .\main.py

rmdir main.build /S /Q
rmdir main.dist /S /Q
rmdir main.onefile-build /S /Q

.\main.exe