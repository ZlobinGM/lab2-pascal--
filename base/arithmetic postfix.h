#ifndef __ARITHMETIC_POSTFIX_H__
#define __ARITHMETIC_POSTFIX_H__

#include <string>
#include <vector>

using namespace std;

class ArithmPostfix
{
	string infix;
	vector<string> postfix;
public:
	bool IsCorrect();
	void ToPostfix(string _infix);
	double Calculate();
};

#endif

