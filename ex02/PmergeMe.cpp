
#include "PmergeMe.hpp"

#include <string>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <cassert>

#include <iostream>

PmergeMe::PmergeMe(int argc, char** argv)
  : numComparisons_(0)
{
  populate(argc, argv);
}

PmergeMe::~PmergeMe() {}

void PmergeMe::sort()
{
  assert(calculateMaxComparisons(4) == 5);
  assert(calculateMaxComparisons(5) == 7);
  assert(calculateMaxComparisons(21) == 66);

  fordJohnsonDeque(deq_.size(), 1);
  fordJohnsonList(list_.size(), 1);
  
  std::cout << "Max allowed comparisons: " << calculateMaxComparisons(deq_.size()) << "\nPerformed comparisons: " << numComparisons_ << "\n";
}

void PmergeMe::populate(int argc, char** argv)
{
  for (int i = 1; i < argc; ++i)
  {
    int current = 0;
    std::istringstream iss(argv[i]);
    iss >> current;
    if (iss.fail() || !iss.eof() || current < 0)
    {
      throw std::runtime_error(std::string("invalid input: ") + argv[i]);
    }
    list_.push_back(current);
    deq_.push_back(current);
  }
  assert(deq_.size() == list_.size());
  assert(deq_.size() == static_cast<unsigned long>(argc - 1));
}

void PmergeMe::fordJohnsonDeque(int numElements, int sizeElements)
{
  if (numElements == 1)
  {
    return;
  }
  pairWiseSortDeque(numElements, sizeElements);
  fordJohnsonDeque(numElements / 2, sizeElements * 2);
  binaryInsertionDeque(numElements, sizeElements);
}

void PmergeMe::pairWiseSortDeque(int numElements, int sizeElements)
{
  (void)numElements; (void)sizeElements;
}

void PmergeMe::binaryInsertionDeque(int numElements, int sizeElements)
{
  (void)numElements; (void)sizeElements;
}

void PmergeMe::fordJohnsonList(int numElements, int sizeElements)
{
  if (numElements == 1)
  {
    return;
  }
  pairWiseSortList(numElements, sizeElements);
  fordJohnsonList(numElements / 2, sizeElements * 2);
  binaryInsertionList(numElements, sizeElements);
}

void PmergeMe::pairWiseSortList(int numElements, int sizeElements)
{
  (void)numElements; (void)sizeElements;
}

void PmergeMe::binaryInsertionList(int numElements, int sizeElements)
{
  (void)numElements; (void)sizeElements;
}

double PmergeMe::log2(double x)
{
  return std::log(x) / std::log(2.0);
}

int PmergeMe::calculateMaxComparisons(int n)
{
  int sum = 0;
  for (int k = 1; k <= n; ++k)
  {
    sum += std::ceil(log2((3.0 / 4.0) * k));
  }
  return sum;
}