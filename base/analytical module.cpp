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
		if (find(str.begin(), str.end(), "const") != str.end()) {
			it++;
			str = *it;
			while ((find(str.begin(), str.end(), "const") == str.end())
				&& (find(str.begin(), str.end(), "var") == str.end())
				&& (find(str.begin(), str.end(), "begin") == str.end())) 
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
		if (find(str.begin(), str.end(), "var") != str.end()) {
			it++;
			str = *it;
			while ((find(str.begin(), str.end(), "const") == str.end())
				&& (find(str.begin(), str.end(), "var") == str.end())
				&& (find(str.begin(), str.end(), "begin") == str.end()))
			{
				for (auto i = str.begin(); i != str.end(); i++)
					if (*i == ':' || *i == ';') *i = ' ';

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
		if (find(str.begin(), str.end(), "begin") != str.end()) {
			flag_begin_end++;
			continue;
		}
		if (find(str.begin(), str.end(), "end") != str.end()) {
			flag_begin_end--;
			continue;
		}

		// if then flag
		if (find(str.begin(), str.end(), "if") != str.end()) flag_if_then++;
		if (find(str.begin(), str.end(), "then") != str.end()) flag_if_then--;

		// uninitialized var don't use
		auto assignment_pos = find(str.begin(), str.end(), ":=");
		if (assignment_pos != str.end())
		{
			short pos = distance(str.begin(), assignment_pos);
			string initvar;
			for each (string var in uninitialized_var)
			{
				auto var_pos = find(str.begin(), str.end(), var);
				if (var_pos != str.end() && distance(str.begin(), var_pos) > pos) 
				{
					if (distance(str.begin(), var_pos) > pos)
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

HierList<string> AnalyticalMod::CreateHierList()
{
	HierList<string> hierlist;
	string str;

	for (auto it = text.begin(); it != text.end(); it++)
	{
		hierlist.InsertNext(*it);
		hierlist.GoNext();

		str = *it;

		string substring;

		// if str contains substring
		if (find(str.begin(), str.end(), "Write") != str.end()) 
		{
			// separating first "(" from the previos and next word
			auto insert = find(str.begin(), str.end(), '(');
			str.replace(insert, insert + 1, " ( ");

			string tmp;
			// separating last ")" from the previos and next word
			tmp = ')';
			insert = find_end(str.begin(), str.end(), tmp.begin(), tmp.end());
			str.replace(insert, insert + 1, " ) ");

			// separating "," after substring from the previos word
			tmp = '"';
			auto endOfStr = find_end(str.begin(), str.end(), tmp.begin(), tmp.end());
			auto iter = endOfStr;
			while ((insert = find(iter, str.end(), ',')) != str.end())
			{
				str.replace(insert, insert + 1, " ,");
				insert = find(insert, str.end(), ',');
				iter = insert + 1;
			}

			// save substring
			auto beginOfStr = find(str.begin(), str.end(), '"');
			substring = str.substr(str.find('"'), distance(beginOfStr, endOfStr) + 1);
			str.replace(beginOfStr, endOfStr + 1, "//ThereWasASubstringHere");
		}
		// str without substring
		else 
		{
			auto iter = str.begin();
			auto insert = iter;

			// separating "," from the previos word
			while ((insert = find(iter, str.end(), ',')) != str.end())
			{
				str.replace(insert, insert + 1, " ,");
				insert = find(insert, str.end(), ',');
				iter = insert + 1;
			}

			// separating ";" from the previos word
			iter = str.begin();
			while ((insert = find(iter, str.end(), ';')) != str.end())
			{
				str.replace(insert, insert + 1, " ;");
				insert = find(insert, str.end(), ';');
				iter = insert + 1;
			}

			// separating ":" from the previos word
			iter = str.begin();
			while ((insert = find(iter, str.end(), ':')) != str.end())
			{
				str.replace(insert, insert + 1, " :");
				insert = find(insert, str.end(), ':');
				iter = insert + 1;
			}

			// separating "(" from the previos and next word
			iter = str.begin();
			while ((insert = find(iter, str.end(), '(')) != str.end())
			{
				str.replace(insert, insert + 1, " ( ");
				insert = find(insert, str.end(), '(');
				iter = insert + 1;
			}

			// separating ")" from the previos and next word
			iter = str.begin();
			while ((insert = find(iter, str.end(), ')')) != str.end())
			{
				str.replace(insert, insert + 1, " ) ");
				insert = find(insert, str.end(), ')');
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
				if (*iter == "//ThereWasASubstringHere") 
				{
					*iter = substring;
					break;
				}
		
		for (auto iter = v.begin(); iter != v.end(); iter++) 
			hierlist.InsertDown(*iter);
	}

	return hierlist;
}
