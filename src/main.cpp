#include "send-presence.h"
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

HMODULE self_module;
HANDLE main_thread;
std::string status;

bool IsProcessRunning(const TCHAR* const executableName) {
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (!Process32First(snapshot, &entry)) {
        CloseHandle(snapshot);
        return false;
    }

    do {
        if (!_tcsicmp(entry.szExeFile, executableName)) {
            CloseHandle(snapshot);
            return true;
        }
    } while (Process32Next(snapshot, &entry));

    CloseHandle(snapshot);
    return false;
}
int main(){
    discordInit();
    status = "";
    while (true) {
        int64_t start_time;
        std::string status_temp;
        if (IsProcessRunning("worms2.exe")) {
            status_temp = "Playing a game";
        }
        else {
            status_temp = "In menus";
        }
        if (status_temp != status) {
            status = status_temp;
            if (status == "Playing a game") {
                start_time = time(0);
            }
            else {
                start_time = NULL;
            }
            updateDiscordPresence(start_time, NULL, status.c_str(), "cover", "", NULL, NULL);
        }
        Sleep(1000);
    }
    return 0;
}

bool APIENTRY DllMain(HINSTANCE hDLLInst, DWORD fdwReason, LPVOID lpvReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH && main_thread == NULL) {
		self_module = hDLLInst;
		main_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)main, NULL, 0, NULL);
		if (main_thread == NULL) {
			return false;
		}
	}
	if (fdwReason == DLL_PROCESS_DETACH && main_thread != NULL){
		TerminateThread(main_thread, 0);
	}
	return true;
}
