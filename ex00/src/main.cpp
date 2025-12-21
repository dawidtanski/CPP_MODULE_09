#include "../inc/BitcoinExchange.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]){

	if (argc != 2){
		std::cerr << "Wrong number of arguments!" << std::endl;
		return 1;
	}
	std::ifstream file;
	file.open(argv[1]);
	if (!file.is_open()){
		std::cerr << "Cannot open the file!" << std::endl;
		return 1;
	}

	return 0;
}