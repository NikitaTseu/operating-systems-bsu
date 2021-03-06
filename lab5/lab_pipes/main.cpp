#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <string>
#define _CRT_SECURE_NO_WARNINGS


int main()
{
	STARTUPINFO si = { sizeof(si) };
	SECURITY_ATTRIBUTES saProcess, saThread;
	PROCESS_INFORMATION piProcessB, piProcessC;
	TCHAR szPath[200];

	saProcess.nLength = sizeof(saProcess);
	saProcess.lpSecurityDescriptor = NULL;
	saProcess.bInheritHandle = TRUE;

	saThread.nLength = sizeof(saThread);
	saThread.lpSecurityDescriptor = NULL;
	saThread.bInheritHandle = FALSE;

	// process A
	lstrcpy(szPath, TEXT("processA"));

	if (!CreateProcess(NULL, szPath, &saProcess, &saThread, FALSE, 0, NULL, NULL, &si, &piProcessB))
	{
		MessageBox(NULL, TEXT("ProcessA failed!"), TEXT("Error"), MB_OK);
		return 0;
	};

	char pid[100];
	sprintf(pid, "%i", piProcessB.dwProcessId);

	//SetEnvironmentVariable("PID_B", pid))

	HANDLE hWritePipe, hReadPipe;
	SECURITY_ATTRIBUTES saPipe = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };

	BOOL pipe = CreatePipe(&hReadPipe, &hWritePipe, &saPipe, 0);
	if (!pipe)
	{
		MessageBox(NULL, TEXT("Pipe failed"), TEXT("Pipe failed"), MB_OK);
		getchar();
		return 0;
	}

	STARTUPINFO startInfoProcess0;
	ZeroMemory(&startInfoProcess0, sizeof(STARTUPINFO));
	//GetStartupInfo(&startInfoProcess0);
	startInfoProcess0.hStdInput = hReadPipe;
	//startInfoProcess0.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	// startInfoProcess0.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	startInfoProcess0.dwFlags |= STARTF_USESTDHANDLES;

	//SetStdHandle(STD_OUTPUT_HANDLE, hWritePipe);
	DWORD written = 0;
	char msg[256];
	WriteFile(hWritePipe, "test\n", 5, &written, NULL);
	sprintf(msg, "%i", written);
	MessageBox(NULL, TEXT(msg), TEXT("written"), MB_OK);
	std::cout << "test" << written << std::endl;
	std::cout.flush();



	// CREATE ProcessC
	sprintf(szPath, TEXT("C:\\Users\\Nikita\\Desktop\\WSpInheritTerminate\\ProcessC\\Release\\ProcessC.exe PID_B"));

	if (!CreateProcess(NULL, szPath,

		NULL, NULL, //BOTH C's HANDLES are NOT INHERITABLE
		TRUE,// FALSE would mean that C has NOTHING inherit  from A 
			 // TRUE means C inherits B's handle!
		NORMAL_PRIORITY_CLASS | CREATE_SUSPENDED, NULL, NULL, &startInfoProcess0, &piProcessC))
	{
		MessageBox(NULL, TEXT("ProcessC failed"), TEXT("1:ProcessA"), MB_OK);
		return(0);
	};

    return 0;
}

