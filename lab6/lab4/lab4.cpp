//#include "stdafx.h"
//#include <Windows.h>
//#include <iostream>
//#include <conio.h>
//
//#pragma data_seg("SharedSection")
//	int ans = 0;
//#pragma data_seg()
//
//#pragma comment(linker,"/Section:SharedSection,RWS")
//
//using namespace std;
//
//int localAns;
//
////bool correctOp(int op) {
////	return (op == int('q') || op == int('-') || op == int('*') || op == int('/'));
////}
//
//int main(int argc, char* argv[])
//{
//	int a, b;
//	/*cout << "Hello! It's a simple calculator with a shared section." << endl;
//	cout << "Enter two numbers: " << endl;*/
//	cout << "a = ";
//	cin >> a;
//	/*cout << endl << "b = ";
//	cin >> b;
//
//	cout << endl << "Press operation key (+, -, *, /): ";
//	int operation = _getch();
//
//	while (!correctOp(operation)) {
//		cout << endl << "Please, press correct operation key (+, -, *, /): ";
//		operation = _getch();
//	}
//
//	if (operation == int('q')) {
//		ans = InterlockedExchangeAdd((PLONG)&ans, a);
//		ans = InterlockedExchangeAdd((PLONG)&ans, b);
//		localAns = InterlockedExchangeAdd((PLONG)&ans, 0);
//		cout << localAns << endl;
//	}*/
//	ans = InterlockedExchangeAdd((PLONG)&ans, 1);
//	localAns = InterlockedExchangeAdd((PLONG)&ans, 0);
//	cout << localAns << endl;
//	int h =_getch();
//	system("pause");
//	return 0;
//}
//


#include "stdafx.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>

#pragma data_seg("SharedSection")
	int ans = 0;
#pragma data_seg()

#pragma comment(linker,"/Section:SharedSection,RWS")

using namespace std;

int currentAns = 0;

void printCurrentMemoryValue() {
	cout << "Current memory value M = " << currentAns << endl;
}

bool correctOperation(int op) {
	return (op == int('+') || op == int('-') || op == int('*') || op == int('/') || op == int('c'));
}

int getOperation() {
	cout << "Enter operation key: ";
	char op;
	cin >> op;

	while (!correctOperation((int)op)) {
		cout << "Please, enter CORRECT operation key: ";
		cin >> op;
	}
	return op;
}

int getArgument() {
	int a;
	cout << "Enter the second argument (int) = ";
	cin >> a;
	return a;
}

void performOperation(int operation, int a) {
	if (operation == int('+')) {
		InterlockedExchangeAdd((PLONG)&ans, a);
		currentAns = InterlockedExchangeAdd((PLONG)&ans, 0);
		cout << "M increased by " << a << endl;
		printCurrentMemoryValue();
	}

	if (operation == int('-')) {
		InterlockedExchangeAdd((PLONG)&ans, (-a));
		currentAns = InterlockedExchangeAdd((PLONG)&ans, 0);
		cout << "M decreased by " << a << endl;
		printCurrentMemoryValue();
	}

	if (operation == int('*')) {
		currentAns = InterlockedExchangeAdd((PLONG)&ans, 0);
		currentAns *= a;
		InterlockedExchange((PLONG)&ans, currentAns);
		cout << "M multiplied by " << a << endl;
		printCurrentMemoryValue();
	}

	if (operation == int('/')) {
		if (a != 0) {
			currentAns = InterlockedExchangeAdd((PLONG)&ans, 0);
			currentAns /= a;
			InterlockedExchange((PLONG)&ans, currentAns);
			cout << "M divided by " << a << endl;
			printCurrentMemoryValue();
		}
		else {
			cout << "Error! Division by 0 is impossible." << endl;
		}
	}

	if (operation == int('c')) {
		InterlockedExchange((PLONG)&ans, 0);
		currentAns = InterlockedExchangeAdd((PLONG)&ans, 0);
		cout << "M was successfully reset." << endl;
		printCurrentMemoryValue();
	}

	cout << endl;
}

int main(int argc, char* argv[])
{
	int a, operation;
	cout << "Hello! It's a simple calculator with a shared section." << endl;
	cout << "Operation keys: '+' for plus, '-' for minus, '*' to multiply, '/' to divide, 'c' to clear memory" << endl;
	currentAns = InterlockedExchangeAdd((PLONG)&ans, 0);
	printCurrentMemoryValue();
	cout << endl;

	while (true) {
		operation = getOperation();
		if (operation == (int)'c') {
			performOperation(operation, 0);
		}
		else {
			a = getArgument();
			performOperation(operation, a);
		}
	}
	return 0;
}


