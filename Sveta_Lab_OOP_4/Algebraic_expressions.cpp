#include "stdafx.h"
#include "Algebraic_expressions.h"

// Constructros
Algebraic_expressions::Algebraic_expressions()
{
	expression = "";
}

Algebraic_expressions::Algebraic_expressions(string str)
{
	expression = str;
}

Algebraic_expressions::Algebraic_expressions(char *str)
{
	string exp(str);
	expression = exp;
}


// Getters / setters
string Algebraic_expressions::getExpression() 
{
	return expression;
}


// Operators
Algebraic_expressions Algebraic_expressions::operator-()
{
	Algebraic_expressions reverseExpression("- (" + expression + ")");
	return reverseExpression;
}

Algebraic_expressions Algebraic_expressions::operator+(Algebraic_expressions newExpression)
{
	Algebraic_expressions sumExpression(expression + " + (" + newExpression.getExpression() + ")");
	return sumExpression;
}

Algebraic_expressions Algebraic_expressions::operator-(Algebraic_expressions newExpression)
{
	Algebraic_expressions subExpression(expression + " - (" + newExpression.getExpression() + ")");
	return subExpression;
}

Algebraic_expressions Algebraic_expressions::operator!()
{
	string *parseResults;
	string integral;
	int counter = 0;

	parseResults = parseStr(&counter);

	integral = findIntegral(parseResults, counter);

	Algebraic_expressions ae(integral);

	return ae;
}


// Private functions
string* Algebraic_expressions::parseStr(int *counter)
{
	string str = expression;
	string *parseArr = new string[str.length()];
	*counter = 0;

	for (int i(0); i < str.length(); i++)
	{
		if (str.at(i) == '-')
		{
			str = str.substr(0, i) + "+ -" + str.substr(i + 2, 1024);
			i += 3;
		}
	}

	while (true)
	{
		int pos = str.find(" + ");

		if (pos == string::npos)
		{

			break;
		}

		parseArr[*counter] = str.substr(0, pos);
		str = str.substr(pos + 3, 1024);
		*counter += 1;
	}

	parseArr[*counter] = str;
	*counter += 1;

	string *ret = new string[*counter + 1];

	for (int i(0); i < *counter; i++)
	{
		ret[i] = parseArr[i];
	}

	return ret;
}

string Algebraic_expressions::findIntegral(string* str, int counter)
{
	string result;
	string *resArr = new string[counter]; // arr jf resulting strings
	string *expr = new string[10]; // arr for expressions
	string *integr = new string[10]; // arr for integrals of expressions
	expr[0] = "exp(x)";
	expr[1] = "x^(1/2)";
	expr[2] = "cos(x)";
	expr[3] = "sin(x)";
	expr[4] = "1/cos(x)^2";
	expr[5] = "1/sin(x)^2";
	expr[6] = "1/((1-x^2)^(1/2))";
	expr[7] = "1/(1+x^2)";
	expr[8] = "1/sin(x)";
	expr[9] = "1/cos(x)";

	integr[0] = "exp(x)";
	integr[1] = "ln(x)";
	integr[2] = "sin(x)";
	integr[3] = "- cos(x)";
	integr[4] = "tg(x)";
	integr[5] = "- ctg(x)";
	integr[6] = "arcsin(x)";
	integr[7] = "arctg(x)";
	integr[8] = "ln|(1-cos(x))/(sin(x))|";
	integr[9] = "ln|(1+sin(x))/(cos(x))|";
	// ...

	for (int i(0); i < counter; i++) 
	{
		if (str[i].at(0) == '-')
		{
			resArr[i] += "- ";
			str[i] = str[i].substr(1, 1024);
		}
	}

	for (int i(0); i < counter; i++)
	{
		if (str[i] == "") continue;
		if (isdigit(str[i].at(0)))
		{
			bool check = true;
			int index = 0;

			for (int j(1); j < str[i].length(); j++)
			{
				if(!isdigit(str[i].at(j)) && str[i].at(j) != '.')
				{
					check = false;
				}
				if (str[i].at(j) == '*')
				{
					index = j;
				}
			}

			if (check)
			{
				resArr[i] += str[i] + "*x";
				str[i] = "";
			}

			if (index != 0)
			{
				resArr[i] += str[i].substr(0, index + 1);
				str[i] = str[i].substr(index + 1, 1024);
			}
		}
	}

	for (int i(0); i < counter; i++)
	{
		int ind = str[i].find("x^(");
		if (ind == 0)
		{
			string tmp = str[i].substr(3, str[i].length() - 4);
			bool check = true;

			for (int j(0); j < tmp.length(); j++)
			{
				if (!isdigit(tmp.at(j)))
				{
					check = false;
					break;
				}
			}

			if (!check)
			{
				resArr[i] += "";
			}
			
			if (check)
			{
				const char *charArr = tmp.c_str();
				char buf[1024];
				int num = atoi(charArr);
				num++;
				resArr[i] += "(x^(";
				resArr[i] += itoa(num, buf, 1024);
				resArr[i] += "))/";
				resArr[i] += itoa(num, buf, 1024);
				str[i] = "";
			}
		}
	}

	for (int i(0); i < counter; i++)
	{
		for (int j(0); j < 10; j++)
		{
			if (str[i].compare(expr[j]) == 0)
			{
				resArr[i] += integr[j];
				str[i] = "";
			}
		}
	}

	for (int i(0); i < counter; i++)
	{
		if (!str[i].empty())
		{
			resArr[i] += "integral_of(" + str[i] + ")";
		}

		if (i == 0)
		{
			result += resArr[i];
		}
		else
		{
			if (resArr[i].at(0) == '-')
				result += " " + resArr[i];
			else
				result += " + " + resArr[i];
		}
	}

	result += " + C";
	
	while(result.find("- -") != string::npos)
		result = result.replace(result.find("- -"), sizeof("+") + 1, "+");

	while (result.find("- +") != string::npos)
		result = result.replace(result.find("- +"), sizeof("-") + 1, "-");

	while (result.find("+ -") != string::npos)
		result = result.replace(result.find("- -"), sizeof("-") + 1, "-");

	return result;
}


// Destrustor
Algebraic_expressions::~Algebraic_expressions()
{
}
