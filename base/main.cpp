#include <iostream>
#include <limits>
#include <string>
#include <conio.h>
#include <ctime>
#include <Windows.h>
#include <fstream>
#include "analytical module.h"
#include "compiler.h"

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream ifile;
	ifile.open("../code.txt");

	try {
		AnalyticalMod amod;
		amod.Read(ifile);
		amod.SyntaxConntrol();
		HierList<string> list;
		list = move(*amod.CreateHierList());
		Compiler comp;
		comp.ProcessProgram(list);
	}
	catch (const char* error) 
	{
		cout << error;
	}
	return 0;
}
