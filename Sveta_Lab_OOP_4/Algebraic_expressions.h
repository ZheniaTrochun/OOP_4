#pragma once

#include <string>
#include <math.h>

using namespace std;

class Algebraic_expressions
{
private:
	string expression;
	string *elements;

	string* parseStr(int*);
	string findIntegral(string*, int);
	
	// utils
	string prettyStr(string);
	int makeDigit(string);
	string makeString(int);

public:
	Algebraic_expressions(string);
	Algebraic_expressions(char*);
	Algebraic_expressions();

	string getExpression();

	string optimize(string);

	Algebraic_expressions operator - ();
	Algebraic_expressions operator + (Algebraic_expressions);
	Algebraic_expressions operator - (Algebraic_expressions);
	Algebraic_expressions operator ! ();

	~Algebraic_expressions();
};

