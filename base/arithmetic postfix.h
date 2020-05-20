#pragma once

#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

class ArithmPostfix
{
	vector<string> postfix;

	int Priority(const string& str);
public:
	bool IsDigit(const string& str);
	bool IsOperation(const string& str);

	void ToPostfix(vector<string>& _infix);
	vector<string>& GetPostfix() { return postfix; };
	double Calculate();
};
