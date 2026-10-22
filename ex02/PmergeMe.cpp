#include "PmergeMe.hpp"

#include <string>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <ctime>
#include <iostream>

////////// public //////////

PmergeMe::PmergeMe(int argc, char** argv)
  : numComparisons_(0)
{
  populate(argc, argv);
}

PmergeMe::~PmergeMe() {}

void PmergeMe::sort()
{
  startDeq_ = clock();
  fordJohnson(deq_, deq_.size(), 1);
  endDeq_ = clock();

  assert(isSorted(deq_.begin(), deq_.end()));
  assert(numComparisons_ <= maxComparisons_);

  numComparisons_ = 0;

  startVec_ = clock();
  fordJohnson(vec_, vec_.size(), 1);
  endVec_ = clock();

  assert(isSorted(vec_.begin(), vec_.end()));
  assert(numComparisons_ <= maxComparisons_);
}

void PmergeMe::printResult()
{
  std::cout << "Before: ";
  printContainer(origin_);
  std::cout << "\n\nAfter: ";
  printContainer(deq_);
  elapsedMicrosecondsDeq_ = (double)(endDeq_ - startDeq_) / CLOCKS_PER_SEC * 1000000.0;
  elapsedMicrosecondsVec_ = (double)(endVec_ - startVec_) / CLOCKS_PER_SEC * 1000000.0;
  std::cout << "\n\nTime to process a range of " << deq_.size() << " elements with std::deque : " << elapsedMicrosecondsDeq_ << " us\n";
  std::cout << "Time to process a range of " << vec_.size() << " elements with std::vector : " << elapsedMicrosecondsVec_ << " us\n";
}

////////// private //////////

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
    origin_.push_back(current);
    deq_.push_back(current);
    vec_.push_back(current);
    maxComparisons_ = calculateMaxComparisons(deq_.size());
  }
}

void PmergeMe::updateJacobsthal(int& currJacobsthal, int& prevJacobsthal) const
{
  int temp = currJacobsthal;
  currJacobsthal = 2 * prevJacobsthal + currJacobsthal;
  prevJacobsthal = temp;
}

int PmergeMe::getCurrElementIdx(const int currJacobsthal, const int numPendingElements) const
{
  return currJacobsthal - 2 > numPendingElements - 1 ? numPendingElements - 1 : currJacobsthal - 2;
}

///////////////// validation ////////////////////////

double PmergeMe::log2(const double x) const
{
  return std::log(x) / std::log(2.0);
}

int PmergeMe::calculateMaxComparisons(const int n) const
{
  int sum = 0;
  for (int k = 1; k <= n; ++k)
  {
    sum += std::ceil(log2((3.0 / 4.0) * k));
  }
  return sum;
}
