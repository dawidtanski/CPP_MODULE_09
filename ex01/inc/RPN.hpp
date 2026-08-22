#pragma once

#include <iostream>
#include <stack>
#include <cctype>

struct Token {
	enum Type { NUMBER, OPERATOR, INVALID } type;
	double value;
	char op;
};

class RPN{

	private:
		std::stack<Token> _stack;
		bool _hasError;
	
	public:

	// Orthodox Canonical Form
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();



		Token initToken(std::string tokenType, char tknValue);
		double	parse(std::string equation);
		bool isOperator(char c);
		void calculate(char op);
		double useOperator(char op, double a, double b);
	bool hasError() const;
};
