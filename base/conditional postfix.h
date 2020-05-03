#ifndef __CONDITIONAL_POSTFIX_H__
#define __CONDITIONAL_POSTFIX_H__

#include <string>
#include <vector>
#include "arithmetic postfix.h"

using namespace std;

class CondPostfix
{
	string infix;
	vector<string> postfix;
	ArithmPostfix arithm;
public:
	bool IsCorrect();
	void CalculateArithmExpressions();
	void ToPostfix(string _infix);
	double Calculate();
};

#endif
