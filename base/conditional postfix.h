#ifndef __CONDITIONAL_POSTFIX_H__
#define __CONDITIONAL_POSTFIX_H__

#include <string>
#include <vector>
#include "arithmetic postfix.h"

using namespace std;

class CondPostfix
{
	vector<string> postfix;
	ArithmPostfix arithm;

	int Priority(const string& str);
public:
	bool IsDigit(const string& str);
	bool IsOperation(const string& str);

	double CalculateArithmExpressions(vector<string> _arithm);
	void ToPostfix(vector<string> _infix);
	bool Calculate();
};

#endif
