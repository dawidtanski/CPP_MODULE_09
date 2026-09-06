#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <deque>
#include <iterator>
#include <string>
#include <vector>

class PmergeMe
{
private:
	template <typename T>
	void mergeInsertionSort(T &container, int pairLevel);

	template <typename T>
	void swapPair(T iterator, int pairLevel);

public:
	PmergeMe();
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	~PmergeMe();

	void sortVector(std::vector<int> &values);
	void sortDeque(std::deque<int> &values);
	bool parseArguments(int argc, char **argv,
		std::vector<int> &vectorValues, std::deque<int> &dequeValues) const;
	static long nbr_of_comps;

private:
	bool parsePositiveInteger(const std::string &text, int &value) const;
};

long jacobsthalNumber(long index);

template <typename T>
bool compareValues(T left, T right)
{
	++PmergeMe::nbr_of_comps;
	return *left < *right;
}

template <typename T>
T iteratorAt(T iterator, int steps)
{
	std::advance(iterator, steps);
	return iterator;
}

// Swap complete groups, not only their key values. This preserves every pair
// and every higher-level group while the recursion changes their order.
template <typename T>
void PmergeMe::swapPair(T iterator, int pairLevel)
{
	T start = iteratorAt(iterator, -pairLevel + 1);
	T end = iteratorAt(start, pairLevel);
	while (start != end)
	{
		std::iter_swap(start, iteratorAt(start, pairLevel));
		++start;
	}
}

// Perform one Ford-Johnson recursion level. pairLevel tells us how many
// consecutive values form one logical element at this level.
template <typename T>
void PmergeMe::mergeInsertionSort(T &container, int pairLevel)
{
	typename T::iterator iterator;
	typename T::iterator last;
	typename T::iterator end;
	std::vector<typename T::iterator> mainChain;
	std::vector<typename T::iterator> pending;
	int pairUnits;
	bool oddPair;
	int jump;
	int previousJacobsthal;
	int insertedCount;
	int k;
	int currentJacobsthal;
	int difference;
	int times;
	int offset;
	int boundIndex;
	int i;

	pairUnits = static_cast<int>(container.size()) / pairLevel;
	if (pairUnits < 2)
		return;
	oddPair = (pairUnits % 2 == 1);
	last = iteratorAt(container.begin(), pairLevel * pairUnits);
	end = iteratorAt(last, -(oddPair * pairLevel));

	// Compare the last value of each group and swap the complete groups when
	// necessary. Then recurse with groups twice as large.
	jump = 2 * pairLevel;
	for (iterator = container.begin(); iterator != end;
		std::advance(iterator, jump))
	{
		typename T::iterator leftGroup = iteratorAt(iterator, pairLevel - 1);
		typename T::iterator rightGroup = iteratorAt(iterator, pairLevel * 2 - 1);
		if (compareValues(rightGroup, leftGroup))
			swapPair(leftGroup, pairLevel);
	}
	mergeInsertionSort(container, pairLevel * 2);

	// The first pair is {b1, a1}. The remaining a-elements go to mainChain,
	// while the remaining b-elements wait in pending.
	mainChain.push_back(iteratorAt(container.begin(), pairLevel - 1));
	mainChain.push_back(iteratorAt(container.begin(), pairLevel * 2 - 1));
	for (i = 4; i <= pairUnits; i += 2)
	{
		pending.push_back(iteratorAt(container.begin(), pairLevel * (i - 1) - 1));
		mainChain.push_back(iteratorAt(container.begin(), pairLevel * i - 1));
	}
	if (oddPair)
		pending.push_back(iteratorAt(end, pairLevel - 1));

	// Insert Jacobsthal groups in reverse order: b3,b2; b5,b4; b11...b6.
	previousJacobsthal = static_cast<int>(jacobsthalNumber(1));
	insertedCount = 0;
	for (k = 2;; ++k)
	{
		currentJacobsthal = static_cast<int>(jacobsthalNumber(k));
		difference = currentJacobsthal - previousJacobsthal;
		if (difference > static_cast<int>(pending.size()))
			break;
		times = difference;
		offset = 0;
		typename std::vector<typename T::iterator>::iterator pendIterator;
		typename std::vector<typename T::iterator>::iterator boundIterator;
		pendIterator = iteratorAt(pending.begin(), difference - 1);
		boundIndex = currentJacobsthal + insertedCount;
		boundIterator = iteratorAt(mainChain.begin(), boundIndex);
		while (times > 0)
		{
			typename std::vector<typename T::iterator>::iterator insertAt;
			typename std::vector<typename T::iterator>::iterator inserted;
			insertAt = std::upper_bound(mainChain.begin(), boundIterator,
				*pendIterator, compareValues<typename T::iterator>);
			inserted = mainChain.insert(insertAt, *pendIterator);
			--times;
			pendIterator = pending.erase(pendIterator);
			std::advance(pendIterator, -1);
			if (static_cast<int>(inserted - mainChain.begin()) == boundIndex)
				++offset;
			boundIterator = iteratorAt(mainChain.begin(),
				boundIndex - offset);
		}
		previousJacobsthal = currentJacobsthal;
		insertedCount += difference;
	}

	// Insert whatever remains from right to left. Each pending group is still
	// bounded by its matching a-group, so the binary search stays restricted.
	for (i = static_cast<int>(pending.size()) - 1; i >= 0; --i)
	{
		typename std::vector<typename T::iterator>::iterator currentPending;
		typename std::vector<typename T::iterator>::iterator currentBound;
		currentPending = iteratorAt(pending.begin(), i);
		boundIndex = static_cast<int>(mainChain.size())
			- static_cast<int>(pending.size()) + i + (oddPair ? 1 : 0);
		currentBound = iteratorAt(mainChain.begin(), boundIndex);
		mainChain.insert(std::upper_bound(mainChain.begin(), currentBound,
			*currentPending, compareValues<typename T::iterator>), *currentPending);
	}

	// Rebuild the original container from the reordered groups. The iterators
	// point into the same storage, so copy values only after mainChain is ready.
	std::vector<int> sorted;
	sorted.reserve(container.size());
	for (typename std::vector<typename T::iterator>::iterator group = mainChain.begin();
		group != mainChain.end(); ++group)
	{
		for (i = 0; i < pairLevel; ++i)
		{
			typename T::iterator value = *group;
			std::advance(value, -pairLevel + i + 1);
			sorted.push_back(*value);
		}
	}
	iterator = container.begin();
	for (typename std::vector<int>::iterator value = sorted.begin();
		value != sorted.end(); ++value, ++iterator)
		*iterator = *value;
}

#endif
