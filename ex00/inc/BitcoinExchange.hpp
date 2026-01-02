#pragma once

#include <iostream>
#include <map>
#include <string>

class BitcoinExchange{

private:
	std::map<std::string, float> _database;

public:
    // Orthodox Canonical Form
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

	void loadData(std::fstream filestream);
	void mapPush(std::string date, float price);
	void mapIterCout() const;
	float getExchangeRate(std::string date);
};