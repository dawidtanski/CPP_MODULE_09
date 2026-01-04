#pragma once

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <cstdlib>

class BitcoinExchange{

private:
	std::multimap<std::string, float> _database;
	std::multimap<std::string, float> _databaseCSV;

public:
    // Orthodox Canonical Form
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

	void loadData();
	void mapPush(std::string date, float value);
	void mapIterCout() const;
	float getExchangeRate(std::string date);
	float	getClosestRate(std::string date);
};


// Helpers
int dateToInt(const std::string &s);
bool isNumber(const std::string &s);
bool dateValidation(std::string date);
bool valueValidation(float value);