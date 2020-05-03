#ifndef __ANALYTICAL_MODULE_H__
#define __ANALYTICAL_MODULE_H__

#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <iostream>
#include "hierarchical list.h"

using namespace std;

class AnalyticalMod
{
protected:
	vector<string> text;
public:
	AnalyticalMod() {}

	void Read(ifstream& input);
	void SyntaxConntrol();
	HierList<string> CreateHierList();
};

#endif
