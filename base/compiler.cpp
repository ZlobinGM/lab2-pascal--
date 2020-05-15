#include "compiler.h"

void Compiler::ProcessProgram(HierList<string>& _code)
{
	code = move(_code);
	code.GoFirst();
	// skip program name
	code.GoNext();
	code.GoDown();

	while (code.ReadCurrent() != "begin")
	{
		if (code.ReadCurrent() == "const")
		{
			code.GoUp();
			code.GoNext();
			code.GoDown();
			do
			{
				CreateConst();
				code.GoUp();
				code.GoNext();
				code.GoDown();
			} while (code.ReadCurrent() != "begin" &&
				code.ReadCurrent() != "var" &&
				code.ReadCurrent() != "const");
		}

		if (code.ReadCurrent() == "var")
		{
			code.GoUp();
			code.GoNext();
			code.GoDown();
			do
			{
				CreateVar();
				code.GoUp();
				code.GoNext();
				code.GoDown();
			} while (code.ReadCurrent() != "begin" &&
				code.ReadCurrent() != "var" &&
				code.ReadCurrent() != "const");
		}
	}

	DoBeginEndBlock();
}

void Compiler::DoBeginEndBlock()
{
	if (code.ReadCurrent() != "begin") throw "no begin-end block";

	string str;
	//выполнение условного перехода if(if-else);

	while (code.ReadCurrent() != "end")
	{
		code.GoUp();

		str = code.ReadCurrent();

		if (str.find("Write") != string::npos)
		{
			code.GoDown();
			ExecuteWrite();
			code.GoUp();
			code.GoNext();
			code.GoDown();
			continue;
		}
		else if (str.find("Read") != string::npos)
		{
			code.GoDown();
			ExecuteRead();
			code.GoUp();
			code.GoNext();
			code.GoDown();
			continue;
		}
		else if (str.find(":=") != string::npos)
		{
			code.GoDown();
			AssigningValue();
			code.GoUp();
			code.GoNext();
			code.GoDown();
			continue;
		}
		else if (str.find("if") != string::npos)
		{
			code.GoDown();
			DoIfBlock();
			continue;
		}

		code.GoNext();
		code.GoDown();
	}

}

void Compiler::DoIfBlock()
{
	if (code.ReadCurrent() != "if") throw "no if block";
	
	// string type:
	// if cond_expression then
	// (begin-end block)
	// (else)

	code.GoNext();
	vector<string> cond_expression;
	while (code.ReadCurrent() != "then")
	{
		cond_expression.push_back(code.ReadCurrent());
		code.GoNext();
	}

	bool value = CalculateCond(cond_expression);

	if (value)
	{
		code.GoUp();
		code.GoNext();
		code.GoDown();

		// begin-end block after if
		if (code.ReadCurrent() == "begin")
		{
			DoBeginEndBlock();
			code.GoUp();
			code.GoNext();
			code.GoDown();
		}
		// 1 string after if
		else
		{
			string str;

			code.GoUp();

			str = code.ReadCurrent();

			if (str.find("Write") != string::npos)
			{
				code.GoDown();
				ExecuteWrite();
				code.GoUp();
				code.GoNext();
				code.GoDown();
			}
			else if (str.find("Read") != string::npos)
			{
				code.GoDown();
				ExecuteRead();
				code.GoUp();
				code.GoNext();
				code.GoDown();
			}
			else if (str.find(":=") != string::npos)
			{
				code.GoDown();
				AssigningValue();
				code.GoUp();
				code.GoNext();
				code.GoDown();
			}
			else if (str.find("if") != string::npos)
			{
				code.GoDown();
				DoIfBlock();
			}
		}

		// if there is no else-block
		if (code.ReadCurrent() != "else") return;
		// if else-block exist
		else
		{
			code.GoUp();
			code.GoNext();
			code.GoDown();

			// 1 string after else
			if (code.ReadCurrent() != "begin")
			{
				code.GoUp();
				code.GoNext();
				code.GoDown();
				return;
			}
			// begin-end block after else
			else
			{
				do
				{
					code.GoUp();
					code.GoNext();
					code.GoDown();
				} while (code.ReadCurrent() != "end");
				code.GoUp();
				code.GoNext();
				code.GoDown();
				return;
			}
		}
	}
	else
	{
		code.GoUp();
		code.GoNext();
		code.GoDown();

		// begin-end block after if
		if (code.ReadCurrent() == "begin")
		{
			do
			{
				code.GoUp();
				code.GoNext();
				code.GoDown();
			} while (code.ReadCurrent() != "end");
			code.GoUp();
			code.GoNext();
			code.GoDown();
		}
		// 1 string after if
		else
		{
			code.GoUp();
			code.GoNext();
			code.GoDown();
		}

		// if there is no else-block
		if (code.ReadCurrent() != "else") return;
		// if else-block exist
		else
		{
			code.GoUp();
			code.GoNext();
			code.GoDown();

			// 1 string after else
			if (code.ReadCurrent() != "begin")
			{
				string str;

				code.GoUp();

				str = code.ReadCurrent();

				if (str.find("Write") != string::npos)
				{
					code.GoDown();
					ExecuteWrite();
					code.GoUp();
					code.GoNext();
					code.GoDown();
				}
				else if (str.find("Read") != string::npos)
				{
					code.GoDown();
					ExecuteRead();
					code.GoUp();
					code.GoNext();
					code.GoDown();
				}
				else if (str.find(":=") != string::npos)
				{
					code.GoDown();
					AssigningValue();
					code.GoUp();
					code.GoNext();
					code.GoDown();
				}
				else if (str.find("if") != string::npos)
				{
					code.GoDown();
					DoIfBlock();
				}
				return;
			}
			// begin-end block after else
			else
			{
				DoBeginEndBlock();
				code.GoUp();
				code.GoNext();
				code.GoDown();
				return;
			}
		}
	}
}

