#include "../inc/BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>


int main(int argc, char *argv[]){

	BitcoinExchange btcEx;
	std::string line;

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
	if (!std::getline(file, line))
		return 1;
	while (std::getline(file, line)){
		if (line.empty())
			continue;

		size_t pos = line.find(" | ");
		if (pos == std::string::npos){
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		std::string date = line.substr(0, pos);
		std::string valueStr = line.substr(pos + 3);

		float value = atof(valueStr.c_str());
		
		if (!dateValidation(date)) {
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}
		
		if (!valueValidation(value))
			continue;
		
		float exchangeRate = btcEx.getClosestRate(date);
		std::cout << date << " => " << value << " = " << (exchangeRate * value) << std::endl;
		}
	// btcEx.mapIterCout();

	return 0;
}