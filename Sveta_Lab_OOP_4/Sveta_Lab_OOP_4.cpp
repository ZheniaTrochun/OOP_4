// Sveta_Lab_OOP_4.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Algebraic_expressions.h"
#include <iostream>

int main()
{
	Algebraic_expressions e1("x^(2) + 5");

	Algebraic_expressions e2("7 + 2*cos(x) - 3*x^(2) - sin(x)");

	Algebraic_expressions e3 = -e1;

	Algebraic_expressions e4 = e1 + e2;

	Algebraic_expressions e5 = e1 - e2;

	Algebraic_expressions e6 = !e2;

	cout << e2.getExpression() << endl;
	cout << e6.getExpression() << endl;

	system("pause");

    return 0;
}