void Compiler::AssigningValue()
{
	// string type:
	// name := arithm_expression ;

	string name = code.ReadCurrent();
	code.GoNext();
	code.GoNext();
	vector<string> arithm_expression;
	while (code.ReadCurrent() != ";")
	{
		arithm_expression.push_back(code.ReadCurrent());
		code.GoNext();
	}

	double value = CalculateArithm(arithm_expression);

	if (int_var.Find(name) != nullptr)
		*int_var.Find(name) = (int)value;
	else if (double_var.Find(name) != nullptr)
		*double_var.Find(name) = value;
	else
		throw "assingning var isn't exist";
}

void Compiler::CreateVar()
{
	// string type:
	// name1 , name2 , ...... , nameN : type(double/int) ;

	vector<string> names;
	while (code.ReadCurrent() != ":")
	{
		if (code.ReadCurrent() == ",") {
			code.GoNext();
			continue;
		}
		names.push_back(code.ReadCurrent());
		code.GoNext();
	}

	code.GoNext();
	string type = code.ReadCurrent();
	if (type == "integer")
	{
		int value = 0;
		for each (string name in names)
			int_var.Insert(name, value);
	}
	else if (type == "double")
	{
		double value = 0;
		for each (string name in names)
			double_var.Insert(name, value);
	}
	else
		throw "no correct type";
}

void Compiler::CreateConst()
{
	// string type:
	// name : type(double/int) = value ;

	string name = code.ReadCurrent();
	code.GoNext();
	code.GoNext();
	string type = code.ReadCurrent();
	code.GoNext();
	code.GoNext();
	if (type == "integer")
	{
		int value = stoi(code.ReadCurrent());
		int_const.Insert(name, value);
	}
	else if (type == "double")
	{
		double value = stod(code.ReadCurrent());
		double_const.Insert(name, value);
	}
	else
		throw "no correct type";
}

void Compiler::ExecuteRead()
{
	if (code.ReadCurrent() != "Read") throw "no read function in string";
	code.GoNext();
	code.GoNext();

	if (int_var.Find(code.ReadCurrent()) != nullptr)
		cin >> *int_var.Find(code.ReadCurrent());
	else if (double_var.Find(code.ReadCurrent()) != nullptr)
		cin >> *double_var.Find(code.ReadCurrent());
	else
		throw "reading var isn't exist";
}

void Compiler::ExecuteWrite()
{
	if (code.ReadCurrent() != "Write") throw "no write function in string";
	code.GoNext();
	code.GoNext();

	string substring = code.ReadCurrent();
	string var;

	code.GoNext();

	// replace var with its value
	if (code.ReadCurrent() == ",")
	{
		code.GoNext();
		if (int_var.Find(code.ReadCurrent()) != nullptr)
			var = to_string(*int_var.Find(code.ReadCurrent()));
		else if (double_var.Find(code.ReadCurrent()) != nullptr)
			var = to_string(*double_var.Find(code.ReadCurrent()));
		else if (int_const.Find(code.ReadCurrent()) != nullptr)
			var = to_string(*int_const.Find(code.ReadCurrent()));
		else if (double_const.Find(code.ReadCurrent()) != nullptr)
			var = to_string(*double_const.Find(code.ReadCurrent()));
		else
			throw "writing var isn't exist";
		substring += var;
	}

	cout << substring;
}

double Compiler::CalculateArithm(vector<string>& expression)
{
	for (auto iter = expression.begin(); iter != expression.end(); iter++)
	{
		if (int_var.Find(*iter) != nullptr)
			*iter = to_string(*int_var.Find(*iter));
		else if (double_var.Find(*iter) != nullptr)
			*iter = to_string(*double_var.Find(*iter));
		else if (int_const.Find(*iter) != nullptr)
			*iter = to_string(*int_const.Find(*iter));
		else if (double_const.Find(*iter) != nullptr)
			*iter = to_string(*double_const.Find(*iter));
	}

	ArithmPostfix postfix;
	postfix.ToPostfix(expression);
	return postfix.Calculate();
}

bool Compiler::CalculateCond(vector<string>& expression)
{
	for (auto iter = expression.begin(); iter != expression.end(); iter++)
	{
		if (int_var.Find(*iter) != nullptr)
			*iter = to_string(*int_var.Find(*iter));
		else if (double_var.Find(*iter) != nullptr)
			*iter = to_string(*double_var.Find(*iter));
		else if (int_const.Find(*iter) != nullptr)
			*iter = to_string(*int_const.Find(*iter));
		else if (double_const.Find(*iter) != nullptr)
			*iter = to_string(*double_const.Find(*iter));
	}

	CondPostfix postfix;
	postfix.ToPostfix(expression);
	return postfix.Calculate();
}
