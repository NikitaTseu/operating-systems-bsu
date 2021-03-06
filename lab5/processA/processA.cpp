#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <string>
#define _CRT_SECURE_NO_WARNINGS

int main()
{
	// creating pipe
	HANDLE hWritePipe, hReadPipe;
	SECURITY_ATTRIBUTES saPipe = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };

	BOOL pipe = CreatePipe(&hReadPipe, &hWritePipe, &saPipe, 0);
	if (!pipe)
	{
		MessageBox(NULL, TEXT("Pipe failed"), TEXT("Pipe failed"), MB_OK);
		getchar();
		return 0;
	}


	// spawning process B
	STARTUPINFO siProcessB = { sizeof(siProcessB) };
	GetStartupInfo(&siProcessB);
	siProcessB.hStdOutput = hWritePipe;
	siProcessB.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	siProcessB.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	//siProcessB.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	siProcessB.dwFlags |= STARTF_USESTDHANDLES;

	SECURITY_ATTRIBUTES saProcess, saThread;
	PROCESS_INFORMATION piProcessB;
	TCHAR szPathB[200];

	saProcess.nLength = sizeof(saProcess);
	saProcess.lpSecurityDescriptor = NULL;
	saProcess.bInheritHandle = TRUE;

	saThread.nLength = sizeof(saThread);
	saThread.lpSecurityDescriptor = NULL;
	saThread.bInheritHandle = FALSE;

	lstrcpy(szPathB, TEXT("C:\\ОСИ\\lab_pipes\\Release\\processB.exe"));

	if (!CreateProcess(NULL, szPathB, &saProcess, &saThread, FALSE, 0, NULL, NULL, &siProcessB, &piProcessB))
	{
		MessageBox(NULL, TEXT("ProcessB failed!"), TEXT("Error"), MB_OK);
		//return 0;
	};


	// spawning process C
	STARTUPINFO siProcessC = { sizeof(siProcessC) };
	GetStartupInfo(&siProcessC);
	siProcessC.hStdInput = hReadPipe;
	siProcessC.dwFlags |= STARTF_USESTDHANDLES;

	PROCESS_INFORMATION piProcessC;
	TCHAR szPathC[200];

	lstrcpy(szPathC, TEXT("processC"));

	if (!CreateProcess(NULL, szPathC, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | CREATE_SUSPENDED, NULL, NULL, &siProcessC, &piProcessC))
	{
		MessageBox(NULL, TEXT("ProcessC failed!"), TEXT("Error"), MB_OK);
		return 0;
	};

	Sleep(5000);

	if (1 == ResumeThread(piProcessC.hThread))

	{
		Sleep(5000);

		MessageBox(NULL, TEXT("ProcessC resumed"), TEXT("1:ProcessA"), MB_OK);
	}

	//Wait for Terminating Process B

	if (WAIT_FAILED == WaitForSingleObject(piProcessB.hProcess, INFINITE))
	{
		MessageBox(NULL, TEXT("WAIT_FAILED for ProcessB"), TEXT("2:ProcessA"), MB_OK);
	};
	//Wait for Finishing Process C

	if (WAIT_FAILED == WaitForSingleObject(piProcessC.hProcess, INFINITE))
	{
		MessageBox(NULL, TEXT("WAIT_FAILED for ProcessC"), TEXT("2:ProcessA"), MB_OK);
	};

	CloseHandle(piProcessB.hProcess);
	//	CloseHandle(piProcessB.hThread);

	CloseHandle(piProcessC.hProcess);
	CloseHandle(piProcessC.hThread);
	MessageBox(NULL, TEXT("ProcessA finished"), TEXT("2:ProcessA"), MB_OK);

	return 0;
}

