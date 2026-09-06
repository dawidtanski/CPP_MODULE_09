#include "../inc/PmergeMe.hpp"

#include <cerrno>
#include <climits>
#include <cstdlib>

long PmergeMe::nbr_of_comps = 0;

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
	(void)other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
		(void)other;
	return *this;
}

PmergeMe::~PmergeMe()
{
}

// Convert one command-line argument and reject signs, decimals, suffixes and overflow.
bool PmergeMe::parsePositiveInteger(const std::string &text, int &value) const
{
	char *end;
	long parsed;

	if (text.empty() || text[0] == '-' || text[0] == '+')
		return false;
	errno = 0;
	parsed = std::strtol(text.c_str(), &end, 10);
	if (end == text.c_str() || *end != '\0' || errno == ERANGE)
		return false;
	if (parsed <= 0 || parsed > INT_MAX)
		return false;
	value = static_cast<int>(parsed);
	return true;
}

// Parse once and copy the same validated sequence into both containers.
bool PmergeMe::parseArguments(int argc, char **argv,
	std::vector<int> &vectorValues, std::deque<int> &dequeValues) const
{
	int value;

	if (argc < 2)
		return false;
	for (int index = 1; index < argc; ++index)
	{
		if (!parsePositiveInteger(argv[index], value))
			return false;
		vectorValues.push_back(value);
		dequeValues.push_back(value);
	}
	return true;
}

// Jacobsthal numbers used by merge-insertion sort, starting with 1, 3, 5, 11.
long jacobsthalNumber(long index)
{
	double value = (std::pow(2.0, index + 1)
		+ std::pow(-1.0, index)) / 3.0;
	return static_cast<long>(std::floor(value + 0.5));
}

// Public entry point for the vector implementation.
void PmergeMe::sortVector(std::vector<int> &values)
{
	mergeInsertionSort(values, 1);
}

// Public entry point for the deque implementation.
void PmergeMe::sortDeque(std::deque<int> &values)
{
	mergeInsertionSort(values, 1);
}
