#include "analytical module.h"

void AnalyticalMod::Read(ifstream& input)
{
	if (!input.fail())
	{
		while (!input.eof())
		{
			string str;
			getline(input, str);
			text.push_back(str);
		}
	}
	else
	{
		throw "can't read from ifstream";
	}
}

void AnalyticalMod::SyntaxConntrol()
{
	string str;
	short flag_begin_end = 0;
	short flag_brackets = 0;
	short flag_quotation_marks = 0;
	short flag_if_then = 0;
	vector<string> all_var_names;
	vector<string> uninitialized_var;

	for (auto it = text.begin(); it != text.end(); it++) 
	{
		str = *it;
		// const section
		if (str.find("const") != string::npos) {
			it++;
			str = *it;
			while ((str.find("const") == string::npos)
				&& (str.find("var") == string::npos)
				&& (str.find("begin") == string::npos))
			{
				for (auto i = str.begin(); i != str.end(); i++)
					if (*i == ':' || *i == '=' || *i == ';') *i = ' ';

				stringstream ss(str);
				string tmp;
				vector<string> v;
				while (ss >> tmp) v.push_back(tmp);
				
				if (v.size() != 3)throw "uncorrect const var format";
				if (v.at(1) != "double" && v.at(1) != "integer") throw "no const type";
				try { stod(v.at(2)); }
				catch (invalid_argument) { throw "no value for const"; }
				for each (string var in all_var_names)
					if (var == v.at(0)) throw "same name";
				all_var_names.push_back(v.at(0));

				it++;
				str = *it;
			}
			it--;
			continue;
		}

		//var section
		if (str.find("var") != string::npos) {
			it++;
			str = *it;
			while ((str.find("const") == string::npos)
				&& (str.find("var") == string::npos)
				&& (str.find("begin") == string::npos))
			{
				for (auto i = str.begin(); i != str.end(); i++)
					if (*i == ':' || *i == ';' || *i == ',') *i = ' ';

				stringstream ss(str);
				string tmp;
				vector<string> v;
				while (ss >> tmp) v.push_back(tmp);

				if (v.size() < 2)throw "uncorrect var format";
				if (v.at(v.size() - 1) != "double" && v.at(v.size() - 1) != "integer") throw "no var type";
				v.pop_back();
				for each (string newvar in v)
				{
					for each (string var in all_var_names)
						if (var == newvar) throw "same name";
					all_var_names.push_back(newvar);
					uninitialized_var.push_back(newvar);
				}

				it++;
				str = *it;
			}
			it--;
			continue;
		}

		// begin end flag
		if (str.find("begin") != string::npos) {
			flag_begin_end++;
			continue;
		}
		if (str.find("end") != string::npos) {
			flag_begin_end--;
			continue;
		}

		// if then flag
		if (str.find("if") != string::npos)
		{
			flag_if_then++;

			// find undeclared var
			string letter_str = str;
			vector<string> all_operations =
			{
				"(", ")", "+", "-", "mod", "div", "*", "/",
				"or", "xor", "and", "not", "=", "<>", ">", "<", ">=", "<="
			};

			for (auto i = letter_str.begin(); i != letter_str.end(); i++)
				if (*i == ')' || *i == ';' || *i == '(') *i = ' ';

			// insert ' ' befor words
			for (size_t i = 0; i < letter_str.size(); i++)
			{
				if ((letter_str[i] >= 'a' && letter_str[i] <= 'z') || (letter_str[i] >= 'A' && letter_str[i] <= 'Z'))
				{
					letter_str.insert(i, 1, ' ');
					do
					{
						i++;
					} while (i < letter_str.size() && letter_str[i] != ' ');
				}
			}

			// erase if, then, all vars, all operations
			size_t pos = letter_str.find("if");
			if (pos != string::npos) letter_str.erase(pos, 2);
			pos = letter_str.find("then");
			if (pos != string::npos) letter_str.erase(pos, 4);
			for each (string var in all_var_names)
			{
				pos = 0;
				while ((pos = letter_str.find(var, pos)) != string::npos)
					if ((pos == 0 || letter_str[pos - 1] == ' ') &&
						(pos == letter_str.size() || letter_str[pos + var.size()] == ' '))
						letter_str.erase(pos, var.size());
					else
						pos++;
			}
			for each (string operation in all_operations)
			{
				pos = 0;
				while ((pos = letter_str.find(operation, pos)) != string::npos)
					if ((pos == 0 || letter_str[pos - 1] == ' ') &&
						(pos == letter_str.size() || letter_str[pos + operation.size()] == ' '))
						letter_str.erase(pos, operation.size());
					else
						pos++;
			}

			// find undeclered letter
			for (auto iter = letter_str.begin(); iter != letter_str.end(); iter++)
			{
				if ((*iter >= 'a' && *iter <= 'z') || (*iter >= 'A' && *iter <= 'Z'))
					throw "undeclared var";
			}
		}
		if (str.find("then") != string::npos) flag_if_then--;

		// init var by read function
		if (str.find("Read") != string::npos)
		{
			string initvar;
			size_t var_pos = str.find('(') + 1;
			for each (string var in uninitialized_var)
			{
				if (str.find(var, var_pos) != string::npos)
					initvar = var;
			}
			for (auto i = uninitialized_var.begin(); i != uninitialized_var.end(); i++)
			{
				if (*i == initvar) {
					uninitialized_var.erase(i);
					break;
				}
			}
		}

		// uninitialized var don't use
		size_t assignment_pos = str.find(":=");
		if (assignment_pos != string::npos)
		{
			string initvar;
			for each (string var in uninitialized_var)
			{
				size_t var_pos = str.find(var);
				if (var_pos != string::npos) 
				{
					if (var_pos > assignment_pos)
						throw "using uninitialized var";
					else
						initvar = var;
				}
			}
			for (auto i = uninitialized_var.begin(); i != uninitialized_var.end(); i++)
			{
				if (*i == initvar) {
					uninitialized_var.erase(i);
					break;
				}
			}

			// find undeclared var
			string letter_str = str;
			vector<string> all_operations =
			{
				"(", ")", "+", "-", "mod", "div", "*", "/",
			};

			for (auto i = letter_str.begin(); i != letter_str.end(); i++)
				if (*i == ')' || *i == ';' || *i == '(') *i = ' ';

			// insert ' ' befor words
			for (size_t i = 0; i < letter_str.size(); i++)
			{
				if ((letter_str[i] >= 'a' && letter_str[i] <= 'z') || (letter_str[i] >= 'A' && letter_str[i] <= 'Z'))
				{
					letter_str.insert(i, 1, ' ');
					do
					{
						i++;
					} while (i < letter_str.size() && letter_str[i] != ' ');
				}
			}

			// erase all vars, all operations
			size_t pos;
			for each (string var in all_var_names)
			{
				pos = 0;
				while ((pos = letter_str.find(var, pos)) != string::npos)
					if ((pos == 0 || letter_str[pos - 1] == ' ') &&
						(pos == letter_str.size() || letter_str[pos + var.size()] == ' '))
						letter_str.erase(pos, var.size());
					else
						pos++;
			}
			for each (string operation in all_operations)
			{
				pos = 0;
				while ((pos = letter_str.find(operation, pos)) != string::npos)
					if ((pos == 0 || letter_str[pos - 1] == ' ') &&
						(pos == letter_str.size() || letter_str[pos + operation.size()] == ' '))
						letter_str.erase(pos, operation.size());
					else
						pos++;
			}

			// find undeclered letter
			for (auto iter = letter_str.begin(); iter != letter_str.end(); iter++)
			{
				if ((*iter >= 'a' && *iter <= 'z') || (*iter >= 'A' && *iter <= 'Z'))
					throw "undeclared var";
			}
		}

		// change some flags
		for (auto i = str.begin(); i != str.end(); i++)
		{
			if (*i == '"') {
				flag_quotation_marks = (flag_quotation_marks + 1) % 2;
				continue;
			}

			if (*i == '(') { 
				flag_brackets++;
				continue;
			}
			if (*i == ')') {
				flag_brackets--;
				continue;
			}
		}

		// check some flags
		if (flag_quotation_marks != 0) throw "quotation marks error";
		if (flag_brackets != 0) throw "brackets error";
		if (flag_if_then != 0) throw "if then error";
	}

	if (flag_begin_end != 0)throw "begin end error";
}

