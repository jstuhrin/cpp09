
#include "PmergeMe.hpp"

#include <string>
#include <sstream>

#include <iostream>

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}


bool PmergeMe::populate(int argc, char** argv)
{
  std::istringstream iss;
  for (int i = 1; i < argc; ++i)
  {
    int current = 0;
    iss.str(std::string(argv[i]));
    iss >> current;
    if (iss.fail() || !iss.eof() || current < 0)
    {
      std::cerr << "Error: invalid input: " << argv[i] << '\n';
      return false;
    }
    list_.push_back(current);
    deq_.push_back(current);
    iss.clear();
  }
  return true;
}