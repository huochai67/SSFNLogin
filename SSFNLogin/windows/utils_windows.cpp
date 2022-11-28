#include <filesystem>

#include <Windows.h>
#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>

#include "../utils.h"

void ssfnlogin::utils::launchProgram(const char* program_path, char* arg, const char* launch_path)
{
    ShellExecute(NULL, "open", program_path, arg, launch_path, SW_SHOWDEFAULT);
}

void ssfnlogin::utils::killProcessByName(const char* filename)
{
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
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