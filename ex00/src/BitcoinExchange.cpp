#include "../inc/BitcoinExchange.hpp"

// Orthodox Canonical Form
BitcoinExchange::BitcoinExchange() {
	loadData();
}

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

void	BitcoinExchange::mapPush(std::string date, float value){
	_database.insert(std::make_pair(date, value));
}

void	BitcoinExchange::mapIterCout() const{
	for (std::map<std::string, float>::const_iterator it = _database.begin(); it != _database.end(); ++it){
		std::cout << "Bitcoin price at: " << it->first << " is: " << it->second << std::endl; 
	}
}

void BitcoinExchange::loadData(){
	std::ifstream file;
	file.open("data.csv");
	if (!file.is_open()){
		std::cerr << "Cannot open the file!" << std::endl;
		return ;
	}

	std::string line;
	if (!std::getline(file, line))
		return ;
	while (std::getline(file, line)){
			if (line.empty())
				continue;
		size_t pos = line.find(",");
		if (pos == std::string::npos){
			// std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		std::string date = line.substr(0, pos);
		std::string valueStr = line.substr(pos + 1);
		float value = atof(valueStr.c_str());
		if (!dateValidation(date))
			continue;
		if (value < 0)
			continue;
		_databaseCSV.insert(std::make_pair(date, value));
	}

}

float	BitcoinExchange::getClosestRate(std::string date){
	if (_databaseCSV.empty())
		return 0;
	
	std::multimap<std::string, float>::iterator it = _databaseCSV.lower_bound(date);

	if (it != _databaseCSV.end() && it->first == date)
		return it->second;
	

	if (it == _databaseCSV.end()) {
		--it;
		return it->second;
	}
	
	if (it == _databaseCSV.begin())
		return 0;
	

	--it;
	return it->second;
}





/// Helpers

int dateToInt(const std::string &s)
{
	int y = (s[0]-'0')*1000 + (s[1]-'0')*100
		+ (s[2]-'0')*10   + (s[3]-'0');
	int m = (s[5]-'0')*10   + (s[6]-'0');
	int d = (s[8]-'0')*10   + (s[9]-'0');

	return y * 10000 + m * 100 + d;
}

bool isNumber(const std::string &s)
{
    char *end;
    strtol(s.c_str(), &end, 10);
    return end != s.c_str() && *end == '\0';
}

bool	dateValidation(std::string date){
	if (date.length() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;
	std::string datecp = date;
	datecp.erase(7,1);
	datecp.erase(4,1);
	if (!isNumber(datecp))
		return false;
	if ((1000 * (date[0] - '0') + 100 * (date[1] - '0')
	+ 10 * (date[2] - '0') + (date[3] - '0')) > 2026 ||
	(1000 * (date[0] - '0') + 100 * (date[1] - '0')
	+ 10 * (date[2] - '0') + (date[3] - '0')) <= 0)
		return false;
	if ((10 * (date[5] - '0') + (date[6] - '0')) > 12 || 
		(10 * (date[5] - '0') + (date[6] - '0')) <= 0)
		return false;
	if ((10 * (date[8] - '0') + (date[9] - '0')) > 31 || 
		(10 * (date[8] - '0') + (date[9] - '0')) <= 0)
		return false;
	// std::cout << "Date-month-day valid format" << std::endl;
	return true;
}

bool valueValidation(float value){
	if (value < 0){
		std::cerr << "Error: not a positive number" << std::endl;
		return false;
	}
	if (value > 1000){
		std::cerr << "Error: too large a number" << std::endl;
		return false;
	}
	return true;
}