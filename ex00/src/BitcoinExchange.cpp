#include "../inc/BitcoinExchange.hpp"

// Orthodox Canonical Form
BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
	_database = other._database;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other) {
		_database = other._database;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void	BitcoinExchange::mapPush(std::string date, float price){
	_database[date] = price;
}

void	BitcoinExchange::mapIterCout() const{
	for (std::map<std::string, float>::const_iterator it = _database.begin(); it != _database.end(); ++it){
		std::cout << "Bitcoin price at: " << it->first << " is: " << it->second << std::endl; 
	}
}

// void BitcoinExchange::loadData(std::fstream filestream){
// 	std::string date;

// 	std::getline(filestream, date, '|');
// }