#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <conio.h>

int main(int argc, char* argv[])
{
	char pid[100], s[100];
	std::cin >> pid;
	
	sprintf(s, "B's PID by pipe = %s", pid);

	MessageBoxA(NULL, s, "Info", MB_OK);

	DWORD  dwBProcessId = atoi(pid);

	HANDLE hProcessB = OpenProcess(PROCESS_TERMINATE, FALSE, dwBProcessId);

	if (TerminateProcess(hProcessB, 2))	
		MessageBoxA(NULL, "Inherited ProcessB terminated", "Info", MB_OK);
	else
		MessageBoxA(NULL, "ProcessB failed to be terminated", "Info", MB_OK);

	CloseHandle(hProcessB);

	printf("\nHello World! from ProcessC\nPress any key to exit!\n");
	_getch();
	return 0;
}