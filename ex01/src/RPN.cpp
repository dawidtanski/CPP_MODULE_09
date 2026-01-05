#include "../inc/RPN.hpp"

// Orthodox Canonical Form
RPN::RPN() : _hasError(false) {
}

RPN::RPN(const RPN& other) {
	_stack = other._stack;
}

RPN& RPN::operator=(const RPN& other) {
	if (this != &other) {
		_stack = other._stack;
	}
	return *this;
}

RPN::~RPN() {}

//////////////////////

Token RPN::initToken(std::string tokenType, char tknValue){

	Token tkn;
	
	if (tokenType == "NUMBER"){
		tkn.value = static_cast<double>(tknValue - '0');
	}
	else if (tokenType == "OPERATOR"){
		tkn.op = tknValue;
	}
	else{
		std::cerr << "Wrong token type" << std::endl;
	}
	return tkn;
}

bool RPN::isOperator(char c){
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return true;
	else
		return false;
}

double RPN::useOperator(char op, double a, double b){
	switch(op){
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			if (b == 0){
				std::cerr << "Cant divide by 0" << std::endl;
				return -1.0;
			}
			return a / b;
		default:
			return 0.0;
	}

}

bool RPN::hasError() const {
	return _hasError;
}

void RPN::calculate(char op){
	if (_stack.size() < 2){
		std::cerr << "Error: not enough operands" << std::endl;
		_hasError = true;
		return;
	}
	
	Token lastTKN = _stack.top();
	_stack.pop();
	Token prevTKN = _stack.top();
	_stack.pop();
	
	double res = useOperator(op, prevTKN.value, lastTKN.value);
	
	// Push result back to stack
	Token resultToken = initToken("NUMBER", '0');
	resultToken.value = res;
	_stack.push(resultToken);
}


double	RPN::parse(std::string equation){
	int i = 0;

	while (equation[i]){
		if (equation[i] == ' '){
			i++;
			continue;
		}
		if (isdigit(equation[i])){
			Token tkn = initToken("NUMBER", equation[i]);
			_stack.push(tkn);
		}
		else if (isOperator(equation[i]))
			calculate(equation[i]);
		else{
			std::cerr << "Error: invalid character '" << equation[i] << "'" << std::endl;
			_hasError = true;
			return -1;
		}
		i++;
	}
	
	if (_stack.size() != 1){
		std::cerr << "Error: invalid expression" << std::endl;
		_hasError = true;
		return 0;
	}
	
	return _stack.top().value;
}