
#include <iostream>

#include "PmergeMe.hpp"

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    std::cerr << "Error: missing parameters\n";
    return 1;
  }

  PmergeMe pmergeMe;

  if (!pmergeMe.populate(argc, argv))
  {
    return 1;
  }

  // pmergeMe.FordJohnsonList();

  // pmergeMe.FordJohnsonDeque();

  return 0;
}