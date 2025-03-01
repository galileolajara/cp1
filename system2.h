#ifdef _WIN32
#include <windows.h>
int system2(char* cmd) {
   STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Change this to any executable you want to run
    // LPCSTR application = "notepad.exe";

    // Create the process
    if (!CreateProcess(
            NULL,              // Application name (NULL means command line contains it)
            cmd, // Command line
            NULL,              // Process handle not inheritable
            NULL,              // Thread handle not inheritable
            FALSE,             // Set handle inheritance to FALSE
            0,                 // No creation flags
            NULL,              // Use parent's environment block
            NULL,              // Use parent's starting directory
            &si,               // Pointer to STARTUPINFO
            &pi)               // Pointer to PROCESS_INFORMATION
    ) {
        printf("Failed to create process. Error: %lu\n", GetLastError());
        return 1;
    }

    // printf("Process created with PID: %lu\n", pi.dwProcessId);

    // Wait for the child process to exit
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Get exit code of the process
    DWORD exitCode;
    if (GetExitCodeProcess(pi.hProcess, &exitCode)) {
        // printf("Process exited with code: %lu\n", exitCode);
    } else {
       exitCode = 1;
        printf("Failed to get exit code. Error: %lu\n", GetLastError());
    }

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return exitCode;
}
#else
int system2(char* cmd) {
   return system(cmd);
}
#endif
