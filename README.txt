DEVELOPMENT - PHOENIXTHRUSH UWU - 06/2022

-----------------------------------------------------------------------------------------------------------------------

- Folder Structure

.
├── main.c
├── Makefile
├── build 
│   ├── .empty  
│   └── ...
├── boot-loader // future
│   ├── .empty  
│   └── ... 
├── source
│   ├── defence.c
│   ├── payloads.c
│   ├── payloads.h
│   ├── permisson.c
│   ├── permisson.h
│   ├── prepare.c
│   ├── prepare.h
│   ├── stage.c
│   ├── stage.h
│   └── ... 
└── ...

-----------------------------------------------------------------------------------------------------------------------

- Code Structure

666 - Core
--> main.c
    --> Calling Defense
    --> Calling Permisson Detached
    --> Calling Stage-Check
    --> Calling Prepare/ Payload Section (decide by return value of Stage-Check) with Stage-Check return value
--> defence.c
    --> Tries not to get debugged
--> permisson.c
    --> Admin Check --> if not admin, goto bypass section else back to main.c
    --> ByPass via Fodhelper and Powershell
    --> UAC Prompting if not successful 
--> stage.c
    --> Checking if Stage-File Exists --> if not, goto First-Run section else back to main.c
--> prepare.c
    --> Creating Directory inside "C:\Windows\SysWOW64\Tasks\Microsoft\Windows\PLA\System"
    --> Hiding Directory (System + Hidden)
    --> Moving Itself
    --> Creating autorun after reboot via "schtask.exe"
--> payloads.c
    --> Executing current stage

-----------------------------------------------------------------------------------------------------------------------

Working with Makefile to build the project