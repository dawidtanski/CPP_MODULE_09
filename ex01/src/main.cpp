#include "../inc/RPN.hpp"


int main(int argc, char *argv[]){

	if (argc != 2){
		std::cerr << "Wrong number of arguments!" << std::endl;
		return 1;
	}
	RPN rpn;
	std::string input(argv[1]);
	double result = rpn.parse(input);
	if (!rpn.hasError())
		std::cout << result << std::endl;
	return 0;
}