HierList<string>* AnalyticalMod::CreateHierList()
{
	HierList<string>* hierlist = new HierList<string>;
	string str;

	for (auto it = text.begin(); it != text.end(); it++)
	{
		hierlist->InsertNext(*it);
		hierlist->GoNext();

		str = *it;

		string substring;

		// if str contains substring
		if (str.find("Write") != string::npos) 
		{

			// separating first "(" from the previos and next word
			size_t insert = str.find('(');
			str.replace(insert, 1, " ( ");

			// separating last ")" from the previos and next word
			insert = str.rfind(')');
			str.replace(insert, 1, " ) ");

			// separating ";" from the previos word
			insert = str.rfind(';');
			str.replace(insert, 1, " ;");

			// separating "," after substring from the previos word
			size_t endOfStr = str.rfind('"');
			size_t iter = endOfStr;
			while ((insert = str.find(',', iter)) != string::npos)
			{
				str.replace(insert, 1, " ,");
				insert = str.find(',', insert);
				iter = insert + 1;
			}

			// save substring
			size_t beginOfStr = str.find('"') + 1;
			substring = str.substr(beginOfStr, endOfStr - beginOfStr);
			beginOfStr--;
			str.replace(beginOfStr, endOfStr - beginOfStr + 1, "ThereWasASubstringHere");
		}
		// str without substring
		else 
		{
			size_t iter = 0;
			size_t insert = iter;

			// separating "," from the previos word
			while ((insert = str.find(',', iter)) != string::npos)
			{
				str.replace(insert, 1, " ,");
				insert = str.find(',', insert);
				iter = insert + 1;
			}

			// replace . for , in numbers
			if (str.find("double") != string::npos)
				while ((insert = str.find('.', iter)) != string::npos &&
					str.at(insert - 1) <= '9' && str.at(insert - 1) >= '0')
			{
				str.replace(insert, 1, ",");
				iter = insert + 1;
			}

			// separating "." from the end
			if ((insert = str.find('.')) != string::npos
				&& str.find("end") != string::npos)
				str.replace(insert, 1, " .");

			// separating ";" from the previos word
			if ((insert = str.rfind(';')) != string::npos
				&& insert == str.size() - 1)
				str.replace(insert, 1, " ;");

			// separating ":" from the previos word
			iter = 0;
			while ((insert = str.find(':', iter)) != string::npos)
			{
				str.replace(insert, 1, " :");
				insert = str.find(':', insert);
				iter = insert + 1;
			}

			// separating "(" from the previos and next word
			iter = 0;
			while ((insert = str.find('(', iter)) != string::npos)
			{
				str.replace(insert, 1, " ( ");
				insert = str.find('(', insert);
				iter = insert + 1;
			}

			// separating ")" from the previos and next word
			iter = 0;
			while ((insert = str.find(')', iter)) != string::npos)
			{
				str.replace(insert, 1, " ) ");
				insert = str.find(')', insert);
				iter = insert + 1;
			}
		}

		// split string to words
		stringstream ss(str);
		string tmp;
		vector<string> v;
		while (ss >> tmp) v.push_back(tmp);

		// return original substring
		if (*(v.begin()) == "Write") 
			for (auto iter = v.begin(); iter != v.end(); iter++)
				if (*iter == "ThereWasASubstringHere") 
				{
					*iter = substring;
					break;
				}
		
		for (auto iter = v.begin(); iter != v.end(); iter++) 
			hierlist->InsertDown(*iter);
	}

	return hierlist;
}
