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

	string path;
	cout << "Enter path to Pascal-- code: ";
	cin >> path;
	/*

	../code.txt
	
	../code1.txt

	../code2.txt

	../code3.txt

	../code3.1.txt

	../code4.txt

	../code4.1.txt

	../code5.txt

	*/
	ifile.open(path);

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
