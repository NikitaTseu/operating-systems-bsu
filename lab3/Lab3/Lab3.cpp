#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include "..\\Vector\\Interface.h"

typedef VectorInterface* (*pMyFunc)(double, double);

int _tmain(int argc, _TCHAR* argv[])
{
	HMODULE hLib = LoadLibraryA("Vector.dll");
	if (!hLib)
	{
		std::cout << "Error=" << GetLastError() << std::endl;
		return 1;
	}

	pMyFunc createVector = (pMyFunc)GetProcAddress(hLib, "createVector");
	VectorInterface* v1 = createVector(-1, 1);
	v1->print();
	std::cout << std::setprecision(4) << "r = " << v1->length() << std::endl << "angle = " << v1->angle() << std::endl << std::endl;

	VectorInterface* v2 = createVector(0, 0);
	v2->print();
	std::cout << std::setprecision(4) << "r = " << v2->length() << std::endl << "angle = " << v2->angle() << std::endl << std::endl;

	VectorInterface* v3 = createVector(0, 5);
	v3->print();
	std::cout << std::setprecision(4) << "r = " << v3->length() << std::endl << "angle = " << v3->angle() << std::endl << std::endl;

	VectorInterface* v4 = createVector(3, 4);
	v4->print();
	std::cout << std::setprecision(4) << "r = " << v4->length() << std::endl << "angle = " << v4->angle() << std::endl << std::endl;
    return 0;
}

