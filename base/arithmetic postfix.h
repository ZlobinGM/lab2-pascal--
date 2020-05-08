#ifndef __ARITHMETIC_POSTFIX_H__
#define __ARITHMETIC_POSTFIX_H__

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
	double Calculate();
};

#endif

