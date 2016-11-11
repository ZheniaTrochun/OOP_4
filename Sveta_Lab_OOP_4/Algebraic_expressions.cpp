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

	Algebraic_expressions ae;

	return ae;
}


// Private functions
string* Algebraic_expressions::parseStr(string str)
{
	string *parseArr = new string[str.length()];
	int counter = 0;

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

		parseArr[counter] = str.substr(0, pos);
		str = str.substr(pos + 3, 1024);
		counter++;
	}

	parseArr[counter] = str;
	counter++;

	string *ret = new string[counter + 1];

	for (int i(0); i < counter; i++)
	{
		ret[i] = parseArr[i];
	}

	return ret;
}


// Destrustor
Algebraic_expressions::~Algebraic_expressions()
{
}
