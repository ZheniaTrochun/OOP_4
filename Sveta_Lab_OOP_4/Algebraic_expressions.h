#pragma once

#include <string>

using namespace std;

class Algebraic_expressions
{
private:
	string expression;
	string *elements;

	string* parseStr(int*);
	string findIntegral(string*, int);
public:
	Algebraic_expressions(string);
	Algebraic_expressions(char*);
	Algebraic_expressions();

	string getExpression();

	Algebraic_expressions operator - ();
	Algebraic_expressions operator + (Algebraic_expressions);
	Algebraic_expressions operator - (Algebraic_expressions);
	Algebraic_expressions operator ! ();

	~Algebraic_expressions();
};

