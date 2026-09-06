#include "../inc/PmergeMe.hpp"

#include <ctime>
#include <iostream>

static void printVector(const std::vector<int> &values)
{
	for (std::vector<int>::const_iterator it = values.begin(); it != values.end(); ++it)
		std::cout << " " << *it;
}

int main(int argc, char **argv)
{
	PmergeMe sorter;
	std::vector<int> vectorValues;
	std::deque<int> dequeValues;
	std::clock_t vectorStart;
	std::clock_t vectorEnd;
	std::clock_t dequeStart;
	std::clock_t dequeEnd;
	double vectorTime;
	double dequeTime;
	long vectorComparisons;
	long dequeComparisons;

	// Parse the arguments and build both required container representations.
	if (!sorter.parseArguments(argc, argv, vectorValues, dequeValues))
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}
	std::cout << "Before:";
	printVector(vectorValues);
	std::cout << std::endl;

	// Measure the complete vector operation, including its data management.
	PmergeMe::nbr_of_comps = 0;
	vectorStart = std::clock();
	sorter.sortVector(vectorValues);
	vectorEnd = std::clock();
	vectorComparisons = PmergeMe::nbr_of_comps;

	// Measure the complete deque operation independently.
	PmergeMe::nbr_of_comps = 0;
	dequeStart = std::clock();
	sorter.sortDeque(dequeValues);
	dequeEnd = std::clock();
	dequeComparisons = PmergeMe::nbr_of_comps;

	vectorTime = static_cast<double>(vectorEnd - vectorStart)
		* 1000000.0 / CLOCKS_PER_SEC;
	dequeTime = static_cast<double>(dequeEnd - dequeStart)
		* 1000000.0 / CLOCKS_PER_SEC;

	std::cout << "After:";
	printVector(vectorValues);
	std::cout << std::endl;
	std::cout << "Time to process a range of " << vectorValues.size()
		<< " elements with std::vector : " << vectorTime << " us"
		<< " (comparisons: " << vectorComparisons << ")" << std::endl;
	std::cout << "Time to process a range of " << dequeValues.size()
		<< " elements with std::deque : " << dequeTime << " us"
		<< " (comparisons: " << dequeComparisons << ")" << std::endl;
	return 0;
}