#include "conditional postfix.h"

int CondPostfix::Priority(const string& str)
{
	if (str == "(") return 0;
	else if (str == ")") return 1;
	else if (str == "or" || str == "xor") return 2;
	else if (str == "and") return 3;
	else if (str == "not") return 4;
	else if (str == "=" || str == "<>" ||
		str == ">" || str == "<" ||
		str == ">=" || str == "<=") return 5;
	else throw "get priority for not an operation";
	return -1;
}

bool CondPostfix::IsDigit(const string& str)
{
	try { stod(str); }
	catch (invalid_argument) { return false; }
	return true;
}

bool CondPostfix::IsOperation(const string& str)
{
	try { 
		if (Priority(str) < 2) return false; 
	}
	catch (const char*) { return false; }
	return true;
}

double CondPostfix::CalculateArithmExpressions(vector<string> _arithm)
{
	arithm.ToPostfix(_arithm);
	return arithm.Calculate();
}

void CondPostfix::ToPostfix(vector<string> _infix)
{
	_infix.push_back(")");
	_infix.insert(_infix.begin(), "(");
	auto it_first = _infix.begin();
	auto it_last = it_first;

	bool flag_arithm_expression = false;

	vector<string> sub_expression;
	for (auto it = _infix.begin(); it != _infix.end(); it++)
	{
		// find arithm operation
		if (arithm.IsOperation(*it) && !flag_arithm_expression)
		{
			flag_arithm_expression = true;
			auto i = it;
			for (i; i != _infix.begin(); i--)
				if (IsOperation(*i)) {
					it_first = i + 1;
					break;
				}
			if (i == _infix.begin()) it_first = i + 1;
			continue;
		}

		// find first conditional operation after arithm operations (or end of expression)
		if (flag_arithm_expression && (IsOperation(*it) || it == _infix.end() - 1))
		{
			it_last = it - 1;

			int flag_subexpression_brackets = 0;
			for (auto i = it - 1; i != it_first - 1; i--)
			{
				if (*i == "(") {
					flag_subexpression_brackets++; continue;
				}
				else if (*i == ")") {
					flag_subexpression_brackets--; continue;
				}
			}

			if (flag_subexpression_brackets > 0) it_first = it_first + flag_subexpression_brackets;
			else if (flag_subexpression_brackets < 0) it_last = it_last + flag_subexpression_brackets;
			
			for (auto i = it_first; i != it_last + 1; i++)
				sub_expression.push_back(*i);

			_infix.erase(it_first + 1, it_last + 1);
			*it_first = to_string(CalculateArithmExpressions(sub_expression));
			sub_expression.clear();

			it = it_first;

			flag_arithm_expression = false;
			continue;
		}
	}

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

bool CondPostfix::Calculate()
{
	if (postfix.empty()) throw "no postfix form";

	bool res = false;
	stack<double> st;
	for (int i = 0; i < postfix.size(); i++) {
		if (IsDigit(postfix[i]))
			st.push(stod(postfix[i]));
		else {
			double arg1;		// arg1 (operation) arg2
			double arg2;
			if (postfix[i] == "=") {
				arg2 = st.top();
				st.pop();
				arg1 = st.top();
				st.pop();
				st.push(arg1 == arg2 ? 1 : 0);
			}
			else if (postfix[i] == "<>") {
				arg2 = st.top();
				st.pop();
				arg1 = st.top();
				st.pop();
				st.push(arg1 != arg2 ? 1 : 0);
			}
			else if (postfix[i] == ">") {
				arg2 = st.top();
				st.pop();
				arg1 = st.top();
				st.pop();
				st.push(arg1 > arg2 ? 1 : 0);
			}
			else if (postfix[i] == "<") {
				arg2 = st.top();
				st.pop();
				arg1 = st.top();
				st.pop();
				st.push(arg1 < arg2 ? 1 : 0);
			}
			else if (postfix[i] == ">=") {
				arg2 = st.top();
				st.pop();
				arg1 = st.top();
				st.pop();
				st.push(arg1 >= arg2 ? 1 : 0);
			}
			else if (postfix[i] == "<=") {
				arg2 = st.top();
				st.pop();
				arg1 = st.top();
				st.pop();
				st.push(arg1 <= arg2 ? 1 : 0);
			}
			else if (postfix[i] == "and") {
				arg2 = st.top();
				st.pop();
				arg1 = st.top();
				st.pop();
				st.push((arg1 != 0) && (arg2 != 0) ? 1 : 0);
			}
			else if (postfix[i] == "or") {
				arg2 = st.top();
				st.pop();
				arg1 = st.top();
				st.pop();
				st.push((arg1 != 0) || (arg2 != 0) ? 1 : 0);
			}
			else if (postfix[i] == "xor") {
				arg2 = st.top();
				st.pop();
				arg1 = st.top();
				st.pop();
				st.push((arg1 != 0) && (arg2 == 0) || (arg1 == 0) && (arg2 != 0) ? 1 : 0);
			}
			else if (postfix[i] == "not") {
				arg1 = st.top();
				st.pop();
				st.push((arg1 == 0) ? 1 : 0);
			}
		}
	}
	return (res = st.top()) != 0;
}
