#include "arithmetic postfix.h"

int ArithmPostfix::Priority(const string& str)
{
	if (str == "(") return 0;
	else if (str == ")") return 1;
	else if (str == "+" || str == "-") return 2;
	else if (str == "mod") return 3;
	else if (str == "div") return 4;
	else if (str == "*" || str == "/") return 5;
	else throw "get priority for not an operation";
	return -1;
}

bool ArithmPostfix::IsDigit(const string& str)
{
	try { stod(str); }
	catch (invalid_argument) { return false; }
	return true;
}

bool ArithmPostfix::IsOperation(const string& str)
{
	try {
		if (Priority(str) < 2) return false;
	}
	catch (const char*) { return false; }
	return true;
}

void ArithmPostfix::ToPostfix(vector<string>& _infix)
{
	stack<string> st;

	for (int i = 0; i < _infix.size(); i++)
	{
		if (IsDigit(_infix[i])) postfix.push_back(_infix[i]);
		else
		{
			if (_infix[i] == "(") st.push(_infix[i]);
			else if (_infix[i] == ")") 
			{
				while (st.top() != "(") 
				{
					postfix.push_back(st.top());
					st.pop();
				}
				st.pop();
			}
			else {
				if (st.empty()) st.push(_infix[i]);
				else {
					while (!st.empty() && Priority(_infix[i]) <= Priority(st.top()))
					{
						postfix.push_back(st.top());
						st.pop();
					}
					st.push(_infix[i]);
				}
			}
		}
	}

	while (!st.empty())
	{
		postfix.push_back(st.top());
		st.pop();
	}
}

double ArithmPostfix::Calculate()
{
	if (postfix.empty()) throw "no postfix form";

	double res = 0;
	stack<double> st;
	for (int i = 0; i < postfix.size(); i++) {
		if (IsDigit(postfix[i]))
			st.push(stod(postfix[i]));
		else {
			double tmp;
			if (postfix[i] == "+") {
				tmp = st.top();
				st.pop();
				tmp += st.top();
				st.pop();
				st.push(tmp);
			}
			else if (postfix[i] == "-") {
				tmp = st.top();
				st.pop();
				tmp = st.top() - tmp;
				st.pop();
				st.push(tmp);
			}
			else if (postfix[i] == "mod") {
				tmp = st.top();
				st.pop();
				tmp = (int)st.top() % (int)tmp;
				st.pop();
				st.push(tmp);
			}
			else if (postfix[i] == "div") {
				tmp = st.top();
				if ((int)tmp == 0)throw "divine by zero";
				st.pop();
				tmp = (int)st.top() / (int)tmp;
				st.pop();
				st.push(tmp);
			}
			else if (postfix[i] == "*") {
				tmp = st.top();
				st.pop();
				tmp *= st.top();
				st.pop();
				st.push(tmp);
			}
			else if (postfix[i] == "/") {
				tmp = st.top();
				if (tmp == 0)throw "divine by zero";
				st.pop();
				tmp = st.top() / tmp;
				st.pop();
				st.push(tmp);
			}
		}
	}
	return res = st.top();
}
