#include "stdafx.h"
#include "Algebraic_expressions.h"


Algebraic_expressions::Algebraic_expressions()
{
	expression = "";
}

Algebraic_expressions::Algebraic_expressions(string str)
{
	//for (int i(0); i < str.length(); i++)
	//{
	//	expression[i] = str[i];
	//}
	expression = str;
}

Algebraic_expressions::Algebraic_expressions(char *str)
{
	//for (int i(0); i < strlen(str); i++)
	//{
	//	expression[i] = str[i];
	//}
	string exp(str);
	expression = exp;
}

string Algebraic_expressions::getExpression() 
{
	return expression;
}

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

Algebraic_expressions::~Algebraic_expressions()
{
}
