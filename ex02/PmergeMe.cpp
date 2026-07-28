
#include "PmergeMe.hpp"

#include <string>
#include <sstream>
#include <stdexcept>

#include <iostream>

PmergeMe::PmergeMe(int argc, char** argv)
{
  populate(argc, argv);
}

PmergeMe::~PmergeMe() {}


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
}

void PmergeMe::fordJohnsonDeque()
{

}

void PmergeMe::pairWiseSortDeque()
{

}

void PmergeMe::binaryInsertionDeque()
{

}

void PmergeMe::fordJohnsonList()
{

}

void PmergeMe::pairWiseSortList()
{

}

void PmergeMe::binaryInsertionList()
{

}
