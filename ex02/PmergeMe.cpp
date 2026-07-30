
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
  // std::cout << "fordJohnsonList(): sizeElements: " << sizeElements << " numElements: " << numElements << '\n';
  if (numElements == 1)
  {
    return;
  }
  pairWiseSortList(numElements, sizeElements);
  fordJohnsonList(numElements / 2, sizeElements * 2);
  binaryInsertionList(numElements, sizeElements);
}

int PmergeMe::getSignificantIntList(std::list<int>::iterator element, int sizeElements)
{
  std::advance(element, sizeElements - 1);
  return *element;
}

void PmergeMe::pairWiseSortList(int numElements, int sizeElements)
{
  std::cout << "list before pair wise sorting: ";
  printList(list_, sizeElements, numElements);
  std::cout << '\n';

  std::list<int>::iterator left = list_.begin();
  std::list<int>::iterator right = list_.begin();
  std::advance(right, sizeElements);

  for (int i = 0; i < numElements / 2; ++i)
  {
    std::list<int>::iterator newLeft = left;
    std::advance(newLeft, sizeElements * 2);
    std::list<int>::iterator newRight = right;
    std::advance(newRight, sizeElements * 2);

    ++numComparisons_;
    if (getSignificantIntList(left, sizeElements) > getSignificantIntList(right, sizeElements))
    {
      std::list<int>::iterator endRight = right;
      std::advance(endRight, sizeElements);
      list_.splice(left, list_, right, endRight);
    }

    std::cout << "*left: " << *left << '\n';
    std::cout << "*right: " << *right << '\n';
    left = newLeft;
    right = newRight;
  }

  std::cout << "list after pair wise sorting: ";
  printList(list_, sizeElements, numElements);
  std::cout << '\n';
}

void PmergeMe::binaryInsertionList(int numElements, int sizeElements)
{
  std::list<int> mainChain;
  std::list<int> bChain;

  std::cout << "list_: "; printList(list_, sizeElements, numElements); std::cout << '\n';

  for (int i = 0; i < numElements; ++ i)
  {
    std::list<int>::iterator endElement = list_.begin();
    std::advance(endElement, sizeElements);
    if (i % 2 == 0)
    {
      bChain.splice(bChain.end(), list_, list_.begin(), endElement);
    }
    else
    {
      mainChain.splice(mainChain.end(), list_, list_.begin(), endElement);
    }
  }


  std::cout << "mainChain: "; printList(mainChain, sizeElements, numElements); std::cout << '\n';
  std::cout << "bChain: "; printList(bChain, sizeElements, numElements); std::cout << '\n';

}





///////////////// debugging and validation ////////////////////////

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

void PmergeMe::printList(std::list<int> currList, int sizeElements, int numElements)
{
  int elementMember = 1;
  int num = 1;
  for (std::list<int>::iterator it = currList.begin(); it != currList.end(); ++it)
  {
    if (elementMember == 1)
    {
      std::cout << '[';
    }
    std::cout << *it;
    if (elementMember == sizeElements)
    {
      std::cout << ']';
    }
    std::cout << ' ';
    
    if (elementMember == sizeElements)
    {
      if (num == numElements)
      {
        break;
      }
      ++num;
      elementMember = 1;
    }
    else
    {
      ++elementMember;
    }
  }
}