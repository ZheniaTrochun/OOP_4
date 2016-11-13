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
	string str = expression;	// temp string with expression

	string *parseArr = new string[str.length()]; // temp array

	*counter = 0;	// counter of len resulying array

	for (int i(0); i < str.length(); i++)
	{
		if (str.at(i) == '-')	// if we found '-' we replace it with "+ -"
		{
			str = str.substr(0, i) + "+ -" + str.substr(i + 2, 1024);
			i += 3;
		}
	}

	// split str by delim " + " to temp array
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

	// make result array of right len
	string *ret = new string[*counter + 1];

	for (int i(0); i < *counter; i++)
	{
		ret[i] = parseArr[i];
	}

	return ret;
}

string Algebraic_expressions::findIntegral(string* str, int counter)
{
	string result; // resulting string
	string *resArr = new string[counter]; // arr for resulting strings
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
		if (str[i].at(0) == '-')					//
		{											// check for negative operands
			resArr[i] += "- ";						// just add "- " to the rusult array[i]
			str[i] = str[i].substr(1, 1024);		// remove "-" from input string array 
		}
	}

	for (int i(0); i < counter; i++)
	{
		if (str[i] == "") continue;					// kostil' na vsiakii vipadok

		if (isdigit(str[i].at(0)))					// if first char at string is number
		{
			bool check = true;	// flag for checking is full str[i] number
			int index = 0;		// if not all str[i] number - index of "*"

			for (int j(1); j < str[i].length(); j++)
			{
				if(!isdigit(str[i].at(j)) && str[i].at(j) != '.')	// if not number
				{			
					check =	false;
				}
				if (str[i].at(j) == '*')							// if after number "*" index = j
				{
					index = j;
				}
			}

			if (check)												// if all str[i] number
			{
				resArr[i] += str[i] + "*x";
				str[i] = "";
			}

			if (index != 0)											// if not <number>*<expression>
			{
				resArr[i] += str[i].substr(0, index + 1);
				str[i] = str[i].substr(index + 1, 1024);
			}
		}
	}

	for (int i(0); i < counter; i++)
	{
		if (str[i].find("x^(") == 0)								// if it's x^(<number>)
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

			if (!check)												// if <number> not number
			{
				resArr[i] += "";
			}
			
			if (check)												// if all good we make intergation
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
			if (str[i].compare(expr[j]) == 0)						// integration of parts of str from simple integrals table
			{
				resArr[i] += integr[j];
				str[i] = "";
			}
		}
	}


	// concatenation of resulting arrays into rusult string
	for (int i(0); i < counter; i++)
	{
		if (!str[i].empty())										// if we can't integrate expression we just weite this
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

	result += " + C"; // add " + C" at the end
	

	// make result string pretty
	while ((result.find("- -") != string::npos) || (result.find("- +") != string::npos) || (result.find("+ -") != string::npos))
	{
		if (result.find("- -") != string::npos)
			result = result.replace(result.find("- -"), sizeof("+") + 1, "+");

		if (result.find("- +") != string::npos)
			result = result.replace(result.find("- +"), sizeof("-") + 1, "-");

		if (result.find("+ -") != string::npos)
			result = result.replace(result.find("+ -"), sizeof("-") + 1, "-");
	}


	return result;
}


// Destrustor
Algebraic_expressions::~Algebraic_expressions()
{
}
